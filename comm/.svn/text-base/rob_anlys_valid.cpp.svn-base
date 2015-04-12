/**
@file rob_anlys_valid.cpp

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		GunLi
@version	1.0
@date		2010/10/22

history:
<PRE>
History ID	:	1
Author    	:	GunLi
DateTime	:	2010/10/22
Description :	Create
</PRE>
*/

#include "rob_anlys_valid.h"
#include "iplib.h"
#include "comm.h"
#include "comm_datetime.h"
#include "comm_logmanager.h"


RobRuleValid::RobRuleValid()
{
	MAKEVALIDLOG="./logs/"+GetCurDateDay()+"QhelperRuleValid.log";
	ValidLOG = new CLog((const char*)MAKEVALIDLOG.c_str());
	ValidLOG->LogOn();
	iRet = 0;
}

RobRuleValid::~RobRuleValid()
{
	if (NULL != ValidLOG)
	{
		delete ValidLOG;
	}
}



/**   receive_doble天内重复来单不受理； 用户暂定为1天
* 		params:		ics_info
* 		return:		int
*/
int RobRuleValid::ProCheckDobleQuest(Qhelper_Ics_Complaint &ics_info)
{
	map<string,string> theParamIn;
	theParamIn.clear();
	//解析vCommand字符串
	std::map<string, string> dst_opData;
	std::string src_cmd = ics_info.vCommand;
	string flag = "& = ";
	SplitToMap(src_cmd, dst_opData, flag, (unsigned int)2); 	
	ValidLOG->WriteLog("in Valid Proccess,ProCheckDobleQuest-IcsInfo==|ICSID:%s| dst_opData[area]:%s | dst_opData[role_id]:%s|iParam_Num:%s\n",ics_info.sICSId.c_str(), dst_opData["area"].c_str(), dst_opData["role_id"].c_str(), ics_info.sParaNum.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(),  dst_opData["role_id"].c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "in Valid Proccess,ProCheckDobleQuest-IcsInfo\n" );

	theParamIn["uin"] = dst_opData["uin"];
	theParamIn["apply_day_in"] = CRobConf::getConf()->GetIcsValid()["receve_double"];  //一天内
	theParamIn["service_id"] = ics_info.sServiceID;
#ifdef dnf2
	//调试阶段以role_name代替role_id
	theParamIn["role_id"] = string(GbkToUtf8((char*)dst_opData["role_name"].c_str()));
#endif
	vector< map<string,string> > base_result;
	theParamIn["role_id"] = dst_opData["rold_id"];

	//ics_log_header header(info.sICSId,info.sUin,info.sServiceID);
	ics_log_header header(ics_info.sICSId,"",ics_info.sServiceID);
	if(0 != valid_parse.GetFunction(header,theParamIn,"ics_apply_repeat_uin",base_result))
	{
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'ics_apply_repeat_uin' happened error,not find info\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'get_ics_info_by_uin' happened error,not find info\n" );
		return STEP_FLITER_RUN_STAT_ERROR_INTERFACE;
	}

	//////////////////////////////////added by v_zhtang on 2012-11-20////////////////////////////////////////
	int check_flag=0;
	int check_running_flag=0;
	int check_false_flag=0;
	int check_result=0;

	if(base_result.size()>1){
		for(int i=0;i<base_result.size();i++){
			ValidLOG->WriteLog("[Info]'ProCheckDobleQuest' Proccessing <%d>&iICSAnaylseResult=<%s>\n",base_result.size(),base_result[i]["sDesc"].c_str());
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info]'ProCheckDobleQuest' Proccessing <%d>&iICSAnaylseResult=<%s>\n",base_result.size(),base_result[i]["sDesc"].c_str() );
			//a 如果存在处理成功的---：此单据为异常单据《重复单据》
			if(StrToInt(base_result[i]["sDesc"])==STEP_FLITER_RUN_STAT_SUCCESS)
			{
				ValidLOG->WriteLog("[Info] [QhelperRuleValid::ProCheckDobleQuest] Get The Fromer icsID Result<%s>, Process Pass Fliter Ok, So Not Pass It\n",base_result[i]["sDesc"].c_str());
				WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "[Info] [QhelperRuleValid::ProCheckDobleQuest] Get The Fromer icsID Result<%s>, Process Pass Fliter Ok, So Not Pass It\n",base_result[i]["sDesc"].c_str() );
				return (STEP_FLITER_RUN_STAT_ERROR_APPLY_AGAIN);
			}
			//a.1 如果存在在阶段的处理的流程中的单据
			if(StrToInt(base_result[i]["sDesc"]) ==STEP_FLITER_RUNNING_STAT)
			{
				ValidLOG->WriteLog("[Info] [QhelperRuleValid::ProCheckDobleQuest] Runing AND False=[%s]\n",base_result[i]["sDesc"].c_str());
				{
					check_result++;
					ValidLOG->WriteLog("[Info] [QhelperRuleValid::ProCheckDobleQuest] Running=%s&check_result=%d\n",base_result[i]["sDesc"].c_str(),check_result);
					WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(),  dst_opData["uin"].c_str(), TLOG_LEVEL_WARNING, __FUNCTION__, "[Info] [QhelperRuleValid::ProCheckDobleQuest] Running=%s&check_result=%d\n",base_result[i]["sDesc"].c_str(),check_result );
				}
			}
			//a.2 如果存在在一次处理多的单据
			if(StrToInt(base_result[i]["sICSAnaylseStatus"])==STEP_FLITER_RUNNING_STAT)
			{
				check_running_flag++;
				ValidLOG->WriteLog("[Info] [QhelperRuleValid::ProCheckDobleQuest] LOT APPLY=%d",check_running_flag);
				WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_WARNING, __FUNCTION__, "[Info] [QhelperRuleValid::ProCheckDobleQuest] LOT APPLY=%d",check_running_flag );
			}
		}
		//如果存在各阶段处理中的单据
		if(check_result>0){
			return STEP_FLITER_RUN_STAT_ERROR_INTERFACE;
		}
		//如果所有的单据的都是在第一个阶段的单据
		if(check_running_flag>1){
			ValidLOG->WriteLog("[Info] [QhelperRuleValid::ProCheckDobleQuest] STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT,So Pass Last It ,check_flag=<%d>\n",check_running_flag);
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_WARNING, __FUNCTION__, "[Info] [QhelperRuleValid::ProCheckDobleQuest] STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT,So Pass Last It ,check_flag=<%d>\n",check_running_flag );
			return STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT;
		}else if(check_running_flag==1){
			ValidLOG->WriteLog("[Info] [QhelperRuleValid::ProCheckDobleQuest] STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT,So I am The Last One ,check_flag=<%d>\n",check_running_flag);
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info] [QhelperRuleValid::ProCheckDobleQuest] STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT,So I am The Last One ,check_flag=<%d>\n",check_running_flag );
			return 0;
		}
		return 0;//其它情况 返回正常
	}else if(base_result.size()==1){
		ValidLOG->WriteLog("[Info] [QhelperRuleValid::ProCheckDobleQuest] The Fisrt Processing Only One, So Pass It\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info] [QhelperRuleValid::ProCheckDobleQuest] The Fisrt Processing Only One, So Pass It\n" );
		return 0;
	}else{
		ValidLOG->WriteLog("[QhelperRuleValid::ProCheckDobleQuest] The <ics_apply_repeat_uin> Processing Interface Error\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "[QhelperRuleValid::ProCheckDobleQuest] The <ics_apply_repeat_uin> Processing Interface Error" );
		return STEP_FLITER_RUN_STAT_ERROR_INTERFACE;
	}
}


/**	返回Master的ics的check过滤函数, 工会信息查询
*   params:		ics_info
* 	return:		int
*/
int RobRuleValid::ProCheckIsMaster(Qhelper_Ics_Complaint& ics_info)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	int iRoleMasterFlag = 0;
	//解析vCommand字符串
	std::map<string, string> dst_opData;
	std::string src_cmd = ics_info.vCommand;
	string flag = "& = ";
	SplitToMap(src_cmd, dst_opData, flag, (unsigned int)2); 	
	ValidLOG->WriteLog("in Valid Proccess,ProCheckIsMaster-IcsInfo==|ICSID:%s| dst_opData[area]:%s | dst_opData[uin]:%s|iParam_Num:%s\n",ics_info.sICSId.c_str(), dst_opData["area"].c_str(), dst_opData["uin"].c_str() );

	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(),  dst_opData["uin"].c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "in Valid Proccess,ProCheckIsMaster-IcsInfo\n ");

	theParamIn["area"]=dst_opData["area"];
	theParamIn["guild_id"]= dst_opData["guild_id"];
	theParamIn["guild_name"]= "";

	ics_log_header header(ics_info.sICSId,dst_opData["uin"],ics_info.sServiceID);
	iRet = valid_parse.GetFunction(header,theParamIn,"guild_info",theGetResult);//编码：无转换 获取。即url编码
	ValidLOG->WriteLog("In Valid Proccess,DoICSSProCheckIsMaster--guild_info-iRet=%d\n",iRet);
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "In Valid Proccess,DoICSSProCheckIsMaster--guild_info-iRet=%d\n", iRet );
	for(int i = 0;i<theGetResult.size();i++)
	{
		ValidLOG->WriteLog("获取玩家ID：%s|填单ID：%s\n",theGetResult[i]["master_no"].c_str(),dst_opData["role_id"].c_str());
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), "", TLOG_LEVEL_DEBUG, __FUNCTION__, "获取玩家ID：%s|填单ID：%s\n",theGetResult[i]["master_no"].c_str(),dst_opData["role_id"].c_str() );

		//判断是否为会长
		if(theGetResult[i]["master_no"]==dst_opData["uin"])
		{
			iRoleMasterFlag = 1;
			ValidLOG->WriteLog("获取工会等级：%s|角色id:%s| 角色名字：%s\n",theGetResult[i]["lev"].c_str(),theGetResult[i]["master_no"].c_str(), theGetResult[i]["master_name"].c_str());
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "获取工会等级：%s|角色id:%s| 角色名字：%s\n",theGetResult[i]["lev"].c_str(),theGetResult[i]["master_no"].c_str(), theGetResult[i]["master_name"].c_str() );
			return iRoleMasterFlag;
		}
		else
		{
			continue; 
		}
	}

	return 0;
}

/**		查询log是否有转服记录
*		params:		ics_info
*		return:		int 
*
*/
int RobRuleValid::ProCheckTransSvrInfo(Qhelper_Ics_Complaint& info)
{
	map<string,string> theParamIn;
	vector< map<string,string> > theResult;

	//解析vCommand字符串
	std::map<string, string> dst_opData;
	std::string src_cmd = info.vCommand;
	string flag = "& = ";
	SplitToMap(src_cmd, dst_opData, flag, (unsigned int)2); 	

	theParamIn.clear();
	theParamIn["area"] = dst_opData["area"];
	theParamIn["uin"] = dst_opData["uin"];

	ics_log_header header(info.sICSId, dst_opData["uin"],info.sServiceID);
	if(0 != valid_parse.GetFunction(header,theParamIn,"ics_user_trans_svr",theResult))
	{
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'ics_user_trans_svr' happened error,not find info\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'ics_user_trans_svr' happened error,not find info\n" );
		return -1;
	}else
	{
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'ics_user_trans_svr' success!\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "In Valid Proccess, Find Uin 'ics_user_trans_svr' success!\n" );
		return theResult.size();
	}

}

/**   调用idip接口查找vip信息
* 		params:		ics_info
* 		return:		int
*/
int RobRuleValid::ProCheckVIPInfo(Qhelper_Ics_Complaint& info)
{
	
	map<string,string> theParamIn;
	vector< map<string,string> > theResult;

	//解析vCommand字符串
	std::map<string, string> dst_opData;
	std::string src_cmd = info.vCommand;
	string flag = "&=";
	SplitToMap(src_cmd, dst_opData, flag, (unsigned int)2); 	

	ValidLOG->WriteLog("In Valid Proccess, --->ProCheckVIPInfo  单号: %s| qq号码: %s !\n", info.sICSId.c_str(), dst_opData["uin"].c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "In Valid Proccess, Find Uin 'get_vip_info' success!\n" );

	theParamIn.clear();
	theParamIn["business"] = "sap";
	theParamIn["uin"] = dst_opData["uin"];
	/*
	 *	
	 <items>
	 <field name="active_type"><![CDATA[0]]></field>
	 <field name="begin_date"><![CDATA[2011-07-01]]></field>
	 <field name="flag"><![CDATA[1]]></field>
	 <field name="point"><![CDATA[0]]></field>
	 <field name="result"><![CDATA[0]]></field>
	 <field name="tgclub_ret"><![CDATA[1]]></field>
	 <field name="type"><![CDATA[0]]></field>
	 <field name="uin"><![CDATA[28063498]]></field>
	 <field name="vaild_date"><![CDATA[2030-12-31]]></field>
	 </items>

	 */
	ics_log_header header(info.sICSId, dst_opData["uin"],info.sServiceID);
	if(0 != valid_parse.GetFunction(header,theParamIn,"get_vip_info",theResult))
	{
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'get_vip_info' happened error,not find info\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'get_vip_info' happened error,not find info\n" );
		return -1;
	}else
	{
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'get_vip_info' success!\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "In Valid Proccess, Find Uin 'get_vip_info' success!\n" );
		info.vCommand += "&vip_level="+theResult[0]["type"];
		return theResult[0]["type"] == "0" ? 0 : 1;
	}

}

/**********************************************************************************
Description:	玩家的角色基本信息更新
@param	[in]	info
@return			int
@exception		none
*/
int RobRuleValid::DoICSSetRoleInfoPro(Qhelper_Ics_Complaint& ics_info)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	int iRoleExistFlag = 0;
	ValidLOG->WriteLog("In Valid Proccess,DoICSSetRoleInfoPro-IcsInfo==|ICSID:%s|iKind:%s|vCommand:%s|iParam_Num:%s\n",ics_info.sICSId.c_str(),ics_info.sKindID.c_str(),ics_info.vCommand.c_str(), ics_info.sParaNum.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "In Valid Proccess,DoICSSetRoleInfoPro-IcsInfo==|ICSID:%s|iKind:%s|vCommand:%s|iParam_Num:%s\n",ics_info.sICSId.c_str(),ics_info.sKindID.c_str(),ics_info.vCommand.c_str(), ics_info.sParaNum.c_str() );

	//第一步角色基本信息更新：角色名字和等级
	//Code From Here Only For dnf2

	//解析vCommand字符串
	std::map<string, string> dst_opData;
	std::string src_cmd = ics_info.vCommand;
	string flag = "&=";
	SplitToMap(src_cmd, dst_opData, flag, (unsigned int)2); 	

	ValidLOG->WriteLog("解析vCommand字符串, 获得用户服务器, 角色ID, src_cmd: %s | dst_opData[type]:%s | dst_opData[area]:%s | dst_opData[role_id]:%s|iParam_Num:%s\n",src_cmd.c_str(),dst_opData["type"].c_str(),dst_opData["area"].c_str(), dst_opData["role_id"].c_str(), ics_info.sParaNum.c_str() );
	//ics_get_role_list
	ValidLOG->WriteLog("In [dnf2] Proccess,前言 准备：角色列表\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(),  dst_opData["role_id"].c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "In [dnf2] Proccess,前言 准备：角色列表\n" );


	theParamIn["area"]=dst_opData["area"];
	theParamIn["uin"]="";
	theParamIn["role_name"]="";
	theParamIn["role_id"]= dst_opData["role_id"];
	ics_log_header header(ics_info.sICSId,"",ics_info.sServiceID);
	iRet = valid_parse.GetFunction(header,theParamIn,"ics_get_role_info",theGetResult);//角色id查询信息
	if (!iRet)
	{
		for ( int i = 0; i < theGetResult.size(); i++)
		{
			ValidLOG->WriteLog("填单ID：%s| 获取玩家QQ：%s|角色ID：%s| 角色等级： %s| 工会ID:%s\n",ics_info.sICSId.c_str(),theGetResult[i]["m_id"].c_str(), theGetResult[i]["charac_no"].c_str(), theGetResult[i]["lev"].c_str(), theGetResult[i]["guild_id"].c_str());
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "填单ID：%s| 获取玩家QQ：%s|角色ID：%s| 角色等级： %s| 工会ID:%s\n",ics_info.sICSId.c_str(),theGetResult[i]["m_id"].c_str(), theGetResult[i]["charac_no"].c_str(), theGetResult[i]["lev"].c_str(), theGetResult[i]["guild_id"].c_str() );
			if(theGetResult[i]["charac_no"]==dst_opData["role_id"])
			{
				dst_opData["uin"]=theGetResult[i]["m_id"];
				std::string sUin = theGetResult[i]["m_id"];
				std::string sRole_Id = theGetResult[i]["charac_no"];
				std::string sRole_Name = theGetResult[i]["charac_name"];
				std::string sRole_Level = theGetResult[i]["lev"];
				std::string sGuild_Id = theGetResult[i]["guild_id"];

				//将信息连接到vCommand后
				ics_info.vCommand += "&uin="+sUin;
				ics_info.vCommand += "&role_id="+sRole_Id;
				ics_info.vCommand += "&role_name="+sRole_Name;
				ics_info.vCommand += "&role_level="+sRole_Level;
				ics_info.vCommand += "&guild_id="+sGuild_Id;
				
				iRoleExistFlag = 1;
				ValidLOG->WriteLog("角色id查询信息cmd=%s| 获取玩家等级：%s|角色名字：%s\n",ics_info.vCommand.c_str(),sRole_Level.c_str(),sRole_Name.c_str());
				WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "角色id查询获取玩家等级：%s|角色名字：%s\n", sRole_Level.c_str(), sRole_Name.c_str() );
			}
		}
	}
	
	if(iRoleExistFlag == 0)
	{

		if(0 <= theGetResult.size())
		{
			string strError = theGetResult[0]["result"];
			if("-1999" == strError)//停服
			{
				ValidLOG->WriteLog("当前大区[%s]停服中\n",ics_info.sServiceID);
				WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), "", TLOG_LEVEL_ERROR, __FUNCTION__, "当前大区[%s]停服中\n", ics_info.sServiceID.c_str() );
				return -12;
			}else
			{
				ValidLOG->WriteLog("没有找到相关玩家角色信息\n");
				WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), "", TLOG_LEVEL_WARNING, __FUNCTION__, "没有找到相关玩家角色信息\n" );
				return STEP_FLITER_RUN_STAT_ERROR_ROLE_INFO_NEW;
			}
		}
	}

	//角色基本信息更新：角色VIP信息
	theParamIn.clear();
	theGetResult.clear();
#ifdef dnf2
	ValidLOG->WriteLog("In [dnf2] Proccess,第三步角色基本信息更新：角色VIP信息\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "In [dnf2] Proccess,第三步角色基本信息更新：角色VIP信息\n");

	ProCheckVIPInfo(ics_info);
#endif
	return 0;

}

/**********************************************************************************
 * *	靠LEVEL縤cs縞heck靠靠
 * *   params:		ics_info
 * * 	return:		int
 * */
int RobRuleValid::ProCheckRoleLevel(Qhelper_Ics_Complaint& info)
{
	//靠縱Command靠靠靠
	//靠vCommand靠?
	std::map<string, string> dst_opData;
	std::string src_cmd = info.vCommand;
	string flag = "& = ";
	SplitToMap(src_cmd, dst_opData, flag, (unsigned int)2); 
	return (StrToInt(dst_opData["role_level"]) < StrToInt(CRobConf::getConf()->GetIcsValid()["role_level"]))?1:0;
}

/*
//Description:	验证单据的合法性
				@param	[in]	info
				@return			int
				@exception		none
*/
int RobRuleValid::DoICSCheckPro(Qhelper_Ics_Complaint& ics_info)
{
	ValidLOG->WriteLog("In Valid Proccess,IcsInfo==|ICSID:%s|sServiceID:%s | sKindID:%s| vCommand:%s | sParaNum:%s \n",ics_info.sICSId.c_str(),ics_info.sServiceID.c_str(), ics_info.sKindID.c_str(), ics_info.vCommand.c_str(), ics_info.sParaNum.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "In Valid Proccess,IcsInfo==|ICSID:%s|UIN:%s|\n", ics_info.sICSId.c_str(),ics_info.sServiceID.c_str(), ics_info.sKindID.c_str(), ics_info.vCommand.c_str(), ics_info.sParaNum.c_str() );
	//A 首先进行相关的玩家数据更新
	iRet = DoICSSetRoleInfoPro(ics_info);
	std::map<string, string> dst_opData;
	std::string src_cmd = ics_info.vCommand;
	string flag = "&=";
	SplitToMap(src_cmd, dst_opData, flag, (unsigned int)2); 	
	if(iRet!=0){
		ValidLOG->WriteLog("玩家基本信息更新出错，错误码【%d】\n",iRet);
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), "", TLOG_LEVEL_ERROR, __FUNCTION__, "玩家基本信息更新出错，错误码【%d】\n", iRet );
		return iRet;
	}
	ValidLOG->WriteLog("玩家基本信息更新正确，返回码【%d】\n", iRet);
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "玩家基本信息更新正确，返回码【%d】\n", iRet );
	ValidLOG->WriteLog("In Valid Proccess,玩家基本信息更新正确--IcsInfo==>>>|ICSID:%s|UIN:%s|sRoleID:%s|sRoleName:%s|sRoleLevel:%s\n",\
		ics_info.sICSId.c_str(),\
		dst_opData["uin"].c_str(),\
		dst_opData["role_id"].c_str(),\
		dst_opData["role_name"].c_str(),\
		/*ics_info.sIsVip.c_str(),*/\
		dst_opData["role_level"].c_str()\
		/*ics_info.siRobedRoleBan.c_str()*/);
	

	
	//TODO
	// 核心逻辑处理
	if ((iRet = ProCheckVIPInfo(ics_info)) != 0/*判断是否为vip用户*/)
	{
		if ((iRet = ProCheckTransSvrInfo(ics_info)) != 0 /*没有转服记录*/)
		{
			if ((iRet =ProCheckIsMaster(ics_info)) != 0/*不是工会会长*/)
			{
				if ((iRet=ProCheckDobleQuest(ics_info)) !=0)
				{
					// 1天内重复来单
					ValidLOG->WriteLog("In Valid Proccess, Find Uin 'ProCheckDobleQuest' is   1天内重复来单\n");
					WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'ProCheckDobleQuest' is 1天内重复来单\n" );
					return iRet;
				} // 24小时内受理记录
				else
				{
					// 删除/恢复角色, 调用idip接口

				} //超过一天
			}
			else
			{
				//是工会会长, 不予恢复删除
				return STEP_FLITER_RUN_STAT_ERROR_LEADER_NEW;
			}
		} //没有转服记录
		else
		{
			return STEP_FLITER_RUN_STAT_ERROR_TRANS_SVR_NEW;
			// 不予恢复/删除
		} //有转服记录
	}
	else
	{
		if (0 != ProCheckRoleLevel(ics_info)){
			// 用户等级不符合分析要求 < 18级
			ValidLOG->WriteLog("In Valid Proccess, Find Uin 'ProCheckRoleLevel' is 用户等级不符合分析要求\n");
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'ProCheckRoleLevel' is 用户等级不符合分析要求\n" );
			return STEP_FLITER_RUN_STAT_ERROR_LEVEL_NEW;
		}
		else
		{
			//走流程
		}
	}

	ValidLOG->WriteLog("In Valid Proccess, Find Uin 'DoICSCheck' is  valid ,Go to Auto Process\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), dst_opData["uin"].c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'DoICSCheck' is  valid ,Go to Auto Process\n" );
	//自助处理完成
	return STEP_FLITER_RUN_STAT_SUCCESS_NEW;
}



/************************************************************************/
/* **********************************************************************/
/************************************************************************/


/**********************************************************************************
Description:	玩家的角色基本信息更新
@param	[in]	info
@return			int
@exception		none
*/
int RobRuleValid::DoICSSetRoleInfoPro(Rob_Ics_Complaint& ics_info)
{
	map<string, string> theParamIn;
	vector < map<string, string> > theGetResult;
	int iRoleExistFlag = 0;
	ValidLOG->WriteLog("单据过滤，验证单据有效性，单据信息：ICSID:%s|UIN:%s|Role_ID:%s\n", ics_info.sICSId.c_str(), ics_info.sUin.c_str(), ics_info.sRoleID.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "单据过滤，验证单据有效性，单据信息：ICSID:%s|UIN:%s|Role_ID:%s\n", ics_info.sICSId.c_str(), ics_info.sUin.c_str(), ics_info.sRoleID.c_str());

	//第一步角色基本信息更新：角色名字和等级
	ValidLOG->WriteLog("获取角色列表\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "获取角色列表\n");
	theParamIn["area"] = ics_info.sWordId;
	theParamIn["uin"]  = ics_info.sUin;
	iRet = valid_parse.GetFunction(ics_log_header(ics_info.sICSId, ics_info.sUin, ics_info.sServiceID), theParamIn, "ics_get_role_list", theGetResult);

	ValidLOG->WriteLog("获取角色列表，完成，结果：%d\n", iRet);
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "获取角色列表，完成，结果：%d\n", iRet);

	for (int i = 0; i < theGetResult.size(); i++)
	{
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "获取玩家ID：%s|填单ID：%s\n", theGetResult[i]["name_0"].c_str(), ics_info.sRoleID.c_str());
		if (theGetResult[i]["name_0"] == ics_info.sRoleID)
		{
			ics_info.sRoleName = theGetResult[i]["name_1"];
			iRoleExistFlag = 1;
			ValidLOG->WriteLog("获取玩家角色名：%s|角色ID：%s\n", ics_info.sRoleName.c_str(), ics_info.sRoleID.c_str());
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "获取玩家等级：%s|角色ID：%s\n", ics_info.sRoleLevel.c_str(), ics_info.sRoleID.c_str());
		}
	}

	if (0 == iRoleExistFlag)
	{
		ValidLOG->WriteLog("没有找到相关玩家角色信息\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_WARNING, __FUNCTION__, "没有找到相关玩家角色信息\n");
		return STEP_FLITER_RUN_STAT_ERROR_ROLE_INFO;
	}


	//第二步角色基本信息更新：【IDIP】
	theParamIn.clear();
	theGetResult.clear();

#ifdef fzr
	ValidLOG->WriteLog("In [fzr] Proccess,第二步角色基本信息更新：角色封号信息\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "In [dj2] Proccess,第二步角色基本信息更新：角色封号信息\n");

	//theParamIn["charac_no"] = ics_info.sRoleID;
	theParamIn["world_id"] = ics_info.sWordId;
	theParamIn["uin"] = ics_info.sUin;
#endif
	iRet = valid_parse.GetFunction(ics_log_header(ics_info.sICSId, ics_info.sUin, ics_info.sServiceID), \
		theParamIn, "ics_get_role_ban_info", theGetResult);
	ValidLOG->WriteLog("In Valid Proccess,DoICSSetRoleInfoPro-ics_get_role_ban_info-iRet=%d\n", iRet);
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "In Valid Proccess,DoICSSetRoleInfoPro-ics_get_role_ban_info-iRet=%d\n", iRet);

	if (iRet != 0 || theGetResult.size() != 1)
	{
		return STEP_FLITER_RUN_STAT_ERROR_ROLE_INFO;
	}
	else
	{
		//ics_info.sRoleLevel = theGetResult[0]["level"];
		string stop_time = theGetResult[0]["ban_end_time"];
		time_t now_time = time(0);
		string strNTime = LLongToStr(now_time);
		ValidLOG->WriteLog("In [fzr] Proccess,DoICSSetRoleInfoPro-ics_get_role_ban_info-stop_time=%s\n", stop_time.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_WARNING, __FUNCTION__, "In [fzr] Proccess,DoICSSetRoleInfoPro-ics_get_role_ban_info-stop_time=%s\n", stop_time.c_str());

		//如果查询到的时间为0，则未封
		if (stop_time < strNTime)
		{
			ics_info.siRobedRoleBan = "0";
		}
		//如果查询到的时间大于0，则已封，表封停时间
		else
		{
			ics_info.siRobedRoleBan = "1";//已封号
		}
	}
	//第三步角色基本信息更新：角色VIP信息
	 theParamIn.clear();
	 theGetResult.clear();
#ifdef fzr
	 	ValidLOG->WriteLog("In [fzr] Proccess,第三步角色基本信息更新：角色VIP信息\n");
	 	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_WARNING, __FUNCTION__, "In [fzr] Proccess,第三步角色基本信息更新：角色VIP信息\n");
	
		//获取被盗用户的VIP 信息
		int iIsVip = ProCheckVIPInfo(ics_info);
		if(-1 == iIsVip)     // 如果获取VIP信息失败则当普通用户来处理
		{
			ics_info.sIsVip = "0";      
		}
		else
		{
			ics_info.sIsVip = IntToStr(iIsVip);
		}


#endif
	return 0;
}

/**********************************************************************************
Description:	验证单据的合法性
@param	[in]	info
@return			int
@exception		none
*/
int RobRuleValid::DoICSCheckPro(Rob_Ics_Complaint& ics_info)
{
	ValidLOG->WriteLog("单据过滤，单据信息：ICSID:%s|UIN:%s|\n", ics_info.sICSId.c_str(), ics_info.sUin.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "单据过滤，单据信息：ICSID:%s|UIN:%s|\n", ics_info.sICSId.c_str(), ics_info.sUin.c_str());
	//A 首先进行相关的玩家数据更新
	iRet = DoICSSetRoleInfoPro(ics_info);
	if (iRet != 0)
	{
		ValidLOG->WriteLog("玩家基本信息更新出错，错误码【%d】\n", iRet);
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "玩家基本信息更新出错，错误码【%d】\n", iRet);
		return iRet;
	}
	ValidLOG->WriteLog("单据合法性分析前玩家基本信息更新正确，返回码【%d】\n", iRet);
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "单据合法性分析前玩家基本信息更新正确，返回码【%d】\n", iRet);
	ValidLOG->WriteLog("In Valid Proccess,IcsInfo==|ICSID:%s|UIN:%s|sRoleID:%s|sRoleName:%s|sIsVip:%s|sRoleLevel:%s|siRobedRoleBan:%s\n", \
		ics_info.sICSId.c_str(), \
		ics_info.sUin.c_str(), \
		ics_info.sRoleID.c_str(), \
		ics_info.sRoleName.c_str(), \
		ics_info.sIsVip.c_str(), \
		ics_info.sRoleLevel.c_str(), \
		ics_info.siRobedRoleBan.c_str());
	if (0 != ProCheckRoleLevel(ics_info))
	{
		// 用户等级不符合分析要求
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'ProCheckRoleLevel' is 用户等级不符合分析要求\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'ProCheckRoleLevel' is 用户等级不符合分析要求\n");
		return STEP_FLITER_RUN_STAT_ERROR_LEVEL;
	}
	// 	else if(0 != ProCheckBlockTime(ics_info))
	// 	{
	// 		// 角色被封大于5天
	// 		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'ProCheckBlockTime' is 角色被封\n");
	// 		return STEP_FLITER_RUN_STAT_ERROR_BANNED;
	// 	}
	else if (0 != ProCheckRobedTime(ics_info))
	{
		// 被盗时间超过申诉要求
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'ProCheckRobedTime' is 被盗时间超过申诉要求\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'ProCheckRobedTime' is 被盗时间超过申诉要求\n");
		return STEP_FLITER_RUN_STAT_ERROR_APPLY_TIME;
	}
	// 	else if (ProIsSendMail(ics_info))
	// 	{
	// // 		string sendto    = CRobConf::getConf()->GetCommonInterface()["MergeSendmailTo"];
	// // 		string sendTitle = Utf8ToGbk((char*)CRobConf::getConf()->GetCommonInterface()["MergeSendmailTiTle"].c_str());
	// // 		string sendTxt   = "单据号:" + ics_info.sICSId + "\n";
	// // 		sendTxt         += "原大区:" + mapMergeArea[ics_info.sWordId] + "\n";
	// // 		sendTxt         += "现大区:" + ics_info.sWordId + "\n";
	// // 		sendTxt         += "QQ号码:" + ics_info.sUin + "\n";
	// // 		sendTxt         += "时间段:" + ics_info.stLastLogin + "\t" + ics_info.stRobeLogin + "\n";
	// // 		CLogManager::SendEmail(sendto,sendTitle,sendTxt);
	// 
	// 		return -1;
	// 	}
	//else if (0 == ProCheckLastTime(ics_info))
	//{
	//	// 发现被盗时间不大于最后一次登陆时间
	//	ValidLOG->WriteLog("In Valid Proccess, Find Uin 'CheckRobedTime' is  发现被盗时间不大于最后一次登陆时间\n");
	//	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'CheckRobedTime' is  发现被盗时间不大于最后一次登陆时间\n" );
	//	return STEP_FLITER_RUN_STAT_ERROR_INPUT_TIME;
	//}
	else if ((iRet = ProCheckDobleQuest(ics_info)) != 0)
	{
		// 60天内重复来单
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'CheckRobedTime' is   180天内重复来单\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'CheckRobedTime' is   180天内重复来单\n");
		return iRet;
	}
	ValidLOG->WriteLog("In Valid Proccess, Find Uin 'DoICSCheck' is  valid ,Go to Auto Process\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, ics_info.sICSId.c_str(), ics_info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'DoICSCheck' is  valid ,Go to Auto Process\n");
	// 允许自助处理
	return STEP_FLITER_RUN_STAT_SUCCESS;
}



/**
Description:	根据业务的策略是否过滤高价值物品
@param	[in]	info
@return			in_size，过滤前的物品股总数 out_size，过滤后的物品的总数 fliter_item_flag 是否进行高价值物品过滤的标志位
				
				fliter_item_flag ：
				0  不用过滤高价值物品
				1  需要过滤高价值物品
				
				return:
				0	   正常
				other  不正常,各种错误信息

@exception		none
*/
int RobRuleValid::DoGetItemsToPresent(spoil_info all_item_info[],spoil_info get_item_info[],const unsigned int in_size,unsigned int& out_size,int fliter_item_flag)
{
	ValidLOG->WriteLog("In DoGetItemsToPresent() Proccess!\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "In DoGetItemsToPresent() Proccess!\n" );
	ValidLOG->WriteLog("DoGetItemsToPresent()INParams=in_size:%d|out_size:%d|fliter_item_flag:%d\n",in_size,out_size,fliter_item_flag);
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "DoGetItemsToPresent()INParams=in_size:%d|out_size:%d|fliter_item_flag:%d\n",in_size,out_size,fliter_item_flag );
	//不过滤
	if(fliter_item_flag == 0)
	{
		for(unsigned int i = 0; i <in_size; i++)
		{
			get_item_info[i]=all_item_info[i];
		}
		out_size = in_size;
	}
	ValidLOG->WriteLog("DoGetItemsToPresent() OUTParams=in_size:%d|out_size:%d|fliter_item_flag:%d\n",in_size,out_size,fliter_item_flag);
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "DoGetItemsToPresent() OUTParams=in_size:%d|out_size:%d|fliter_item_flag:%d\n", in_size, out_size, fliter_item_flag );
	return 0;
}


/**
Description:	设定各个物品是否转人工处理；
@param			[in]	info
@				(a):    物品是否叠加
@return			int     接口正确与否
@exception		none
*/
int RobRuleValid::DoSetItemsToPresent(spoil_info all_item_info[],const unsigned int in_size)
{
	ValidLOG->WriteLog("In DoSetItemsToPresent() Proccess!\n");
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "In DoSetItemsToPresent() Proccess!\n" );
	for(unsigned int i = 0; i <in_size; i++)
	{
		  /* 
		  @ (a): 如果物品是叠加状态；
		  @		  Status   1    转人工处理
		  */
		  if(all_item_info[i].ItemCou != "1")
		  {
			  all_item_info[i].Status = "1"; //需要人工处理
		  }
		  else
		  {
			  all_item_info[i].Status = "0";
		  }
	}
	return 0;
}









/**********************************************************************************
*	返回LEVEL的ics的check过滤函数
*   params:		ics_info
* 	return:		int
*/
int RobRuleValid::ProCheckRoleLevel(Rob_Ics_Complaint& info)
{
	return (StrToInt(info.sRoleLevel) < StrToInt(CRobConf::getConf()->GetIcsValid()["role_level"]))?1:0;
}
/***********************************************************************************	
*	返回BLOCK的ics的check过滤函数
*   params:		ics_info
* 	return:		int
*/
int RobRuleValid::ProCheckBlockTime(Rob_Ics_Complaint& info)
{
	return StrToInt(info.siRobedRoleBan)==0?0:1;
}

/**  被盗时间超过申诉要求, 普通用户暂定为15天，VIP为20天***********************************************************************************	
* 		params:		ics_info
* 		return:		int
*/
int RobRuleValid::ProCheckRobedTime(Rob_Ics_Complaint &info)
{
	time_t	tRobedTime;
	time_t	tCurTime = time(0);
	char szRobedTime[256];
	sprintf(szRobedTime, "%s", (char*)(info.stBookTime.c_str()));
	GetTmsecFromUnxfmt(tRobedTime, szRobedTime);

	return ((tCurTime-tRobedTime) > 3600*24*StrToInt(CRobConf::getConf()->GetIcsValid()["create_due"]))?1:0;
}
/**  被盗时间超过最后登录的时间, 符合规则************************************
* 		params:		ics_info
* 		return:		int
*/
int RobRuleValid::ProCheckLastTime(Rob_Ics_Complaint &info)
{
	char szLastLogin[256];
	sprintf(szLastLogin, "%s", (char*)(info.stLastLogin).c_str());
	char szRobedTime[256];
	sprintf(szRobedTime, "%s", (char*)(info.stRobeLogin).c_str());

	return (GetDiffTime(szRobedTime,szLastLogin)<0)?0:1;
}
/**   receive_doble天内重复来单不受理； 普通用户暂定为180天，VIP为90天
* 		params:		ics_info
* 		return:		int
*/
int RobRuleValid::ProCheckDobleQuest(Rob_Ics_Complaint &info)
{
	//此处需要详细的规划下,暂时不处理
	//select count(*) as applyValueCount from tbICSComplaint where TO_DAYS(now())-TO_DAYS(dtBookTime)<=60
	// and iUin='732945415' and iRoleID='12306';
	//
	map<string,string> theParamIn;
	theParamIn.clear();
	theParamIn["uin"]          = info.sUin;
	theParamIn["role_id"]      = info.sRoleID;
	theParamIn["apply_day_in"] = CRobConf::getConf()->GetIcsValid()["receve_double"];
	theParamIn["service_id"]   = info.sServiceID;
	theParamIn["role_id"]      = info.sRoleID;

	vector< map<string,string> > base_result;
	if(0 != valid_parse.GetFunction(ics_log_header(info.sICSId,info.sUin,info.sServiceID),\
									theParamIn,"ics_apply_repeat_uin",base_result))
	{
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'get_ics_info_by_uin' happened error,not find info\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'get_ics_info_by_uin' happened error,not find info\n" );
		return STEP_FLITER_RUN_STAT_ERROR_INTERFACE;
	}
	
	int check_flag=0;
	int check_running_flag=0;
	int check_false_flag=0;
	int check_result=0;

	if(base_result.size()>1)
	{
		for(int i=0;i<base_result.size();i++)
		{
			ValidLOG->WriteLog("[Info]'ProCheckDobleQuest' Proccessing <%d>&iICSAnaylseResult=<%s>\n",base_result.size(),base_result[i]["iICSAnaylseResult"].c_str());
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info]'ProCheckDobleQuest' Proccessing <%d>&iICSAnaylseResult=<%s>\n",base_result.size(),base_result[i]["iICSAnaylseResult"].c_str() );
			//a 如果存在处理成功的---：此单据为异常单据《重复单据》
			if(StrToInt(base_result[i]["iICSAnaylseResult"])>=STEP_ITEMFSEND_RUN_RESULT_TURE)
			{
				ValidLOG->WriteLog("[Info] [RobRuleValid::ProCheckDobleQuest] Get The Fromer icsID Result<%s>, Process Pass Fliter Ok, So Not Pass It\n",base_result[i]["iICSAnaylseResult"].c_str());
				WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info] [RobRuleValid::ProCheckDobleQuest] Get The Fromer icsID Result<%s>, Process Pass Fliter Ok, So Not Pass It\n",base_result[i]["iICSAnaylseResult"].c_str() );
				return STEP_FLITER_RUN_STAT_ERROR_APPLY_AGAIN;
			}
			//a.1 如果存在在阶段的处理的流程中的单据
			if(StrToInt(base_result[i]["iICSAnaylseResult"])>=STEP_FLITER_RUN_RESULT_TURE&&StrToInt(base_result[i]["iICSAnaylseResult"])<STEP_ITEMFSEND_RUN_RESULT_TURE)
			{
				ValidLOG->WriteLog("[Info] [RobRuleValid::ProCheckDobleQuest] Runing AND False=[%s]\n",base_result[i]["iICSAnaylseResult"].c_str());
				if(StrToInt(base_result[i]["iICSAnaylseResult"])==STEP_ROBSLOT_RUN_RESULT_FALSE||\
					StrToInt(base_result[i]["iICSAnaylseResult"])==STEP_ITEMFLOW_RUN_RESULT_FALSE||\
					StrToInt(base_result[i]["iICSAnaylseResult"])==STEP_ITEMFTRACE_RUN_RESULT_FALSE||\
					StrToInt(base_result[i]["iICSAnaylseResult"])==STEP_ITEMFSEND_RUN_RESULT_FALSE){
						check_false_flag++;
						ValidLOG->WriteLog("[Info] [RobRuleValid::ProCheckDobleQuest] False=%s&check_false_flag=%d\n",base_result[i]["iICSAnaylseResult"].c_str(),check_false_flag);
						WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info] [RobRuleValid::ProCheckDobleQuest] False=%s&check_false_flag=%d\n",base_result[i]["iICSAnaylseResult"].c_str(),check_false_flag );
				}
				else
				{
					check_result++;
					ValidLOG->WriteLog("[Info] [RobRuleValid::ProCheckDobleQuest] Running=%s&check_result=%d\n",base_result[i]["iICSAnaylseResult"].c_str(),check_result);
					WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info] [RobRuleValid::ProCheckDobleQuest] Running=%s&check_result=%d\n",base_result[i]["iICSAnaylseResult"].c_str(),check_result );
				}
			}
			//a.2 如果存在在一次处理多的单据
			if(StrToInt(base_result[i]["iICSAnaylseStat"])==STEP_FLITER_RUNNING_STAT)
			{
				check_running_flag++;
				ValidLOG->WriteLog("[Info] [RobRuleValid::ProCheckDobleQuest] LOT APPLY=%d",check_running_flag);
				WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info] [RobRuleValid::ProCheckDobleQuest] LOT APPLY=%d",check_running_flag );
			}
		}
		//如果存在各阶段处理中的单据
		if(check_result>0)
		{
			return STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT;
		}
		//如果所有的单据的都是在第一个阶段的单据
		if(check_running_flag>1)
		{
			ValidLOG->WriteLog("[Info] [RobRuleValid::ProCheckDobleQuest] STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT,So Pass Last It ,check_flag=<%d>\n",check_running_flag);
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_WARNING, __FUNCTION__, "[Info] [RobRuleValid::ProCheckDobleQuest] STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT,So Pass Last It ,check_flag=<%d>\n",check_running_flag );
			return STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT;
		}
		else if(check_running_flag==1)
		{
			ValidLOG->WriteLog("[Info] [RobRuleValid::ProCheckDobleQuest] STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT,So I am The Last One ,check_flag=<%d>\n",check_running_flag);
			WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info] [RobRuleValid::ProCheckDobleQuest] STEP_FLITER_RUN_STAT_ERROR_APPLY_LOT,So I am The Last One ,check_flag=<%d>\n",check_running_flag );
			return 0;
		}
		return 0;//其它情况 返回正常
	}
	else if(base_result.size()==1)
	{
		ValidLOG->WriteLog("[Info] [RobRuleValid::ProCheckDobleQuest] The Fisrt Processing Only One, So Pass It\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[Info] [RobRuleValid::ProCheckDobleQuest] The Fisrt Processing Only One, So Pass It\n" );
		return 0;
	}
	else
	{
		ValidLOG->WriteLog("[Info] [RobRuleValid::ProCheckDobleQuest] The <ics_apply_repeat_uin> Processing Interface Error\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "[RobRuleValid::ProCheckDobleQuest] The <ics_apply_repeat_uin> Processing Interface Error" );
		return STEP_FLITER_RUN_STAT_ERROR_INTERFACE;
	}
}

/**   调用idip接口查找vip信息
* 		params:		ics_info
* 		return:		int
*/
int RobRuleValid::ProCheckVIPInfo(Rob_Ics_Complaint& info)
{
	map<string,string> theParamIn;
	vector< map<string,string> > theResult;

	theParamIn.clear();
	theParamIn["uin"] = info.sUin;
	theParamIn["business"] = "sap";

	if(0 != valid_parse.GetFunction(ics_log_header(info.sICSId,info.sUin,info.sServiceID),\
									theParamIn,"get_vip_info",theResult))
	{
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'get_vip_info' happened error,not find info\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "In Valid Proccess, Find Uin 'get_vip_info' happened error,not find info\n" );
		return -1;
	}else
	{
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'get_vip_info' success!\n");
		WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "In Valid Proccess, Find Uin 'get_vip_info' success!\n" );
		info.sIsVip = theResult[0]["type"];
		return theResult[0]["type"] == "0" ? 0 : 1;
	}

}
/*=======================V1.00=================================*/


/**
Description:	验证单据的合法性
@param	[in]	info
@return			int
@exception		none
*/
int RobRuleValid::DoICSCheck(ics_info& info)
{
	ValidLOG->WriteLog("In Valid Proccess,IcsInfo==|ICSID:%s|UserID:%s|\n",info.ICSID.c_str(),info.UserID.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBANLYSVALID, info.ICSID.c_str(), info.UserID.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "In Valid Proccess,IcsInfo==|ICSID:%s|UserID:%s|\n", info.ICSID.c_str(), info.UserID.c_str() );
	/*if (0 != CheckRoleLevel(info))
	{
		// 用户等级不符合分析要求
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'CheckRoleLevel' is 用户等级不符合分析要求\n");
		return STEP_FLITER_RUN_STAT_ERROR_LEVEL;
	}
	else if (0 != CheckRobedTime(info))
	{
		// 被盗时间超过申诉要求
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'CheckRobedTime' is 被盗时间超过申诉要求\n");
		return STEP_FLITER_RUN_STAT_ERROR_APPLY_TIME;
	}
	else if (0 != CheckLastTime(info))
	{
		// 发现被盗时间不大于最后一次登陆时间
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'CheckRobedTime' is  发现被盗时间不大于最后一次登陆时间\n");
		return STEP_FLITER_RUN_STAT_ERROR_INPUT_TIME;
	}
	else if (0 != CheckDobleQuest(info))
	{
		// 60天内重复来单
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'CheckRobedTime' is   60天内重复来单\n");
		return STEP_FLITER_RUN_STAT_ERROR_APPLY_AGAIN;
	}
	else if (0 != CheckBlockTime(info))
	{
		// 角色被封大于5天
		ValidLOG->WriteLog("In Valid Proccess, Find Uin 'CheckRobedTime' is  角色被封大于5天\n");
		return STEP_FLITER_RUN_STAT_ERROR_BANNED;
	}
	ValidLOG->WriteLog("In Valid Proccess, Find Uin 'DoICSCheck' is  valid ,Go to Auto Process\n");
	// 允许自助处理*/
	return STEP_FLITER_RUN_STAT_SUCCESS;
}

// bool RobRuleValid::ProIsSendMail(Rob_Ics_Complaint& info)
// {
// 	string strArea = info.sWordId;
// 
// 	ValidLOG->WriteLog("%s\n", strArea.c_str());
// 	map< string, string >::iterator itAreaPos = mapMergeArea.find(strArea);
// 	map< string, string >::iterator itTimePos = mapMergeTime.find(strArea);
// 
// 	if ( itAreaPos != mapMergeArea.end() && itTimePos != mapMergeTime.end() )
// 	{
// 
// 		ValidLOG->WriteLog("11111");
// 		time_t tLastTime = 0;
// 		char szLastTime[256];
// 		sprintf(szLastTime, "%s", (char*)(info.stLastLogin.c_str()));
// 		GetTmsecFromUnxfmt(tLastTime, szLastTime);
// 
// 		ValidLOG->WriteLog("lastTime;%s\n",info.stLastLogin.c_str() );
// 		ValidLOG->WriteLog("%ld-%ld=%ld\n", tLastTime, StrToLLong(mapMergeTime[strArea]), tLastTime-StrToLLong(mapMergeTime[strArea]));
// 
// 		if ( tLastTime <= StrToLLong(mapMergeTime[strArea]))
// 		{	
// 			return true;
// 		}
// 	}
// 	else
// 	{
// 		return false;
// 	}
// }






