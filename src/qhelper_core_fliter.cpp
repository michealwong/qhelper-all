/**
@file qhelper_core_anaylse.cpp

@brief 

	
	---------------------------------------------------------
	Qhelper������������
	
	�����ĵ��ݱ����ǵ��ݺϷ��ģ�
	����������£�
	1) ��ȡҪ�����ĵ��ݣ�
	2) ���ݹ���ϵͳ; 
	3) ����״̬����;
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
	//������־
	CLog* ICSFliterLOG;
	
	//����ģ����
	RobICSOper icsOper;
	RobRuleValid icsCheckValid;
	RobRuleLogic icsRobRuleLogic;
	int iRet = 0;

	//������־�ĳ�ʼ��
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
	@   A: �ڴ洢�棬Rob_Ics_Complaint
	@	1.��ȡSIZE_OF_ICS�ĵ�����Ϣ������Ics_Info������
	*/
	Qhelper_Ics_Complaint Ics_Info[SIZE_OF_ICS];

	map<string,string> theParamIn;
	vector < map<string,string> > icsResult;
	
	int size_of_ics_info = icsOper.ReadICSInfoListNew(STEP_WAITING_RUN_ICS_NEW,Ics_Info,SIZE_OF_ICS);
	if(size_of_ics_info > 0 && size_of_ics_info <= SIZE_OF_ICS){
		ICSFliterLOG->WriteLog("ReadICSInfo GET ics_info size:%d and less than SIZE_OF_ICS Successfully\n",size_of_ics_info);
		//2.���µ���״̬Ϊ������
		for(int j=0;j<size_of_ics_info;j++){
			iRet = icsOper.UpdateICSProc(Ics_Info[j].sICSId,STEP_FLITER_RUN_ICS_NEW, STEP_FLITER_RUNNING_STAT_NEW);
			ICSFliterLOG->WriteLog("UpdateICSProc iRet:%d\n",iRet);
			if(iRet!=0){
				//������Ҫ�ʼ��������������汾����
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
	@   B: ���ö�ȡ����Ϣ������ع���ϵͳ�����жϣ�Rob_Ics_Complaint
	@	1.ѭ���жϺͶ�ȡ
	*/
	for(int i=0;i<size_of_ics_info;i++)
	{
		iRet = icsCheckValid.DoICSCheckPro(Ics_Info[i]);
		ICSFliterLOG->WriteLog("icsCheckValid.DoICSCheck iRetResult:%d\n",iRet);
		if((ApplyAnaylseResult_New)iRet==STEP_FLITER_RUN_STAT_SUCCESS_NEW){
			ICSFliterLOG->WriteLog("���ݡ�%s����֤��ȷ!!!\n",Ics_Info[i].sICSId.c_str());
			icsOper.UpdateICSProc(Ics_Info[i].sICSId,STEP_FLITER_RUN_ICS_NEW,(ApplyAnaylseResult_New)iRet);
		}else{
			ICSFliterLOG->WriteLog("���ݡ�%s����֤ʧ��!!!\n",Ics_Info[i].sICSId.c_str());
			icsOper.UpdateICSProc(Ics_Info[i].sICSId,STEP_FLITER_FAILED_ICS_NEW,(ApplyAnaylseResult_New)iRet);
		}
	
		//// 3.��ɫ������Ϣ����
		//iRet = icsOper.UpdateICSRoleInfo(Ics_Info[i]);
		//if(iRet!=0){
		//	ICSFliterLOG->WriteLog("���ݡ�%s����ɫ������Ϣ����ʧ��!!!�����룺%d\n",Ics_Info[i].sICSId.c_str(),iRet);
		//}
		//ICSFliterLOG->WriteLog("���ݡ�%s����ɫ������Ϣ���³ɹ�!!!�����룺%d\n",Ics_Info[i].sICSId.c_str(),iRet);
	}

	if (NULL != ICSFliterLOG)
	{
		delete ICSFliterLOG;
		ICSFliterLOG = NULL;
	}

	return 0;

}
