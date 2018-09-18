#pragma once
#include <string>
#include <vector>
#include "Action.h"
#include "../SendInterface.h"

namespace fsm
{
namespace model
{
	/// </summary>
	class  Send :public Action
	{
	private:
		std::string id;
		std::string idexpr;
		std::string target;
		std::string targetexpr;
		std::string type;
		std::string typeexpr;
		std::string from;
		std::string fromexpr;
		std::string dest;
		std::string destexpr;
		std::string _event;
		//std::string namelist;
		std::string eventexpr;

		struct ParamStruct
		{
			std::string name;
			std::string type;
			std::string value;
			uint32_t lineno;
		};
		std::vector<ParamStruct> m_Params;

	public:
		Send(const std::string &filename, uint32_t lineno);

		void setId(const std::string &strValue);
		void setIdExpr(const std::string & idexpr);
		void setTarget(const std::string & target);
		const std::string& getTarget()const;
		//void setTargetExpr(const std::string & targetexpr);
		void setType(const std::string & type);
		void setTypeExpr(const std::string & typeexpr);
		void setFrom(const std::string & from);
		void setFromExpr(const std::string & fromexpr);
		void setDestination(const std::string & dest);
		void setDestinationExpr(const std::string & destexpr);
		void setEvent(const std::string & event);
		void setEventExpr(const std::string & eventexpr);
		void addParam(const std::string &name, const std::string & type, const std::string &value, uint32_t lineno);
		//std::string& getNamelist();
		//std::string& getTargetExpr();
		//std::map<std::string, std::string>& getParams();
		virtual  void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;
		void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId , FireDataType & fireData) const;
	private:
		const std::string& getId()const;
		const std::string& getIdExpr()const;
		//const std::string& getTargetExpr()const;
		const std::string& getType()const;
		const std::string& getTypeExpr()const;
		const std::string& getFrom()const;
		const std::string& getFromExpr()const;
		const std::string& getDestination()const;
		const std::string& getDestinationExpr()const;
		const std::string& getEvent()const;
		const std::string& getEventExpr()const;
	};
}
}