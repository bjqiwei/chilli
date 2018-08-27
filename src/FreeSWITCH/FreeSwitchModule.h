#pragma once
#include <log4cplus/logger.h>
#include "../model/ProcessModule.h"
#include <esl.h>
#include <thread>

namespace chilli{
namespace FreeSwitch{

	class FreeSwitchModule :public model::ProcessModule
	{
	public:
		explicit FreeSwitchModule(const std::string & id, uint32_t threadSize = 16);
		virtual ~FreeSwitchModule(void);
		virtual int Start() override;
		virtual int Stop() override;
		virtual bool LoadConfig(const std::string & config) override;
	protected:
		//inherit from SendInterface
		virtual void fireSend(const std::string &strContent, const void * param) override;
		void processSend(Json::Value &jsonData, const void * param, bool & bHandled, log4cplus::Logger & log);
		bool MakeCall(Json::Value & param, log4cplus::Logger & log);
		bool MakeConnection(Json::Value & param, log4cplus::Logger & log);
		bool ClearConnection(Json::Value & param, log4cplus::Logger & log);
		bool StartRecord(Json::Value & param, log4cplus::Logger & log);
		bool Divert(Json::Value &param, log4cplus::Logger & log);
		bool PlayFile(Json::Value & param, log4cplus::Logger & log);


		std::string dialStringFindNumber(const std::string & dialString);
		std::string toDialString(const std::string & sipId, const std::string & uuid, const std::string & caller);
	private:
		std::thread m_Thread;
		std::string m_Host;
		int m_Port = 0;
		std::string m_User;
		std::string m_Password;
		esl_handle_t m_Handle = { { 0 } };
		void ConnectFS();
		typedef std::string TsessionID;
		std::mutex m_sessionMtx;
		std::map<std::string, std::string>m_Session_DeviceId;
		void setSessionDevice(const TsessionID & sessionId, const std::string & device);
		bool getSessionDevice(const TsessionID & sessionId, std::string & device);
		void removeSessionDevice(const TsessionID &sessionId);

		typedef std::string TJobID;
		std::map<std::string, std::string>m_Job_Session;
		void setJobSession(const TJobID & job, const TsessionID & sessionId);
		bool getJobSession(const TJobID & job, TsessionID & sessionId);
		void removeJobSession(const TJobID & job);

		std::map<std::string, std::string>m_device_StateMachine;
		virtual void run() override;
		virtual void execute(helper::CEventBuffer<model::EventType_t> * eventQueue) override;
		Json::Value routeConfig;
		friend class FreeSwitchDevice;
	};

}
}
