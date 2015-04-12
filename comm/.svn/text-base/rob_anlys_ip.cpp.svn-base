/**
@file rob_anlys_ip.cpp

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		GunLi
@version	1.0
@date		2010/10/12

history:
<PRE>
History ID	:	1
Author    	:	asherzhou
DateTime	:	2011/05/07
Description :	Alert
</PRE>
*/

#include <iostream>

#include "rob_anlys_ip.h"
#include "iplib.h"
#include "comm_datetime.h"
#include "comm_strings.h"
#include "comm_value.h"

/**
Description:	构造函数
@param	[in]	none
@return			bool
@exception		none
*/
RobAnlysIP::RobAnlysIP()
{
	sLOGINOUTLOG ="./logs/"+GetCurDateDay()+"RobAnlysIP.log";
	LogInOutLOG = new CLog((const char*)sLOGINOUTLOG.c_str());
	LogInOutLOG->LogOn();
}
/**
Description:	析构函数
@param	[in]	none
@return			bool
@exception		none
*/
RobAnlysIP::~RobAnlysIP()
{
	if(NULL!=LogInOutLOG)
	{
		delete LogInOutLOG;
	}
}
/**
Description:	输入参数合法性验证
@param	[in]	begin
@param	[in]	end
@return			bool
@exception		none
*/
bool RobAnlysIP::checkValid(time_t begin, time_t end)
{
	if (begin>end)
	{
		LogInOutLOG->WriteLog("Check LogIn and LogOut Time Value is Invalid\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, "", "", TLOG_LEVEL_ERROR, __FUNCTION__, "Check LogIn and LogOut Time Value is Invalid\n" );
		return false;
	}
	else{
		LogInOutLOG->WriteLog("Check LogIn and LogOut Time Value is Valid\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "Check LogIn and LogOut Time Value is Valid\n" );
		return true;
	}
}
/*
判断盗号时间规则，两者时间相差不到12小时，则为正常，返回true，否则返回false
*/
bool RobAnlysIP::checkRobedTime(time_t t_lastlogin, time_t t_robed, string logouttime)
{
	time_t t_logout;

	GetTmsecFromUnxfmt(t_logout,(logouttime).c_str());

	if (t_logout<t_robed && t_logout>t_lastlogin)
	{
		cout << logouttime << "need" << endl;
		return true;
	}
	else
	{
		cout << logouttime << "no" << endl;
		return false;
	}

}
/**
Description:	游戏登陆日志分析逻辑
@param	[in]	string
@param	[in]	in_data
@param	[in]	string
@param	[in]	err_area
@return			void
@exception		none
*/
#define AREA_TYPE_NUM	7
#define ABNORMAL_TIME_TOTAL		6*60*60
int RobAnlysIP::anaylseData(Rob_Ics_Complaint& Ics_Loginout, std::vector< map<string,string> > &LogInOutData, vector< Rob_SLOT > &PutOutData)
{
	LogInOutLOG->WriteLog("************In getRobLogInOutLog.anaylseData() Proccess! Begin**************\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "************In getRobLogInOutLog.anaylseData() Proccess! Begin**************\n" );

	//用于记录在不同的地区登陆的总的时长
	map <string,unsigned int> mAreaTime;			//记录登录地区的总统计时间
	map <string,unsigned int> mAreaCount;			//记录登录地区的次数
	map <string,unsigned int> mAreaDiffentCount;	//记录登录不同地区的次数
	map <string,string> mIPtoArea;					//记录登录IP对应的区域数
	PutOutData.clear();


	//记录上一条记录中的ip对应的地区
	string sLastArea = "0";
	string sLogIp = "0.0.0.0";
	string sLogIPName = "广东省.深圳市";
	string sIpFlag = "vClientIp";
	string sLoginTime = "0";
	string sLogoutTime = "0";
	string sLoginTimeFlag = "dtLoginTime";
	string sLogoutTimeFlag = "dtEventTime";
	string sLogDuration = "0";
	string sLogDurationFlag = "iOnlineTime";

	int iRobFlag = 0;
	unsigned int from_id = 0;
	unsigned int end_id = LogInOutData.size();



	LogInOutLOG->WriteLog("@@@Begin anaylseData() Traversal Logic Process@@@\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "@@@Begin anaylseData() Traversal Logic Process@@@\n" );
	//首次遍历，IP转化成地域值，同时计算出在同一地区登陆的总时长
	for(unsigned int i = from_id; i < end_id; i++)
	{
		Rob_SLOT LogInOutSlotList;
		sLogIp = LogInOutData[i][(char*)sIpFlag.c_str()];
		sLoginTime = LogInOutData[i][(char*)sLoginTimeFlag.c_str()];
		sLogoutTime = LogInOutData[i][(char*)sLogoutTimeFlag.c_str()];
		sLogDuration = LogInOutData[i][(char*)sLogDurationFlag.c_str()];//从LOG 数据库对应字段取值
		sLogIPName = IPLib::getAreaByIP(sLogIp);
		LogInOutSlotList.ICSID = Ics_Loginout.sICSId;
		LogInOutSlotList.ServiceID = Ics_Loginout.sServiceID;
		LogInOutSlotList.UserID = Ics_Loginout.sUin;
		LogInOutSlotList.WorldID = Ics_Loginout.sWordId;
		LogInOutSlotList.RoleID = Ics_Loginout.sRoleID;
		LogInOutSlotList.RoleName = Ics_Loginout.sRoleName;
		LogInOutSlotList.sBlackRobIp = sLogIp;
		LogInOutSlotList.sRobIPName = sLogIPName;
		LogInOutSlotList.LoginTime = sLoginTime;
		LogInOutSlotList.LogoutTime = sLogoutTime;
		LogInOutSlotList.OnLineTime = sLogDuration;
		LogInOutSlotList.iRobFlag = "0";
			
		PutOutData.push_back(LogInOutSlotList);
		mAreaTime[sLogIPName] += StrToInt(sLogDuration);
	}
	//test begin
	LogInOutLOG->WriteLog("test 异常地域遍历begin\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, 
		"test 异常地域遍历begin\n");

	map <string,unsigned int>::iterator it;
	for(it = mAreaTime.begin(); it != mAreaTime.end(); it++)
	{
		LogInOutLOG->WriteLog("登录地区: %s|总时长: %d(s)\n",it->first.c_str(),it->second);
		WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, 
			"登录地区: %s|总时长: %d(s)\n",it->first.c_str(),it->second);
	}
	LogInOutLOG->WriteLog("test 异常地域遍历over\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, 
		"test 异常地域遍历over\n");
	//test end
	LogInOutLOG->WriteLog("5.<登陆登出信息总条数>iCount=%d\n",PutOutData.size());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "5.<登陆登出信息总条数>iCount=%d\n",PutOutData.size() );
	/*B---标记异常的登录总时长判断mAreaTime
	@	   1.如果总的地域种类数>5返回，无法判断处理；
	@	   2.如果总的地域时长<2小时，为异常登录，大于2小时则为正常,更新异常；
	@	   3.如果玩家没有异常登录时间段，返回异常
	*/
	if(mAreaTime.size() > AREA_TYPE_NUM)
	{
		return STEP_ROBSLOT_RUN_STAT_ERROR_AREAS_EXCEED;
	}
	else if(mAreaTime.size() == 1)
	{
		return STEP_ROBSLOT_RUN_STAT_ERROR_FIND_ROB_SLOT;
	}
	LogInOutLOG->WriteLog("@@@Begin anaylseData() Rob Slot Find Logic Process@@@\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "@@@Begin anaylseData() Rob Slot Find Logic Process@@@\n" );
	for(unsigned int i = 0; i< PutOutData.size(); i++ )
	{
		if (mAreaTime[(char*)PutOutData[i].sRobIPName.c_str()] < ABNORMAL_TIME_TOTAL )
		{
			LogInOutLOG->WriteLog("1.<发现异常登录段>sRobIPName=【%s】&sOnlineSum=【%u】\n",PutOutData[i].sRobIPName.c_str(),mAreaTime[(char*)PutOutData[i].sRobIPName.c_str()]);
			WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "1.<发现异常登录段>sRobIPName=【%s】&sOnlineSum=【%u】\n",PutOutData[i].sRobIPName.c_str(),mAreaTime[(char*)PutOutData[i].sRobIPName.c_str()]);
			PutOutData[i].iRobFlag = "1";
			iRobFlag = 1;
		}
		else
		{
			LogInOutLOG->WriteLog("2.<发现正常登录段>sRobIPName=%s&sOnlineSum=%u\n",PutOutData[i].sRobIPName.c_str(),mAreaTime[(char*)PutOutData[i].sRobIPName.c_str()]);
			WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__,"2.<发现正常登录段>sRobIPName=%s&sOnlineSum=%u\n",PutOutData[i].sRobIPName.c_str(),mAreaTime[(char*)PutOutData[i].sRobIPName.c_str()]);
			PutOutData[i].iRobFlag = "0";
		}
	}
	if(iRobFlag!=1)
	{
		return STEP_ROBSLOT_RUN_STAT_ERROR_FIND_ROB_SLOT;
	}
	LogInOutLOG->WriteLog("************getRobLogInOutLog.anaylseData() Proccess Ended**************\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "************getRobLogInOutLog.anaylseData() Proccess Ended**************\n" );
	return 0;
}

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
int RobAnlysIP::getRobLogInOutLog(Rob_Ics_Complaint& Ics_Loginout, std::vector< Rob_SLOT > &rob_data)
{
	time_t	begin;
	time_t	end;
	//起始时间，终止时间
	//发现被盗时间---最后一次登录时间
	string	s_begin	= Ics_Loginout.stLastLogin;
	string	s_end	= Ics_Loginout.stRobeLogin;

	string	s_uin	= Ics_Loginout.sUin;
	string	s_roleid = Ics_Loginout.sRoleID;
	string	s_wid	= Ics_Loginout.sWordId;
	string  s_rolename = Ics_Loginout.sRoleName;
	//接口的入参和出参
	vector< map<string,string> > data;
	map<string,string> LoginLogoutParam;
	//至少的登出日志条数
	int ThresholdCount = 1;
	int iRes = 0;

#ifdef ylzt
		//因为登录登出日志分开导致必须要修改阀值
		ThresholdCount = 6;
#endif

	GetTmsecFromUnxfmt(begin,(s_begin).c_str());
	GetTmsecFromUnxfmt(end,(s_end).c_str());
	
	//LogInOutLOG->WriteLog("未扩张范围前：Get LogIn and LogOut Time Between Value is %s and %s\n",s_begin.c_str(),s_end.c_str());
	/*将查询登陆日志的时间前后延长10天*/
	GetUnxfmtFromTmsec(s_begin,(begin-8*24*3600));
	GetUnxfmtFromTmsec(s_end,(end+2*24*3600));
	LogInOutLOG->WriteLog("Get LogIn and LogOut Time Between Value is %s and %s\n",s_begin.c_str(),s_end.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "Get LogIn and LogOut Time Between Value is %s and %s\n", s_begin.c_str(), s_end.c_str() );

	/*判断盗号开始时间和结束时间的有效时间*/
	if(!checkValid(begin, end))
	{
		return STEP_ROBSLOT_RUN_STAT_ERROR_TIMESLOT;
	}
	
	/*查询角色登录登出日志*/
	LogInOutLOG->WriteLog("Get LogIn and LogOut Role Info=>|QQ:%s|RoleId:%s|Area:%s|\n",s_uin.c_str(),s_roleid.c_str(),s_wid.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, Ics_Loginout.sICSId.c_str(), Ics_Loginout.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "Get LogIn and LogOut Role Info=>|QQ:%s|RoleId:%s|Area:%s|\n",s_uin.c_str(),s_roleid.c_str(),s_wid.c_str());

	LoginLogoutParam["uin"]        = s_uin;
	LoginLogoutParam["roleid"]     = s_roleid;
	LoginLogoutParam["area"]       = s_wid;
	LoginLogoutParam["start_time"] = s_begin;
	LoginLogoutParam["end_time"]   = s_end;
	int ires = api_log.GetFunction(ics_log_header(Ics_Loginout.sICSId,s_uin,Ics_Loginout.sServiceID),LoginLogoutParam,"login_logout_log",data);
	if (0 != ires)
	{
		LogInOutLOG->WriteLog("Get LogInAndOut Glog Interface Error Res(%d) and DataResult'Size(%d)\n",ires,data.size());
		return STEP_ROBSLOT_RUN_STAT_ERROR_INTERFACE;
	}
	LogInOutLOG->WriteLog("Get LogInAndOut Glog Interface Successfully Res(%d) and DataResult'Size(%d)\n",ires,data.size());
	
	/*玩家的登录登出的日志总条数不能小于ThresholdCount
	if(data.size() < ThresholdCount)
	{
		LogInOutLOG->WriteLog("Get DataResult'Size[%d] Too Small AND Less Than [%d]\n",data.size(),ThresholdCount);
		return STEP_ROBSLOT_RUN_STAT_ERROR_COUNT_SMALL;
	}*/
	//在已查日志中分析异常登录时间

	//////////////////////////////过滤掉切服登入的登出日志////////////////////////////////////////////
	//select iChangSvr from RoleLogin where dtEventTime = $(loginTime) and iUin = $(uin) and iRoleId = $(role_id);
	//filterChangeSvrLogin(rob_data);
	iRes = anaylseData(Ics_Loginout, data, rob_data);
	return iRes;
}


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
int RobAnlysIP::getItemFlowLog(const std::string &t_begin, const std::string &t_end, const std::string &uin, const std::string &roleid, const std::string &world, std::vector<map<string,string> > &rob_item_data)
{
	string	s_begin	= t_begin;
	string	s_end	= t_end;

	string	s_uin	= uin;
	string	s_roleid = roleid;
	string	s_wid	= world;

	/*查询物品流水日志*/
	map<string,string> ItemFlowResultReq;
	LogInOutLOG->WriteLog("Get getItemFlowLog Info=>|QQ:%s|RoleId:%s|Area:%s|Time_Begin:%s|Time_End:%s|\n",s_uin.c_str(),s_roleid.c_str(),s_wid.c_str(),s_begin.c_str(),s_end.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, "", uin.c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "Get getItemFlowLog Info=>|QQ:%s|RoleId:%s|Area:%s|Time_Begin:%s|Time_End:%s|\n",s_uin.c_str(),s_roleid.c_str(),s_wid.c_str(),s_begin.c_str(),s_end.c_str() );
	ItemFlowResultReq["uin"] = s_uin;
	ItemFlowResultReq["gid"] = s_roleid;
	ItemFlowResultReq["area"] = s_wid;
	ItemFlowResultReq["start_date"] = s_begin;
	ItemFlowResultReq["end_date"] = s_end;

	int ires = api_log.GetFunction(ics_log_header("",s_uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),ItemFlowResultReq,"ItemFlow",rob_item_data);
	if (0 != ires)
	{
		LogInOutLOG->WriteLog("Get getItemFlowLog Glog Interface Error Res(%d) and DataResult'Size(%d)\n",ires,rob_item_data.size());
		WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, "", uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "Get getItemFlowLog Glog Interface Error Res(%d) and DataResult'Size(%d)\n",ires,rob_item_data.size() );
		return ires;
	}
	LogInOutLOG->WriteLog("Get getItemFlowLog Glog Interface Successfully Res(%d) and DataResult'Size(%d)\n",ires,rob_item_data.size());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSIP, "", uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "Get getItemFlowLog Glog Interface Successfully Res(%d) and DataResult'Size(%d)\n",ires,rob_item_data.size() );
	
	return 0;
}


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
//int RobAnlysIP::getArmFlowLog(const std::string &t_begin, const std::string &t_end, const std::string &uin, const std::string &roleid, const std::string &world, std::vector<map<string,string> > &rob_item_data)
//{
//	string	s_begin	= t_begin;
//	string	s_end	= t_end;
//
//	string	s_uin	= uin;
//	string	s_roleid = roleid;
//	string	s_wid	= world;
//
//	/*查询物品流水日志*/
//	map<string,string> ItemFlowResultReq;
//	LogInOutLOG->WriteLog("Get getArmFlowLog Info=>|QQ:%s|RoleId:%s|Area:%s|Time_Begin:%s|Time_End:%s|\n",s_uin.c_str(),s_roleid.c_str(),s_wid.c_str(),s_begin.c_str(),s_end.c_str());
//	ItemFlowResultReq["uin"] = s_uin;
//	ItemFlowResultReq["gid"] = s_roleid;
//	ItemFlowResultReq["area"] = s_wid;
//	ItemFlowResultReq["start_date"] = s_begin;
//	ItemFlowResultReq["end_date"] = s_end;
//
//	int ires = api_log.GetFunction(ItemFlowResultReq,"ArmFlow",rob_item_data);
//	if (0 != ires)
//	{
//		LogInOutLOG->WriteLog("Get getArmFlowLog Glog Interface Error Res(%d) and DataResult'Size(%d)\n",ires,rob_item_data.size());
//		return ires;
//	}
//	LogInOutLOG->WriteLog("Get getArmFlowLog Glog Interface Successfully Res(%d) and DataResult'Size(%d)\n",ires,rob_item_data.size());
//	
//	return 0;
//}
//
///**
//Description:	分析宠物流水日志
//@param	[in]	t_begin
//@param	[in]	t_end
//@param	[in]	uin
//@param	[in]	roleid
//@param	[in]	world
//@param	[in]	map<string
//@param	[in]	data
//@return			void
//@exception		none
//*/
//int RobAnlysIP::getPetFlowLog(const std::string &t_begin, const std::string &t_end, const std::string &uin, const std::string &roleid, const std::string &world, std::vector<map<string,string> > &rob_item_data)
//{
//	string	s_begin	= t_begin;
//	string	s_end	= t_end;
//
//	string	s_uin	= uin;
//	string	s_roleid = roleid;
//	string	s_wid	= world;
//
//	/*查询物品流水日志*/
//	map<string,string> ItemFlowResultReq;
//	LogInOutLOG->WriteLog("Get getPetFlowLog Info=>|QQ:%s|RoleId:%s|Area:%s|Time_Begin:%s|Time_End:%s|\n",s_uin.c_str(),s_roleid.c_str(),s_wid.c_str(),s_begin.c_str(),s_end.c_str());
//	ItemFlowResultReq["uin"] = s_uin;
//	ItemFlowResultReq["gid"] = s_roleid;
//	ItemFlowResultReq["area"] = s_wid;
//	ItemFlowResultReq["start_date"] = s_begin;
//	ItemFlowResultReq["end_date"] = s_end;
//
//	int ires = api_log.GetFunction(ItemFlowResultReq,"ArmFlow",rob_item_data);
//	if (0 != ires)
//	{
//		LogInOutLOG->WriteLog("Get getPetFlowLog Glog Interface Error Res(%d) and DataResult'Size(%d)\n",ires,rob_item_data.size());
//		return ires;
//	}
//	LogInOutLOG->WriteLog("Get getPetFlowLog Glog Interface Successfully Res(%d) and DataResult'Size(%d)\n",ires,rob_item_data.size());
//	
//	return 0;
//}
/**
	Description:	判断该条日志是否切服登入
	@param	[in]	in_data
	@return			bool 1:切服登入   0：正常上下线
	@exception		none
*/
bool RobAnlysIP::filterChangeSvrLogin(std::vector< Rob_SLOT > &rob_data){
	bool isChangeSvr = false;
	int iRet = 0;
	string changeSrvFlag("1");//切服标识

	std::map< string, string > mapInParams;//db input
	std::vector< map< string, string > > vecResultLogin;//db output
	std::vector< Rob_SLOT > vecRobData;//after filter
	vecRobData.clear();


	//循环遍历登录时间，以dtLoginTime为where条件，从RoleLogin寻找iChangSvr字段：1 切服；0 正常上线
	for (int k=0; k<rob_data.size(); k++)
	{
		mapInParams.clear();
		vecResultLogin.clear();

		mapInParams["uin"] = rob_data[k].UserID;
		mapInParams["role_id"] = rob_data[k].RoleID;
		mapInParams["area"] = rob_data[k].WorldID;
		mapInParams["dtLoginTime"] = rob_data[k].LoginTime;

		iRet = api_log.GetFunction(ics_log_header(rob_data[k].ICSID,rob_data[k].UserID,rob_data[k].ServiceID),mapInParams,"login_changesrv_query",vecResultLogin);

		if (iRet != 0)
		{
			LogInOutLOG->WriteLog("查询单据【%s】登录时间【%s】切服字段失败，继续下一条查询\n",rob_data[k].ICSID.c_str(),rob_data[k].LoginTime.c_str());
			continue;
		}

		if (vecResultLogin.size() != 0)
		{
			changeSrvFlag = vecResultLogin[0]["iChangSvr"];
			if (changeSrvFlag == "0")//正常上下线
			{
				vecRobData.push_back(rob_data[k]);
				LogInOutLOG->WriteLog("查询单据【%s】登录时间【%s】在RoleLogin表里为正常上线\n",rob_data[k].ICSID.c_str(),rob_data[k].LoginTime.c_str());
			}
		}else
		{
			LogInOutLOG->WriteLog("查询单据【%s】登录时间【%s】在RoleLogin表里无登录记录，继续下一条查询\n",rob_data[k].ICSID.c_str(),rob_data[k].LoginTime.c_str());
			continue;
		}
	}
	rob_data = vecRobData;//返回筛选后的

	return true;
}