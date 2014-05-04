#pragma once
#ifndef FSM_CONTEXT_HEADER_
#define FSM_CONTEXT_HEADER_
#include <map>
#include <string>
#include "libxml/tree.h"


namespace fsm{

	class Evaluator;
	class  Context
	{
	public:
		Context(Evaluator * evl, Context * _parent):evaluator(evl),parent(_parent){
		};
		virtual ~Context(void){
		};

	public:

		/// <summary>
		/// Assigns a new value to an existing variable or creates a new one.
		/// The method allows to shadow a variable of the same name up the
		/// Context chain.
		/// </summary>
		/// <param name="name"> The variable name </param>
		/// <param name="value"> The variable value </param>
		virtual void setLocal(const std::string & name, const std::string & value,bool eventVars=true) = 0;

		/// <summary>
		/// Get the Map of all variables in this Context.
		/// </summary>
		/// <returns> Local variable entries Map
		/// To get variables in parent Context, call getParent().getVars(). </returns>
		/// <seealso cref= #getParent() </seealso>
		virtual std::map<std::string,std::string> & getEventVars() = 0;

		/// <summary>
		/// Set the Map of all variables in event vars of this Context.
		/// </summary>
		virtual void SetEventVars(const std::map<std::string,std::string> &vars) = 0;
		
		/// <summary>
		/// Clear  this event vars.
		/// </summary>
		virtual void ClearEventVars() = 0;
		/// <summary>
		/// reset this Context.
		/// </summary>
		virtual void Reset() = 0;

		/// <summary>
		/// Get the parent Context, may be null.
		/// </summary>
		/// <returns> The parent Context in a chained Context environment </returns>
		virtual Context *getParent() = 0;

		///<summary>
		///编译一段脚本。
		///</summary>
		///<returns>返回此脚本执行是否成功的结果。</returns>
		virtual bool CompileScript(const std::string &script,const std::string &filename, unsigned int line,void *index) = 0;

		///<summary>
		///计算一段表达式脚本。
		///</summary>
		///<returns>返回此表达式执行的结果，转换为string类型。</returns>
		virtual std::string eval(const std::string &expr,const std::string &filename, unsigned int line,void *index) = 0;

		///<summary>
		///计算一段boolen表达式脚本
		///</summary>
		///<returns>返回此表达式执行的结果。</returns>
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line,void *index) = 0;

		///<summary>
		///设置私有数据。
		///</summary>
		virtual void SetContextPrivate(void *data) = 0;

		///<summary>
		///获取它的虚拟机。
		///</summary>
		///<returns>返回虚拟机指针。</returns>
		virtual Evaluator * getEvaluator(){ return evaluator; };

		///<summary>
		///执行一段脚本文件。
		///</summary>
		virtual void ExecuteFile(const std::string &fileName) = 0;

	protected:
		Evaluator * evaluator;
		//父Context
		Context *parent;
		//上下文中的变量
		std::map<std::string,std::string> eventVars;
	};

}

#endif //end Context