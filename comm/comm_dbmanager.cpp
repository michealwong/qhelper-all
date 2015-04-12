#include "comm_dbmanager.h"
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
#include "soapdbmanagerProxy.h"
#include "comm_strings.h"
#include "comm_value.h"
#include "../include/result_xml/sapTest/StdAfx.h"
#include "../include/result_xml/sap/sap.h"

UNIX_config<NDS_single_config_node>* CDBManager::fConf = NULL;
string CDBManager::sEndPointUrl = "";

using namespace sap;


//string CDBManager::MAKEFACELOG="./logs/"+GetCurDateDay()+"DbManager.log";
//CLog* CDBManager::TraceLOG = new CLog((const char*)MAKEFACELOG.c_str());



CDBManager::CDBManager()
{
	
}

CDBManager::~CDBManager()
{
}

CDBManager& CDBManager::GetInstance()
{
	static CDBManager _LogManager;
	return _LogManager;
}

void CDBManager::PrintLog(const char *format, ...)
{
	static string logPath= "./logs/"+GetCurDateDay()+"DbManager.log";

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
		time_t          curr;
		struct tm		current_time;
		char            time_buffer[128];

		curr = time(NULL);
		localtime_r(&curr, &current_time);
		strftime(time_buffer, 128, "%Y-%m-%d %H:%M:%S", &current_time);
		//fprintf(pstFile, "[%s|%s|%s]",time_buffer,ICS_STRING_CODE.c_str(),ICS_UIN_CODE.c_str());
		//fprintf(pstFile, "[%s]",time_buffer);

		char opString[1024*1024];
		va_list args;

		va_start(args, format);
		vsprintf(opString, format, args);
		va_end(args);

		
		*LogFile << "[" << time_buffer << "]" << opString << endl;
	}
	delete LogFile;
}

bool CDBManager::XMLToDataResult(char* xml,DataResult& outResult)
{
	try{
		xercesc::XMLPlatformUtils::Initialize();
	
		string theDecodedXML = xml;
		Csap doc = Csap::LoadFromString(theDecodedXML);
	
		outResult.xml = theDecodedXML;
		//PrintLog("1 xml:%s",theDecodedXML.c_str());
		//PrintLog("xml1:%s",outResult.xml.c_str());
	
		if( !doc.saproot.exists() )
		{
			PrintLog("Uncompleted xml.");
			//TraceLOG->WriteLog("Uncompleted xml.\n");
			xercesc::XMLPlatformUtils::Terminate();
			return false;
		}

		//doc.SetXsiType();
		CsaprootType root = doc.saproot.first();
		CresultType ret = root.result.first();
		outResult.errCode = ret.errcode.first();
		outResult.dataNum = ret.datanum.first();
		string s = ret.desc.first();
		string theDesc = URLDecode(ret.desc.first());
		outResult.resultDesc = Inner(theDesc,"<![CDATA[","]]>");
		if( outResult.resultDesc == "" )
		{
			outResult.resultDesc = theDesc;
		}
		
		if( ret.datahead.exists() )
		{
			sap::CdataheadType head = ret.datahead.first();
			if( head.column.exists() )
			{
				for (unsigned int i = 0; i < head.column.count(); ++i)
				{
					outResult.dataHead.push_back(URLDecode(tstring(head.column[i])));
				}
			}
		}
		/*
		for (sap::Csap::column::iterator it = head.all(); it; ++it)
		{
		theResult.dataHead.push_back(tstring(it));
		}*/
		if( root.resultset.exists() )
		{
			sap::CresultsetType dataset = root.resultset.first();
			if( dataset.items.exists() )
			{
				for (unsigned int i = 0; i < dataset.items.count(); ++i)
				{
					map<string,string> item;
					for (unsigned int j = 0; j < dataset.items[i].field.count(); ++j)
					{
						string key,val;
						//PrintLog("BEFOR");
						if( dataset.items[i].field[j].name.exists() )
						{
							key = dataset.items[i].field[j].name;
						}else
						{	
							key = "col_" + string(itoa(j));
						}
						val = URLDecode(tstring(dataset.items[i].field[j]));
						item[key] = Inner(val,"<![CDATA[","]]>");
					}
					outResult.resultSet.push_back(item);
				}
			}
		}

		xercesc::XMLPlatformUtils::Terminate();
		return true;

	}catch (...)
	{
		PrintLog("Unknown error");
		//TraceLOG->WriteLog("Unknown error\n");
		return false;
	}
}

bool CDBManager::DataResultToXML(DataResult& inResult,string& outXML)
{
	try{
		xercesc::XMLPlatformUtils::Initialize();
		Csap doc = Csap::CreateDocument();
		CsaprootType root = doc.saproot.append();
		//doc.SetSchemaLocation(_T("sap.xsd"));

		CresultType ret = root.result.append();
		ret.errcode.append() = inResult.errCode;
		ret.datanum.append() = inResult.resultSet.size();
		ret.desc.append() = URLEncode("<![CDATA[" + inResult.resultDesc + "]]>");
		sap::CdataheadType head = ret.datahead.append();

		if( inResult.resultSet.size() > 0 )
		{
			CresultsetType retset = root.resultset.append();
			for ( map<string,string>::iterator it = inResult.resultSet[0].begin() ; it != inResult.resultSet[0].end(); it++ )
			{
				head.column.append() = URLEncode((*it).first);
			}
			for( int i=0; i<inResult.resultSet.size(); i++)
			{
				CitemsType item = retset.items.append();
				for ( map<string,string>::iterator it = inResult.resultSet[i].begin() ; it != inResult.resultSet[i].end(); it++ )
				{				
					CfieldType theField = item.field.append();
					theField =  URLEncode("<![CDATA[" + (*it).second + "]]>");
					theField.name = (*it).first;
				}			
			}
		}

		string s = doc.SaveToString(true);
		string oldhead = "UTF-16";
		string newhead = "gbk";
		Replace(s,oldhead,newhead);

		outXML = _T(s);
		//PrintLog("XML:%s",outXML.c_str());
		xercesc::XMLPlatformUtils::Terminate();
		return true;
	}catch (...)
	{
		PrintLog("Unknown error");
		xercesc::XMLPlatformUtils::Terminate();
		return false;
	}
}

bool CDBManager::ExeSql(char* inDBIP,char* inDBUser,char* inDBPwd,char* inDBName,char* inSqlStatement,char* inDbCategory,int inDBPort,char* inCharset,DataResult& outResult)
{
	try
	{
		PrintLog("Start to ExeSql.");
		if( sEndPointUrl == "" )
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_db");
			delete fConf;
		}
		
		char* outXML = NULL;
		PrintLog("endPoint:%s ip:%s user:%s pwd:%s dbname:%s",sEndPointUrl.c_str(),inDBIP,inDBUser,inDBPwd,inDBName);

		dbmanagerProxy theSap(SOAP_XML_TREE,SOAP_XML_TREE);
		theSap.soap_endpoint = sEndPointUrl.c_str();
		int ret = theSap.ExeSql(inDBIP,inDBUser,inDBPwd,inDBName,inSqlStatement,inDbCategory,inDBPort,inCharset,&outXML);
		if( ret != SOAP_OK )
		{
			PrintLog("Failed to ExeSql.ret:%d",ret);
			return  false;
		}

		if( XMLToDataResult(outXML,outResult) == false )
		{
			PrintLog("Failed to convert xml to result.");
			return false;
		}

		PrintLog("End to ExeSql.");
		
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to ExeSql.");
		return  false;
	}
}

bool CDBManager::ExeSqlByDataOper(int inDBId,char*  inDBName,char*  inSqlStatement,char* inDbCategory,int inDBPort,char* inCharset,DataResult& outResult)
{
	try
	{
		if( sEndPointUrl == "" )
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_db");
			delete fConf;
		}

		char* outXML = NULL;

		dbmanagerProxy theSap(SOAP_XML_TREE,SOAP_XML_TREE);
		theSap.soap_endpoint = sEndPointUrl.c_str();
		int ret = theSap.ExeSqlByDataOper(inDBId,inDBName,inSqlStatement,inDbCategory,inDBPort,inCharset,&outXML);
		if( ret != SOAP_OK )
		{
			PrintLog("Failed to ExeSqlByDataOper.ret:%d",ret);
			return  false;
		}

		if( XMLToDataResult(outXML,outResult) == false )
		{
			PrintLog("Failed to convert xml to result.");
			return false;
		}

		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to ExeSqlByDataOper.");
		return  false;
	}
}

bool CDBManager::ExeMultiSql(int inDBId,char*  inDBName,char* inSQLFormat,long inStartTime,long inEndTime,long inStep,char* inCharset,DataResult& outResult)
{
	try
	{
		if( sEndPointUrl == "" )
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_db");
			delete fConf;
		}
		char* outXML = NULL;

		dbmanagerProxy theSap(SOAP_XML_TREE,SOAP_XML_TREE);
		theSap.soap_endpoint = sEndPointUrl.c_str();
		int ret = theSap.ExeSqlFromMultiTable(inDBId,inDBName,inSQLFormat,inStartTime,inEndTime,inStep,inCharset,&outXML);
		if( ret != SOAP_OK )
		{
			PrintLog("Failed to ExeMultiSql.ret:%d",ret);
			return  false;
		}

		if( XMLToDataResult(outXML,outResult) == false )
		{
			PrintLog("Failed to convert xml to result.");
			return false;
		}

		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to ExeSqlMultiTable.");
		return  false;
	}
}

bool CDBManager::ExeSqlByWorldId(int inServiceId,int inWorldId,int inDBType,char* inDBName,char* inSql,char* inDbCategory,int inDBPort,char* inCharset,DataResult& outResult)
{
	try
	{
		PrintLog("Start to ExeSqlByWorldId.");
		if( sEndPointUrl == "" )
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_db");
			delete fConf;
		}
		char* outXML = NULL;

		dbmanagerProxy theSap(SOAP_XML_TREE,SOAP_XML_TREE);
		theSap.soap_endpoint = sEndPointUrl.c_str();

		int ret = theSap.ExeSqlByWorldId(inServiceId,inWorldId,inDBType,inDBName,inSql,inDbCategory,inDBPort,inCharset,&outXML);
		if( ret != SOAP_OK )
		{
			PrintLog("Failed to ExeSqlByWorldId.ret:%d",ret);
			return  false;
		}
		if( XMLToDataResult(outXML,outResult) == false )
		{
			PrintLog("Failed to convert xml to result.");
			return false;
		}
		PrintLog("End to ExeSqlByWorldId.");
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to ExeSqlByWorldId.");
		return  false;
	}
}

bool CDBManager::ExeQuerier(const ics_log_header& header,int inQueryId, map< string,string >& inParams,DataResult& outResult)
{
	string strLogHeader = header.ServiceID+ "|" + header.ICSID + "|" + header.UserID;
	try
	{
		PrintLog("Start to ExeQuerier.");
		WriteLogsT(TLOG_TYPE_DBMANAGER,"%s|%d|Start to ExeQuerier\n",strLogHeader.c_str(),inQueryId);
		if( sEndPointUrl == "" )
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_db");
			delete fConf;
		}
		char* outXML = NULL;

		/* 接口添加source、serial
		 * @add by v_sjwang 2012/11/7 17:30:27
		 */
		inParams["serial"] = GetSerial();
		inParams["source"] = "20";

		vector<string> theVarPairList;
		for ( map<string,string>::iterator it = inParams.begin() ; it != inParams.end(); it++ )
		{
			string theVarPair = (*it).first + "=" + (*it).second;
			theVarPairList.push_back(theVarPair);
		}
		string theParamListString;
		Join(theVarPairList,'&',theParamListString);
		theParamListString = Utf8ToGbk((char*)theParamListString.c_str());

		dbmanagerProxy theSap(SOAP_XML_TREE,SOAP_XML_TREE);
		theSap.soap_endpoint = sEndPointUrl.c_str();

		PrintLog("%s|QueryId[%d]|ParamsList:[%s]|",strLogHeader.c_str(),inQueryId,theParamListString.c_str());
		WriteLogsT(TLOG_TYPE_DBMANAGER,"%s|%d|ParamsList:[%s]\n",strLogHeader.c_str(),inQueryId,theParamListString.c_str());
		int ret = theSap.Querier(inQueryId,(char*)theParamListString.c_str(),&outXML);
		if( ret != SOAP_OK )
		{
			PrintLog("Failed to ExeQuerier.ret:%d",ret);
			WriteLogsT(TLOG_TYPE_DBMANAGER,"%s|Failed to ExeQuerier.ret:%d\n",strLogHeader.c_str(),ret);
			return  false;
		}
		
		if( XMLToDataResult(outXML,outResult) == false )
		{
			PrintLog("Failed to convert xml to result.");
			WriteLogsT(TLOG_TYPE_DBMANAGER,"%s|Failed to convert xml to result.\n",strLogHeader.c_str());
			return false;
		}

		PrintLog("%s|QueryId[%d]|Result:errCode[%d],size:[%d],desc:[%s]",strLogHeader.c_str(),inQueryId,outResult.errCode,outResult.dataNum,outResult.resultDesc.c_str());
		string strDes = outResult.resultDesc;
		Replace(strDes,"|","%7c");
		WriteLogsT(TLOG_TYPE_DBMANAGER,"%s|%d|Result:errCode[%d],size:[%d],desc:[%s]\n",\
										strLogHeader.c_str(),
										inQueryId,
										outResult.errCode,
										outResult.dataNum,
										strDes.c_str());

		PrintLog("End to ExeQuerier.");
		WriteLogsT(TLOG_TYPE_DBMANAGER,"%s|%d|End to ExeQuerier\n",strLogHeader.c_str(),inQueryId);
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to ExeQuerier.");
		WriteLogsT(TLOG_TYPE_DBMANAGER,"%s|Failed to ExeQuerier\n",strLogHeader.c_str());
		return  false;
	}
}

bool CDBManager::ExeQuerierByAlias(int inServiceId,char* inAlias, map<string,string>& inParams,DataResult& outResult)
{
	try
	{
		PrintLog("Start to ExeQuerierByAlias.");
		//TraceLOG->WriteLog("Start to ExeQuerierByAlias.");
		if( sEndPointUrl == "" )
		{
			fConf = new UNIX_config<NDS_single_config_node>("./0206.conf");
			sEndPointUrl = (*fConf)["COMMON"]("sapws_db");
			delete fConf;
		}
		char* outXML = NULL;

		vector<string> theVarPairList;
		for ( map<string,string>::iterator it = inParams.begin() ; it != inParams.end(); it++ )
		{
			string theVarPair = (*it).first + "=" + (*it).second;
			theVarPairList.push_back(theVarPair);
		}
		string theParamListString;
		Join(theVarPairList,'&',theParamListString);
		theParamListString = Utf8ToGbk((char*)theParamListString.c_str());

		dbmanagerProxy theSap(SOAP_XML_TREE,SOAP_XML_TREE);
		theSap.soap_endpoint = sEndPointUrl.c_str();

		PrintLog("Querier-ServiceId[%d] Alias:[%s] ParamsList:[%s]",inServiceId,inAlias,theParamListString.c_str());
		int ret = theSap.QuerierByAlias(inServiceId,inAlias,(char*)theParamListString.c_str(),&outXML);
		if( ret != SOAP_OK )
		{
			PrintLog("Failed to ExeQuerierByAlias.ret:%d",ret);
			return  false;
		}

		if( XMLToDataResult(outXML,outResult) == false )
		{
			PrintLog("Failed to convert xml to result.");
			return false;
		}

		PrintLog("Querier-Result errCode[%d] desc:[%s]",outResult.errCode,outResult.resultDesc.c_str());

		PrintLog("End to ExeQuerierByAlias.");
		return  true;
	}
	catch(...)
	{
		PrintLog("Failed to ExeQuerier.");
		return  false;
	}
}

