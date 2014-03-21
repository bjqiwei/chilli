#pragma once
#ifndef _FSM_EVENTDISPATCHER_HEADER_
#define _FSM_EVENTDISPATCHER_HEADER_
#include <string>
#include <map>
#include <log4cplus/logger.h>

namespace fsm
{


	/// <summary>
	/// The event controller interface used to send messages containing
	/// events or other information directly to other module,
	/// other external systems using an Event I/O Processor or to raise
	/// events in the current SCXML session.
	/// 
	/// </summary>
	class FSM_EXPORT EventDispatcher
	{
	public:
		EventDispatcher(const std::string &target):_target(target){}

		// Receive messages module name
		std::string _target;

		//get module name
		std::string getTarget(){ return _target ;}
		
	public:
		/// <summary>
		/// Cancel the specified send message.This feature is not yet implemented
		/// </summary>
		/// <param name="sendId"> The ID of the send message to cancel </param>
		virtual void cancel(const std::string &sendId){};

		/// <summary>
		/// Send this message to the target.
		/// </summary>
	
		virtual void fireSend(const std::string &strContent,void * param) = 0;

	};
}
#endif //end eventdispather header