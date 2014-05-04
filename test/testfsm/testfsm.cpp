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
 		log4cplus::PropertyConfigurator::doConfigure(".\\log4cplus.properties");
		
		//char szFilePath[_MAX_PATH-1];
		//::GetCurrentDirectory(_MAX_PATH, szFilePath);
		string strStateFile;
		strStateFile.append(".\\scm.xml");
		fsm::SMInstance m_smInstance;
		fsm::StateMachine mysmscxml;
		SendImp mySend;
		mysmscxml.Init(strStateFile);
		mysmscxml.setName("fsm");
		mysmscxml.setscInstance(&m_smInstance);
		mysmscxml.addEventDispatcher(&mySend);
		mysmscxml.setSessionID("123456");

		mysmscxml.go();
		std::string strEvent;
		
		
		while (std::cin>>strEvent && strEvent.compare("quit") != 0){
			fsm::TriggerEvent evt(strEvent,0);
			mysmscxml.pushEvent(evt);
			//string stateid = getXmlNodeAttributesValue(mysmscxml.getCurrentState(),"id");
			//std::cout << stateid << endl;
		}
	}
	catch(exception & e)
	{
		std::cout<<e.what()<<endl;
	}
	getchar();

	return 0;
}

void SendImp::fireSend(const std::string& strContent,void * param)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("sendimp");
	LOG4CPLUS_DEBUG(log, strContent);
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

