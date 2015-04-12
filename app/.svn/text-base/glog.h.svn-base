/**
@file glog.h

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		Darrenqiu
@version	1.0
@date		2010/10/12

history:
<PRE>
History ID	:	1
Author    	:	Darrenqiu
DateTime	:	2010/10/12
Description :	Create
</PRE>
*/

#ifndef __GLOG_H__
#define	__GLOG_H__

// SYSTEM INCLUDES
#include <string>
#include <vector>
#include <map>
// STANDERD INCLUDES
// APPLICATION INCLUDES
#include "conf.h"
// USING NAMESPACES
using namespace std;
// DEFINES
// MACROS
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STRUCTS
// TYPEDEFS
// FORWARD DECLARATIONS


/** 
@class GLog
@brief 
@details 
*/
class GLog
{
public:

	GLog(){};
	~GLog(){};

	/**
	Description:	填单
	@param	[in]	world
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	rolelevel
	@param	[in]	lastlogintime
	@param	[in]	createTime
	@param	[in]	roberedtime
	@param	[in]	icsid
	@return			int
	@exception		none
	*/
	int SaveIcsInfo(const string& world,
		const string& uin,
		const string& roleid,
		const string& rolelevel,
		const string& lastlogintime,
		const string& createTime,
		const string& roberedtime,
		const string& icsid);

	/**
	Description:	根据ICS单号拉取填单信息
	默认拉取未处理，但是经过单据合法分析的单据信息
	@param	[in]	icsid		ICS单号	
	@param	[in]	result		返回结果
	@param	[in]	hand_res	处理状态，0表示未处理
	@param	[in]	anaylse_res	分析状态，6表示经单据合法性分析可以自动分析处理
	@return			int
	@exception		none
	*/
	int GetIcsInfoByID(const string& icsid, vector< map<string,string> >& result,const string& hand_res="0", const string& anaylse_res="6");

	int GetIcsInfo(vector< map<string,string> >& result);

	/**
	Description:	保存物品流水分析后的状态
	@param	[in]	spoilid		赃物记录ID
	@param	[in]	datetime	物品追踪到时间点
	@param	[in]	state		物品追踪结果状态
	@return			int
	@exception		none
	*/
	int SaveSpoilState(const string& spoilid, const string& datetime, const string& state="1");

	int UpdateIcsState(const string& incsid, const string& state="1");

	int GetRobSpoil(ics_info& info, std::vector< std::map<std::string, std::string> >& result);

	int SaveTracedSpoil(const string& world, spoil_info& info, const string& flag="0");

	int SaveSpoil(ics_info& ics, spoil_info& spoil);

	void WriteSpoilFromFlow(map<string,string>& in_data, spoil_info& out_data);




	int GetLog(const string& world, const string& sql, std::vector< std::map<std::string, std::string> >& result);

	/**
	Description:	得到角色登出日志
	@param	[in]	world
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	begintime
	@param	[in]	endtime
	@param	[in]	std::map<std::string
	@param	[in]	result
	@return			int
	@exception		none
	*/
	int GetLogoutLog(const string& world,\
		const string& uin, \
		const string& roleid, \
		const string& begintime, \
		const string& endtime, \
		std::vector< std::map<std::string, std::string> >& result);

	int GetFlowLog(const string& world, spoil_info& info, std::vector< std::map<std::string, std::string> >& result);

	int GetSpoilLog(const string& world, const string& sql, vector< map<string,string> >&result);

protected:
	
private:

}; //end GLog


#endif	//__GLOG_H__
