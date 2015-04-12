/**
@file log.h

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		Darrenqiu
@version	1.0
@date		2010/10/09

history:
<PRE>
History ID	:	1
Author    	:	asherzhou
DateTime	:	2011/04/29
Description :	Create
</PRE>
*/

#ifndef __LOG_H__
#define	__LOG_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include "msg.h"
//#include "conf.h"


///////////////////////////////tlog ID define///////////////////////////////////////////
#define DEFAULTTLOG "./cfg/tlog.xml"

#define TLOG_TYPE_DBMANAGER			"71_153"		//接口执行前后情况

#define TLOG_TYPE_ROBICSFILTER		"71_155"		//单据过滤模块，运行状态日志
#define TLOG_TYPE_ROBLOGOUTANALYSE	"71_156"		//登出分析模块，运行状态日志
#define TLOG_TYPE_ROBITEMFLOW		"71_157"		//流水过滤模块，运行状态日志
#define TLOG_TYPE_ROBITEMTRACE		"71_158"		//物品追踪模块，运行状态日志
#define TLOG_TYPE_ROBITEMSEND		"71_165"		//物品补送模块，运行状态日志
#define TLOG_TYPE_ROBREPLYAUTO		"71_160"		//盗号二次回复系统

#define TLOG_TYPE_ROBICSOPER		"71_154"		//单据操作类，逻辑处理日志
#define TLOG_TYPE_ROBANLYSVALID		"71_161"		//有效规则分析类，逻辑处理类
#define TLOG_TYPE_ROBRULELOGIC		"71_162"		//逻辑处理日志
#define TLOG_TYPE_ROBANLYSIP		"71_163"		//IP分析类，运行日志
#define TLOG_TYPE_ROBCONF			"71_164"		//rob配置文件解析日志


#define TLOG_LEVEL_DEBUG	0
#define TLOG_LEVEL_INFO		1
#define TLOG_LEVEL_WARNING	2
#define TLOG_LEVEL_ERROR	3

#define TLOG_LEVEL_CONF		10

static int initFlg = 0;						// @add by v_sjwang 2012/10/30 16:39:17
static std::string iServiceId = "229";		// @add by v_sjwang 2012/10/30 16:39:30
static int tlogLevelSign[4] = { 1, 1, 1, 1 };
static char *tlogLevelArr[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

//////////////////////////////////////////////////////////////////////////
#ifdef __cpluscplus
#define STRING_API extern
#else
#define STRING_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	STRING_API  void WriteLogs(char* logId,const char *LogStr,...);
	STRING_API  void WriteLogsT(char* logId,const char *LogStr,...);
	STRING_API  void WriteLogsC(char* conf,char* logId,const char *LogStr,...);
	STRING_API  void WriteLogsCT(char* conf,char* logId,const char *LogStr,...);

	//STRING_API  void WriteLogsIDIPStart(char* logId, const char *ics_id, const char *uin, const char *serviceId, const char *idipId, const char *Parms, ...);
	//STRING_API  void WriteLogsIDIPEnd(char* logId, const char *ics_id, const char *uin, const char *serviceId, const char *idipId, const char *dataNum, const char *errCode, const char *dataResult, ...);
	//STRING_API  void WriteLogsRUN(char* logId, const char *ics_id, const char *uin, const char *serviceId, int logLevel, const char *FuncName, const char *LogStr,...);
	STRING_API  void WriteLogsRUN(char* logId, const char *ics_id, const char *uin, int logLevel, const char *FuncName, const char *LogStr,...); // 去掉serviceId字段，用不到serviceId @modify by v_sjwang 2012/11/13 15:23:04
	
	// add  by windhe for 记录tdwlogdb日志
	STRING_API  void WriteLogstdw(char* serverid,char* ics, char* uin, char* roleid, char* rolename, char* rolelevel,
	char* role_ban, char* world, char* booktime, char* lastLogintime, char* robedtime, char* updatetime,char* vip,
	char* Step, char* result, char* stat, char* Source);
#ifdef __cplusplus
}
#endif
/** 
@class CLog
@brief 
@details 
*/
class CLog
{
public:
	
	/**
	Description:	Default constructor
	@exception		none
	*/
	CLog();
	CLog(const char * LogFile);
	/**
	Description:	Destructor
	*/
	~CLog();

	/**
	Description:	打开文件
	@param	[in]	LogFile
	@return			void
	@exception		none
	*/
	void OpenLog(const char * LogFile);


	/**
	Description:	写日志
	@param	[in]	LogStr
	@param	[in]	
	@return			void
	@exception		none
	*/
	void WriteLog(const char *LogStr,...);


	/**
	Description:	关闭文件
	@return			void
	@exception		none
	*/
	void CloseLog();
	
	/**
	Description:	日志开关
	@return			void
	@exception		none
	*/
	void LogOn();
	void LogOff();

protected:	
	
private:
	FILE  *pstFile;
	int   switchLock;

}; //end CLog


#endif	//__LOG_H__

