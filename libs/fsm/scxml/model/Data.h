#pragma once
#ifndef _FSM_MODEL_DATA_HEADER_
#define _FSM_MODEL_DATA_HEADER_
#include <string>
#include <libxml/tree.h>
#include "Action.h"

namespace fsm
{
namespace model
{


class Data :public Action
{


private:
	xmlNodePtr node;
	std::string m_strId;
	std::string m_strExpr;
public:
	Data(xmlNodePtr xNode);

	const std::string  &getId() const;
	//void setId(const std::string &id);
	//const std::string  getSrc() const ;
	//void setSrc(const std::string &src);
	const std::string  &getExpr() const;
	//void setExpr(const std::string &expr);
	//xmlNodePtr getNode() ;
	//void setNode( xmlNodePtr const node);
	virtual void execute(fsm::Evaluator * evl,fsm::Context * ctx);

};


}
}
#endif //end header file
