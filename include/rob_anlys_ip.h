/**
@file rob_anlys_ip.h

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

#ifndef __ROB_ANLYS_IP_H__
#define	__ROB_ANLYS_IP_H__


#include <string>
#include <map>
#include <vector>

#include "glog.h"
#include "log.h"
#include "msg.h"
#include "conf.h"

using namespace std;


/** 
@class RobAnlysIP
@brief 
@details 
*/
class RobAnlysIP
{
public:
	/**
	Description:	Default constructor
	@exception		none
	*/
	RobAnlysIP();

	/**
	Description:	Destructor
	*/
	~RobAnlysIP();

	
	/**
	Description:	登录日志的内存模块
	*/
	Rob_SLOT LogInOutSlotList;

	/**
	Description:	分析输入的所有的登陆日志，并将全部返回，用于手动
	@param	[in]	t_begin
	@param	[in]	t_end
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	world
	@param	[in]	map<string
	@param	[in]	data
	@return			void
	@exception		none
	*/
	int getRobLogInOutLog(Rob_Ics_Complaint& Ics_Loginout,
		vector< Rob_SLOT >& rob_data);

	/**
	Description:	分析物品流水日志
	@param	[in]	t_begin
	@param	[in]	t_end
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	world
	@param	[in]	map<string
	@param	[in]	data
	@return			void
	@exception		none
	*/

	int getItemFlowLog(const std::string &t_begin,\
		const std::string &t_end, \
		const std::string &uin, \
		const std::string &roleid, \
		const std::string &world, \
		std::vector<map<string,string> > &rob_item_data);



		/**
	Description:	分析宠物流水日志
	@param	[in]	t_begin
	@param	[in]	t_end
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	world
	@param	[in]	map<string
	@param	[in]	data
	@return			void
	@exception		none
	*/
	int getPetFlowLog(const std::string &t_begin, \
		const std::string &t_end, \
		const std::string &uin, \
		const std::string &roleid, \
		const std::string &world, \
		std::vector<map<string,string> > &rob_item_data);

		/**
	Description:	分析装备流水日志
	@param	[in]	t_begin
	@param	[in]	t_end
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	world
	@param	[in]	map<string
	@param	[in]	data
	@return			void
	@exception		none
	*/
	int getArmFlowLog(const std::string &t_begin, \
		const std::string &t_end, \
		const std::string &uin, \
		const std::string &roleid, \
		const std::string &world, \
		std::vector<map<string,string> > &rob_item_data);


protected:
	
private:
	GLog		api_log;	//< 查询游戏日志接口对象
	CLog*		LogInOutLOG;   //< 调试日志
	std::string sLOGINOUTLOG;
	/**
	Description:	输入参数合法性验证
	@param	[in]	begin
	@param	[in]	end
	@return			bool
	@exception		none
	*/
	bool checkValid(time_t begin, time_t end);

	/*
	判断盗号时间规则，两者时间相差不到12小时，则为正常，返回true，否则返回false
	*/
	bool checkRobedTime(time_t t_lastlogin, time_t t_robed, string logouttime);

	/**
	Description:	游戏登陆日志分析逻辑
	@param	[in]	string
	@param	[in]	in_data
	@param	[in]	string
	@param	[in]	err_area
	@return			void
	@exception		none
	*/
	int anaylseData(Rob_Ics_Complaint& Ics_Loginout, vector< map< string,string > >& LogInOutData, vector< Rob_SLOT >& PutOutData);

	/**
	Description:	判断该条日志是否切服登入
	@param	[in]	in_data
	@return			bool 1:切服登入   0：正常上下线
	@exception		none
	*/
	bool filterChangeSvrLogin(std::vector< Rob_SLOT > &rob_data);
}; //end RobAnlysIP



#endif	//__ROB_ANLYS_IP_H__
