#include "comm_logmanager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <sstream>
#include <unistd.h>
#include <iconv.h>
#include <stdarg.h>
#include <sys/stat.h>
#include "comm_value.h"
#include "soaplogmanagerProxy.h"
#include "conf.h"

using namespace  std;

UNIX_config<NDS_single_config_node>* CLogManager::fConf = NULL;
string CLogManager::sEndPointUrl = "";

CLogManager::CLogManager()
{
	
}

CLogManager::~CLogManager()
{
	
}

CLogManager& CLogManager::GetInstance()
{
	static CLogManager _LogManager;
	return _LogManager;
}

void CLogManager::PrintLog(const char *format, ...)
{
	char opString[3*1024];
	va_list args;

	va_start(args, format);
	vsprintf(opString, format, args);
	va_end(args);

	string logPath= "./logs/LogManager.log";

	unsigned long file_size = 0;
	struct stat file_stats;
	stat(logPath.c_str(), &file_stats);
	file_size = file_stats.st_size;
	ofstream * LogFile=NULL;
	if( file_size > 1024*1024*10)
	{
		LogFile = new ofstream(logPath.c_str());   //重新开始写
	}
	else
	{
		LogFile = new ofstream(logPath.c_str(),ios::app); // 追加
	}

	if (LogFile)
	{
		*LogFile << opString << endl;
	}
	delete LogFile;
}

void CLogManager::PrintLocalLog(const char* logPath,const char *format, ...)
{
	char opString[1*1024*1024];
	va_list args;

	va_start(args, format);
	vsprintf(opString, format, args);
	va_end(args);

	unsigned long file_size = 0;
	struct stat file_stats;
	stat(logPath, &file_stats);
	file_size = file_stats.st_size;
	ofstream * LogFile=NULL;
	if( file_size > 1024*1024*10)
	{
		LogFile = new ofstream(logPath);   //重新开始写
	}
	else
	{
		LogFile = new ofstream(logPath,ios::app); // 追加
	}

	if (LogFile)
	{
		*LogFile << opString << endl;
	}
	delete LogFile;
}

bool CLogManager::WriteDebugLog(int logLevel,string user,int groupId,string logContent,string localLogPath)
{
	string logEnable = "1";
	if( sEndPointUrl == "" )
	{
		sEndPointUrl = CRobConf::getConf()->GetCommonInterface()["cmlogserver"];//"http://172.23.16.11/cgi-bin/111228/logmanagerserver";
		try
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_log");
			logEnable = (*fConf)["COMMON"]("log_enable");
			delete fConf;
		}catch(...){}
	}

	try
	{
		//PrintLog("endPoint:%s user:%s groupId:%d logContent:%s logLevel:%d",endPoint.c_str(),user.c_str(),groupId,logContent.c_str(),logLevel);
		if( logEnable == "1" )
		{
			PrintLocalLog(localLogPath.c_str(),"%s\n",logContent.c_str());
		}

		logmanagerProxy theSap(SOAP_C_UTFSTRING,SOAP_C_UTFSTRING);
		theSap.soap_endpoint = sEndPointUrl.c_str();
		sap__WriteResult theResult;
		int ret = theSap.WriteDebugLog(sap__LogLevel(logLevel),TYPE_DEBUG,(char*)user.c_str(),groupId,(char*)logContent.c_str(),&theResult);
		//PrintLog("ret:%d write ret:%d content:%s\n",ret,theResult,logContent.c_str());

		if( ret != SOAP_OK || theResult != WRITE_OK )
		{
			PrintLog("Failed to WriteDebugLog.ret:%d\n",ret);
			return  false;
		}
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to WriteDebugLog.\n");
		return  false;
	}
}

bool CLogManager::WriteCMLog(string inUser,
					 int inGroupId,
					 int inOptId,
					 unsigned long long inUin,
					 int inWorldId,
					 int inResult,
					 string inOptType,
					 string inIP,
					 string inSeqId,
					 string inPlayerId,
					 string inPlayerName,
					 int inItemId,
					 int inItemCount,
					 string inItemDesc,
					 string inReason,
					 string inMemo,
					 string inCmd,
					 int inSourceId,
					 string inSerial)
{
	try
	{
		string logEnable = "1";
		if( sEndPointUrl == "" )
		{
			sEndPointUrl = CRobConf::getConf()->GetCommonInterface()["cmlogserver"];//"http://172.23.16.11/cgi-bin/120912/logmanagerserver";
			try
			{
				fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
				sEndPointUrl = (*fConf)["COMMON"]("sapws_log");
				logEnable = (*fConf)["COMMON"]("log_enable");
				delete fConf;
			}catch(...){}
		}

		logmanagerProxy theSap(SOAP_C_UTFSTRING,SOAP_C_UTFSTRING);
		theSap.soap_endpoint = sEndPointUrl.c_str();
		sap__WriteResult theResult;
		int ret = theSap.WriteCMLog((char*)inUser.c_str(),inGroupId,inOptId,inUin,inWorldId,inResult,(char*)inOptType.c_str(),
			(char*)inOptType.c_str(),
			(char*)inSeqId.c_str(),
			(char*)inPlayerId.c_str(),
			(char*)inPlayerName.c_str(),
			inItemId,
			inItemCount,
			(char*)inItemDesc.c_str(),
			(char*)inReason.c_str(),
			(char*)inMemo.c_str(),
			(char*)inCmd.c_str(),
			inSourceId,
			(char*)inSerial.c_str(),
			&theResult);
		if( ret != SOAP_OK || theResult != WRITE_OK )
		{
			PrintLog("Failed to write cm log.\nuser:%s groupId:%d optId:%d Uin:%llu worldId:%d endPoint:%s\n",
				inUser.c_str(),inGroupId,inOptId,inUin,inWorldId,sEndPointUrl.c_str());
			return  false;
		}
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to WriteCMLog\n");
		return  false;
	}
}

bool CLogManager::WriteCMLog(string sIntfUrl,
					 string inUser,
					 int inGroupId,
					 int inOptId,
					 unsigned long long inUin,
					 int inWorldId,
					 int inResult,
					 string inOptType,
					 string inIP,
					 string inSeqId,
					 string inPlayerId,
					 string inPlayerName,
					 int inItemId,
					 int inItemCount,
					 string inItemDesc,
					 string inReason,
					 string inMemo,
					 string inCmd,
					 int inSourceId,
					 string inSerial)
{
	try
	{
		string logEnable = "1";
		sEndPointUrl = sIntfUrl;
		if( sEndPointUrl == "" )
		{
			sEndPointUrl = CRobConf::getConf()->GetCommonInterface()["cmlogserver"];//"http://172.23.16.11/cgi-bin/120912/logmanagerserver";
			try
			{
				fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
				sEndPointUrl = (*fConf)["COMMON"]("sapws_log");
				logEnable = (*fConf)["COMMON"]("log_enable");
				delete fConf;
			}catch(...){}
		}

		logmanagerProxy theSap(SOAP_C_UTFSTRING,SOAP_C_UTFSTRING);
		theSap.soap_endpoint = sEndPointUrl.c_str();
		sap__WriteResult theResult;
		int ret = theSap.WriteCMLog((char*)inUser.c_str(),inGroupId,inOptId,inUin,inWorldId,inResult,(char*)inOptType.c_str(),
			(char*)inOptType.c_str(),
			(char*)inSeqId.c_str(),
			(char*)inPlayerId.c_str(),
			(char*)inPlayerName.c_str(),
			inItemId,
			inItemCount,
			(char*)inItemDesc.c_str(),
			(char*)inReason.c_str(),
			(char*)inMemo.c_str(),
			(char*)inCmd.c_str(),
			inSourceId,
			(char*)inSerial.c_str(),
			&theResult);
		if( ret != SOAP_OK || theResult != WRITE_OK )
		{
			PrintLog("Failed to write cm log.\nuser:%s groupId:%d optId:%d Uin:%llu worldId:%d endPoint:%s\n",
				inUser.c_str(),inGroupId,inOptId,inUin,inWorldId,sEndPointUrl.c_str());
			return  false;
		}
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to WriteCMLog\n");
		return  false;
	}
}

bool CLogManager::WriteMonitorLog(int logLevel,string user,int serviceId,int funcId,string funcParams,int val,int result)
{
	string logEnable = "1";
	if( sEndPointUrl == "" )
	{
		sEndPointUrl = CRobConf::getConf()->GetCommonInterface()["cmlogserver"];//"http://172.23.16.11/cgi-bin/1228/logmanagerserver";
		try
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_log");
			logEnable = (*fConf)["COMMON"]("log_enable");
			delete fConf;
		}catch(...){}
	}

	try{
		PrintLog("endPoint:%s user:%s serviceId:%d funcId:%d funcParams:%s logLevel:%d\n",sEndPointUrl.c_str(),user.c_str(),serviceId,funcId,funcParams.c_str(),logLevel);
		logmanagerProxy theSap(SOAP_C_UTFSTRING,SOAP_C_UTFSTRING);
		theSap.soap_endpoint = sEndPointUrl.c_str();
		sap__WriteResult theResult;
		int ret = theSap.WriteMonitorLog(TYPE_MONITOR,(sap__MonitorLevel)logLevel,(char*)user.c_str(),serviceId,funcId,(char*)funcParams.c_str(),val,result,&theResult);
		//PrintLog("ret:%d write ret:%d\n",ret,theResult);

		if( ret != SOAP_OK || theResult != WRITE_OK )
		{
			PrintLog("Failed to WriteMonitorLog.ret:%d\n",ret);
			return  false;
		}
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to WriteMonitorLog.\n");
		return  false;
	}
}

bool CLogManager::ReadDebugLog(int logLevel,int logType,string user,int groupId, vector< map<string,string> > &oData)
{
	string logEnable = "1";
	if( sEndPointUrl == "" )
	{
		sEndPointUrl = CRobConf::getConf()->GetCommonInterface()["cmlogserver"];//"http://172.23.16.11/cgi-bin/1228/logmanagerserver";
		try
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_log");
			logEnable = (*fConf)["COMMON"]("log_enable");
			delete fConf;
		}catch(...){}
	}

	try{
		PrintLog("endPoint:%s user:%s groupId:%d\n",sEndPointUrl.c_str(),user.c_str(),groupId);
		logmanagerProxy theSap(SOAP_C_UTFSTRING,SOAP_C_UTFSTRING);
		theSap.soap_endpoint = sEndPointUrl.c_str();
		sap__QueryDebugLogResponse theResult;
	
		int ret = theSap.QueryDebugLog((char*)user.c_str(),groupId,sap__LogLevel(logLevel),&theResult);
		//PrintLog("2 ret:%d\n",ret);
		//PrintLog("ret:%d write ret:%d\n",ret,theResult);

		if( ret != SOAP_OK )
		{
			PrintLog("Failed to QueryDebugLog.ret:%d\n",ret);
			return  false;
		}

		for(int i=0; i< theResult.dataSet.__size; i++ )
		{
			sap__DebugLogData& theItem = theResult.dataSet.items[i];
			//PrintLog("Log:%s\n",theItem._logContent);
		}
		//PrintLog("4\n");
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to QueryDebugLog.\n");
		return  false;
	}

}

bool CLogManager::SendEmail(string mailTo,string mailTitle,string mailText)
{
	string logEnable = "1";
	if( sEndPointUrl == "" )
	{
		sEndPointUrl = CRobConf::getConf()->GetCommonInterface()["cmlogserver"];//"http://172.23.16.11/cgi-bin/1228/logmanagerserver";
		try
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_log");
			logEnable = (*fConf)["COMMON"]("log_enable");
			delete fConf;
		}catch(...){}
	}

	try{
		PrintLog("endPoint:%s mailTo:%s mailTitle:%s mailText:%s",sEndPointUrl.c_str(),mailTo.c_str(),mailTitle.c_str(),mailText.c_str());
		logmanagerProxy theSap(SOAP_C_UTFSTRING,SOAP_C_UTFSTRING);
		theSap.soap_endpoint = sEndPointUrl.c_str();
		sap__WriteResult theResult;
		int ret = theSap.SendEmail((char*)mailTo.c_str(),(char*)mailTitle.c_str(),(char*)mailText.c_str(),&theResult);
		//PrintLog("ret:%d write ret:%d\n",ret,theResult);

		if( ret != SOAP_OK || theResult != WRITE_OK )
		{
			PrintLog("Failed to SendEmail.ret:%d\n",ret);
			return  false;
		}
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to SendEmail.\n");
		return  false;
	}
}	