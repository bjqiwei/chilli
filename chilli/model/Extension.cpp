#include "stdafx.h"
#include "Extension.h"
#include "GlobalObject.h"
#include <scxml/env/JSContext.h>
#include "../Device/DevModule.h"

namespace chilli{
namespace abstract{

Extension::Extension(void):m_xmlConfigNodePtr(NULL),m_bEnable(false),NewConfig(false),EventDispatcher("extension"){
	InitializeInstanceFields();
}


Extension::~Extension(void){

}
void Extension::InitializeInstanceFields(){
	log = log4cplus::Logger::getInstance("chilli.abstract.Extension");
	stateMachie.setLog(log);
}
bool Extension::setExtensionNumber(std::string &number)
{
	LOG4CPLUS_DEBUG(log,"set ExtensionNumber="<<number);
	log4cplus::tostringstream tss;
	tss <<log.getName() << "." << number;
	log = log4cplus::Logger::getInstance(tss.str());
	stateMachie.setLog(log);
	this->m_strExtensionNumber = number;
	return true;
}

bool Extension::setEnable(std::string &strEnable)
{
	strEnable = strEnable.substr(0,1);
	this->m_bEnable = atoi(strEnable.c_str()) == 0 ? false:true;
	LOG4CPLUS_DEBUG(log,"set "<< m_strExtensionNumber <<":, enable="  <<strEnable);
	return true;
}

bool Extension::setEnable(bool nEnable)
{
	this->m_bEnable = nEnable;
	return true;
}

bool Extension::setXmlConfigNode(xmlNodePtr xNodePtr)
{
	if (xNodePtr == NULL)
	{
		LOG4CPLUS_ERROR(log,"set extension xml config extenion="
			<< m_strExtensionNumber<<
			" parameter is null. ");
		return false;
	}
	this->m_xmlConfigNodePtr = xNodePtr;
	LOG4CPLUS_DEBUG(log,"set extension xml config.");
	return true;
}

const std::string & Extension::getExtensionNumber(){
	return m_strExtensionNumber;
}
int Extension::getChannelID()
{
	return -1;
}

void Extension::pushEvent(fsm::TriggerEvent &evt){
	stateMachie.pushEvent(evt);
}

bool Extension::setStateMachineFile(std::string smFile)
{
	this->_stateMachieFile = smFile;
	LOG4CPLUS_DEBUG(log, " state machine file="  <<smFile);
	return true;
}
bool Extension::isExtConfigNode(xmlNodePtr xExtNode){
	return xExtNode && xExtNode->type == XML_ELEMENT_NODE && xmlStrEqual(xExtNode->name,BAD_CAST("Extension")); 
}
bool Extension::ParserConfig(void)
{
	if (m_xmlConfigNodePtr == NULL)
	{
		LOG4CPLUS_ERROR(log,"xmlConfigNode is null.");
		return false;
	}
	this->setExtensionNumber(fsm::xmlHelper::getXmlNodeAttributesValue(m_xmlConfigNodePtr,"ExtensionNumber"));
	this->setStateMachineFile(fsm::xmlHelper::getXmlNodeAttributesValue(m_xmlConfigNodePtr,"StateMachine"));
	this->setEnable(fsm::xmlHelper::getXmlNodeAttributesValue(m_xmlConfigNodePtr,"Enable"));
	return true;
}

const std::string Extension::getStateID()
{
	return stateMachie.getCurrentStateID();
}

bool Extension::isIdle()
{
	return (getStateID().compare("idle") == 0) || (getStateID().compare("init") == 0) ;
}
bool Extension::Init(void)
{
	stateMachie.addEventDispatcher(this);
	stateMachie.addEventDispatcher(&this->acdEvtDis);
	//stateMachie.setscInstance(&DevModule::scInstance);
	stateMachie.Init(_stateMachieFile);
	fsm::Context * ctx = stateMachie.getRootContext();
	fsm::env::JsContext * jsctx = dynamic_cast<fsm::env::JsContext *>(ctx);
	if (jsctx){
		/*实例化extension对象*/
		JSObject * obj = jsctx->JSDefineObject("extension", &ExtensionClass);
		/*创建对象的属性*/
		jsctx->JSDefineProperties (obj,Properties );
	}

	stateMachie.setName(this->m_strExtensionNumber);

	return true;
}

bool Extension::isNewConfig(){
	return NewConfig;
}

void Extension::go(){
	stateMachie.go();
}

bool Extension::reload(void)
{
	if (isNewConfig())
	{
		NewConfig = false;
		Global::m_ExtMap.erase(Global::m_ExtMap.find(this->m_strExtensionNumber));
		this->ParserConfig();
		this->Init();
		Global::m_ExtMap[this->m_strExtensionNumber] = this;
		LOG4CPLUS_DEBUG(log,"reload ok ");
	}
	return true;
}
void Extension::setIsNewConfig(bool bNew){
	NewConfig = bNew;
}

 JSBool Extension::GetProperty (JSContext *cx, ::JS::HandleObject obj, JS::Handle<jsid> id, ::JS::MutableHandleValue vp)
{
	ExtensionPtr extPtr = NULL;
	static log4cplus::Logger log = log4cplus::Logger::getInstance("chilli.abstract.Extension.GetProperty");
	/*scxml::env::ToStringHelper idString(cx, id);
	LOG4CPLUS_INFO(log, "getting its property %s," << idString.getBytes());
	scxml::env::ToStringHelper valueString(cx, vp);
	LOG4CPLUS_INFO(log, " initial value %s\n", valueString.getBytes());*/

	for (std::map<std::string,ExtensionPtr>::const_iterator it = Global::m_ExtMap.begin();
		it != Global::m_ExtMap.end(); it++)
	{
		if (it->second){
			fsm::Context * ctx = it->second->stateMachie.getRootContext();
			fsm::env::JsContext * jsctx = dynamic_cast<fsm::env::JsContext *>(ctx);
			if (jsctx && jsctx->ctx == cx){
				extPtr = it->second;
				break;
			}
		}
	}

	if (!extPtr) return JS_FALSE;
	int nid = JSID_TO_INT(id);
	switch (nid ) {
	case ExtensionNumber:{
			JSString * jss = JS_NewStringCopyZ (cx,extPtr->m_strExtensionNumber.c_str());
			vp.setString(jss);
		}
		break;
	case Channel:
		vp.setInt32(extPtr->getChannelID());
		break;
	case Enable:
		vp.setBoolean(extPtr->m_bEnable);
		break;
	case EventData:{
			JSString * jss = JS_NewStringCopyZ(cx,extPtr->_event_data.c_str());
			vp.setString(jss);
		}
		break;
	case CallerId:{
			JSString * jss = JS_NewStringCopyZ(cx,extPtr->m_CallerId.c_str());
			vp.setString(jss);
		}
		break;
	case CalleeId:{
			JSString * jss = JS_NewStringCopyZ(cx,extPtr->m_CalleeId.c_str());
			vp.setString(jss);
		}
		break;
	case PendingReason:{
		JSString * jss = JS_NewStringCopyZ (cx,extPtr->m_PendingReason.c_str());
		vp.setString(jss);
		}
		break;
	default:
		break;
	}
	
	return JS_TRUE;
}
/*定义属性的SETTER*/
JSBool Extension::SetProperty (JSContext *cx, ::JS::HandleObject obj, ::JS::HandleId id, JSBool strict,::JS::MutableHandleValue vp)
{
	ExtensionPtr extPtr = NULL;
	for (std::map<std::string,ExtensionPtr>::const_iterator it = Global::m_ExtMap.begin();
		it != Global::m_ExtMap.end(); it++)
	{
		if (it->second){
			fsm::Context * ctx = it->second->stateMachie.getRootContext();
			fsm::env::JsContext * jsctx = dynamic_cast<fsm::env::JsContext *>(ctx);
			if (jsctx && jsctx->ctx == cx){
				extPtr = it->second;
				break;
			}
		}
	}

	if (!extPtr) return JS_FALSE;


	switch (JSID_TO_INT(id)) {
	//case ExtensionNumber:
	//		extPtr->m_strExtensionNumber = JS_EncodeString(cx,vp.toString());
	//	break;
	//case Channel:
	//		extPtr->Ch = vp.toInt32();
	//	break;
	//case Enable:
	//	extPtr->m_bEnable = vp.toBoolean();
	//	break;
	case Enable:
	default:
		break;
	}
	
	return JS_TRUE;
}

/*定义extension类的属性数组*/
JSPropertySpec Extension::Properties[] =
{
	{"number",ExtensionNumber,    JSPROP_ENUMERATE },
	{"ch",  Channel,     JSPROP_ENUMERATE },
	{"enable",  Enable,     JSPROP_ENUMERATE },
	{"eventData",  EventData,     JSPROP_ENUMERATE },
	{"Caller",  CallerId,     JSPROP_ENUMERATE },
	{"Callee",  CalleeId,     JSPROP_ENUMERATE },
	{"pendingReason",  PendingReason,     JSPROP_ENUMERATE },
	{0}
};
/*定义extension类*/
JSClass Extension::ExtensionClass = {
	"extension",0,
	JS_PropertyStub,JS_DeletePropertyStub, GetProperty, SetProperty,
	JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, NULL
};


}
}
