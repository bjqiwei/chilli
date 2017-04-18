#include "MySqlModule.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <sstream>


namespace chilli{
namespace DataBase{


MySqlModule::MySqlModule(const std::string & id) :ProcessModule(id)
{
	log =log4cplus::Logger::getInstance("chilli.MySqlModule");
	LOG4CPLUS_DEBUG(log, "Constuction a module.");
}


MySqlModule::~MySqlModule(void)
{
	if (m_bRunning){
		Stop();
	}

	for (auto & it : m_Extensions) {
		g_Extensions.erase(it.first);
	}

	LOG4CPLUS_DEBUG(log, "Destruction a module.");
}

int MySqlModule::Stop(void)
{
	LOG4CPLUS_DEBUG(log,"Stop module");
	if (m_bRunning) {
		m_bRunning = false;
		for (auto & it : m_Extensions) {
			it.second->Stop();
		}

		chilli::model::SQLEventType_t stopEvent("");
		m_SqlBuffer.Put(stopEvent);
		if (m_thread.joinable())
			m_thread.join();

	}
	return 0;
}

int MySqlModule::Start()
{
	LOG4CPLUS_DEBUG(log, "Start module");
	if (!m_bRunning){
		m_bRunning = true;
		for (auto & it : m_Extensions) {
			it.second->Start();
		}
		m_thread = std::thread(&MySqlModule::executeSql, this);
	}
	return 0;
}

bool MySqlModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS){
		LOG4CPLUS_ERROR(log, "load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
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

const model::ExtensionMap & MySqlModule::GetExtension()
{
	return m_Extensions;
}

Json::Value MySqlModule::executeQuery(const std::string & sql)
{
	sql::mysql::MySQL_Driver driver;
	std::shared_ptr<sql::Connection> connect;
	Json::Value result;

	try {
		connect.reset(driver.connect(m_Host, m_UserID, m_Password));

		/* select appropriate database schema */
		if (!m_DataBase.empty()) {
			connect->setSchema(m_DataBase);
		}
		if (sql.empty())
			return Json::Value();

		/* create a statement object */
		std::auto_ptr<sql::Statement> stmt(connect->createStatement());
		std::auto_ptr<sql::ResultSet> resultset(stmt->executeQuery(sql));
		
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
				default:
					record[res_meta->getColumnLabel(i).asStdString()] = resultset->getString(i).asStdString();
				}

			}
			data.append(record);
		} // while  
		result = data;
		
	}
	catch (sql::SQLException &e) {
		std::ostringstream oss;
		oss << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
		LOG4CPLUS_DEBUG(log, oss.str());

	}
	catch (std::runtime_error &e) {
		LOG4CPLUS_ERROR(log, "ERROR: " << e.what());
	}

	if (connect && !connect->isClosed())
		connect->close();

	return result;
}

void MySqlModule::fireSend(const std::string &strContent, const void * param)
{
	LOG4CPLUS_DEBUG(log, "fireSend:" << strContent);
	Json::Value jsonEvent;
	Json::Reader jsonReader;
	if (!jsonReader.parse(strContent, jsonEvent)) {
		LOG4CPLUS_ERROR(log, strContent << " not json data.");
		return;
	}

	std::string eventName;
	std::string typeName;
	std::string dest;
	std::string from;

	if (jsonEvent["type"].isString()) {
		typeName = jsonEvent["type"].asString();
	}

	if (typeName != "cmd") {
		return;
	}

	if (jsonEvent["dest"].isString()) {
		dest = jsonEvent["dest"].asString();
	}

	if (jsonEvent["event"].isString()) {
		eventName = jsonEvent["event"].asString();
	}

	if (jsonEvent["event"].isString()) {
		eventName = jsonEvent["event"].asString();
	}

	if (jsonEvent["from"].isString()) {
		from = jsonEvent["from"].asString();
	}

	std::string sql;

	if (jsonEvent["param"]["sql"].isString())
		sql = jsonEvent["param"]["sql"].asString();

	chilli::model::SQLEventType_t event(sql, from);
	m_SqlBuffer.Put(event);

}

static std::string  MetadataInfo(sql::DatabaseMetaData *dbcon_meta)
{
	std::ostringstream oss;

	oss << "Database Metadata" << boolalpha << endl;

	oss << "Database Product Name: " << dbcon_meta->getDatabaseProductName() << endl;
	oss << "Database Product Version: " << dbcon_meta->getDatabaseProductVersion() << endl;
	oss << "Database User Name: " << dbcon_meta->getUserName() << endl << endl;

	oss << "Driver name: " << dbcon_meta->getDriverName() << endl;
	oss << "Driver version: " << dbcon_meta->getDriverVersion() << endl << endl;

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
		oss << row << ". " << rs->getString("TABLE_SCHEM") << endl;
		++row;
	} // while 

	return oss.str();
}

void MySqlModule::executeSql()
{
	LOG4CPLUS_INFO(log, "Starting...");
	while (m_bRunning)
	{
		sql::mysql::MySQL_Driver driver;
		std::shared_ptr<sql::Connection> connect;

		try {
			connect.reset(driver.connect(m_Host, m_UserID, m_Password));
			//connect->setAutoCommit(0);
			LOG4CPLUS_DEBUG(log, "Database connection  autocommit mode = " << connect->getAutoCommit());

			/* select appropriate database schema */
			if (!m_DataBase.empty()) {
				connect->setSchema(m_DataBase);
			}

			LOG4CPLUS_DEBUG(log, MetadataInfo(connect->getMetaData()));

			model::SQLEventType_t Event;
			while (m_SqlBuffer.Get(Event) && !Event.m_sql.empty())
			{
				if (Event.m_sql.empty())
					break;

				Json::Value result;
				result["status"] = 0;
				result["msg"] = "success";

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
					std::ostringstream oss;
					oss << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
					LOG4CPLUS_DEBUG(log, oss.str());

					if (connect->isClosed()) {
						m_SqlBuffer.Put(Event);
						break;
					}
					else {
						result["status"] = e.getErrorCode();
						result["msg"] = e.what();
					}
				}

				result["extension"] = Event.m_ExtNumber;
				result["event"] = "SQL";

				chilli::model::EventType_t resultEvent(result);
				this->PushEvent(resultEvent);
			}
		}
		catch (sql::SQLException &e) {
			std::ostringstream oss;
			oss << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
			LOG4CPLUS_DEBUG(log, oss.str());

			if (connect && connect->isClosed()){
				continue;
			}

		}
		catch (std::runtime_error &e) {
			LOG4CPLUS_ERROR(log, "ERROR: " << e.what());
			if (connect && connect->isClosed()) {
				continue;
			}
		}
		
		if (connect && !connect->isClosed())
			connect->close();

	}
	LOG4CPLUS_INFO(log, "Stoped.");
	log4cplus::threadCleanup();
}
}
}
