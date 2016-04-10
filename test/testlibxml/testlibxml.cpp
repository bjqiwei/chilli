// testlibxml.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>

/********************************************************************

    created:   2007/11/09

    created:   9:11:2007   15:34

    filename: CreateXmlFile.cpp

    author:       Wang xuebin 

    depend:       libxml2.lib 

    build:     nmake TARGET_NAME=CreateXmlFile

    purpose:   创建一个xml文件

*********************************************************************/

#include <stdio.h>

#include <libxml/parser.h>

#include <libxml/tree.h>
#include <WinSock2.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")

using namespace std;
int main()

{

    //定义文档和节点指针

    xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");

    xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"root");

    //设置根节点

    xmlDocSetRootElement(doc,root_node);

    //在根节点中直接创建节点

    xmlNewTextChild(root_node, NULL, BAD_CAST "newNode1", BAD_CAST "newNode1 \r\n content");

    xmlNewTextChild(root_node, NULL, BAD_CAST "newNode2", BAD_CAST "newNode2 \r\n content");

	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode3", BAD_CAST "POST /2013-12-26/SubAccounts/46b60327bfcc11e389eed89d672b9690/Calls/Callback?sig=AC9B193CA9D51FF7B6E0F764FE47D418 HTTP/1.1\r\nHost:112.124.0.43:8881\r\nConnection:close\r\nContent-length:112\r\nAccept:application/xml;\r\nContent-Type:application/xml;charset=utf-8;\r\nAuthorization:NDZiNjAzMjdiZmNjMTFlMzg5ZWVkODlkNjcyYjk2OTA6MjAxNDA2MjUxNDQzNDU=\r\n\r\n<?xml version=\"1.0\" encoding=\"utf-8\" ?>\r\n<CallBack>\r\n<from>18310536874</from>\r\n<to>15110162856</to>\r\n</CallBack>");

    //创建一个节点，设置其内容和属性，然后加入根结点

    xmlNodePtr node = xmlNewNode(NULL,BAD_CAST"node2");

    xmlNodePtr content = xmlNewText(BAD_CAST"NODE CONTENT");

    xmlAddChild(root_node,node);

    xmlAddChild(node,content);

    xmlNewProp(node,BAD_CAST"attribute",BAD_CAST "yes");

    //创建一个儿子和孙子节点

    node = xmlNewNode(NULL, BAD_CAST "son");

    xmlAddChild(root_node,node);

    xmlNodePtr grandson = xmlNewNode(NULL, BAD_CAST "grandson");

    xmlAddChild(node,grandson);

    xmlAddChild(grandson, xmlNewText(BAD_CAST "This is a grandson node"));

    //存储xml文档

    int nRel = xmlSaveFile("CreatedXml.xml",doc);

    if (nRel != -1)

    {

       cout<<"一个xml文档被创建,写入"<<nRel<<"个字节"<<endl;

    }

    //释放文档内节点动态申请的内存

    xmlFreeDoc(doc);

	doc = xmlParseFile("CreatedXml.xml");
	ofstream out("write.txt", ios::binary);
	xmlNodePtr rootNode =  xmlDocGetRootElement(doc);
	
	
	for (xmlNodePtr  xchildNode = rootNode->children; xchildNode != NULL; xchildNode = xchildNode->next)
	{
		if(xchildNode->type == XML_ELEMENT_NODE)
		{
			std::string str;
			xmlChar * content = xmlNodeGetContent(xchildNode);
			printf("%s=%s", xchildNode->name, content);
			str.append((const char *)xchildNode->name);
			str.append("=");
			str.append((const char *)content);
			out.write(str.c_str(),str.length());
			xmlFree(content);
		}
	}
	out.close();
	getchar();
    return 1;

}

