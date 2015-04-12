#include "rob_ics_oper.h"
#include "comm_value.h"
#include "comm_logmanager.h"

RobICSOper::RobICSOper()
{
	//调试日志
	ICSOPERLOG="./logs/"+GetCurDateDay()+"QhelperICSOper.log";
	ValidLOG = new CLog((const char*)ICSOPERLOG.c_str());
	ValidLOG->LogOn();
	iRet=0;
}

RobICSOper::~RobICSOper()
{
	if(ValidLOG!=NULL)
	{
		delete ValidLOG;
	}
}


/*******************************************************************
Description:	单据tbICSComplaint读取
Params:			单据的大小：size_ics_info，私有变量;
				单据的读取数组： get_ics_info[] 传入变量;
return:			真实的获取到处理的单据大小
@exception		none
*/
unsigned int RobICSOper::ReadICSInfoListNew(ApplyAnaylseStep_New enumApplyAnaylseStep,Qhelper_Ics_Complaint get_ics_info[],int get_size)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	int interface_index = 0;
	//分析单据阶段，
	//step和result状态值都为0
	//不同阶段读取的参数不同
	theParamIn["size"] = IntToStr(get_size);
	theParamIn["service_id"] = CRobConf::getConf()->GetGroupInfo()["group_id"];
	theParamIn["interval_up"] = "0";
	theParamIn["interval"] = "0";

	ValidLOG->WriteLog("-------------Read Auto QHelper Info Size[%d]---------------\n",get_size);
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "-------------Read Auto QHelper Info Size[%d]---------------\n", get_size );
	//单据过滤处理
	theParamIn["step"]=IntToStr(enumApplyAnaylseStep);
	theParamIn["result"]=IntToStr(STEP_WAITING_RUN_STAT_NEW);
	theParamIn["interval_up"] = CRobConf::getConf()->GetIcsValid()["interval_up"];
	theParamIn["interval"] = CRobConf::getConf()->GetIcsValid()["interval"];

	ValidLOG->WriteLog("-------------Read Auto Qhelper Info begin status: [%s]---------------\n", IntToStr(enumApplyAnaylseStep).c_str());
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "-------------Read Auto Qhelper Info begin status: [%s]---------------\n", IntToStr(enumApplyAnaylseStep).c_str() );

	ics_log_header header("","",CRobConf::getConf()->GetGroupInfo()["group_id"]);
	ICS_Oper.GetFunction(header,theParamIn,"ics_info_list",theGetResult); //加入正式环境，测试环境分离判断


	for(unsigned int index_GetResult=0; index_GetResult<theGetResult.size(); index_GetResult++)
	{
		SaveAutoHalfIcsInfo(get_ics_info[index_GetResult], theGetResult[index_GetResult]);
		ValidLOG->WriteLog("Read Auto QHelper Info:icsid=%s|,sServiceID=%s|, sKindID=%s|, vCommmand=%s|, iParaNum=%s\n", 
			get_ics_info[index_GetResult].sICSId.c_str(), 
			get_ics_info[index_GetResult].sServiceID.c_str(), 
			get_ics_info[index_GetResult].sKindID.c_str(),
			get_ics_info[index_GetResult].vCommand.c_str(),
			get_ics_info[index_GetResult].sParaNum.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "Read Auto QHelper Info:icsid=%s|,sServiceID=%s|, sKindID=%s|, vCommmand=%s|,  iParaNum=%s\n", 
			get_ics_info[index_GetResult].sICSId.c_str(), 
			get_ics_info[index_GetResult].sServiceID.c_str(), 
			get_ics_info[index_GetResult].sKindID.c_str(),
			get_ics_info[index_GetResult].vCommand.c_str(),
			get_ics_info[index_GetResult].sParaNum.c_str());
	}
	return theGetResult.size();
} // end ReadICSInfoList

/*******************************************************************
Description:	单据内存的状态值
@exception		none
@return 		int 操作接口返回结果
*/

int RobICSOper::SaveAutoHalfIcsInfo(Qhelper_Ics_Complaint& present_item_res, map<string,string>& input_params)
{
	int res = 0;

	present_item_res.sID = input_params["iID"];
	present_item_res.sICSId = input_params["iICSId"];
	present_item_res.sServiceID = input_params["iServiceID"];
	present_item_res.sKindID = input_params["iKind"];
	present_item_res.vCommand = input_params["vCommand"];
	present_item_res.sParaNum = input_params["para_num"];
	present_item_res.stBookTime = input_params["dtBookTime"];
	present_item_res.dtFinishTime = input_params["dtFinishTime"];
	present_item_res.sResultDesc = input_params["sDesc"];
	present_item_res.sICSAnaylseStatus = input_params["iCurStatus"];
	present_item_res.sUndefined1 = input_params["Undefined1"]==""?"0":input_params["Undefined1"];
	present_item_res.sUndefined2 = input_params["Undefined2"]==""?"0":input_params["Undefined2"];
	present_item_res.sUndefined3 = input_params["Undefined3"]==""?"0":input_params["Undefined3"];
	return res;
}

/*******************************************************************
Description:	单据tbICSInfo的更新，主要是状态，结果更新
@desc			包括单据在各种情况下的读取
@exception		none
*/
int RobICSOper::UpdateICSProc(std::string sIcsID,ApplyAnaylseStep_New enumApplyAnaylseStep,ApplyAnaylseResult_New enumApplyAnaylseResult)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	theParamIn.clear();
	theParamIn["ics_id"]     = sIcsID;
	theParamIn["step"]       = IntToStr(enumApplyAnaylseStep);
	theParamIn["result"]     = IntToStr(enumApplyAnaylseResult);
	theParamIn["service_id"] = CRobConf::getConf()->GetGroupInfo()["group_id"];

	ValidLOG->WriteLog("-------------更新单据[%s]:结果为:[%s]和状态: [%s]:---------------\n",sIcsID.c_str(),theParamIn["step"].c_str(), theParamIn["result"].c_str() );
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, sIcsID.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "-------------需要读取的单据ID:[%s]---------------\n", sIcsID.c_str() );

	ics_log_header header("","",CRobConf::getConf()->GetGroupInfo()["group_id"]);
	return ICS_Oper.GetFunction(header,theParamIn,"ics_status_update",theGetResult); //更新单据状态和结果
	//return ICS_Oper.GetFunction(ics_log_header(sIcsID,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),theParamIn,"ics_status_update",theGetResult);
}

/************************************************************************/
/* ********************************************************************** */
/************************************************************************/

/*******************************************************************
Description:	单据tbICSComplaint读取
Params:			单据的大小：size_ics_info，私有变量;
				单据的读取数组： get_ics_info[] 传入变量;
return:			真实的获取到处理的单据大小
@exception		none
*/
unsigned int RobICSOper::ReadICSInfoOneItem(ApplyAnaylseStep enumApplyAnaylseStep,Rob_Ics_Complaint get_ics_info[],string ics_id)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	int interface_index = 0;
	//分析单据阶段
	theParamIn["ics_id"]     = ics_id;//单据id
	theParamIn["service_id"] = CRobConf::getConf()->GetGroupInfo()["group_id"];
	ValidLOG->WriteLog("-------------需要读取的单据ID:[%s]---------------\n",ics_id.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ics_id.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "-------------需要读取的单据ID:[%s]---------------\n", ics_id.c_str() );

	switch(enumApplyAnaylseStep)
	{
	case STEP_FLITER_RUN_ICS:			//单据过滤处理
		theParamIn["step"]   = IntToStr(STEP_WAITING_RUN_ICS);
		theParamIn["result"] = IntToStr(STEP_WAITING_RUN_RESULT);
		break;
	case STEP_ROBSLOT_RUN_ICS:			//登入登出
		theParamIn["step"]   = IntToStr(STEP_FLITER_RUN_ICS);
		theParamIn["result"] = IntToStr(STEP_FLITER_RUN_RESULT_TURE);
		break;
	case STEP_ITEMFLOW_RUN_ICS:			//物品流水
		theParamIn["step"]   = IntToStr(STEP_ROBSLOT_RUN_ICS);
		theParamIn["result"] = IntToStr(STEP_ROBSLOT_RUN_RESULT_TURE);
		break;
	case STEP_ITEMTRACE_RUN_ICS:		//物品追踪
		theParamIn["step"]   = IntToStr(STEP_ITEMFLOW_RUN_ICS);
		theParamIn["result"] = IntToStr(STEP_ITEMFLOW_RUN_RESULT_TURE);
		break;
	case STEP_ITEMSEND_RUN_ICS:			//物品补送
		theParamIn["step"]   = IntToStr(STEP_ITEMTRACE_RUN_ICS);
		theParamIn["result"] = IntToStr(STEP_ITEMFTRACE_RUN_RESULT_TURE);
		break;
	case STEP_REPLAY_RUN_ICS:			//单据回复
		interface_index             = 1;
		theParamIn["AnaylseResult"] = "(12,21,31,41,51,52)";
		break;
	default:
		return 0;
	}
	ValidLOG->WriteLog("-------------单据处理阶段为：【%s】---------------\n", IntToStr(enumApplyAnaylseStep).c_str());
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ics_id.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "-------------单据处理阶段为：【%s】---------------\n", IntToStr(enumApplyAnaylseStep).c_str() );

	if( 1 == interface_index )
	{
		ICS_Oper.GetFunction(ics_log_header("","",CRobConf::getConf()->GetGroupInfo()["group_id"]),	theParamIn,"rob_ics_need_reply_one",theGetResult);
		ValidLOG->WriteLog("[rob_ics_need_reply_one]-------------读取指定待回复单据一条---------------\n");
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ics_id.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "[rob_ics_need_reply_one]-------------读取指定待回复单据一条---------------\n" );
	}
	else
	{
		ValidLOG->WriteLog("读取指定的单据【%s】\n", theParamIn["ics_id"].c_str());
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ics_id.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "读取指定的单据【%s】\n", theParamIn["ics_id"].c_str() );
		ICS_Oper.GetFunction(ics_log_header("","",CRobConf::getConf()->GetGroupInfo()["group_id"]),theParamIn,"ics_info_one",theGetResult);
	}

	for(unsigned int index_GetResult=0; index_GetResult<theGetResult.size(); index_GetResult++)
	{
		SaveAutoHalfIcsInfo(get_ics_info[index_GetResult], theGetResult[index_GetResult]);
		ValidLOG->WriteLog("Read Auto Rob Info:icsid=%s|,uin=%s|, RoleId=%s|, RoleName=%s\n",get_ics_info[index_GetResult].sICSId.c_str(), get_ics_info[index_GetResult].sUin.c_str(), get_ics_info[index_GetResult].sRoleID.c_str(),get_ics_info[index_GetResult].sRoleName.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, get_ics_info[index_GetResult].sICSId.c_str(), get_ics_info[index_GetResult].sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "Read Auto Rob Info:icsid=%s|,uin=%s|, RoleId=%s|, RoleName=%s\n", get_ics_info[index_GetResult].sICSId.c_str(), get_ics_info[index_GetResult].sUin.c_str(), get_ics_info[index_GetResult].sRoleID.c_str(), get_ics_info[index_GetResult].sRoleName.c_str() );
	}

	return theGetResult.size();
}

/*******************************************************************
Description:	单据tbICSComplaint读取
Params:			单据的大小：size_ics_info，私有变量;
				单据的读取数组： get_ics_info[] 传入变量;
return:			真实的获取到处理的单据大小
@exception		none
*/
//分模块：与填单时间的间隔设置
//#define	INTERVAL_DELAY_FILTER		60*60*2  
#define	INTERVAL_DELAY_NORMAL		0
//分模块：与最近更新处理的间隔设置
//#define	INTERVAL_UPDATE_SEND		60*60*1 //即补送模块读取2h之前追踪模块完成的单据
#define	INTERVAL_UPDATE_NORMAL  	0
unsigned int RobICSOper::ReadICSInfoList(ApplyAnaylseStep enumApplyAnaylseStep,Rob_Ics_Complaint get_ics_info[],int get_size)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	int interface_index = 0;

	//分析单据阶段
	theParamIn["size"] = IntToStr(get_size);
	theParamIn["service_id"] = CRobConf::getConf()->GetGroupInfo()["group_id"];
	theParamIn["ics_source"] = CRobConf::getConf()->GetIcsValid()["ics_source"];
	ValidLOG->WriteLog("-------------需要读取的单据的数量为[%d]---------------\n",get_size);
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "-------------需要读取的单据的数量为[%d, %s]---------------\n", get_size , theParamIn["ics_source"].c_str());
	switch(enumApplyAnaylseStep)
	{
		case STEP_FLITER_RUN_ICS:			//单据过滤处理
			theParamIn["step"]        = IntToStr(STEP_WAITING_RUN_ICS);
			theParamIn["result"]      = IntToStr(STEP_WAITING_RUN_RESULT);
			theParamIn["interval"]    = CRobConf::getConf()->GetIcsValid()["interval_delay_filter"];
			theParamIn["interval_up"] = IntToStr(INTERVAL_UPDATE_NORMAL);
			break;
		case STEP_ROBSLOT_RUN_ICS:			//登入登出
			theParamIn["step"]        = IntToStr(STEP_FLITER_RUN_ICS);
			theParamIn["result"]      = IntToStr(STEP_FLITER_RUN_RESULT_TURE);
			theParamIn["interval"]    = IntToStr(INTERVAL_DELAY_NORMAL);
			theParamIn["interval_up"] = IntToStr(INTERVAL_UPDATE_NORMAL);
			break;
		case STEP_ITEMFLOW_RUN_ICS:			//物品流水
			theParamIn["step"]        = IntToStr(STEP_ROBSLOT_RUN_ICS);
			theParamIn["result"]      = IntToStr(STEP_ROBSLOT_RUN_RESULT_TURE);
			theParamIn["interval"]    = IntToStr(INTERVAL_DELAY_NORMAL);
			theParamIn["interval_up"] = IntToStr(INTERVAL_UPDATE_NORMAL);
			break;
		case STEP_ITEMTRACE_RUN_ICS:		//物品追踪
			theParamIn["step"]        = IntToStr(STEP_ITEMFLOW_RUN_ICS);
			theParamIn["result"]      = IntToStr(STEP_ITEMFLOW_RUN_RESULT_TURE);
			theParamIn["interval"]    = IntToStr(INTERVAL_DELAY_NORMAL);
			theParamIn["interval_up"] = IntToStr(INTERVAL_UPDATE_NORMAL);
			break;
		case STEP_ITEMSEND_RUN_ICS:			//物品补送
			theParamIn["step"]        = IntToStr(STEP_ITEMTRACE_RUN_ICS);
			theParamIn["result"]      = IntToStr(STEP_ITEMFTRACE_RUN_RESULT_TURE);
			theParamIn["interval"]    = IntToStr(INTERVAL_DELAY_NORMAL);
			theParamIn["interval_up"] = CRobConf::getConf()->GetIcsValid()["interval_update_send"];
			break;
		case STEP_REPLAY_RUN_ICS:			//单据回复
			interface_index             = 1;
			theParamIn["AnaylseResult"] = "(12,21,31,41,51,52)";
			break;
		default:
			return 0;
	}
	ValidLOG->WriteLog("-------------单据处理阶段为：【%s】---------------\n", IntToStr(enumApplyAnaylseStep).c_str());
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "-------------单据处理阶段为：【%s】---------------\n", IntToStr(enumApplyAnaylseStep).c_str() );

	if(1 == interface_index)
	{
		ICS_Oper.GetFunction(ics_log_header("","",CRobConf::getConf()->GetGroupInfo()["group_id"]),theParamIn,"rob_ics_need_reply_list",theGetResult);
	}
	else
	{
		ICS_Oper.GetFunction(ics_log_header("","",CRobConf::getConf()->GetGroupInfo()["group_id"]),theParamIn,"ics_info_list",theGetResult);
	}

	for(unsigned int index_GetResult=0; index_GetResult<theGetResult.size(); index_GetResult++)
	{
		SaveAutoHalfIcsInfo(get_ics_info[index_GetResult], theGetResult[index_GetResult]);
		ValidLOG->WriteLog("Read Auto Rob Info:icsid=%s|,uin=%s|, RoleId=%s|\n", get_ics_info[index_GetResult].sICSId.c_str(), get_ics_info[index_GetResult].sUin.c_str(), get_ics_info[index_GetResult].sRoleID.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, get_ics_info[index_GetResult].sICSId.c_str(), get_ics_info[index_GetResult].sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "Read Auto Rob Info:icsid=%s|,uin=%s|, RoleId=%s|\n", get_ics_info[index_GetResult].sICSId.c_str(), get_ics_info[index_GetResult].sUin.c_str(), get_ics_info[index_GetResult].sRoleID.c_str());
	}
	return theGetResult.size();
}


/*******************************************************************
Description:	单据内存的状态值
@exception		none
@return 		int 操作接口返回结果
*/

int RobICSOper::SaveAutoHalfIcsInfo(Rob_Ics_Complaint& present_item_res, map<string,string>& input_params)
{
	int res = 0;

	present_item_res.sID               = input_params["iID"];
	present_item_res.sServiceID        = input_params["iServiceID"];
	present_item_res.sICSId            = input_params["iICSId"];
	present_item_res.sUin              = input_params["iRobed_Uin"];
	present_item_res.sRoleID           = input_params["vRobed_RoleId"];
	present_item_res.sRoleName         = input_params["vRobed_RoleName"]==""?"0":input_params["vRobed_RoleName"];
	present_item_res.sRoleLevel        = input_params["iRobed_RoleLevel"]==""?"0":input_params["iRobed_RoleLevel"];
	present_item_res.sWordId           = input_params["iWordId"];
	present_item_res.stBookTime        = input_params["dtBookTime"];
	present_item_res.stLastLogin       = input_params["dtLastLogin"];
	present_item_res.stRobeLogin       = input_params["dtRobedTime"];
	present_item_res.sUpdateTime       = input_params["dtUpdateTime"];
	present_item_res.sIsVip            = input_params["iVip"]==""?"0":input_params["iVip"];
	present_item_res.sUndefined1       = input_params["Undefined1"]==""?"0":input_params["Undefined1"];
	present_item_res.sUndefined2       = input_params["Undefined2"]==""?"0":input_params["Undefined2"];
	present_item_res.sUndefined3       = input_params["Undefined3"]==""?"0":input_params["Undefined3"];
	present_item_res.siRobedRoleBan    = input_params["siRobedRoleBan"]==""?"0":input_params["siRobedRoleBan"];
	present_item_res.siSource          = input_params["iSource"]==""?"0":input_params["iSource"];
	present_item_res.siReplyResult     = input_params["iReplyResult"]==""?"0":input_params["iReplyResult"];
	present_item_res.sICSAnaylseResult = input_params["iICSAnaylseResult"]==""?"0":input_params["iICSAnaylseResult"];
	present_item_res.sICSAnaylseStat   =  input_params["iICSAnaylseStat"]==""?"0":input_params["iICSAnaylseStat"];
	present_item_res.sICSAnaylseStep   = input_params["iICSAnaylseStep"]==""?"0":input_params["iICSAnaylseStep"];
	return res;
}

/*******************************************************************
Description:	单据tbICSInfo的更新，主要是状态，结果，步骤的更新
@desc			包括单据在各种情况下的读取
@exception		none
*/
int RobICSOper::UpdateICSProc(std::string sIcsID,ApplyAnaylseStep enumApplyAnaylseStep,ApplyAnaylseResult enumApplyAnaylseResult, ApplyAnaylseStat enumApplyAnaylseStat)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	theParamIn.clear();
	theParamIn["ics_id"]     = sIcsID;
	theParamIn["step"]       = IntToStr(enumApplyAnaylseStep);
	theParamIn["result"]     = IntToStr(enumApplyAnaylseResult);
	theParamIn["state"]      = IntToStr(enumApplyAnaylseStat);
	theParamIn["service_id"] = CRobConf::getConf()->GetGroupInfo()["group_id"];
	return ICS_Oper.GetFunction(ics_log_header(sIcsID,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),theParamIn,"ics_status_update",theGetResult);
}

/*********************************************************************
Description:	单据tbICSRoleLogout插入
@desc			包括单据在读取异常登录时间段插入
@exception		none
*/
int RobICSOper::InsertICSRobSlotData(Rob_SLOT& robSlotTime)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	theParamIn["iServiceID"]      = robSlotTime.ServiceID;
	theParamIn["iWordId"]         = robSlotTime.WorldID;
	theParamIn["iICSid"]          = robSlotTime.ICSID;
	theParamIn["vIP"]             = robSlotTime.sBlackRobIp;
	theParamIn["vIPArea"]         = string(GbkToUtf8((char*)robSlotTime.sRobIPName.c_str()));
	theParamIn["iRobed_Uin"]      = robSlotTime.UserID;
	theParamIn["vRobed_RoleId"]   = robSlotTime.RoleID;
	theParamIn["vRobed_RoleName"] = string(GbkToUtf8((char*)robSlotTime.RoleName.c_str()));
	theParamIn["dtLoginInTime"]   = robSlotTime.LoginTime;
	theParamIn["dtLoginOutTime"]  = robSlotTime.LogoutTime;
	theParamIn["iDuration"]       = robSlotTime.OnLineTime;
	theParamIn["iMoney_Sub"]      = "0";//robSlotTime.iMoney_Sub;//暂不关心丢失金钱
	ValidLOG->WriteLog("InsertICSRobSlotData:icsid=%s&dtLoginInTime=%s&dtLoginOutTime=%s|\n",\
				theParamIn["iICSid"].c_str(), \
				theParamIn["dtLoginInTime"].c_str(), \
				theParamIn["dtLoginOutTime"].c_str());
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "InsertICSRobSlotData:icsid=%s&dtLoginInTime=%s&dtLoginOutTime=%s|\n", theParamIn["iICSid"].c_str(), theParamIn["dtLoginInTime"].c_str(), theParamIn["dtLoginOutTime"].c_str() );
	ics_log_header header(robSlotTime.ICSID,robSlotTime.UserID,robSlotTime.ServiceID);
	return ICS_Oper.GetFunction(header,theParamIn,"ics_rob_slot_insert",theGetResult);
}

/**********************************************************************
	Description:	单据tbICSRoleLogout获取
	@desc			包括单据在读取异常登录时间段获取
	@exception		none
*/
int RobICSOper::ReadICSRobSlot(std::vector < Rob_SLOT > &robSlotInfo,std::string sServiceId,std::string sICS_Id)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	Rob_SLOT tempVar;
	robSlotInfo.clear();
	theParamIn["service_id"] = sServiceId;
	theParamIn["ics_id"]     = sICS_Id;
	ValidLOG->WriteLog("【函数】ReadICSRobSlot()【入参】:ics_id=%s&service_id=%s\n",sICS_Id.c_str(), sServiceId.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "【函数】ReadICSRobSlot()【入参】:ics_id=%s&service_id=%s\n",sICS_Id.c_str(), sServiceId.c_str() );

	ics_log_header header(sICS_Id,"",sServiceId);
	ICS_Oper.GetFunction(header,theParamIn,"ics_rob_logout_proc_list",theGetResult);
	if(theGetResult.size() <= 0)
	{
		ValidLOG->WriteLog("【函数】ReadICSRobSlot()结果返回值为【0】【%d】,返回-10000\n",theGetResult.size());
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_ERROR, __FUNCTION__, "【函数】ReadICSRobSlot()结果返回值为【0】【%d】-10000", theGetResult.size() );
		return -10000;
	}
	else
	{
		ValidLOG->WriteLog("【函数】ReadICSRobSlot()结果返回值为【%d】\n",theGetResult.size());
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "【函数】ReadICSRobSlot()结果返回值为【%d】\n", theGetResult.size() );
		for(int j=0;j<theGetResult.size();j++)
		{
				tempVar.ICSID      = theGetResult[j]["iICSId"];
				tempVar.LoginTime  = theGetResult[j]["dtLoginInTime"];
				tempVar.LogoutTime = theGetResult[j]["dtLoginOutTime"];
				tempVar.RoleID     = theGetResult[j]["vRobed_RoleId"];
				tempVar.RoleName   = theGetResult[j]["vRobed_RoleName"];
				tempVar.ServiceID  = theGetResult[j]["iServiceID"];
				tempVar.UserID     = theGetResult[j]["iRobed_Uin"];
				tempVar.WorldID    = theGetResult[j]["iWordId"];
				tempVar.iMoney_Sub = theGetResult[j]["iMoney_Sub"];
				robSlotInfo.push_back(tempVar);
				ValidLOG->WriteLog("【函数】ReadICSRobSlot()循环赋值大小【%d】\n",robSlotInfo.size());
			WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "【函数】ReadICSRobSlot()循环赋值大小【%d】\n", robSlotInfo.size() );
		}
		return 0;
	}
}
int RobICSOper::InsertICSRobItemFlowData(std::vector < Item_Flow_List > &robItemFlow,std::string sServiceId)
{
	
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	
	ValidLOG->WriteLog("生成玩家的异常时间段内赃物流水程序\n");
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "生成玩家的异常时间段内赃物流水程序\n" );
	for(int t=0;t<robItemFlow.size();t++)
	{
		theParamIn["event_time"] = robItemFlow[t].dtEventTime;
		theParamIn["service_id"] = robItemFlow[t].iServiceID;
		theParamIn["ics_id"]     = robItemFlow[t].ICSID;
		theParamIn["area"]       = robItemFlow[t].iWordId;
		//被盗者
		theParamIn["uin"]        = robItemFlow[t].iRobed_Uin;
		theParamIn["role_id"]    = robItemFlow[t].vRobed_RoleId;
		theParamIn["role_name"]  = string(GbkToUtf8((char*)robItemFlow[t].vRobed_RoleName.c_str()));
		//盗号着
		theParamIn["rob_roleid"]   = robItemFlow[t].vRobTo_RoleId;
		theParamIn["rob_uin"]      = robItemFlow[t].iRobTo_Uin;
		theParamIn["rob_rolename"] =  string(GbkToUtf8((char*)robItemFlow[t].vRobTo_RoleName.c_str()));
		//物品信息
		theParamIn["item_id"]     = robItemFlow[t].iItem_Id;
		theParamIn["item_unique"] = robItemFlow[t].iItem_Unique_Id;
		theParamIn["item_name"]   = string(GbkToUtf8((char*)robItemFlow[t].iItem_Name.c_str()));
		ValidLOG->WriteLog("找到赃物ID【%s】\n",theParamIn["item_id"].c_str(),theParamIn["item_name"].c_str());
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, robItemFlow[t].ICSID.c_str(), robItemFlow[t].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "找到赃物ID【%s】\n", theParamIn["item_id"].c_str(), theParamIn["item_name"].c_str() );
		theParamIn["item_upgrade_level"] = robItemFlow[t].iItem_Attribute_1;
		theParamIn["iItem_Attribute_2"]  = robItemFlow[t].iItem_Attribute_2;
		theParamIn["item_type"]          = robItemFlow[t].iItem_Type;
		theParamIn["item_value"]         = robItemFlow[t].iItem_Price_Value;
		theParamIn["item_num"]           = robItemFlow[t].iItem_Num;
		theParamIn["item_base_level"]    = robItemFlow[t].iItem_Level;
		theParamIn["item_blob"]          = robItemFlow[t].iItem_Attribute_blob;
		//动作信息
		theParamIn["action"]             = robItemFlow[t].iFlowAction;
		theParamIn["action_dsc"]         =  string(GbkToUtf8((char*)robItemFlow[t].vFlowDsc.c_str()));
		//后续处理信息
		theParamIn["def_action"]         = robItemFlow[t].iDefineProc;

#ifdef dzs
		//a.只处理基础等级物品，高等级物品不处理---针对全体用户适用
		//b.只处理强化等级<=15等级的物品---针对权限用户适用
		//c.对于加强物品且小于15级的,VIP用户补送，基础用户不补送


#endif
		ICS_Oper.GetFunction(ics_log_header(robItemFlow[t].ICSID,robItemFlow[t].iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
							theParamIn,"ics_item_flow_general",theGetResult);
		ValidLOG->WriteLog("异常时间段内赃物流水程序，单据【%s】\n",theParamIn["ics_id"].c_str());
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, robItemFlow[t].ICSID.c_str(), robItemFlow[t].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "异常时间段内赃物流水程序，单据【%s】\n", theParamIn["ics_id"].c_str() );
	}
	return 0;
}

/************************************************************************
	Description:	单据tbICSRoleLogout更新
	@desc			包括单据在的运行阶段
	@exception		none
*/
int RobICSOper::UpdateICSRobSlotProc(std::string sServiceId, std::string sICS_Id, ApplySlotStat eRunStat)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	ValidLOG->WriteLog("UpdateICSRobSlotProc单据【%s】,状态【%d】更新\n",sServiceId.c_str(),eRunStat);
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, sICS_Id.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "UpdateICSRobSlotProc单据【%s】,状态【%d】更新\n", sServiceId.c_str(), eRunStat );
	theParamIn["ics_id"]= sICS_Id;
	theParamIn["servcie_id"]= sServiceId;
	theParamIn["run_stat"]= IntToStr(eRunStat);
	return ICS_Oper.GetFunction(ics_log_header(sICS_Id,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								theParamIn,"ics_slot_runstat_update",theGetResult);
}


/************************************************************************
Description:单据tbICSItemStats的统计库的
@desc		包括单据在各种情况下的读取
@exception	none
*/
int RobICSOper::UpdateICSItemStatsProc(std::string sUpdateType,vector <string>& vUpdateNum,std::string sIcsId)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;

	theParamIn["ics_id"]= sIcsId;
	theParamIn["item_add_num"]= "0";//被盗数量
	theParamIn["item_high_level_num"] = "0";
	theParamIn["item_trace_num"]= "0";//已追踪数量
	theParamIn["money_add_num"]= "0";
	theParamIn["item_for_send_num"] = "0";//待补送数量
	theParamIn["item_already_send_num"]= "0";//已成功补送数量
	theParamIn["service_id"] = CRobConf::getConf()->GetGroupInfo()["group_id"];

	//需要更新的字段分类
	if(sUpdateType=="Item")
	{
		theParamIn["item_add_num"] = vUpdateNum[0];
	}
	else if(sUpdateType=="trace")
	{
		theParamIn["item_trace_num"] = vUpdateNum[0];
	}
	else if(sUpdateType == "waiting_send")//待补送
	{
		theParamIn["item_for_send_num"] = vUpdateNum[0];
	}
	else if(sUpdateType == "send_finished")
	{
		theParamIn["item_already_send_num"] = vUpdateNum[0];
	}
	else if(sUpdateType=="Money")
	{
		theParamIn["money_add_num"] = vUpdateNum[0];
	}
	else if(sUpdateType=="Item-HighLevel-Money")
	{
		ValidLOG->WriteLog("UpdateICSItemStatsProc类型【ItemAndMoney】,种类【%d】更新\n",vUpdateNum[0].size());
		theParamIn["item_add_num"] = vUpdateNum[0];
		theParamIn["item_high_level_num"] = vUpdateNum[1];
		theParamIn["money_add_num"]= vUpdateNum[2];
		ValidLOG->WriteLog("UpdateICSItemStatsProc类型【ItemAndMoney】,物品总数【%s】高等级物品【%s】金钱总数【%s】更新\n",vUpdateNum[0].c_str(),vUpdateNum[1].c_str(),vUpdateNum[2].c_str());
	}
	return ICS_Oper.GetFunction(ics_log_header(sIcsId,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								theParamIn,"ics_stat_item_add",theGetResult);
}

/**
Description:	单据tbICSItemStats的统计库的最后补送物品统计更新
@desc			包括单据在各种情况下的读取
@exception		none
*/	
int RobICSOper::updateICSItemStatsResult(std::string sUpdateType,vector <string>& vUpdateNum,std::string sIcsId){
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	theParamIn["ics_id"]= sIcsId;

	theParamIn["item_retrieve_num"]= "0";
	theParamIn["item_retrieve_level_num"] = "0";

	theParamIn["arm_retrieve_num"]= "0";

	theParamIn["money_retrieve_num"]= "0";
	
	//需要更新的字段分类
	if(sUpdateType=="Item"){
		theParamIn["item_retrieve_num"] = vUpdateNum[0];
	}else if(sUpdateType=="Arm"){
		theParamIn["arm_retrieve_num"] = vUpdateNum[0];
	}else if(sUpdateType=="Money"){
		theParamIn["money_retrieve_num"] = vUpdateNum[0];
	}else if(sUpdateType=="ItemHighLevel"){
		theParamIn["item_retrieve_level_num"] = vUpdateNum[0];
	}else if(sUpdateType=="Item-ItemHighLevel"){
		theParamIn["item_retrieve_num"] = vUpdateNum[0];
		theParamIn["item_retrieve_level_num"] = vUpdateNum[1];
	}
	return ICS_Oper.GetFunction(ics_log_header(sIcsId,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								theParamIn,"ics_stat_result_update",theGetResult);
}







/*******************************************************************
Description:	单据tbICSItemStats的统计库的初始化插入
@desc			包括单据在各种情况下的读取
@exception		none
*/
int RobICSOper::AddICSItemStatsProc(std::string sIcsID,std::string sServiceID)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	theParamIn["ics_id"]= sIcsID;
	theParamIn["service_id"] = sServiceID;
	return ICS_Oper.GetFunction(ics_log_header(sIcsID,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								theParamIn,"ics_stat_add",theGetResult);
}
/*******************************************************************
Description:	单据tbICSInfo的状态的基本信息的更新---在过滤系统之后
@desc			包括单据在各种情况下的读取
@exception		none
*/
int RobICSOper::UpdateICSRoleInfo(Rob_Ics_Complaint& new_ics_info)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	//where条件
	theParamIn["sICSId"] = new_ics_info.sICSId;
	theParamIn["sServiceID"] = new_ics_info.sServiceID;
	//更新字段

	theParamIn["sRoleLevel"] = new_ics_info.sRoleLevel;
	theParamIn["sRoleName"] = string(GbkToUtf8((char*)new_ics_info.sRoleName.c_str()));
	theParamIn["sRoleID"] = new_ics_info.sRoleID;
	theParamIn["siRobedRoleBan"] = new_ics_info.siRobedRoleBan;
	theParamIn["sVip"]=new_ics_info.sIsVip;
	ValidLOG->WriteLog("---RobICSOper::UpdateICSRoleInfo---sICSId:%s|sServiceID:%s|sRoleLevel:%s|sRoleName:%s|siRobedRoleBan:%s|sVip:%s\n",\
						theParamIn["sICSId"].c_str(),\
						theParamIn["sServiceID"].c_str(),\
						theParamIn["sRoleLevel"].c_str(),\
						theParamIn["sRoleName"].c_str(),\
						theParamIn["siRobedRoleBan"].c_str(),\
															theParamIn["sVip"].c_str());
	return ICS_Oper.GetFunction(ics_log_header(new_ics_info.sICSId,new_ics_info.sUin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								theParamIn,"ics_info_role_update",theGetResult);

}

/*******************************************************************
	Description:	单据tbICSItemFlow读取---在物品追踪系统之前
	@desc			包括单据在各种情况下的读取
	@exception		none
*/
int RobICSOper::ReadICSItemListProc(vector < Item_Flow_List >& robItemFlowInfo,std::string sIcsId)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	Item_Flow_List sTempItemFlow;
	robItemFlowInfo.clear();
	theParamIn["sICSId"]        = sIcsId;
	theParamIn["iDefineAction"] = "1"; //需要处理的单据
	theParamIn["service_id"]    = CRobConf::getConf()->GetGroupInfo()["group_id"];

	ValidLOG->WriteLog("---RobICSOper::ReadICSItemListProc---sICSId:%s\n",sIcsId.c_str());
	iRet = ICS_Oper.GetFunction(ics_log_header(sIcsId,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),theParamIn,"ics_item_flow_query_proc",theGetResult);
	
	if(iRet == 0)
	{
		if(theGetResult.size()==0)
		{
			//没有需要处理追踪的物品
			return STEP_ITEMTRACE_RUN_STAT_ERROR_NO_ICS;
		}
		for(int j=0;j<theGetResult.size();j++)
		{
			sTempItemFlow.dtEventTime          = theGetResult[j]["dtEventTime"];
			sTempItemFlow.ICSID                = theGetResult[j]["iICSId"];
			sTempItemFlow.iDefineProc          = theGetResult[j]["iDefineAction"];
			sTempItemFlow.iFlowAction          = theGetResult[j]["iFlowAction"];
			sTempItemFlow.iItem_Attribute_1    = theGetResult[j]["iItem_Attribute_1"];
			sTempItemFlow.iItem_Id             = theGetResult[j]["iItem_Id"];
			sTempItemFlow.iItem_Level          = theGetResult[j]["iItem_Level"];
			sTempItemFlow.iItem_Name           = theGetResult[j]["iItem_Name"];
			sTempItemFlow.iItem_Num            = theGetResult[j]["iItem_Num"];
			sTempItemFlow.iItem_Price_Value    = theGetResult[j]["iItem_Price_Value"];
			sTempItemFlow.iItem_Type           = theGetResult[j]["iItem_Type"];
			sTempItemFlow.iItem_Unique_Id      = theGetResult[j]["iItem_Unique_Id"];
			sTempItemFlow.iRobed_Uin           = theGetResult[j]["iRobed_Uin"];
			sTempItemFlow.iRobTo_Uin           = theGetResult[j]["iRobTo_Uin"];
			sTempItemFlow.iServiceID           = theGetResult[j]["iServiceID"];
			sTempItemFlow.iWordId              = theGetResult[j]["iWordId"];
			sTempItemFlow.vFlowDsc             = theGetResult[j]["iFlowDesc"];
			sTempItemFlow.vRobed_RoleId        = theGetResult[j]["vRobed_RoleId"];
			sTempItemFlow.vRobed_RoleName      = theGetResult[j]["vRobed_RoleName"];
			sTempItemFlow.vRobTo_RoleId        = theGetResult[j]["vRobTo_RoleId"];
			sTempItemFlow.vRobTo_RoleName      = theGetResult[j]["vRobTo_RoleName"];
			sTempItemFlow.iTraceResult         = theGetResult[j]["iTraceResult"];
			sTempItemFlow.iTraceStat           = theGetResult[j]["iTraceStat"];
			sTempItemFlow.iItem_Attribute_blob = theGetResult[j]["iItem_Attribute_blob"];
			
			robItemFlowInfo.push_back(sTempItemFlow);
		}
	}
	ValidLOG->WriteLog("---RobICSOper::ReadICSItemListProc---GetItemFlowSize():%d\n",robItemFlowInfo.size());
	return 0;
}


int RobICSOper::InsertICSItemTrace(vector < Item_Trace_List >& robItemTrace)
{
	
	ValidLOG->WriteLog("---RobICSOper::InsertICSItemTrace---robItemTrace.size():%d\n",robItemTrace.size());
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	int iFlag = 0;
	for(int j=0;j<robItemTrace.size();j++)
	{
		theParamIn.clear();
		theParamIn["trace_hand"]           = robItemTrace[j].iTraceHand;
		theParamIn["item_level"]           = robItemTrace[j].iItem_Level;
		theParamIn["area"]                 = robItemTrace[j].iWordId;
		theParamIn["role_name"]            = string(GbkToUtf8((char*)robItemTrace[j].vRobed_RoleName.c_str()));
		theParamIn["event_time"]           = robItemTrace[j].dtEventTime;
		theParamIn["rob_uin"]              = robItemTrace[j].iRobTo_Uin;
		theParamIn["rob_roleid"]           = robItemTrace[j].vRobTo_RoleId;
		theParamIn["rob_rolename"]         = string(GbkToUtf8((char*)robItemTrace[j].vRobTo_RoleName.c_str()));
		theParamIn["item_id"]              = robItemTrace[j].iItem_Id;
		theParamIn["item_unique"]          = robItemTrace[j].iItem_Unique_Id;
		theParamIn["item_name"]            = string(GbkToUtf8((char*)robItemTrace[j].iItem_Name.c_str()));
		theParamIn["item_important"]       = robItemTrace[j].iItem_Attribute_1;
		theParamIn["iItem_Attribute_blob"] = robItemTrace[j].iItem_Attribute_blob;
		theParamIn["iItem_Attribute_2"]    = robItemTrace[j].iItem_Attribute_2 != "" ? robItemTrace[j].iItem_Attribute_2: "0";//玩家等级
		theParamIn["iItem_Attribute_3"]    = robItemTrace[j].iItem_Attribute_3;
		theParamIn["action"]               = robItemTrace[j].iFlowAction;
		theParamIn["action_dsc"]           = string(GbkToUtf8((char*)robItemTrace[j].vFlowDsc.c_str()));
		theParamIn["item_type"]            = robItemTrace[j].iItem_Type;
		theParamIn["trace_result"]         = robItemTrace[j].iTraceResult;
		theParamIn["item_num"]             = robItemTrace[j].iItem_Num;
		theParamIn["ics_id"]               = robItemTrace[j].ICSID;
		theParamIn["service_id"]           = robItemTrace[j].iServiceID;
		theParamIn["uin"]                  = robItemTrace[j].iRobed_Uin;
		theParamIn["role_id"]              = robItemTrace[j].vRobed_RoleId;
		theParamIn["send_action"]          = robItemTrace[j].iSendAction;
		theParamIn["send_result"]          = robItemTrace[j].iSendResult;
		//add by v_zhtang 20120524;
		theParamIn["LastFlowAction"]       = robItemTrace[j].Undefined1;
		theParamIn["tradeID"]              = robItemTrace[j].Undefined2 != "" ? robItemTrace[j].Undefined2: "0";//玩家等级;
		//end
		iRet = ICS_Oper.GetFunction(ics_log_header(robItemTrace[j].ICSID,robItemTrace[j].iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									theParamIn,"ics_item_trace_general",theGetResult);
		ValidLOG->WriteLog("---RobICSOper::InsertICSItemTrace---[%d][iRet=%d]\n",j,iRet);
		if (0 != iRet)
		{
			iFlag = 0;
			continue;
		}
	}
	return iFlag;
}


/**
Description:	单据UpdateICSItemFlow状态的【全单据】的变更
@desc			包括单据在各种情况下的状态的【全单据】的变更
@exception		none
*/
int RobICSOper::UpdateICSItemFlow(std::string sIcsId,std::string sServiceID,ApplyItemFlowStat stat,ApplyItemFlowResult res){
	
	ValidLOG->WriteLog("---RobICSOper::UpdateICSItemFlow---sIcsId:%s&sServiceID=%s\n",sIcsId.c_str(),sServiceID.c_str());
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	theParamIn["ics_id"] = sIcsId;
	theParamIn["service_id"] = sServiceID;
	theParamIn["run_result"] = IntToStr(res);
	theParamIn["run_stat"] = IntToStr(stat);
	return  ICS_Oper.GetFunction(ics_log_header(sIcsId,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									theParamIn,"ics_item_flow_runstat_update",theGetResult);
}


/**
Description:	单据tbICSItemTrace的读取赠送列表
@desc			包括单据在各种情况下的读取
@exception		none
*/

int RobICSOper::getICSItemSendList(vector < Item_Trace_List >& robItemList,std::string sIcsId,std::string sServiceId,int type)
{
	ValidLOG->WriteLog("---RobICSOper::getICSItemSendList---sIcsId:%s&sServiceID=%s&sProcType=%d\n",sIcsId.c_str(),sServiceId.c_str(),type);
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, sIcsId.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "---RobICSOper::getICSItemSendList---sIcsId:%s&sServiceID=%s&sProcType=%d\n", sIcsId.c_str(), sServiceId.c_str(), type );
	robItemList.clear();
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	theParamIn["ics_id"]      = sIcsId;
	theParamIn["service_id"]  = sServiceId;
	theParamIn["send_result"] = IntToStr(type);
	iRet =  ICS_Oper.GetFunction(ics_log_header(sIcsId,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),	theParamIn,"ics_item_send_query_proc",theGetResult);
	if(theGetResult.size() <= 0)
	{
		return STEP_ITEMSEND_RUN_STAT_ERROR_NO_LIST;
	}
	ValidLOG->WriteLog("---RobICSOper::getICSItemSendList---theGetResult.size():%d\n",theGetResult.size());
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, sIcsId.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "---RobICSOper::getICSItemSendList---theGetResult.size():%d\n", theGetResult.size() );
	for(int j=0;j<theGetResult.size();j++)
	{
		//这里只需要赠送和变更后面数据的参数即可
		//单据信息
		struTempItemTrace.iID         = theGetResult[j]["iID"];
		struTempItemTrace.ICSID       = theGetResult[j]["iICSId"];
		struTempItemTrace.dtEventTime = theGetResult[j]["dtEventTime"];
		struTempItemTrace.iServiceID  = theGetResult[j]["iServiceID"];
		struTempItemTrace.iSendAction = theGetResult[j]["iSendAction"];
		struTempItemTrace.iTraceHand  = theGetResult[j]["iTraceHand"];
		struTempItemTrace.iSendResult = theGetResult[j]["iSendResult"];
		//物品信息
		struTempItemTrace.iItem_Attribute_1    = theGetResult[j]["iItem_Attribute_1"];
		struTempItemTrace.iItem_Attribute_2    = theGetResult[j]["iItem_Attribute_2"];
		struTempItemTrace.iItem_Attribute_blob = theGetResult[j]["iItem_Attribute_blob"];
		struTempItemTrace.iItem_Id             = theGetResult[j]["iItem_Id"];
		struTempItemTrace.iItem_Level          = theGetResult[j]["iItem_Level"];
		struTempItemTrace.iItem_Name           = theGetResult[j]["iItem_Name"];
		struTempItemTrace.iItem_Num            = theGetResult[j]["iItem_Num"];
		struTempItemTrace.iItem_Type           = theGetResult[j]["iItem_Type"];
		struTempItemTrace.iItem_Unique_Id      = theGetResult[j]["iItem_Unique_Id"];
		struTempItemTrace.iFlowAction          = theGetResult[j]["iFlowAction"];
		//角色信息
		struTempItemTrace.iWordId         = theGetResult[j]["iWordId"];
		struTempItemTrace.iRobed_Uin      = theGetResult[j]["iRobed_Uin"];
		struTempItemTrace.iRobTo_Uin      = theGetResult[j]["iRobTo_Uin"];
		struTempItemTrace.vRobTo_RoleId   = theGetResult[j]["vRobTo_RoleId"];
		struTempItemTrace.vRobed_RoleId   = theGetResult[j]["vRobed_RoleId"];
		struTempItemTrace.vRobed_RoleName = theGetResult[j]["vRobed_RoleName"];
		struTempItemTrace.vRobTo_RoleName = theGetResult[j]["vRobTo_RoleName"];
		struTempItemTrace.Undefined1      =  theGetResult[j]["Undefined1"];
		struTempItemTrace.Undefined2      =  theGetResult[j]["Undefined2"];
		//赋值
		robItemList.push_back(struTempItemTrace);
	}
	ValidLOG->WriteLog("---RobICSOper::getICSItemSendList---over!!!\n");
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, sIcsId.c_str(), "", TLOG_LEVEL_INFO, __FUNCTION__, "---RobICSOper::getICSItemSendList---over!!!\n" );
	return 0;
}

/**
Description:	单据tbICSItemTrace的赠送结果和处理结果的更新
@desc			包括单据在各种情况下的更新
@exception		none
*/
int RobICSOper::updateICSItemSendList(vector < Item_Trace_List >& robItemList)
{
	
	ValidLOG->WriteLog("---RobICSOper::updateICSItemSendList---sIcsId:%s&sServiceID=%s\n",robItemList[0].ICSID.c_str(),robItemList[0].iServiceID.c_str());
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;


	for(int i=0;i<robItemList.size();i++)
	{
		theParamIn.clear();
		theParamIn["ics_id"] = robItemList[i].ICSID;
		theParamIn["service_id"] = robItemList[i].iServiceID;
		theParamIn["send_result"] = robItemList[i].iSendResult;
		theParamIn["guid"] = robItemList[i].iItem_Unique_Id;
		theParamIn["iID"] = robItemList[i].iID;//add by v_zhtang on 2012-11-22
		iRet = ICS_Oper.GetFunction(ics_log_header(robItemList[i].ICSID,robItemList[i].iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									theParamIn,"ics_item_send_runstat_update",theGetResult);
		ValidLOG->WriteLog("---RobICSOper::updateICSItemSendList---iRet:%d\n",iRet);
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, robItemList[i].ICSID.c_str(), robItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "---RobICSOper::updateICSItemSendList---iRet:%d\n", iRet );
	}
	return 0;
}
/**
Description:	单据tbICSComplaint的回复结果更新
@desc			
@exception		none
*/
int RobICSOper::updateICSReplyResult(Rob_Ics_Complaint& _reply_result)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;

	theParamIn["id"]         = _reply_result.sID;
	theParamIn["content"]    = _reply_result.sContent;
	theParamIn["result"]     = _reply_result.siReplyResult;
	theParamIn["service_id"] = CRobConf::getConf()->GetGroupInfo()["group_id"];
	ValidLOG->WriteLog("[STEP:INFO]:::RobICSOper::updateICSReplyResult:[service_id=%s&id=%s&content=%s&result=%s]\n",theParamIn["service_id"].c_str(),theParamIn["id"].c_str(),theParamIn["content"].c_str(),theParamIn["result"].c_str());
	WriteLogsRUN(TLOG_TYPE_ROBICSOPER, _reply_result.sICSId.c_str(), _reply_result.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "[STEP:INFO]:::RobICSOper::updateICSReplyResult:[service_id=%s&id=%s&content=%s&result=%s]\n", theParamIn["service_id"].c_str(), theParamIn["id"].c_str(), theParamIn["content"].c_str(), theParamIn["result"].c_str() );

	ics_log_header header(_reply_result.sICSId,_reply_result.sUin,CRobConf::getConf()->GetGroupInfo()["group_id"]);
	return ICS_Oper.GetFunction(header,theParamIn,"ics_reply_status_update",theGetResult);
}

/*********************************************************************
Description:	查询重复补送物品列表 @add by v_zhtang 2012-11-15;
@				
				ItemInfo: 输入参数
@desc			theResult : 查询结果集
				返回值：-1	查询失败
						0	查询成功，没有重复补送记录
						1	查询成功，有重复补送记录
@exception		none
*/
int RobICSOper::GetReSendList(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult)
{
	map<string,string> inParams;
	inParams.clear();
	inParams["iRobed_Uin"]  = ItemInfo.iRobed_Uin;
	inParams["Guid"]        = ItemInfo.iItem_Unique_Id;
	inParams["iServiceID"]  = ItemInfo.iServiceID;
	inParams["dtEventTime"] = ItemInfo.dtEventTime;
	
	//ics_log_header header(ItemInfo.ICSID, ItemInfo.iRobTo_Uin, ItemInfo.iServiceID);
	int iRet = ICS_Oper.GetFunction( ics_log_header(ItemInfo.ICSID,ItemInfo.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
										inParams, "ics_item_send_result_select", theResult );
	if ( 0 != iRet )
	{
		ValidLOG->WriteLog("查询重复补送物品列表失败");
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(), ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "查询重复补送物品列表失败" );
		return -1;
	}
	else if ( theResult.size() != 0 )
	{
		ValidLOG->WriteLog("查询重复补送物品列表成功，查询到重复补送记录[%d]条", theResult.size() );
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(), ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_WARNING, __FUNCTION__, "查询重复补送物品列表成功，查询到重复补送记录[%d]条", theResult.size() );
		return 1;
	}
	else
	{
		ValidLOG->WriteLog("查询重复补送物品列表成功，未查询到重复补送记录" );
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(), ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "查询重复补送物品列表成功，未查询到重复补送记录" );
		return 0;
	}
}

/*********************************************************************
Description:	重复补送物品，邮件预警、更新邮件预警次数 @add by v_zhtang 2012-11-15;
@				
				ItemInfo: 输入参数
@desc			theResult : 错误信息
				返回值：0-成功 非0-失败
@exception		none
*/
int RobICSOper::UpdateWarnMailCount(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult)
{
	map<string,string> inParams;
	inParams.clear();
	inParams["iRobed_Uin"]  = ItemInfo.iRobed_Uin;
	inParams["Guid"]        = ItemInfo.iItem_Unique_Id;
	inParams["iServiceID"]  = ItemInfo.iServiceID;
	inParams["dtEventTime"] = ItemInfo.dtEventTime;
	
	//ics_log_header header(ItemInfo.ICSID, ItemInfo.iRobTo_Uin, ItemInfo.iServiceID);
	int iRet = ICS_Oper.GetFunction( ics_log_header(ItemInfo.ICSID,ItemInfo.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
										inParams, "ics_item_send_warn_mail_update", theResult );
	if ( 0 == iRet )
	{
		ValidLOG->WriteLog("更新预警邮件次数成功");
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(), ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "更新预警邮件次数成功" );
	}
	else
	{
		ValidLOG->WriteLog("更新预警邮件次数失败");
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(), ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "更新预警邮件次数失败" );
	}
	return iRet;
}

/*********************************************************************
Description:	插入补送物品信息 @add by v_zhtang 2012-11-15;
@				
				ItemInfo: 输入参数
@desc			theResult : 错误信息
				返回值：0-成功 非0-失败
@exception		none
*/
int RobICSOper::InsertSendInfo(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult)
{
	map<string,string> inParamsIst;
	inParamsIst.clear();

	inParamsIst["iICSId"              ] = ItemInfo.ICSID;
	inParamsIst["iServiceID"          ] = ItemInfo.iServiceID;
	inParamsIst["iRobed_Uin"          ] = ItemInfo.iRobed_Uin;
	inParamsIst["vRobed_RoleId"       ] = ItemInfo.vRobed_RoleId;
	inParamsIst["vRobed_RoleName"     ] = string(GbkToUtf8((char*)ItemInfo.vRobed_RoleName.c_str()));
	inParamsIst["iWordId"             ] = ItemInfo.iWordId;
	inParamsIst["dtEventTime"         ] = ItemInfo.dtEventTime;
	inParamsIst["iItem_Id"            ] = ItemInfo.iItem_Id;
	inParamsIst["iItem_Unique_Id"     ] = ItemInfo.iItem_Unique_Id;
	inParamsIst["iItem_Num"           ] = ItemInfo.iItem_Num;
	inParamsIst["iSendResult"         ] = "0";
	inParamsIst["iItem_Attribute_blob"] = ItemInfo.iItem_Attribute_blob;
	inParamsIst["vMemo"               ] = ItemInfo.iItem_Level;//物品等级@@modified by v_zhtang on 2013-01-04
	inParamsIst["Undefined1"          ] = ItemInfo.iItem_Type;//modified by v_zhtang on 2012-12-20;save type for send items;
	
	iRet = ICS_Oper.GetFunction( ics_log_header(ItemInfo.ICSID,ItemInfo.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								inParamsIst, "ics_item_send_info_insert", theResult );
	if ( iRet == 0 )
	{
		ValidLOG->WriteLog("补送物品前，插入补送物品结果成功");
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(), ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "补送物品前，插入补送物品结果成功" );
	}
	else
	{
		ValidLOG->WriteLog("补送物品前，插入补送物品结果失败");
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(), ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "补送物品前，插入补送物品结果失败" );
	}
	return iRet;
}

/*********************************************************************
Description:	更新物品补送结果 @add by v_zhtang 2012-11-15;
@				
				ItemInfo: 输入参数
@desc			theResult : 错误信息
				返回值：0-成功 非0-失败
@exception		none
*/
int RobICSOper::UpdateSendResult(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult)
{
	map<string,string> inParams;
	inParams.clear();
	inParams["iRobed_Uin"]  = ItemInfo.iRobed_Uin;
	inParams["Guid"]        = ItemInfo.iItem_Unique_Id;
	inParams["iSendResult"] = ItemInfo.iSendResult;
	inParams["iServiceID"]  = ItemInfo.iServiceID;
	inParams["dtEventTime"] = ItemInfo.dtEventTime;
	//@added by v_zhtang on 2012-12-31; 更新blob至 补送结果表
	inParams["item_blob"] = ItemInfo.iItem_Attribute_blob;
	
	int iRet = ICS_Oper.GetFunction(ics_log_header(ItemInfo.ICSID,ItemInfo.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									inParams, "ics_item_send_result_update", theResult );
	if ( 0 == iRet )
	{
		ValidLOG->WriteLog("更新补送结果成功");
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(), ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, "更新补送结果成功" );
	}
	else
	{
		ValidLOG->WriteLog("更新补送结果失败");
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(), ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "更新补送结果失败" );
	}
	return iRet;
}

/**
	Description:	单据tbICSItemFlow待礼包补偿物品读取---补送物品之后，差价补偿@add by v_zhtang 2013-1-5;
	@desc			
	@exception		none
*/
int RobICSOper::ReadICSItemsCompensate(vector < Item_Flow_List >& robItemFlowInfo,std::string sIcsId)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	Item_Flow_List sTempItemFlow;
	robItemFlowInfo.clear();
	theParamIn["ics_id"] = sIcsId;//需要处理的单据
	theParamIn["serviceId"] = CRobConf::getConf()->GetGroupInfo()["group_id"];

	ValidLOG->WriteLog("---RobICSOper::ReadICSItemListProc---sICSId:%s\n",sIcsId.c_str());
	iRet = ICS_Oper.GetFunction(ics_log_header(sIcsId,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),\
		theParamIn,"ics_item_compensate_query",theGetResult);
	if(iRet == 0){
		if(theGetResult.size()==0){
			//没有需要处理差价补偿的物品
			return -11;
		}
		for(int j=0;j<theGetResult.size();j++){
			sTempItemFlow.dtEventTime = theGetResult[j]["dtEventTime"];
			sTempItemFlow.ICSID =theGetResult[j]["iICSId"];
			sTempItemFlow.iDefineProc = theGetResult[j]["iDefineAction"];
			sTempItemFlow.iFlowAction = theGetResult[j]["iFlowAction"];
			sTempItemFlow.iItem_Attribute_1 = theGetResult[j]["iItem_Attribute_1"];
			sTempItemFlow.iItem_Attribute_2 = theGetResult[j]["iItem_Attribute_2"];
			sTempItemFlow.iItem_Id = theGetResult[j]["iItem_Id"];
			sTempItemFlow.iItem_Level = theGetResult[j]["iItem_Level"];
			sTempItemFlow.iItem_Name = theGetResult[j]["iItem_Name"];
			sTempItemFlow.iItem_Num = theGetResult[j]["iItem_Num"];
			sTempItemFlow.iItem_Price_Value = theGetResult[j]["iItem_Price_Value"];
			sTempItemFlow.iItem_Type = theGetResult[j]["iItem_Type"];
			sTempItemFlow.iItem_Unique_Id = theGetResult[j]["iItem_Unique_Id"];
			sTempItemFlow.iRobed_Uin = theGetResult[j]["iRobed_Uin"];
			sTempItemFlow.iRobTo_Uin = theGetResult[j]["iRobTo_Uin"];
			sTempItemFlow.iServiceID = theGetResult[j]["iServiceID"];
			sTempItemFlow.iWordId = theGetResult[j]["iWordId"];
			sTempItemFlow.vFlowDsc = theGetResult[j]["iFlowDesc"];
			sTempItemFlow.vRobed_RoleId = theGetResult[j]["vRobed_RoleId"];
			sTempItemFlow.vRobed_RoleName = theGetResult[j]["vRobed_RoleName"];
			sTempItemFlow.vRobTo_RoleId = theGetResult[j]["vRobTo_RoleId"];
			sTempItemFlow.vRobTo_RoleName = theGetResult[j]["vRobTo_RoleName"];
			sTempItemFlow.iTraceResult = theGetResult[j]["iTraceResult"];
			sTempItemFlow.iTraceStat = theGetResult[j]["iTraceStat"];

			robItemFlowInfo.push_back(sTempItemFlow);
		}
	}
	ValidLOG->WriteLog("---RobICSOper::ReadICSItemListProc---GetItemFlowSize():%d\n",robItemFlowInfo.size());
	return 0;
}

/**
	Description:	道具物品价值读取---补送物品之后，差价补偿
	@desc			
	@exception		none
*/
double RobICSOper::GetDefinedGoodsValue(const Item_Flow_List &ItemInfo)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	
	theParamIn["itemId"] = ItemInfo.iItem_Id;//需要处理的单据
	theParamIn["itemLevel"] = ItemInfo.iItem_Level;

	iRet = ICS_Oper.GetFunction(ics_log_header(ItemInfo.ICSID,ItemInfo.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
		theParamIn,"defined_goods_value_query",theGetResult);
	if(iRet == 0){
		if(theGetResult.size()==0){
			//没有
			return 0;
		}
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(),ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
		"该物品【%s】差价补偿价值为【dItemsValue=%lf】\n",ItemInfo.iItem_Unique_Id.c_str(),(StrToDouble(theGetResult[0]["iAveragePrice"])) * StrToInt(ItemInfo.iItem_Num));
		cout << (StrToDouble(theGetResult[0]["iAveragePrice"])) * StrToInt(ItemInfo.iItem_Num) << endl;
		return (StrToDouble(theGetResult[0]["iAveragePrice"])) * StrToInt(ItemInfo.iItem_Num);
	}

}

/**
	Description:	装备价值读取---补送物品之后，差价补偿
	@desc			
	@exception		none
*/

double RobICSOper::GetDefinedEquipValue(const Item_Flow_List &ItemInfo, const string &flag)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theGetResult;
	
	theParamIn["color"] = ItemInfo.iItem_Level;
	theParamIn["prefix"] = ItemInfo.iItem_Attribute_2;//前缀
	theParamIn["flag"] = flag;//封印等级

	iRet = ICS_Oper.GetFunction(ics_log_header(ItemInfo.ICSID,ItemInfo.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
		theParamIn,"defined_equip_value_query",theGetResult);
	if(iRet == 0){
		if(theGetResult.size()==0){
			//没有
			if ("0" != ItemInfo.iItem_Level)
			{
				return 0.1;
			}
			//return 0;
		}
		WriteLogsRUN(TLOG_TYPE_ROBICSOPER, ItemInfo.ICSID.c_str(),ItemInfo.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
		"该物品【%s】差价补偿价值为【dItemsValue=%lf】\n",ItemInfo.iItem_Unique_Id.c_str(),StrToDouble(theGetResult[0]["iItem_Price"]));
		cout << StrToDouble(theGetResult[0]["iItem_Price"]) << endl;
		return StrToDouble(theGetResult[0]["iItem_Price"]);
	}
}

/**
	Description:	更新单据表的undefine1字段，内容为礼包id对应的价值---补送物品之后，差价补偿
	@desc			
	@exception		none
*/
int RobICSOper::UpdateICSCompensateResult(const std::string &sIcsId,const std::string &strGift)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theResult;

	theParamIn["ics_id"] = sIcsId;
	theParamIn["serviceId"] = CRobConf::getConf()->GetGroupInfo()["group_id"];
	theParamIn["gift"] = strGift;

	return ICS_Oper.GetFunction(ics_log_header(sIcsId,"",CRobConf::getConf()->GetGroupInfo()["group_id"]),\
		theParamIn,"update_ics_compensate_result",theResult);
}

/*********************************************************************
	Description:	更新物品补送结果 @add by v_zhtang 2013-01-4;
	@params			
					enumLastResult: 读取哪些阶段异常的
					ItemSend: 返回的读取结果
					Size : 一次读取的大小
					ics_id：读取指定单据
	@return			返回值：0-成功 非0-失败
	@exception		none
*/
int RobICSOper::ReadRehandleItems(ApplyRehandleResult enumLastResult,Item_Trace_List ItemSend[],int Size,string ics_id)
{
	string sCmdFlg("");

	map<string,string> theParamIn;
	vector < map<string, string> > theResult;

	if (enumLastResult == (ApplyRehandleResult)STEP_REHANDLE_ITEM_SEND_FAILURE)
	{
#ifdef ylzt
		theParamIn["result"] = IntToStr(STEP_ITEMSEND_RUN_STAT_SEND_FINISH);
#endif
		theParamIn["iServiceID"] = CRobConf::getConf()->GetGroupInfo()["group_id"];

		if ("" == ics_id)
		{
			theParamIn["size"] = IntToStr(Size);
			sCmdFlg = "send_rehandle_item_list";
		}else
		{
			theParamIn["ics_id"] = ics_id;
			sCmdFlg = "send_rehandle_item_one";
		}

		int iRet = ICS_Oper.GetFunction(ics_log_header("","",CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									theParamIn, sCmdFlg.c_str(), theResult );
		if (theResult.size() > 0 && 0 == iRet)
		{
			for (int i=0; i<theResult.size(); i++)
			{
				ItemSend[i].iID = theResult[i]["iID"];
				ItemSend[i].ICSID = theResult[i]["iICSId"];
				ItemSend[i].iRobed_Uin = theResult[i]["iRobed_Uin"];
				ItemSend[i].vRobed_RoleId = theResult[i]["vRobed_RoleId"];
				ItemSend[i].vRobed_RoleName = theResult[i]["vRobed_RoleName"];
				ItemSend[i].iWordId = theResult[i]["iWordId"];
				ItemSend[i].iSendResult = theResult[i]["iSendResult"];
				ItemSend[i].iServiceID = theResult[i]["iServiceID"];
				ItemSend[i].iItem_Unique_Id = theResult[i]["iItem_Unique_Id"];
				ItemSend[i].iItem_Type = theResult[i]["Undefined1"];
				ItemSend[i].iItem_Level = theResult[i]["vMemo"];
				ItemSend[i].iItem_Num = theResult[i]["iItem_Num"];
				ItemSend[i].iItem_Id = theResult[i]["iItem_Id"];
				ItemSend[i].iItem_Attribute_blob = theResult[i]["iItem_Attribute_blob"];
			}
		}
	}else
	{

	}

	return theResult.size();
}

/*********************************************************************
	Description:	二次处理再一次更新物品补送结果 @add by v_zhtang 2013-01-4;
	@params			
					
					ItemSend: 物品补送信息
					
	@return			返回值：0-成功 非0-失败
	@exception		none
*/
int RobICSOper::ReHandleUpdateSendItems(Item_Trace_List &ItemSend)
{
	map<string,string> theParamIn;
	vector < map<string, string> > theResult;

	theParamIn["iServiceID"] = CRobConf::getConf()->GetGroupInfo()["group_id"];
	theParamIn["iID"] = ItemSend.iID;
	theParamIn["result"] = ItemSend.iSendResult;
	theParamIn["blob"] = ItemSend.iItem_Attribute_blob;

	return ICS_Oper.GetFunction(ics_log_header("","",CRobConf::getConf()->GetGroupInfo()["group_id"]),\
		theParamIn, "send_rehandle_update_item", theResult );
}

void RobICSOper::WriteTdwLog(Rob_Ics_Complaint &ics_info)
{
	//WriteLogstdw(char* serverid,char* ics, char* uin, char* roleid, char* rolename, char* rolelevel,
	//char* role_ban, char* world, char* booktime, char* lastLogintime, char* robedtime, char* updatetime,char* vip,
	//char* Step, char* result, char* stat, char* Source)
	
	WriteLogstdw((char *)ics_info.sServiceID.c_str(),(char *)ics_info.sICSId.c_str(), (char *)ics_info.sUin.c_str(), (char *)ics_info.sRoleID.c_str(), GbkToUtf8((char *)ics_info.sRoleName.c_str()), (char *)ics_info.sRoleLevel.c_str(),	"", (char *)ics_info.sWordId.c_str(), (char *)ics_info.stBookTime.c_str(), (char *)ics_info.stLastLogin.c_str(), (char *)ics_info.stRobeLogin.c_str(), (char *)ics_info.sUpdateTime.c_str(), (char *)ics_info.sIsVip.c_str(), (char *)ics_info.sICSAnaylseStep.c_str(), (char *)ics_info.sICSAnaylseResult.c_str(), (char *)ics_info.sICSAnaylseStat.c_str(), (char *)ics_info.siSource.c_str());
	(char *)ics_info.sServiceID.c_str();
}
