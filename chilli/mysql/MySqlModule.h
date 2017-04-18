#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <atomic>

namespace chilli{
namespace DataBase{

class MySqlModule :public model::ProcessModule
{
public:
	explicit MySqlModule(const std::string & id);
	virtual ~MySqlModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual const model::ExtensionMap & GetExtension() override;
	Json::Value executeQuery(const std::string & sql);
private:
	//inherit from SendInterface
	virtual void fireSend(const std::string &strContent, const void * param) override;
private:
	log4cplus::Logger log;
	std::atomic_bool m_bRunning = false;
	model::ExtensionMap m_Extensions;
	std::thread m_thread;
	helper::CEventBuffer<chilli::model::SQLEventType_t> m_SqlBuffer;
	std::string m_Host;
	std::string m_UserID;
	std::string m_Password;
	std::string m_DataBase;
	void executeSql();
};
}
}

