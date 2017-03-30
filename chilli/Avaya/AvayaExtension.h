#pragma once
#include "..\Extension\ExtensionImp.h"
#include <log4cplus\logger.h>


namespace chilli{
	namespace Avaya {

		class TSAPIModule;
		class AvayaExtension :public Extension::ExtensionImp {
		public:
			AvayaExtension(TSAPIModule * model, const std::string &ext, const std::string &smFileName);
			virtual ~AvayaExtension();

			//inherit from SendInterface
			virtual void fireSend(const std::string &strContent, const void * param) override;

		protected:
			void processSend(const std::string &strContent, const void * param, bool & bHandled);
		private:
			TSAPIModule * m_model;

		};
		typedef std::shared_ptr<AvayaExtension>  AvayaExtensionImpPtr;
	}
}