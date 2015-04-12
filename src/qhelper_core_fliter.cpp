/**
@file qhelper_core_anaylse.cpp

@brief 

	
	---------------------------------------------------------
	Qhelper自助分析功能
	
	分析的单据必须是单据合法的；
	处理过程如下，
	1) 获取要分析的单据；
	2) 单据过滤系统; 
	3) 单据状态更新;
	---------------------------------------------------------

@details
Copyright (c) 2012 Tencent. All rights reserved.

@author		asherzhou
@version	1.0
@date		2011/02/13
</PRE>
*/
#include <iostream>
#include "rob_anlys_valid.h"
#include "rob_rule_logic.h"
#include "rob_ics_oper.h"
#include "log.h"
#include "msg.h"
#include "glog.h"
#include "rob_anlys_ip.h"
#include "comm_datetime.h"
#include "comm_strings.h"
#include "conf.h"


int main(int argc, char** argv)
{
	//调试日志
	CLog* ICSFliterLOG;
	
	//基础模块类
	RobICSOper icsOper;
	RobRuleValid icsCheckValid;
	RobRuleLogic icsRobRuleLogic;
	int iRet = 0;

	//调试日志的初始化
	GetCurDateDay();
	std::string sICSFliterLOG="./logs/"+GetCurDateDay()+"QhelperICSFliter.log";
	ICSFliterLOG = new CLog((const char*)sICSFliterLOG.c_str());
	ICSFliterLOG->LogOn();
	
	
	ICSFliterLOG->WriteLog("------------------Start QhelperICSFliter-----------------\n");
#ifdef dnf2
	ICSFliterLOG->WriteLog("------------------In The [dnf2] Prcosess-----------------\n");
#endif
	int SIZE_OF_ICS = StrToInt(CRobConf::getConf()->GetIcsValid()["size_of_ics_one"]);
	ICSFliterLOG->WriteLog("Read ICS Count is %d\n",SIZE_OF_ICS);
	
	/*****************************************************************************************
	@   A: 内存储存，Rob_Ics_Complaint
	@	1.读取SIZE_OF_ICS的单据信息，存在Ics_Info的数组
	*/
	Qhelper_Ics_Complaint Ics_Info[SIZE_OF_ICS];

	map<string,string> theParamIn;
	vector < map<string,string> > icsResult;
	
	int size_of_ics_info = icsOper.ReadICSInfoListNew(STEP_WAITING_RUN_ICS_NEW,Ics_Info,SIZE_OF_ICS);
	if(size_of_ics_info > 0 && size_of_ics_info <= SIZE_OF_ICS){
		ICSFliterLOG->WriteLog("ReadICSInfo GET ics_info size:%d and less than SIZE_OF_ICS Successfully\n",size_of_ics_info);
		//2.更新单据状态为处理中
		for(int j=0;j<size_of_ics_info;j++){
			iRet = icsOper.UpdateICSProc(Ics_Info[j].sICSId,STEP_FLITER_RUN_ICS_NEW, STEP_FLITER_RUNNING_STAT_NEW);
			ICSFliterLOG->WriteLog("UpdateICSProc iRet:%d\n",iRet);
			if(iRet!=0){
				//这里需要邮件报警处理！后续版本控制
				ICSFliterLOG->WriteLog("UpdateICSProc Happend Error-iRet:%d\n",iRet);
			}
		}
	}else{
		ICSFliterLOG->WriteLog("ReadICSInfo GET ics_info size:%d Happend Error\n",size_of_ics_info);
		delete ICSFliterLOG;
		ICSFliterLOG = NULL;
		return -1;
	}
	/*****************************************************************************************
	@   B: 利用读取的信息进行相关过滤系统给的判断，Rob_Ics_Complaint
	@	1.循环判断和读取
	*/
	for(int i=0;i<size_of_ics_info;i++)
	{
		iRet = icsCheckValid.DoICSCheckPro(Ics_Info[i]);
		ICSFliterLOG->WriteLog("icsCheckValid.DoICSCheck iRetResult:%d\n",iRet);
		if((ApplyAnaylseResult_New)iRet==STEP_FLITER_RUN_STAT_SUCCESS_NEW){
			ICSFliterLOG->WriteLog("单据【%s】验证正确!!!\n",Ics_Info[i].sICSId.c_str());
			icsOper.UpdateICSProc(Ics_Info[i].sICSId,STEP_FLITER_RUN_ICS_NEW,(ApplyAnaylseResult_New)iRet);
		}else{
			ICSFliterLOG->WriteLog("单据【%s】验证失败!!!\n",Ics_Info[i].sICSId.c_str());
			icsOper.UpdateICSProc(Ics_Info[i].sICSId,STEP_FLITER_FAILED_ICS_NEW,(ApplyAnaylseResult_New)iRet);
		}
	
		//// 3.角色基本信息更新
		//iRet = icsOper.UpdateICSRoleInfo(Ics_Info[i]);
		//if(iRet!=0){
		//	ICSFliterLOG->WriteLog("单据【%s】角色基本信息更新失败!!!返回码：%d\n",Ics_Info[i].sICSId.c_str(),iRet);
		//}
		//ICSFliterLOG->WriteLog("单据【%s】角色基本信息更新成功!!!返回码：%d\n",Ics_Info[i].sICSId.c_str(),iRet);
	}

	if (NULL != ICSFliterLOG)
	{
		delete ICSFliterLOG;
		ICSFliterLOG = NULL;
	}

	return 0;

}
