#pragma once
#include "../config.h"
#include <string>
#include <json/json.h>

namespace fsm
{
	typedef FSM_EXPORT struct 
	{
		std::string id;
		std::string event;
		std::string type;
		std::string from;
		std::string dest;
		std::string target;
		Json::Value param;

	}FireDataType;

	class FSM_EXPORT SendInterface
	{
	public:
		SendInterface(const std::string &target, void * userdata):_target(target),_userdata(userdata){}

		// Receive messages module name
		const std::string _target;
		void * _userdata = nullptr;
		//get module name
		const std::string & getTarget() const { return _target ;}
		
		const void * getUserData()const { return _userdata; }
	public:
		/// <summary>
		/// Cancel the specified send message.This feature is not yet implemented
		/// </summary>
		/// <param name="sendId"> The ID of the send message to cancel </param>
		virtual void cancel(const std::string &sendId){};

		/// <summary>
		/// Send this message to the target.
		/// </summary>
	
		virtual void fireSend(const FireDataType &fireData,const void * param) = 0;

	};
}