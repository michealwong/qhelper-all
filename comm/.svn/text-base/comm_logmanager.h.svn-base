#ifndef __LOGMANAGER_H__
#define __LOGMANAGER_H__


#include "NDS_config.h"

// 调试日志级别
#define LOG_LEVEL_TRACE 0
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARN 3
#define LOG_LEVEL_ERROR 4
#define LOG_LEVEL_FATAL 5

// 监控日志级别
#define LOG_MONITOR_WARN 0		// 警告类
#define LOG_MONITOR_ERROR 1		// 错误类
#define LOG_MONITOR_FATAL 2		// 致命错误类
#define LOG_MONITOR_STAT 3		// 统计类
#define LOG_MONITOR_OTHER 4		// 未分类

// 远端调试日志
#define WRITE_DEBUG_LOG(logLevel,strUser,iGroupId,strLogContent,localLogPath)\	
	CLogManager::GetInstance().WriteDebugLog(logLevel,strUser,iGroupId,strLogContent,localLogPath)

// 写敏感日志
#define WRITE_CM_LOG(strUser,iGroupId,iOptId,iUin,iWorldId,iResult,strOptType,strIP,strSeqId,strPlayerId,strPlayerName,iItemId,iItemCount,strItemDesc,strReason,strMemo)\
	CLogManager::GetInstance().WriteCMLog(strUser,iGroupId,iOptId,iUin,iWorldId,iResult,strOptType,strIP,strSeqId,strPlayerId,strPlayerName,iItemId,iItemCount,strItemDesc,strReason,strMemo)

// 写敏感日志
#define WRITE_CM_LOG_NEW(strUrl,strUser,iGroupId,iOptId,iUin,iWorldId,iResult,strOptType,strIP,strSeqId,strPlayerId,strPlayerName,iItemId,iItemCount,strItemDesc,strReason,strMemo)\
	CLogManager::GetInstance().WriteCMLog(strUrl,strUser,iGroupId,iOptId,iUin,iWorldId,iResult,strOptType,strIP,strSeqId,strPlayerId,strPlayerName,iItemId,iItemCount,strItemDesc,strReason,strMemo)

// 写监控日志
#define WRITE_MONITOR_LOG(logLevel,strUser,iGroupId,iFuncId,strFuncParams,val,iResult)\
	CLogManager::GetInstance().WriteMonitorLog(logLevel,strUser,iGroupId,iFuncId,strFuncParams,val,iResult)

// 发送邮件
#define SEND_EMAIL(mailTo,mailTitle,mailText)\
	CLogManager::GetInstance().SendEmail(mailTo,mailTitle,mailText);

#define SET_ENDPOINT(url)\	
	CLogManager::GetInstance().sEndPointUrl = url

class CLogManager
{
	public:
		CLogManager();
		~CLogManager();
		static string sEndPointUrl;
		static CLogManager& GetInstance();	
		static bool WriteDebugLog(int logLevel,string user,int groupId,string logContent,string localLogPath);
		static bool WriteCMLog(string inUser,
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
			string inCmd="",
			int inSourceId=0,
			string inSerial="");
		static bool WriteCMLog(string inUrl,
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
			string inCmd="",
			int inSourceId=0,
			string inSerial="");
		static bool WriteMonitorLog(int logLevel,string user,int serviceId,int funcId,string funcParams,int val,int result);
		static bool ReadDebugLog(int logLevel,int logType,string user,int groupId, vector< map<string,string> > &oData);
		static bool SendEmail(string mailTo,string mailTitle,string mailText);
	private:
		static void PrintLog(const char *format, ...);
		static void PrintLocalLog(const char* logPath,const char *format, ...);
		static UNIX_config<NDS_single_config_node>* fConf;
		
};

#endif
