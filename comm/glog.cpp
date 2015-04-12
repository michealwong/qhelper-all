/**
@file glog.cpp

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		Darrenqiu
@version	1.0
@date		2010/10/12

history:
<PRE>
History ID	:	1
Author    	:	asherzhou
DateTime	:	2011/04/26
Description :	alert alot
</PRE>
*/

#ifndef __GLOG_CPP__
#define	__GLOG_CPP__
//sap头文件
#include "comm_dbmanager.h"
#include "glog.h"
#include "conf.h"
#include "msg.h"
#include "comm_strings.h"
#include "comm_datetime.h"
GLog::GLog()
{
	MAKEFACELOG="./logs/"+GetCurDateDay()+"GLog.log";
	TraceLOG = new CLog((const char*)MAKEFACELOG.c_str());
	TraceLOG->LogOn();

	//added by v_zhtang on 2013-03-22
	string strHost = CRobConf::getConf()->GetCommonInterface()["dbserver"].substr(7,CRobConf::getConf()->GetCommonInterface()["dbserver"].length()-7-31);
	mapHosts[strHost] = CRobConf::getConf()->GetCommonInterface()["dbserver"];
}


GLog::~GLog()
{
	if(NULL != TraceLOG)
	{
		delete 	TraceLOG;
		TraceLOG = NULL;
	}
	mapHosts.clear();
}

/* add by asherzhou
*	重载GetLog,适应新SAP框架的查询结果。结果写入std::vector
*	主要的作用就是调用SAP的接口层
*/
int GLog::GetLog(const ics_log_header& header,const int id,std::map<string,string>& theParam,std::vector< std::map<std::string,std::string> >& result)
{
    DataResult QueryResult;
	vector< map<std::string,std::string> >::iterator itor;
	//避开了0206  GetReachableEndPoint();//
	CDBManager::GetInstance().sEndPointUrl = CRobConf::getConf()->GetCommonInterface()["dbserver"];//"http://10.134.139.214/cgi-bin/120815/dbmanagerserver";
	if( false == CDBManager::GetInstance().ExeQuerier(header,id,theParam,QueryResult) )
	{
		TraceLOG->WriteLog("SAP InterFace Function sId: %d \n",id);
		QueryResult.errCode =	-10012;				// 自定义错误码,稍后实施
		QueryResult.resultDesc = "错误描述";		// 错误描述信息
		return -1;
	}
	else
	{
		if(QueryResult.errCode>=0){
			TraceLOG->WriteLog("SAP InterFace Function , Return ErrorCode : %d  Function Id: %d\n",QueryResult.errCode,id);
			result.clear();
			for(itor=QueryResult.resultSet.begin(); itor !=QueryResult.resultSet.end(); itor++)
			{
				result.push_back((*itor));
			}
			return QueryResult.errCode;
		}else
		{
			TraceLOG->WriteLog("SAP InterFace Function Error, Return ErrorCode : %d  Function Id: %d\n",QueryResult.errCode,id);
			return QueryResult.errCode;
		}
	}
}
/* add by asherzhou
*	GetLogicLog,适应新SAP框架的查询结果。结果写入std::vector
*	主要的作用就是调用SAP的逻辑层
*   具体需要功能项什么参数，请查看rob.conf来确定输入
*/
int GLog::GetFunction(const ics_log_header& header,std::map<string,string>& theParamIn,const char* functionName,std::vector< map<string,string> >& result)
{
	   //配置文件依据functionName读取相关的ID，配置化体现
	   //修改--怎么修改呢？
	   //获取配置文件的对象,然后功能名字下的ID和params
	   TraceLOG->WriteLog("Get Function result\n");
       //1.获得功能ID
	   int selectId=StrToInt(CRobConf::getConf()->GetIcsOper()[functionName]);
	   TraceLOG->WriteLog("Function Id value id is :%d\n",selectId);
	   //2.调用函数进行处理
	   TraceLOG->WriteLog("GetLogicLog functionName: %s , sId: %d\n",functionName,selectId);
	   TraceLOG->WriteLog("Begin To Apply To  Interface Function to Get Data Result\n");
	   return GetLog(header,selectId, theParamIn, result);
}

/*
*	added by v_zhtang 2013-03-22
*   得到可用主机服务器
*	CRobConf::getConf()->GetCommonInterface()["dbserver"]
*	"http://10.134.139.214/cgi-bin/120815/dbmanagerserver";
*/
std::string GLog::GetReachableEndPoint()
{
	string strEndPt = CRobConf::getConf()->GetCommonInterface()["dbserver"];
	
	TraceLOG->WriteLog("[INFO]: Server Host size [%d]! \n",mapHosts.size());
	if (mapHosts.size() > 0)
	{
		for (std::map<string, string>::iterator it=mapHosts.begin(); it!=mapHosts.end(); it++)
		{
			string cmd = "ping -c 1 ";
			string strIp = it->first;
			cmd.append(strIp);
			TraceLOG->WriteLog("[INFO]: The cmd is [%s] \n",cmd.c_str());
			if (0 == system(cmd.c_str()))
			{
				strEndPt = it->second;
				TraceLOG->WriteLog("[INFO]: The host [%s] is on. Just use this server:[%s]\n",it->first.c_str(),strEndPt.c_str());
				break;
			}
			TraceLOG->WriteLog("[ERROR]: The host [%s] is not reachable! \n",it->first.c_str());
		}
	}
	

	return strEndPt;
}

#endif	
