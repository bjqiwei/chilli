#include "TcpClientModule.h"
#include <json/config.h>
#include <json/json.h>
#include <event2/thread.h>


class TestMoudle :public TcpClientModule {
protected:
	virtual void Login() override
	{
		Json::Value login;
		login["cmd"] = "cmdconnect";
		login["senderuri"] = "";
		login["asstation"] = 1234;

		Json::FastWriter write;
		std::string data = write.write(login);
		Send(data.c_str(), data.length());
	}
	virtual void Ping() override
	{
		Json::Value ping;
		ping["cmd"] = "cmdactive";
		ping["senderuri"] = "";
		ping["asstation"] = 1234;

		Json::FastWriter write;
		std::string data = write.write(ping);
		Send(data.c_str(), data.length());
	}

};

int main()
{
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2, 2), &wsa_data);
	evthread_use_windows_threads();
#else
	evthread_use_pthreads();
#endif

	TestMoudle tcpclient;
	Json::Value ips;
	Json::Value ip;
	ip["ipaddr"] = "114.215.196.183";
	ip["socketport"] = 9093;
	ips.append(ip);

	tcpclient.Start(ips);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::string data = "{\"custId\":\"100002 | 01080566667\",\"taskid\":54,\"tracedata\":\"535bbf55246b421fa0e164d58643d5d9 | 54 | 2 | 1487672075725\",\"companyid\":2,\"pds_station_no\":210,\"cmd\":\"cmdstartflow\",\"userdata\":\"535bbf55246b421fa0e164d58643d5d9 | 54 | 2 | 1487672075725\",\"autocall\":1,\"called\":\"2\",\"filename\":\"makecall.lua\",\"tracestation\":210,\"displayno\":\"\",\"groupid\":895}";
	for (int i = 0; i < 1; i++)
	{
		tcpclient.Send(data.c_str(), data.length());
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	tcpclient.Stop();
	std::getchar();

#ifdef WIN32
	WSACleanup();
#endif
	return 0;
}

