// testfsm.cpp : Defines the entry point for the console application.
//
//#define SCXML 1
#include "stdafx.h"
//#ifdef SCXML 
#include <fsm.h>
#include "sendimp.h"
//#endif // SCXML
//#include "io/SCXMLParser.h"
#include <string>
#include <iostream>

using namespace std;


//#ifdef SCXML
using namespace fsm;
int main(int argc, _TCHAR* argv[])
{
	try{
 		log4cplus::initialize();
 		log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(true);
 		log4cplus::PropertyConfigurator::doConfigure("log4cplus.properties");
		
		xmlInitParser();
#ifdef LIBXML_READER_ENABLED
		char szFilePath[_MAX_PATH-1];
		::GetCurrentDirectory(_MAX_PATH, szFilePath);
		string strStateFile("");
		strStateFile.append("E:\\chilli\\Win32\\bin.Debug\\Anolog_User.xml");
		fsm::StateMachine mysmscxml = StateMachine(strStateFile);
		
 		//mysmscxml.Init();
		SendImp mySend;
		SendImp mySend2;
		//mysmscxml.addEventDispatcher(&mySend);
		//mysmscxml.go();
		std::string strEvent;
		string stateid;// = getXmlNodeAttributesValue(mysmscxml.getCurrentState(),"id");
		std::cout << stateid << endl;
		
		
		while (std::cin>>strEvent && strEvent.compare("quit") != 0){
			fsm::TriggerEvent evt(strEvent,0);
			mySend.fireSend("");
			mySend2.fireSend("");
			//mysmscxml.pushEvent(evt);
			//string stateid = getXmlNodeAttributesValue(mysmscxml.getCurrentState(),"id");
			//std::cout << stateid << endl;
		}
	}
	catch(exception & e)
	{
		std::cout<<e.what()<<endl;
	}
#endif
	xmlCleanupParser();
	getchar();

	return 0;
}

void SendImp::fireSend(const std::string& strContent)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("sendimp");
	std::cout << strContent << endl;
}
//#else
//int main(int argc, _TCHAR* argv[]){
//	scxml::model::SCXML scxml;
//	scxml::io::SCXMLParser::Initialize();
//	scxml::io::SCXMLParser::parse("D:\\qiwei\\CTI\\ShCTI\\Win32\\bin.Debug\\config\\Anolog_User.xml",&scxml);
//	scxml::io::SCXMLParser::Terminate();
//	return 0;
//}
//#endif

