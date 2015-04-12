/**
@file rob_ics_oper.h
@brief 
@details	Copyright (c) 2011 Tencent. All rights reserved.
@author		asherzhou
@version	2.0
@date		2011/05/20

history:
<PRE>
History ID	:	2
Author    	:	asherzhou
DateTime	:	2011/05/21
Description :	Create
</PRE>
*/

#ifndef __ROB_ICS_OPER_H__
#define	__ROB_ICS_OPER_H__

#include <iostream>
#include <string>
#include "comm_datetime.h"
#include "comm_strings.h"
#include "msg.h"
#include "glog.h"
#include "conf.h"
#include "log.h"
#include "comm_logmanager.h"

class RobICSOper
{

public:
	/**
	Description:	Default constructor
	@exception		none
	*/
	RobICSOper();
	~RobICSOper();

	CLog *ValidLOG;
	GLog ICS_Oper;


	/**
	Description:	����tbICSInfo��ȡ
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	unsigned int ReadICSInfoListNew(ApplyAnaylseStep_New enumApplyAnaylseStep,Qhelper_Ics_Complaint get_ics_info[],int get_size);

	/**
	Description:	�����ڴ����
	@exception		none
	@return 		int �����ӿڷ��ؽ��
	*/

	int SaveAutoHalfIcsInfo(Qhelper_Ics_Complaint& present_item_res, map<string,string>& input_params);

	
	/**
	Description:	����tbICSInfo�ĸ��£���Ҫ��״̬�����������ĸ���
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	int UpdateICSProc(std::string sIcsID,ApplyAnaylseStep_New enumApplyAnaylseStep,ApplyAnaylseResult_New enumApplyAnaylseResult);

	
	/************************************************************************/
	/* *********************************************************************** */
	/************************************************************************/


	/**
	Description:	����tbICSInfo��ȡָ��һ��
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	unsigned int ReadICSInfoOneItem(ApplyAnaylseStep enumApplyAnaylseStep,Rob_Ics_Complaint get_ics_info[],string ics_id);

	/**
	Description:	����tbICSInfo��ȡ
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	unsigned int ReadICSInfoList(ApplyAnaylseStep enumApplyAnaylseStep,Rob_Ics_Complaint get_ics_info[],int get_size);

	/**
	Description:	�����ڴ����
	@exception		none
	@return 		int �����ӿڷ��ؽ��
	*/

	int SaveAutoHalfIcsInfo(Rob_Ics_Complaint& present_item_res, map<string,string>& input_params);

	/**
	Description:	����tbICSInfo�ĸ��£���Ҫ��״̬�����������ĸ���
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	int UpdateICSProc(std::string sIcsID,ApplyAnaylseStep enumApplyAnaylseStep,ApplyAnaylseResult enumApplyAnaylseResult,ApplyAnaylseStat enumApplyAnaylseStat);


	/**
	Description:	����tbICSRoleLogout����
	@desc			���������ڶ�ȡ�쳣��¼ʱ��β���
	@exception		none
	*/
	int InsertICSRobSlotData(Rob_SLOT& robSlotTime);
	

	/**
	Description:	����tbICSRoleLogout��ȡ
	@desc			���������ڶ�ȡ�쳣��¼ʱ��λ�ȡ
	@exception		none
	*/
	int ReadICSRobSlot(std::vector < Rob_SLOT > &robSlotList,std::string sServiceId,std::string sICS_Id);
	/**
	Description:	����tbICSRoleLogout����
	@desc			���������ڵ����н׶�
	@exception		none
	*/
	int UpdateICSRobSlotProc(std::string sServiceId,std::string sICS_Id, ApplySlotStat eRunStat);


	/**
	Description:	����tbICSItemFlow����
	@desc			�����������쳣��¼ʱ����ڵ���Ʒ��ˮ����
	@exception		none
	*/
	int InsertICSRobItemFlowData(std::vector < Item_Flow_List > &robItemFlow,std::string sServiceId);




	/**
	Description:	����tbICSItemStats��ͳ�ƿ�ĳ�ʼ������
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	int AddICSItemStatsProc(std::string sIcsID,std::string sServiceID);


	/**
	Description:	����tbICSItemStats��ͳ�ƿ�Ĳ���ǰ����Ʒͳ�Ƹ���
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	int UpdateICSItemStatsProc(std::string sUpdateType,vector <string>& vUpdateNum,std::string sIcsId);

	/**
	Description:	����tbICSItemStats��ͳ�ƿ���������Ʒͳ�Ƹ���
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/	
	int updateICSItemStatsResult(std::string sUpdateType,vector <string>& vUpdateNum,std::string sIcsId);
	
	/**
	Description:	����tbICSInfo��״̬�Ļ�����Ϣ�ĸ���---�ڹ���ϵͳ֮ǰ
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	int UpdateICSRoleInfo(Rob_Ics_Complaint& new_ics_info);
	
	/**
	Description:	����tbICSItemFlow��ȡ---����Ʒ׷��ϵͳ֮ǰ
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	int ReadICSItemListProc(vector < Item_Flow_List >& robItemFlowInfo,std::string sIcsId);


	/**
	Description:	����UpdateICSItemFlow״̬�ġ�ȫ���ݡ��ı��
	@desc			���������ڸ�������µ�״̬�ġ�ȫ���ݡ��ı��
	@exception		none
	*/
	int UpdateICSItemFlow(std::string sIcsId,std::string sServiceID,ApplyItemFlowStat stat,ApplyItemFlowResult res);



	/**
	Description:	����tbICSItemTrace����
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	int InsertICSItemTrace(vector < Item_Trace_List >& robItemTrace);




	/**
	Description:	����tbICSItemTrace�Ķ�ȡ�����б�
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	int getICSItemSendList(vector < Item_Trace_List >& robItemList,std::string sIcsId,std::string sServiceId,int type=0);


	/**
	Description:	����tbICSItemTrace�����ͽ���ʹ������ĸ���
	@desc			���������ڸ�������µĸ���
	@exception		none
	*/
	int updateICSItemSendList(vector < Item_Trace_List >& robItemList);


	/**
	Description:	����tbICSComplaint�Ļظ�����ʹ������ĸ���
	@desc			���������ڸ�������µĸ���
	@exception		none
	*/
	int updateICSReplyResult(Rob_Ics_Complaint& _reply_result);


	/*********************************************************************
	Description:	��ѯ�ظ�������Ʒ�б� @add by v_zhtang 2012-11-15;
	@				
					ItemInfo: �������
	@desc			theResult : ��ѯ�����
					����ֵ��-1	��ѯʧ��
							0	��ѯ�ɹ���û���ظ����ͼ�¼
							1	��ѯ�ɹ������ظ����ͼ�¼
	@exception		none
	*/
	int GetReSendList(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult);
	
	/*********************************************************************
	Description:	�ظ�������Ʒ���ʼ�Ԥ���������ʼ�Ԥ������ @add by v_zhtang 2012-11-15;
	@				
					ItemInfo: �������
	@desc			theResult : ������Ϣ
					����ֵ��0-�ɹ� ��0-ʧ��
	@exception		none
	*/
	int UpdateWarnMailCount(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult);
	
	/*********************************************************************
	Description:	���벹����Ʒ��Ϣ @add by v_zhtang 2012-11-15;
	@				
					ItemInfo: �������
	@desc			theResult : ������Ϣ
					����ֵ��0-�ɹ� ��0-ʧ��
	@exception		none
	*/
	int InsertSendInfo(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult);
	
	/*********************************************************************
	Description:	������Ʒ���ͽ�� @add by v_zhtang 2012-11-15;
	@				
					ItemInfo: �������
	@desc			theResult : ������Ϣ
					����ֵ��0-�ɹ� ��0-ʧ��
	@exception		none
	*/
	int UpdateSendResult(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult);
	
	//@add by v_zhtang 2013-1-5;
	/**
	Description:	����tbICSItemFlow�����������Ʒ��ȡ---������Ʒ֮�󣬲�۲���
	@desc			
	@exception		none
	*/
	int ReadICSItemsCompensate(vector < Item_Flow_List >& robItemFlowInfo,std::string sIcsId);

	/**
	Description:	������Ʒ��ֵ��ȡ---������Ʒ֮�󣬲�۲���
	@desc			
	@return			��ֵ�����صļ�ֵ ����ʧ��
	@exception		none
	*/
	double GetDefinedGoodsValue(const Item_Flow_List &ItemInfo);

	/**
	Description:	װ����ֵ��ȡ---������Ʒ֮�󣬲�۲���
	@desc			
	@return			��ֵ�����صļ�ֵ ����ʧ��
	@exception		none
	*/
	double GetDefinedEquipValue(const Item_Flow_List &ItemInfo, const string &flag);

	/**
	Description:	���µ��ݱ��undefine1�ֶΣ�����Ϊ���id��Ӧ�ļ�ֵ---������Ʒ֮�󣬲�۲���
	@desc			
	@exception		none
	*/
	int UpdateICSCompensateResult(const std::string &sIcsId,const std::string &strGift);
	//@end add
	
	/*********************************************************************
	Description:	��ȡ�����쳣����Ʒlist @add by v_zhtang 2013-01-4;
	@params			
					enumLastResult: ��ȡ��Щ�׶��쳣��
					ItemSend: ���صĶ�ȡ���
					Size : һ�ζ�ȡ�Ĵ�С
					ics_id����ȡָ������
	@return			����ֵ��0-�ɹ� ��0-ʧ��
	@exception		none
	*/
	int ReadRehandleItems(ApplyRehandleResult enumLastResult,Item_Trace_List ItemSend[],int Size,string ics_id="");

	/*********************************************************************
	Description:	���δ�����һ�θ�����Ʒ���ͽ�� @add by v_zhtang 2013-01-4;
	@params			
					
					ItemSend: ��Ʒ������Ϣ
					
	@return			����ֵ��0-�ɹ� ��0-ʧ��
	@exception		none
	*/
	int ReHandleUpdateSendItems(Item_Trace_List &ItemSend);
	
	void WriteTdwLog(Rob_Ics_Complaint & ics_info);
private:
	std::string ICSOPERLOG;
	Item_Trace_List struTempItemTrace;
	int iRet;
};



#endif
