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
		FireDataType fireData;

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
		const std::string& getId()const;
		void setId(const std::string &strValue);
		const std::string& getIdExpr()const;
		void setIdExpr(const std::string & idexpr);

		const std::string& getTarget()const;
		void setTarget(const std::string & target);
		const std::string& getTargetExpr()const;
		void setTargetExpr(const std::string & targetexpr);

		const std::string& getType()const;
		void setType(const std::string & type);
		const std::string& getTypeExpr()const;
		void setTypeExpr(const std::string & typeexpr);

		const std::string& getFrom()const;
		void setFrom(const std::string & from);
		const std::string& getFromExpr()const;
		void setFromExpr(const std::string & fromexpr);

		const std::string& getDestination()const;
		void setDestination(const std::string & dest);
		const std::string& getDestinationExpr()const;
		void setDestinationExpr(const std::string & destexpr);

		const std::string& getEvent()const;
		void setEvent(const std::string & event);
		const std::string& getEventExpr()const;
		void setEventExpr(const std::string & eventexpr);

		void addParam(const std::string &name, const std::string & type, const std::string &value, uint32_t lineno);
		//std::string& getNamelist();
		//std::string& getTargetExpr();
		const FireDataType & getFireData()const;
		//std::map<std::string, std::string>& getParams();
		virtual  void execute(fsm::Context * ctx, const log4cplus::Logger & log, const std::string & sessionId) const override;
	};
}
}