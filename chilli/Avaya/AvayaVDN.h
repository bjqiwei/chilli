#pragma once
#include "..\model\Extension.h"
#include <log4cplus\logger.h>


namespace chilli{
	namespace Avaya {

		class TSAPIModule;
		class AvayaVDN :public model::Extension {
		public:
			AvayaVDN(TSAPIModule * model, const std::string &ext, const std::string &smFileName);
			virtual ~AvayaVDN();

			virtual void Start() override;
			virtual void Stop() override;
			virtual bool IsFinalState() override;
			virtual bool setVar(const std::string &name, const Json::Value &value) override;

			virtual int pushEvent(const model::EventType_t &evt) override;
			virtual void mainEventLoop() override;

			//inherit from SendInterface
			virtual void fireSend(const std::string &strContent, const void * param) override;

			//media interface
			virtual int Answer() override;
			virtual int PlayFile(const std::string &fileName) override;
			virtual int HangUp() override;

		private:
			TSAPIModule * m_model;
			std::map<std::string, bool>m_ACDExts;
			std::map<uint32_t, std::string>m_callid2Extenion;
		};
		typedef std::shared_ptr<AvayaVDN>  AvayaVDNPtr;
	}
}