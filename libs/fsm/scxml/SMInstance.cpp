
#include "SMInstance.h"
#include "env/JSEvaluator.h"
#include <log4cplus/loggingmacros.h>
#ifdef WIN32
#include <process.h>
#include <Windows.h>
#else
#include <errno.h>
#include <semaphore.h>
#include <sys/timeb.h>

#endif

namespace fsm
{

	log4cplus::Logger SMInstance::log = log4cplus::Logger::getInstance("fsm.SMInstance");
	SMInstance::SMInstance()
	{
		LOG4CPLUS_DEBUG(log,"new fsm.SMInstance object...");
		LOG4CPLUS_DEBUG(log,"new fsm.SMInstance object.");
	}

	SMInstance::~SMInstance()
	{
		LOG4CPLUS_DEBUG(log , "destruction fsm.SMInstance object...");
		
		contexts.clear();

		removedContexts.clear();
		//if (rootContext) delete rootContext;
		for (std::vector<Evaluator *>::iterator it = evaluator.begin(); it != evaluator.end(); ++it)
		{
			delete *it;
		}

			
		LOG4CPLUS_DEBUG(log , "destruction fsm.SMInstance object.");
	}
	Evaluator *SMInstance::getEvaluator()const
	{
		LOG4CPLUS_DEBUG(log,"getEvaluator,evaluator vector size="<< evaluator.size());
		for (std::vector<Evaluator *>::iterator it = evaluator.begin(); it != evaluator.end(); ++it)
		{
			if((*it)->hasContext()){
				LOG4CPLUS_DEBUG(log,"find a evaluator " << *it);
				return *it;
			}
		}
		
		Evaluator * evl = NULL;
		try
		{
			LOG4CPLUS_INFO(log,"not find idle evaluator ,new a JSEvaluator.");
			evl = new env::JSEvaluator();
			evaluator.push_back(evl);
			return evl;
		}
			
		catch (...)
		{
			throw;
		}
		return NULL;
	}

	//void SMInstance::setEvaluator(Evaluator *const evaluator)
	//{
	//	if (evaluator) delete evaluator;
	//	this->evaluator = evaluator;
	//}

	Context *SMInstance::getRootContext()const
	{
		/*if (getEvaluator() != 0)
		{
			if (contexts[0] == 0)
			{
				contexts[0] = getEvaluator()->newContext(NULL);
			}
			return contexts[0];
		}*/
		return NULL;
	}

	//void SMInstance::setRootContext(Context *const context)
	//{
	//	if (rootContext) delete rootContext;
	//
	//	this->rootContext = context;
	//}

	Context *SMInstance::getContext(xmlNodePtr xNode)const
	{
		Context *context =NULL ; 
		std::map<xmlNodePtr,Context *>::iterator it = contexts.find(xNode);
		if (it != contexts.end())
		{
			context = it->second;
			//LOG4CPLUS_DEBUG(log,"find the context "  << context <<" by key:" << xNode);
		}
		
		if (context == NULL && xNode != NULL)
		{
			if (!removedContexts.empty())
			{
				context = removedContexts.front();
				removedContexts.pop_front();
				LOG4CPLUS_DEBUG(log,"find a context " << context << " in the removedContext set. still has " << removedContexts.size());
			}
			

			if (context == NULL)
			{
				Evaluator * evl = getEvaluator();
				context = evl->newContext(NULL);
			}
			
			//xmlNodePtr parent = xNode->parent;
			//if (parent == 0 || parent->type == XML_DOCUMENT_NODE)
			//{// docroot
			//	LOG4CPLUS_DEBUG(log,"not find  context by id=" << xNode << ",serch parent context,parent id=NULL");
			//	//context = getEvaluator()->newContext(getRootContext());
			//}
			//else
			//{
			//	LOG4CPLUS_DEBUG(log,"not find  context by id=" << xNode << ",serch parent context,parent id=" << parent);
			//	context = getEvaluator()->newContext(getContext(parent));
			//}
			contexts[xNode] = context;
		}
		return context;
	}
	void SMInstance::removeContext(xmlNodePtr xNode)
	{
		std::map<xmlNodePtr,Context *>::iterator it = contexts.find(xNode);
		if (it != contexts.end())
		{
			LOG4CPLUS_DEBUG(log,"removeing context " << it->second);
			//delete contexts[xNode];

			removedContexts.push_back(it->second);
			it->second->reset();
			contexts.erase(it);
			LOG4CPLUS_DEBUG(log,"remove from contexts to removedContexts,contexts size " << contexts.size() << " add  removedContexts size " << removedContexts.size());
		}
		
		LOG4CPLUS_DEBUG(log,"context size:" << contexts.size());
	}
	Context *SMInstance::lookupContext(xmlNodePtr xNode)
	{
		if (contexts.count(xNode) > 0)
		{
			return contexts[xNode];
		}
		return NULL;
	}

	void SMInstance::setContext(xmlNodePtr xNode, Context *const context)
	{
		if (contexts[xNode] != NULL)
		{
			delete contexts[xNode];
		}
		contexts[xNode] = context;
	}

}

