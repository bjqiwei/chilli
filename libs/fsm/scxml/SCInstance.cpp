
#include "SCInstance.h"
#include "scxml/env/JSEvaluator.h"
#include <process.h>
#include <Windows.h>

namespace fsm
{

	
	SCInstance::SCInstance():evaluator(NULL),global_cls(NULL),addEventFunction(NULL)
	{
		log=log4cplus::Logger::getInstance("fsm.SCInstance");
		InitializeCriticalSection(&csection);
		timerTheradSemaphore = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
		if (NULL == timerTheradSemaphore){
			LOG4CPLUS_ERROR(log,"Structure SCInstance encountered an error,error=" << GetLastError());
		}
		StartTimerThread();
		LOG4CPLUS_INFO(log,"new fsm.SCInstance object.");
	}

	SCInstance::~SCInstance()
	{
		ReleaseSemaphore(timerTheradSemaphore, 1, NULL);
		
		for (std::map<xmlNodePtr,Context*>::const_iterator it = contexts.begin();
			it != contexts.end(); it++)
		{
			delete it->second;
		}
		contexts.clear();
		//if (rootContext) delete rootContext;
		if (evaluator) delete evaluator;
		CloseHandle(td.thread_hnd);
		DeleteCriticalSection(&csection);
		LOG4CPLUS_INFO(log,"destruction fsm.SCInstance object.");
	}
	Evaluator *SCInstance::getEvaluator()const
	{
		if (evaluator == NULL)
		{
			try
			{
				evaluator = new env::JSEvaluator();
			}
			
			catch (...)
			{
				throw;
			}
		}
		return evaluator;
	}

	//void SCInstance::setEvaluator(Evaluator *const evaluator)
	//{
	//	if (evaluator) delete evaluator;
	//	this->evaluator = evaluator;
	//}

	Context *SCInstance::getRootContext(log4cplus::Logger log)const
	{
		if (getEvaluator() != 0)
		{
			if (contexts[0] == 0)
			{
				contexts[0] = getEvaluator()->newContext(NULL,log);
			}
			return contexts[0];
		}
		return NULL;
	}

	//void SCInstance::setRootContext(Context *const context)
	//{
	//	if (rootContext) delete rootContext;
	//
	//	this->rootContext = context;
	//}

	Context *SCInstance::getContext(xmlNodePtr xNode,log4cplus::Logger log)const
	{
		Context *context =NULL ; 
		if (contexts.count(xNode) > 0)
		{
			context=contexts[xNode];
		}
		if (context == NULL)
		{
			xmlNodePtr parent = xNode->parent;

			if (parent == 0 || parent->type == XML_DOCUMENT_NODE)
			{// docroot
				context = getEvaluator()->newContext(getRootContext(this->log),log);
			}
			else
			{
				context = getEvaluator()->newContext(getContext(parent,log),log);
			}
			contexts[xNode] = context;
		}
		return context;
	}
	void SCInstance::removeContext(xmlNodePtr xNode)
	{
		if (contexts.count(xNode) > 0 && contexts[xNode] != NULL)
		{
			delete contexts[xNode];
		}
		contexts.erase(contexts.find(xNode));
	}
	Context *SCInstance::lookupContext(xmlNodePtr xNode)
	{
		if (contexts.count(xNode) > 0)
		{
			return contexts[xNode];
		}
		return NULL;
	}

	void SCInstance::setContext(xmlNodePtr xNode, Context *const context)
	{
		if (contexts[xNode] != NULL)
		{
			delete contexts[xNode];
		}
		contexts[xNode] = context;
	}



	void SCInstance::setLog(log4cplus::Logger log)
	{
		this->log = log;
	}
	
	unsigned int SCInstance::TimerThreadProc( void *pParam )
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("fsm.SCInstance.TimerThreadProc");
		SCInstance * scInstance = (SCInstance *)pParam;
		HANDLE semaphore = scInstance->timerTheradSemaphore;
		DWORD rv;
		while(1)
		{
			rv = WaitForSingleObject(semaphore,10);
			switch (rv) {
			case WAIT_OBJECT_0:{
					CloseHandle(semaphore);
					LOG4CPLUS_WARN(log,"exit timer thread.");
					_endthreadex(0);
					return 0;
				}
				break;
			case WAIT_TIMEOUT:
				EnterCriticalSection(&scInstance->csection);
				for (std::list<Timer>::iterator iter =scInstance->m_timer.begin();iter != scInstance->m_timer.end(); iter++)
				{
					if (iter->valid == false)
					{
						iter = scInstance->m_timer.erase(iter);
						break;
					}
				}
			
				for (std::list<Timer>::iterator iter =scInstance->m_timer.begin();iter != scInstance->m_timer.end(); iter++)
				{
					std::string strContent = iter->Step();
		
					if (scInstance->addEventFunction != NULL && !SCXMLHelper::isStringEmpty(strContent))
					{
						scInstance->addEventFunction(strContent);
					}else if (scInstance->addEventFunction == NULL && !SCXMLHelper::isStringEmpty(strContent))
					{
						LOG4CPLUS_ERROR(log,"timer event callback function is empty. event=" << strContent);
					}
				}
				LeaveCriticalSection(&scInstance->csection);
				break;
			case WAIT_FAILED:
				LOG4CPLUS_ERROR(log,"WaitForSingleObject, wait failed.error=" << GetLastError());
				break;
			default:
				LOG4CPLUS_WARN(log,"WaitForSingleObject, unknow single.");
				break;
			}
		}
	}

	void SCInstance::StartTimerThread(){

		td.thread_hnd = (HANDLE)_beginthreadex(NULL,0,TimerThreadProc,this,0,&td.thread_id);

		if (!td.thread_hnd){
			LOG4CPLUS_ERROR(log,"_beginthreadex() TimerThreadProc failed;error no.=" << GetLastError());
		}else{
			LOG4CPLUS_INFO(log,"_beginthreadex() TimerThreadProc ok;thread_id=" << td.thread_id);
		}
	}

	void SCInstance::AddTimer(Timer _timer)
	{
		EnterCriticalSection(&csection);
		m_timer.push_back(_timer);
		LeaveCriticalSection(&csection);
	}
}

