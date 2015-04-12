#ifndef __DBMANAGER_H__
#define __DBMANAGER_H__


#include "NDS_config.h"
#include <string>
#include <vector>
#include "log.h"
#include "comm_strings.h"
#include "comm_datetime.h"


using namespace  std;

#define EXE_SQL(dbip,dbuser,dbpwd,dbname,sql,dbCategory,dbport,charset,o)\	
	CDBManager::GetInstance().ExeSql(dbip,dbuser,dbpwd,dbname,sql,dbCategory,dbport,charset,o)

#define EXE_SQL_BY_DATAOPER(dbid,dbname,sql,charset,dbCategory,dbport,o)\	
	CDBManager::GetInstance().ExeSqlByDataOper(dbid,dbname,sql,dbCategory,dbport,charset,o)

#define EXE_SQL_BY_WORLDID(serviceid,worldid,dbtype,dbname,sql,dbCategory,dbport,charset,o)\	
	CDBManager::GetInstance().ExeSqlByWorldId(serviceid,worldid,dbtype,dbname,sql,dbCategory,dbport,charset,o)

#define EXE_MULTI_SQL(dbid,dbname,sqlformat,starttime,endtime,step,charset,o)\	
	CDBManager::GetInstance().ExeMultiSql(dbid,dbname,sqlformat,starttime,endtime,step,charset,o)

#define EXE_QUERIER(header,queryid,paramsmap,o)\	
	CDBManager::GetInstance().ExeQuerier(header,queryid,paramsmap,o)

#define EXE_QUERIER_BY_ALIAS(serviceid,alias,paramsmap,o)\	
	CDBManager::GetInstance().ExeQuerierByAlias(serviceid,alias,paramsmap,o)

#define SET_ENDPOINT(url)\	
	CDBManager::GetInstance().sEndPointUrl = url

#define DataSetToXML(d,x)\
	CDBManager::GetInstance().DataResultToXML(d,x)

#define XMLToDataSet(x,d)\
	CDBManager::GetInstance().XMLToDataResult(x,d)

typedef struct _DataResult
{
	int		errCode;
	int		dataNum;
	string  resultDesc;
	vector<string> dataHead;
	vector< map<string,string> > resultSet;
	string  xml;
}DataResult;

class CDBManager
{
	public:
		CDBManager();
		~CDBManager();
		static string sEndPointUrl;
		
		static CDBManager& GetInstance();		
		static bool ExeSql(char* inDBIP,char* inDBUser,char* inDBPwd,char* inDBName,char* inSqlStatement,char* inDbCategory,int inDBPort,char* inCharset,DataResult& outResult);
		static bool ExeSqlByDataOper(int inDBId,char*  inDBName,char*  inSqlStatement,char* inDbCategory,int inDBPort,char* inCharset,DataResult& outResult);
		static bool ExeMultiSql(int inDBId,char*  inDBName,char* inSQLFormat,long inStartTime,long inEndTime,long inStep,char* inCharset,DataResult& outResult);
		static bool ExeSqlByWorldId(int inServiceId,int inWorldId,int inDBType,char* inDBName,char* inSql,char* inDbCategory,int inDBPort,char* inCharset,DataResult& outResult);
		static bool ExeQuerier(const ics_log_header& header,int inQueryId, map< string,string >& inParams,DataResult& outResult);
		static bool ExeQuerierByAlias(int inServiceId,char* inAlias, map<string,string>& inParams,DataResult& outResult);
		static bool DataResultToXML(DataResult& inResult,string& outXML);
		static bool XMLToDataResult(char* xml,DataResult& outResult);
	private:
		static void PrintLog(const char *format, ...);
		static UNIX_config<NDS_single_config_node>* fConf;
		static DataResult fDataResult;

		//µ˜ ‘»’÷æ
		/*static CLog*  TraceLOG;
		static std::string	MAKEFACELOG;*/
};

#endif
