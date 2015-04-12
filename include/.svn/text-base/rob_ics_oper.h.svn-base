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
	Description:	单据tbICSInfo读取
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	unsigned int ReadICSInfoListNew(ApplyAnaylseStep_New enumApplyAnaylseStep,Qhelper_Ics_Complaint get_ics_info[],int get_size);

	/**
	Description:	单据内存更新
	@exception		none
	@return 		int 操作接口返回结果
	*/

	int SaveAutoHalfIcsInfo(Qhelper_Ics_Complaint& present_item_res, map<string,string>& input_params);

	
	/**
	Description:	单据tbICSInfo的更新，主要是状态，结果，步骤的更新
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	int UpdateICSProc(std::string sIcsID,ApplyAnaylseStep_New enumApplyAnaylseStep,ApplyAnaylseResult_New enumApplyAnaylseResult);

	
	/************************************************************************/
	/* *********************************************************************** */
	/************************************************************************/


	/**
	Description:	单据tbICSInfo读取指定一条
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	unsigned int ReadICSInfoOneItem(ApplyAnaylseStep enumApplyAnaylseStep,Rob_Ics_Complaint get_ics_info[],string ics_id);

	/**
	Description:	单据tbICSInfo读取
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	unsigned int ReadICSInfoList(ApplyAnaylseStep enumApplyAnaylseStep,Rob_Ics_Complaint get_ics_info[],int get_size);

	/**
	Description:	单据内存更新
	@exception		none
	@return 		int 操作接口返回结果
	*/

	int SaveAutoHalfIcsInfo(Rob_Ics_Complaint& present_item_res, map<string,string>& input_params);

	/**
	Description:	单据tbICSInfo的更新，主要是状态，结果，步骤的更新
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	int UpdateICSProc(std::string sIcsID,ApplyAnaylseStep enumApplyAnaylseStep,ApplyAnaylseResult enumApplyAnaylseResult,ApplyAnaylseStat enumApplyAnaylseStat);


	/**
	Description:	单据tbICSRoleLogout插入
	@desc			包括单据在读取异常登录时间段插入
	@exception		none
	*/
	int InsertICSRobSlotData(Rob_SLOT& robSlotTime);
	

	/**
	Description:	单据tbICSRoleLogout获取
	@desc			包括单据在读取异常登录时间段获取
	@exception		none
	*/
	int ReadICSRobSlot(std::vector < Rob_SLOT > &robSlotList,std::string sServiceId,std::string sICS_Id);
	/**
	Description:	单据tbICSRoleLogout更新
	@desc			包括单据在的运行阶段
	@exception		none
	*/
	int UpdateICSRobSlotProc(std::string sServiceId,std::string sICS_Id, ApplySlotStat eRunStat);


	/**
	Description:	单据tbICSItemFlow生成
	@desc			包括单据在异常登录时间段内的物品流水生成
	@exception		none
	*/
	int InsertICSRobItemFlowData(std::vector < Item_Flow_List > &robItemFlow,std::string sServiceId);




	/**
	Description:	单据tbICSItemStats的统计库的初始化插入
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	int AddICSItemStatsProc(std::string sIcsID,std::string sServiceID);


	/**
	Description:	单据tbICSItemStats的统计库的补送前的物品统计更新
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	int UpdateICSItemStatsProc(std::string sUpdateType,vector <string>& vUpdateNum,std::string sIcsId);

	/**
	Description:	单据tbICSItemStats的统计库的最后补送物品统计更新
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/	
	int updateICSItemStatsResult(std::string sUpdateType,vector <string>& vUpdateNum,std::string sIcsId);
	
	/**
	Description:	单据tbICSInfo的状态的基本信息的更新---在过滤系统之前
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	int UpdateICSRoleInfo(Rob_Ics_Complaint& new_ics_info);
	
	/**
	Description:	单据tbICSItemFlow读取---在物品追踪系统之前
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	int ReadICSItemListProc(vector < Item_Flow_List >& robItemFlowInfo,std::string sIcsId);


	/**
	Description:	单据UpdateICSItemFlow状态的【全单据】的变更
	@desc			包括单据在各种情况下的状态的【全单据】的变更
	@exception		none
	*/
	int UpdateICSItemFlow(std::string sIcsId,std::string sServiceID,ApplyItemFlowStat stat,ApplyItemFlowResult res);



	/**
	Description:	单据tbICSItemTrace生成
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	int InsertICSItemTrace(vector < Item_Trace_List >& robItemTrace);




	/**
	Description:	单据tbICSItemTrace的读取赠送列表
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	int getICSItemSendList(vector < Item_Trace_List >& robItemList,std::string sIcsId,std::string sServiceId,int type=0);


	/**
	Description:	单据tbICSItemTrace的赠送结果和处理结果的更新
	@desc			包括单据在各种情况下的更新
	@exception		none
	*/
	int updateICSItemSendList(vector < Item_Trace_List >& robItemList);


	/**
	Description:	单据tbICSComplaint的回复结果和处理结果的更新
	@desc			包括单据在各种情况下的更新
	@exception		none
	*/
	int updateICSReplyResult(Rob_Ics_Complaint& _reply_result);


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
	int GetReSendList(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult);
	
	/*********************************************************************
	Description:	重复补送物品，邮件预警、更新邮件预警次数 @add by v_zhtang 2012-11-15;
	@				
					ItemInfo: 输入参数
	@desc			theResult : 错误信息
					返回值：0-成功 非0-失败
	@exception		none
	*/
	int UpdateWarnMailCount(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult);
	
	/*********************************************************************
	Description:	插入补送物品信息 @add by v_zhtang 2012-11-15;
	@				
					ItemInfo: 输入参数
	@desc			theResult : 错误信息
					返回值：0-成功 非0-失败
	@exception		none
	*/
	int InsertSendInfo(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult);
	
	/*********************************************************************
	Description:	更新物品补送结果 @add by v_zhtang 2012-11-15;
	@				
					ItemInfo: 输入参数
	@desc			theResult : 错误信息
					返回值：0-成功 非0-失败
	@exception		none
	*/
	int UpdateSendResult(Item_Trace_List &ItemInfo, vector < map<string, string> > &theResult);
	
	//@add by v_zhtang 2013-1-5;
	/**
	Description:	单据tbICSItemFlow待礼包补偿物品读取---补送物品之后，差价补偿
	@desc			
	@exception		none
	*/
	int ReadICSItemsCompensate(vector < Item_Flow_List >& robItemFlowInfo,std::string sIcsId);

	/**
	Description:	道具物品价值读取---补送物品之后，差价补偿
	@desc			
	@return			正值：返回的价值 其他失败
	@exception		none
	*/
	double GetDefinedGoodsValue(const Item_Flow_List &ItemInfo);

	/**
	Description:	装备价值读取---补送物品之后，差价补偿
	@desc			
	@return			正值：返回的价值 其他失败
	@exception		none
	*/
	double GetDefinedEquipValue(const Item_Flow_List &ItemInfo, const string &flag);

	/**
	Description:	更新单据表的undefine1字段，内容为礼包id对应的价值---补送物品之后，差价补偿
	@desc			
	@exception		none
	*/
	int UpdateICSCompensateResult(const std::string &sIcsId,const std::string &strGift);
	//@end add
	
	/*********************************************************************
	Description:	读取补送异常的物品list @add by v_zhtang 2013-01-4;
	@params			
					enumLastResult: 读取哪些阶段异常的
					ItemSend: 返回的读取结果
					Size : 一次读取的大小
					ics_id：读取指定单据
	@return			返回值：0-成功 非0-失败
	@exception		none
	*/
	int ReadRehandleItems(ApplyRehandleResult enumLastResult,Item_Trace_List ItemSend[],int Size,string ics_id="");

	/*********************************************************************
	Description:	二次处理再一次更新物品补送结果 @add by v_zhtang 2013-01-4;
	@params			
					
					ItemSend: 物品补送信息
					
	@return			返回值：0-成功 非0-失败
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
