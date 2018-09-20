#include "MySqlModule.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/config.h>
#include <json/json.h>
#if (defined(_WIN32) || defined(_WIN64))
#include <WinSock2.h>
#include <mysql.h>
#include <errmsg.h>
#else
#include <mysql/mysql.h>
#include <mysql/errmsg.h>
#endif


namespace chilli{
namespace DataBase {


	MySqlModule::MySqlModule(const std::string & id, uint32_t threadSize) :ProcessModule(id, threadSize)
	{
		log = log4cplus::Logger::getInstance("chilli.MySqlModule");
		LOG4CPLUS_DEBUG(log, "." + this->getId(), " Constuction a module.");
	}


	MySqlModule::~MySqlModule(void)
	{
		if (m_bRunning) {
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
		if (!m_bRunning) {
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
		if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS) {
			LOG4CPLUS_ERROR(log, "." + this->getId(), " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
			return false;
		}
		XMLElement * mysql = config.FirstChildElement("MySql");
		const char * host = mysql->Attribute("Host");
		const char * port = mysql->Attribute("Port");
		const char * userId = mysql->Attribute("UserID");
		const char * password = mysql->Attribute("Password");
		const char * db = mysql->Attribute("DataBase");
		m_Host = host ? host : std::string();
		if (port) {
			try{
			m_Port = std::stoul(port);
			}
			catch (...)
			{
			}
		}
		
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
		MYSQL mysql;
		mysql.options.connect_timeout = 1000*1000;
		MYSQL_RES *res = nullptr;       //查询结果集，结构类型
		MYSQL_FIELD *fd = nullptr;     //包含字段信息的结构
		MYSQL_ROW row = nullptr;       //存放一行查询结果的字符串数组
		mysql_init(&mysql);

		Json::Value result;

		if (mysql_real_connect(&mysql, m_Host.c_str(), m_UserID.c_str(), m_Password.c_str(), m_DataBase.c_str(), m_Port, nullptr, 0) == nullptr)
		{
			LOG4CPLUS_ERROR(log, "." + this->getId(), "ERROR: " << mysql_error(&mysql) << " (MySQL error code: " << mysql_errno(&mysql) << ", SQLState: " << mysql_sqlstate(&mysql) << ")");
			return result;
		}



		if (mysql_query(&mysql, sql.c_str())) {
			LOG4CPLUS_ERROR(log, "." + this->getId(), "ERROR: " << mysql_error(&mysql) << " (MySQL error code: " << mysql_errno(&mysql) << ", SQLState: " << mysql_sqlstate(&mysql) << ")");
			return result;
		}

		if ((res = mysql_store_result(&mysql)) == nullptr) {
			LOG4CPLUS_ERROR(log, "." + this->getId(), "ERROR: " << mysql_error(&mysql) << " (MySQL error code: " << mysql_errno(&mysql) << ", SQLState: " << mysql_sqlstate(&mysql) << ")");
			return result;
		}

		uint32_t num_fields = mysql_num_fields(res);
		MYSQL_FIELD *fields = nullptr;
		fields = mysql_fetch_fields(res);

		while ((row = mysql_fetch_row(res)))
		{
			unsigned long *lengths;
			lengths = mysql_fetch_lengths(res);
			Json::Value jrow;
			for (uint32_t i = 0; i < num_fields; i++)
			{
				if (row[i])
					jrow[fields[i].name] = row[i];
				else
					jrow[fields[i].name] = Json::nullValue;
			}
			result.append(jrow);
		}


		mysql_free_result(res);
		mysql_close(&mysql);

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
		LOG4CPLUS_INFO(log, "." + this->getId(), " sql:" << event.m_sql);
		m_SqlBuffer.Put(event);

	}


	void MySqlModule::executeSql()
	{
		LOG4CPLUS_INFO(log, "." + this->getId(), " Starting...");
		while (m_bRunning)
		{
			MYSQL mysql;
			mysql.options.connect_timeout = 1000*1000;
			MYSQL_RES *res = nullptr;       //查询结果集，结构类型
			MYSQL_FIELD *fd = nullptr;     //包含字段信息的结构
			MYSQL_ROW row = nullptr;       //存放一行查询结果的字符串数组
			mysql_init(&mysql);

			Json::Value result;

			if (mysql_real_connect(&mysql, m_Host.c_str(), m_UserID.c_str(), m_Password.c_str(), m_DataBase.c_str(), m_Port, nullptr, 0) == nullptr)
			{
				LOG4CPLUS_ERROR(log, "." + this->getId(), "ERROR: " << mysql_error(&mysql) << " (MySQL error code: " << mysql_errno(&mysql) << ", SQLState: " << mysql_sqlstate(&mysql) << ")");
				std::this_thread::sleep_for(std::chrono::seconds(1));
				continue;
			}

			LOG4CPLUS_DEBUG(log, "." + this->getId(), mysql_get_server_info(&mysql));

			model::SQLEventType_t Event;
			while (m_SqlBuffer.Get(Event) && !Event.m_sql.empty())
			{
				LOG4CPLUS_DEBUG(log, "." + this->getId(), Event.m_ExtNumber << " executeSql:" << Event.m_sql);
				if (Event.m_sql.empty())
					break;

				Json::Value result;
				result["cause"] = 0;
				result["reason"] = "success";



				if (mysql_query(&mysql, Event.m_sql.c_str()) || (res = mysql_store_result(&mysql)) == nullptr) {
					LOG4CPLUS_ERROR(log, "." + this->getId(), "ERROR: " << mysql_error(&mysql) << " (MySQL error code: " << mysql_errno(&mysql) << ", SQLState: " << mysql_sqlstate(&mysql) << ")");
					if (Event.m_times++ < 5) {
						m_SqlBuffer.Put(Event);
						break;
					}
					else if (mysql_errno(&mysql) == CR_SERVER_LOST) {
						m_SqlBuffer.Put(Event);
						break;
					}
					else if (mysql_errno(&mysql) == CR_OUT_OF_MEMORY) {
						m_SqlBuffer.Put(Event);
						abort(); //内存溢出
					}
					else {
						result["cause"] = mysql_errno(&mysql);
						result["reason"] = mysql_error(&mysql);
					}
					continue;
				}

				Json::Value data;

				uint32_t num_fields = mysql_num_fields(res);
				MYSQL_FIELD *fields = nullptr;
				fields = mysql_fetch_fields(res);

				while ((row = mysql_fetch_row(res)))
				{
					unsigned long *lengths;
					lengths = mysql_fetch_lengths(res);
					Json::Value jrow;
					for (uint32_t i = 0; i < num_fields; i++)
					{
						if (row[i])
							jrow[fields[i].name] = row[i];
						else
							jrow[fields[i].name] = Json::nullValue;
					}
					data.append(jrow);
				}


				result["UpdateCount"] = (uint32_t)res->row_count;

				mysql_free_result(res);

				result["data"] = data;

				result["id"] = Event.m_ExtNumber;
				result["ConnectionID"] = Event.m_ConnectionID;
				result["event"] = "SQL";
				result["type"] = "result";

				chilli::model::EventType_t resultEvent(new model::_EventType(result));
				this->PushEvent(resultEvent);
			}

		}


		LOG4CPLUS_INFO(log, "." + this->getId(), " Stoped.");
		log4cplus::threadCleanup();
	}
}
}
