// testfsm.cpp : Defines the entry point for the console application.
//
//#define SCXML 1
#include "stdafx.h"
//#ifdef SCXML 
#include "sendimp.h"
#include <FSM.h>
//#endif // SCXML
//#include "io/SCXMLParser.h"
#include <string>
#include <iostream>
#include <thread>

using namespace std;

//#ifdef SCXML
using namespace fsm;

class ontimer :public OnTimerInterface {

	virtual void OnTimer(unsigned long timerId, const std::string & attr, void * userdata)
	{
		static log4cplus::Logger log = log4cplus::Logger::getInstance("timer");
		LOG4CPLUS_DEBUG(log, "", attr);
	}
}my_timer;


int main(int argc, _TCHAR* argv[])
{
	log4cplus::initialize();
	fsm::initialize();

	try{
 		log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(true);
 		log4cplus::PropertyConfigurator::doConfigure(".\\log4cplus.properties");
		

		//char szFilePath[_MAX_PATH-1];
		//::GetCurrentDirectory(_MAX_PATH, szFilePath);
		string strStateFile;
		strStateFile.append(".\\fsm.xml");
		fsm::StateMachine  *  mysmscxml = fsm::fsmParseFile(strStateFile);
		if (mysmscxml)
		{
			mysmscxml->setLoggerId("fsm");
			mysmscxml->setSessionID("0123456");
			mysmscxml->setOnTimer(&my_timer);
		}
		SendImp mySend;

		std::thread th([&]() {
			mysmscxml->addSendImplement(&mySend);

			mysmscxml->start();
			mysmscxml->mainEventLoop();
			std::cout << mysmscxml->isInFinalState() << endl;
			fsm::threadCleanup();
		});

		
		std::string strEvent;
		
		while (std::cin>>strEvent && strEvent.compare("quit") != 0){
			fsm::TriggerEvent evt(strEvent,"");
			mysmscxml->pushEvent(evt);
			//string stateid = getXmlNodeAttributesValue(mysmscxml.getCurrentState(),"id");
		}

		mysmscxml->stop();
		th.join();
		delete mysmscxml;

	}
	catch(exception & e)
	{
		std::cout<<e.what()<<endl;
	}
	fsm::unInitialize();
	getchar();

	return 0;
}

void SendImp::fireSend(const fsm::FireDataType & fireData, const void * param)
{
	static log4cplus::Logger log = log4cplus::Logger::getInstance("sendimp");
	LOG4CPLUS_DEBUG(log,"", fireData.id << ":" << fireData.event << ":" << fireData.param.toStyledString());
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

