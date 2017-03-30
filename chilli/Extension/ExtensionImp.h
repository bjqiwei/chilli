#pragma once
#include "..\model\extension.h"
#include <log4cplus\logger.h>


namespace chilli{
	namespace Extension {

		class ExtensionImp :public model::Extension {
		public:
			ExtensionImp(const std::string &ext, const std::string &smFileName);
			virtual ~ExtensionImp();

			virtual const std::string & getExtensionNumber() const override;
			virtual void setSessionId(const std::string & sessinId) override;
			virtual const std::string & getSessionId() override;

			virtual int pushEvent(const model::EventType_t &evt) override;

			//inherit from SendInterface
			virtual void fireSend(const std::string &strContent, const void * param) override;

			//media interface
			virtual int Answer() override;
			virtual int PlayFile(const std::string &fileName) override;
			virtual int HangUp() override;

		protected:
			void processSend(const std::string &strContent, const void * param, bool & bHandled);

			std::string m_ExtNumber;
			std::string m_SessionId;

		};
		typedef std::shared_ptr<ExtensionImp>  ExtensionImpPtr;
	}
}