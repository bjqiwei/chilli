#pragma  once
#ifndef _CHILLI_IVRMODULE_HEADER_
#define _CHILLI_IVRMODULE_HEADER_
#include <FSM.h>
#include "IVRExtension.h"
#include "../CEventBuffer.h"
#include "../model/ProcessModule.h"


namespace chilli{
namespace IVR
{
	class IVRModule:public abstract::ProcessModule
	{
	public:
		IVRModule(void);
		virtual ~IVRModule(void);
		virtual bool Init(xmlNodePtr xNodePtr);
		virtual bool reloadConfig(xmlNodePtr xNode);
		virtual bool Init(void);
		virtual	void Start();
		virtual int Close(void);
		int EvtHandler(std::string strEvent);
		void	DisplayEventInfo ( std::string strEvent );

		virtual bool ParserConfig(void);
		static const std::vector<IVR::IVRExtensionPtr> & getExtVec();
		static void addEventToBuffer(std::string strContent);
		friend class IVRExtension;

	private:
		static std::vector<IVRExtensionPtr> m_ExtensionVector;
		static helper::CEventBuffer<std::string> recEvtBuffer;
		IVRModule(const IVRModule & other);
		IVRModule & operator=(const IVRModule &);
		static unsigned int __stdcall ThreadProc( void *pParam );
		static fsm::SMInstance smInstance;
		abstract::thread_data td;
	};

}
}
#endif // end ivr header

