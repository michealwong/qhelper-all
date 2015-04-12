#ifndef __ROB_RULE_LOGIC_H__
#define __ROB_RULE_LOGIC_H__

#include <iostream>
#include "msg.h"
#include "glog.h"
#include "log.h"
#include "comm_logmanager.h"
#include "HttpRpc.h"
#include "rob_ics_oper.h"
#include <algorithm>

#define SEND_EQUIP_CMD	75711
#define SEND_GOODS_CMD	31015
#define DEL_BAG_CMD		71123
#define DEL_STORAGE_CMD	71124
#define KICK_PLAYER_OFF_CMD	75501
#define DEL_CONSIGNMENT_CMD	6346
#define DEL_MAIL_ACCESSORY_CMD	6343

#define CONSIGNMENT_START_ACTION	136//寄售扣除
#define MAIL_ACCESSORY_ACTION	301
#define CONSIGNMENT_TIMEOUT_ACTION	140//寄售超时
#define CONSIGNMENT_PURCHASE_ACTION	142//寄售购买
#define CONSIGNMENT_CANCEL_ACTION	141//寄售退出
#define STORAGE_IN_ACTION	5//存入仓库


#define STALLBUY_ACTION	61
#define P2P_DEDUCT_ACTION	13

#define ABANDON_ACTION	140//玩家销毁,消耗
#define NPC_DEDUCT_ACTION	30//NPC卖，消耗
#define EQUIP_SPLIT_ACTION	90//装备分解，消耗
#define FEED_HORSE_ACTION	80

#define BAN_LEVEL_LIMIT		20	//封号处理，等级限制

class RobRuleLogic
{
  public:
	/*********************************************************************
	Description:	Default constructor
	@exception		none
	*/
	RobRuleLogic();
	virtual ~RobRuleLogic();

	/*********************************************************************
	Description:	获取业务的找寻物品的list的size（）主要验证类的初始化的正确性。
	@desc			存在map<string,string> vItemProList;
	@exception		none
	*/
	int getItemListSize();
	/*********************************************************************
	Description:	获取业务的找寻物品的list是否存在制定item_id。
	@desc			存在map<string,string> vItemProList;
	@exception		none
	*/
	bool checkItemNeedProc(string iItem_id);
	/*********************************************************************
	Description:	获取业务的找寻物品的list的物品贵重性。
	@desc			存在map<string,string> vItemProList;
	@exception		none
	*/
	std::map<string,string> getItemValueLevel();

	bool IsNeedFind(string strItemID);
	/*********************************************************************
	Description:	获取getRoleItemFlowList()的物品流水。
	@desc			包括单据在各种情况下的读取
	@exception		none
	*/
	int getRoleItemFlowList(std::vector< Item_Flow_List > &rob_Item_List,std::vector< Rob_SLOT> &rob_data,string vip="0");

	/*********************************************************************
	Description:	物品guid的位置所在
	@desc			
	@exception		none
	*/
	int getRobItemLocation(const string &ics_id, const string &robed_to_uin, const string &area, const string &GUID, string &location);

	/*********************************************************************
	Description:	获取getRobItemTrace()物品追踪日志（按guid）
	@				分为：NoTracking 和 ByTracking的两种情况
	@desc			包括盗号时间段情况下的读物品追踪。
	@exception		none
	*/
	int getRobItemTraceNoTracking(std::vector< Item_Trace_List > &TraceResult,Item_Flow_List &FlowParams, vector< map<string,string> >& vecItemFirstLast);

	int getRobItemTraceNoTracking(std::vector< Item_Trace_List > &TraceResult,std::vector< Item_Flow_List > &FlowParams, string strLogin="0", string strRobed="0");
	/*********************************************************************
	Description:	根据物品流水记录某物品guid查找该物品最后一手，判断是否还在游戏当中
	@				分为：若丢弃、销毁则不在游戏当中，不追踪；若交易中(p2p、邮件等)，则继续追踪
	@desc			包括按guid物品最后一手流水接口
	@exception		none
	*/
	int robItemTraceJudge(int &iTraceProcFlag,Item_Flow_List &ItemFlow, vector< map<string,string> >& vecItemFlowLast);
	/*********************************************************************
	Description:	根据物品流水记录某物品guid查找该物品所有交易流水，包括p2p、邮件、摆摊等
	@
	@desc			包括按guid物品交易流水接口
	@exception		none
	*/
	int robItemTraceByGuid(vector <Item_Trace_List> &vecItemTrace,Item_Flow_List &ItemFlow, vector< map<string,string> >& vecItemFirstLast);
	/*********************************************************************
	Description:	根据物品追踪结果保存相关信息
	@desc			
	@exception		none
	*/	
	int SaveItemTrace(const Item_Flow_List& ItemFlow, map<string, string>& mapItemRes, Item_Trace_List& ItemTrace);
	/*********************************************************************
	Description:	删除玩家身上或仓库物品
	@desc			
	@exception		none
	@retun			0:删除成功，	非0:删除失败
	*/	
	int PlayerItemDel(Item_Trace_List& ItemTrace, const char* strOperFlag);
	/*********************************************************************
	Description:	根据最后一手动作id，删除玩家寄售行、邮件附件物品
	@desc			
	@exception		none
	@retun			0:删除成功，	非0:删除失败
	*/	
	int PlayerItemDelMailorConsi(Item_Trace_List& ItemTrace);
	/*********************************************************************
	Description:	获取doRobItemSend()物品补送接口
	@				分为：各个业务需要单独来定义自己的流程，详细的见代码
	@desc			包括盗号时间段情况下的物品补送接口。
	@exception		none
	*/
	int doRobItemSend(std::vector< Item_Trace_List > &ItemList, int &iWarnFlag);
	/*********************************************************************
	Description:	物品删除总接口  added by v_zhtang on 2012-10-11;
	@				分为：各个业务需要单独来定义自己的流程，详细的见代码
	@desc			
	@exception		none
	*/
	int doRobItemDelete(Item_Trace_List &ItemList);//modified by v_zhtang on 2012-12-19
	/*********************************************************************
	Description:	记录敏感日志
	@				
	@desc			
	@exception		none
	*/
	int LogCM(const Item_Trace_List &ItemList,
			  const string& strOptType, 
			  const string& strReason, 
			  const string& strMemo,
			  const string& strFuntionName,
			  const string& iUin,
			  const string& iRoleId,
			  const string& vRoleName,
			  const string& strCmd,
			  const int& iResult,
			  const string& StrSerial);
	/************************************************************************/
	/* Description:	 获取物品blob（按一定规则）                                                                     */
	   
	/************************************************************************/
	int FetchItemBlob(Item_Trace_List &ItemList,vector < map<string, string> > &theItemBlobResult);

	/*********************************************************************
	Description:	将等级物品的道具按照90+level+ItemId整合,返回形如900xxxxx的虚拟编号字符串
	@				
	@desc			
	@exception		none
	*/
	string ItemIdLevelTransfer(Item_Trace_List &ItemList);


	/*********************************************************************
	Description:	获取doReplayIcsResult()二次单据回复处理结果
	@				依据不同的结果来发送WEB接口回复
	@desc			包括盗号时间段情况下的所有情况的处理回复
	@exception		none
	*/
	int doReplayIcsResult(Rob_Ics_Complaint& autoReplayICS, string& sSource);

	/*********************************************************************
	Description:	发邮件
	@				
	@desc			
	@exception		none
	*/
	int SendWarnMail(const string& mailTitle, const string& mailContext);

	/*********************************************************************
	Description:	封停玩家QQ
	@				
	@desc			type: 0：全服封停帐号
	@exception		none
	*/
	int BanQQ(Item_Trace_List& ItemTrace, const string& sMemo, const unsigned int iTime, const int type=0);

	/*********************************************************************
	Description:	查询玩家在线信息
	@				
	@desc			负值表查询失败，1：表在线，0：表不在线
	@exception		none
	*/
	int CheckOnline(Item_Trace_List& ItemTrace,const string& uin, const string& roleId, const string& roleName);
	
	/****************************added by v_zhtang on 2012-12-12*****************************************
	Description:	对于找回范围物品，正常流转或拔取失败的物品，给与等价礼包赠送
	@param			sIcsId: 待处理单据
	@return			0：成功，非0：失败
	@exception		none
	*/
	int DoGiftCompensate(Rob_Ics_Complaint &sIcsId);

	/*****************************added by v_zhtang on 2012-12-18****************************************
	Description:	查询封印等级；查流水时，顺便记录该区的封印等级IDIP
	@param			
					SealLevel: 查询封印等级结果
	@return			0：成功，非0：失败
	@exception		none
	*/
	int QuerySealLevel(const string &sICSID,const string &sUin,const string &sArea,string &SealLevel);

	/*****************************added by v_zhtang on 2013-1-5****************************************
	Description:	统计该ics单据所有该统计列表的价值
	@param			
				robItemFlowInfo:		被统计列表
				ItemValueTotal：		    返回的价值，单位RMB
	@return			正值：返回的价值 其他失败
	@exception		none
	*/
	double GetICSItemValue(vector < Item_Flow_List > &robItemFlowInfo);

	/*****************************added by v_zhtang on 2013-1-16****************************************
	Description:	获取被盗装备的异常登入前的最后星级
	@param			
				rob_slot:		异常时间段
				item_guid：		装备guid
				cur_star:	返回的星级
	@return			0：成功，非0：失败
	@exception		none
	*/
	int GetItemCurStarBeforeLogin(Rob_SLOT &rob_slot, string &item_guid, string &cur_star);

	/*****************************added by v_zhtang on 2013-1-25****************************************
	Description:	判断补偿礼包的次数
	@param			
				Rob_Ics_Complaint:		投诉单据
			
	@return			0：成功，非0：失败
	@exception		none
	*/
	int CheckGiftSendCount(Rob_Ics_Complaint &info);
	
	/*********************************************************************
	Description:	重新二次补偿物品
	@				
	@desc			
	@exception		none
	*/
	int ReHandleSendItems(Item_Trace_List& ItemSend);

	CLog *RuleLOG;
	GLog RuleGet;
  protected:
	void LoadItemProcList();
  private:
	string ROBRULELOG;
	std::map<string,string> vItemProList;
	std::vector< string > vetNeedFindIDs;
	std::map<string,string> mapIDandNames;
	std::map<string,string> vItemValueList;
	std::map<string, string> vItemAddableList;
	std::map<string,string> mReplyContentList;//回复内容map
	//added by v_zhtang on 2012-12-31;
	std::map<string,string> vItemUseLevelList;
	std::map<string,string> vItemStarValueList;
	//end add;
	string iItemValueType;
	Item_Flow_List struTempItemFlow;
	Item_Trace_List struTempItemTrace;
	int iRet ;

	HttpRpc _rob_httpRpc;
	HttpRpc _rob_httpRpc_R;
	string _rob_httpRpc_proxy;
	string _rob_httpRpc_url;
	string _rob_httpRpc_proxy_R;
	string _rob_httpRpc_url_R;

	//added by v_zhtang on 2013-1-7
	HttpRpc _rob_httpRpc_T;
	string _rob_httpRpc_proxy_T;
	string _rob_httpRpc_url_T;
	//end add;

};

#endif