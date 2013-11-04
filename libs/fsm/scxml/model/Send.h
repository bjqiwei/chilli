#pragma once
#ifndef _SCXML_MODEL_SEND_HEADER_
#define  _SCXML_MODEL_SEND_HEADER_

#include <string>
#include <map>
#include <vector>
#include <xmlHelper.h>
#include <log4cplus/logger.h>
#include <scxml/model/Action.h>


namespace fsm
{
namespace model
{
	/// </summary>
	class  Send :public Action
	{
	private:
		log4cplus::Logger log;
		xmlNodePtr node;
		std::string id;
		std::string idlocation;
		std::string target;
		std::string targetexpr;
		std::string type;
		std::string typeexpr;
		std::string from;
		std::string dest;
		std::string _event;
		std::string namelist;
		std::string eventexpr;
		std::map<std::string,std::string> params;
	public:
		Send(xmlNodePtr xNode);
		std::string& getId();
		void setId(const std::string strValue);
		std::string& getIdLocation();
		std::string& getTarget();
		std::string& getType();
		std::string& getEvent();
		std::string& getEventExpr();
		std::string& getFrom();
		std::string& getNamelist();
		std::string& getTargetExpr();
		std::string& getDestination();
		std::map<std::string, std::string>& getParams();
		virtual  void execute(fsm::Evaluator * evl,fsm::Context * ctx);
	};
}
}

#endif //end scxml.model.send header