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
#include <fstream>
#include <thread>
#include <tchar.h>

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

int test()
{
	int i = 1000;
	std::vector<fsm::StateMachine *> m_scxml;
	time_t mtime = 0;
	while (i--) {
		struct stat fileStatus;
		stat("./fsm.xml", &fileStatus);
		fsm::StateMachine  *  mysmscxml = nullptr;
		if (mtime == fileStatus.st_atime) {
			mysmscxml = new fsm::StateMachine(*m_scxml.back());
		}
		else {
			mysmscxml = fsm::fsmParseFile("./fsm.xml");
			mtime = fileStatus.st_atime;
		}

	
		mysmscxml->setLoggerId("fsm");
		mysmscxml->setSessionID("0123456");
		mysmscxml->setOnTimer(&my_timer);
		mysmscxml->setVar("chilli.qiwei.name", "qiwei");
		mysmscxml->start(false);
		m_scxml.push_back(mysmscxml);
	}


	while (!m_scxml.empty()) {
		m_scxml.back()->stop();
		delete m_scxml.back();
		m_scxml.pop_back();
	}


	int ii = 2000;
	while (ii--)
	{
		fsm::threadIdle();
	}
	getchar();
	std::cout << "thread stoped." << std::endl;
	return 0;
}

int main(int argc, _TCHAR* argv[])
{
	log4cplus::initialize();
	fsm::initialize();

	try{
 		log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(true);
 		log4cplus::PropertyConfigurator::doConfigure(".\\log4cplus.properties");
		

		//char szFilePath[_MAX_PATH-1];
		//::GetCurrentDirectory(_MAX_PATH, szFilePath);
#if 1
		
		std::thread th1(test);
		std::thread th2(test);
		std::thread th3(test);

		th1.join();
		th2.join();
		th3.join();

		std::cout << "all thread stoped." << std::endl;
		getchar();

#else
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
			fsm::threadIdle();
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
#endif

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

