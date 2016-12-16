// testfsm.cpp : Defines the entry point for the console application.
//
//#define SCXML 1
#include "stdafx.h"
//#ifdef SCXML 
#include "sendimp.h"
#include <fsm.h>
//#endif // SCXML
//#include "io/SCXMLParser.h"
#include <string>
#include <iostream>
#include <thread>

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
		strStateFile.append(".\\fsm.xml");
		fsm::StateMachine mysmscxml("0123456",strStateFile);
		SendImp mySend;

		std::thread th([&]() {
			mysmscxml.addSendImplement(&mySend);

			mysmscxml.go();
			mysmscxml.mainEventLoop();
		});

		
		std::string strEvent;
		
		while (std::cin>>strEvent && strEvent.compare("quit") != 0){
			fsm::TriggerEvent evt(strEvent,"");
			mysmscxml.pushEvent(evt);
			//string stateid = getXmlNodeAttributesValue(mysmscxml.getCurrentState(),"id");
			//std::cout << stateid << endl;
		}
		mysmscxml.termination();
		th.join();
	}
	catch(exception & e)
	{
		std::cout<<e.what()<<endl;
	}
	getchar();

	return 0;
}

void SendImp::fireSend(const std::string& strContent, const void * param)
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

