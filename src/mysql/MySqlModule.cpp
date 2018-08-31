#include "MySqlModule.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/config.h>
#include <json/json.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <sstream>


namespace chilli{
namespace DataBase{


MySqlModule::MySqlModule(const std::string & id, uint32_t threadSize) :ProcessModule(id, threadSize)
{
	log =log4cplus::Logger::getInstance("chilli.MySqlModule");
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Constuction a module.");
}


MySqlModule::~MySqlModule(void)
{
	if (m_bRunning){
		Stop();
	}

	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Destruction a module.");
}

int MySqlModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Stop module");
	if (m_bRunning) {
		ProcessModule::Stop();
		m_bRunning = false;

		chilli::model::SQLEventType_t stopEvent("");
		m_SqlBuffer.Put(stopEvent);
		if (m_thread.joinable())
			m_thread.join();

	}
	return 0;
}

int MySqlModule::Start()
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Start module");
	if (!m_bRunning){
		ProcessModule::Start();
		m_bRunning = true;
		m_thread = std::thread(&MySqlModule::executeSql, this);
	}
	return 0;
}

bool MySqlModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS){
		LOG4CPLUS_ERROR(log, "." + this->getId(), " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	XMLElement * mysql = config.FirstChildElement("MySql");
	const char * host = mysql->Attribute("Host");
	const char * userId = mysql->Attribute("UserID");
	const char * password = mysql->Attribute("Password");
	const char * db = mysql->Attribute("DataBase");
	m_Host = host ? host : std::string();
	m_UserID = userId ? userId : std::string();
	m_Password = password ? password : std::string();
	m_DataBase = db ? db : std::string();
	return true;
}

void MySqlModule::run()
{

}

void MySqlModule::execute(helper::CEventBuffer<model::EventType_t>* eventQueue)
{
	fsm::threadIdle();
	fsm::threadCleanup();
	log4cplus::threadCleanup();
}

Json::Value MySqlModule::executeQuery(const std::string & sql)
{
	sql::Driver * driver = get_driver_instance();
	std::shared_ptr<sql::Connection> connect;
	Json::Value result;

	try {
		connect.reset(driver->connect(m_Host.c_str(), m_UserID.c_str(), m_Password.c_str()));

		/* select appropriate database schema */
		if (!m_DataBase.empty()) {
			connect->setSchema(m_DataBase.c_str());
		}
		if (sql.empty())
			return Json::Value();

		/* create a statement object */
		std::auto_ptr<sql::Statement> stmt(connect->createStatement());
		std::auto_ptr<sql::ResultSet> resultset(stmt->executeQuery(sql.c_str()));
		
		Json::Value data;

		/*The following commented statement won't work with Connector/C++ 1.0.5 and later */
		//auto_ptr < ResultSetMetaData > res_meta ( rs -> getMetaData() );  
		sql::ResultSetMetaData *res_meta = resultset->getMetaData();

		int numcols = res_meta->getColumnCount();

		while (resultset->next())
		{
			Json::Value record;

			for (int i = 1; i <= numcols; ++i) {
				switch (res_meta->getColumnType(i)) {
				case sql::DataType::INTEGER:
					record[res_meta->getColumnLabel(i).c_str()] = resultset->getUInt64(i); break;
				case sql::DataType::BIGINT:
					record[res_meta->getColumnLabel(i).c_str()] = resultset->getUInt64(i); break;
				case sql::DataType::SMALLINT:
					record[res_meta->getColumnLabel(i).c_str()] = resultset->getUInt(i); break;
				default:
					record[res_meta->getColumnLabel(i).c_str()] = resultset->getString(i).c_str();
				}

			}
			data.append(record);
		} // while  
		result = data;
		
	}
	catch (sql::SQLException &e) {
		std::ostringstream oss;
		oss << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLStateCStr() << ")";
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " " <<oss.str());

	}
	catch (std::runtime_error &e) {
		LOG4CPLUS_ERROR(log, "." + this->getId(), " ERROR: " << e.what());
	}

	if (connect && !connect->isClosed())
		connect->close();

	return result;
}

void MySqlModule::fireSend(const fsm::FireDataType & fireData, const void * param)
{
	LOG4CPLUS_TRACE(log, "." + this->getId(), " fireSend:" << fireData.event);

	const std::string & eventName = fireData.event;
	const std::string & typeName = fireData.type;
	const std::string & dest = fireData.dest;
	const std::string & from = fireData.from;


	if (typeName != "cmd") {
		return;
	}

	std::string sql;
	std::string conctionId;

	if (fireData.param["sql"].isString())
		sql = fireData.param["sql"].asString();

	if (fireData.param["ConnectionID"].isString()) {
		conctionId = fireData.param["ConnectionID"].asString();
	}



	chilli::model::SQLEventType_t event(sql, from);
	event.m_ConnectionID = conctionId;
	LOG4CPLUS_INFO(log, "." + this->getId(), " sql:"  << event.m_sql);
	m_SqlBuffer.Put(event);

}

static std::string  MetadataInfo(sql::DatabaseMetaData *dbcon_meta)
{
	std::ostringstream oss;

	oss << "Database Metadata" << boolalpha << endl;

	oss << "Database Product Name: " << dbcon_meta->getDatabaseProductName().c_str() << endl;
	oss << "Database Product Version: " << dbcon_meta->getDatabaseProductVersion().c_str() << endl;
	oss << "Database User Name: " << dbcon_meta->getUserName().c_str() << endl << endl;

	oss << "Driver name: " << dbcon_meta->getDriverName().c_str() << endl;
	oss << "Driver version: " << dbcon_meta->getDriverVersion().c_str() << endl << endl;

	oss << "Database in Read-Only Mode?: " << dbcon_meta->isReadOnly() << endl;
	oss << "Supports Transactions?: " << dbcon_meta->supportsTransactions() << endl;
	oss << "Supports DML Transactions only?: " << dbcon_meta->supportsDataManipulationTransactionsOnly() << endl;
	oss << "Supports Batch Updates?: " << dbcon_meta->supportsBatchUpdates() << endl;
	oss << "Supports Outer Joins?: " << dbcon_meta->supportsOuterJoins() << endl;
	oss << "Supports Multiple Transactions?: " << dbcon_meta->supportsMultipleTransactions() << endl;
	oss << "Supports Named Parameters?: " << dbcon_meta->supportsNamedParameters() << endl;
	oss << "Supports Statement Pooling?: " << dbcon_meta->supportsStatementPooling() << endl;
	oss << "Supports Stored Procedures?: " << dbcon_meta->supportsStoredProcedures() << endl;
	oss << "Supports Union?: " << dbcon_meta->supportsUnion() << endl << endl;

	oss << "Maximum Connections: " << dbcon_meta->getMaxConnections() << endl;
	oss << "Maximum Columns per Table: " << dbcon_meta->getMaxColumnsInTable() << endl;
	oss << "Maximum Columns per Index: " << dbcon_meta->getMaxColumnsInIndex() << endl;
	oss << "Maximum Row Size per Table: " << dbcon_meta->getMaxRowSize() << " bytes" << endl;

	oss << "Database schemas: " << endl;

	std::auto_ptr<sql::ResultSet> rs(dbcon_meta->getSchemas());

	oss << "Total number of schemas = " << rs->rowsCount() << endl;
	oss << endl;

	int row = 1;

	while (rs->next()) {
		oss << row << ". " << rs->getString("TABLE_SCHEM").c_str() << endl;
		++row;
	} // while 

	return oss.str();
}

void MySqlModule::executeSql()
{
	LOG4CPLUS_INFO(log, "." + this->getId(), " Starting...");
	while (m_bRunning)
	{
		sql::Driver *driver = get_driver_instance();
		std::shared_ptr<sql::Connection> connect;

		try {
			connect.reset(driver->connect(m_Host.c_str(), m_UserID.c_str(), m_Password.c_str()));
			//connect->setAutoCommit(0);
			LOG4CPLUS_DEBUG(log, "." + this->getId(), " Database connection  autocommit mode = " << connect->getAutoCommit());

			/* select appropriate database schema */
			if (!m_DataBase.empty()) {
				connect->setSchema(m_DataBase.c_str());
			}

			LOG4CPLUS_DEBUG(log, "." + this->getId(), MetadataInfo(connect->getMetaData()));

			model::SQLEventType_t Event;
			while (m_SqlBuffer.Get(Event) && !Event.m_sql.empty())
			{
				LOG4CPLUS_DEBUG(log, "." + this->getId(), Event.m_ExtNumber << " executeSql:" << Event.m_sql);
				if (Event.m_sql.empty())
					break;

				Json::Value result;
				result["cause"] = 0;
				result["reason"] = "success";

				/* create a statement object */
				std::auto_ptr<sql::Statement> stmt(connect->createStatement());
				try
				{
					if (stmt->execute(Event.m_sql) == true) {
						/* retrieve and display the result set metadata */
						std::auto_ptr<sql::ResultSet> resultset(stmt->getResultSet());
						Json::Value data;

						/*The following commented statement won't work with Connector/C++ 1.0.5 and later */
						//auto_ptr < ResultSetMetaData > res_meta ( rs -> getMetaData() );  
						sql::ResultSetMetaData *res_meta = resultset->getMetaData();

						int numcols = res_meta->getColumnCount();

						while (resultset->next())
						{							
							Json::Value record;
							
							for (int i = 1; i <= numcols; ++i) {
								switch (res_meta->getColumnType(i)) {

								/*case sql::DataType::TINYINT:
								case sql::DataType::SMALLINT:
								case sql::DataType::MEDIUMINT:
								case sql::DataType::INTEGER:
								case sql::DataType::BIGINT:
									record[res_meta->getColumnLabel(i).asStdString()] = resultset->getUInt(i);
									break;
								case sql::DataType::TIMESTAMP:
								case sql::DataType::DATE:
								case sql::DataType::TIME:
								case sql::DataType::YEAR:
									record[res_meta->getColumnLabel(i).asStdString()] = resultset->getString(i).asStdString();
									break;
								case sql::DataType::REAL:
								case sql::DataType::DOUBLE:
								case sql::DataType::DECIMAL:
								case sql::DataType::NUMERIC:
									record[res_meta->getColumnLabel(i).asStdString()] = (double)resultset->getDouble(i);
									break;*/
								default:
									record[res_meta->getColumnLabel(i).asStdString()] = resultset->getString(i).asStdString();
								}

							}
							data.append(record);
						} // while  
						result["data"] = data;
					}
					else
					{
						result["UpdateCount"] = uint32_t(stmt->getUpdateCount());
					}
				}
				catch (sql::SQLException &e) {
					LOG4CPLUS_DEBUG(log, "." + this->getId(), "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")");
					
					if (Event.m_times++ < 5){
						m_SqlBuffer.Put(Event);
						break;
					}
					else if (connect->isClosed()) {
						m_SqlBuffer.Put(Event);
						break;
					}
					else {
						result["cause"] = e.getErrorCode();
						result["reason"] = e.what();
					}
				}

				result["id"] = Event.m_ExtNumber;
				result["ConnectionID"] = Event.m_ConnectionID;
				result["event"] = "SQL";
				result["type"] = "result";

				chilli::model::EventType_t resultEvent(new model::_EventType(result));
				this->PushEvent(resultEvent);
			}
		}
		catch (sql::SQLException &e) {
			LOG4CPLUS_DEBUG(log, "." + this->getId(), "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLStateCStr() << ")");
			std::this_thread::sleep_for(std::chrono::seconds(30));
			if (connect && connect->isClosed()){
				continue;
			}

		}
		catch (std::runtime_error &e) {
			LOG4CPLUS_ERROR(log, "." + this->getId(), " ERROR: " << e.what());
			std::this_thread::sleep_for(std::chrono::seconds(30));
			if (connect && connect->isClosed()) {
				continue;
			}
		}
		
		if (connect && !connect->isClosed())
			connect->close();

	}
	LOG4CPLUS_INFO(log, "." + this->getId(), " Stoped.");
	log4cplus::threadCleanup();
}
}
}
