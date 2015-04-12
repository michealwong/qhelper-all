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

#define CONSIGNMENT_START_ACTION	136//���ۿ۳�
#define MAIL_ACCESSORY_ACTION	301
#define CONSIGNMENT_TIMEOUT_ACTION	140//���۳�ʱ
#define CONSIGNMENT_PURCHASE_ACTION	142//���۹���
#define CONSIGNMENT_CANCEL_ACTION	141//�����˳�
#define STORAGE_IN_ACTION	5//����ֿ�


#define STALLBUY_ACTION	61
#define P2P_DEDUCT_ACTION	13

#define ABANDON_ACTION	140//�������,����
#define NPC_DEDUCT_ACTION	30//NPC��������
#define EQUIP_SPLIT_ACTION	90//װ���ֽ⣬����
#define FEED_HORSE_ACTION	80

#define BAN_LEVEL_LIMIT		20	//��Ŵ����ȼ�����

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
	Description:	��ȡҵ�����Ѱ��Ʒ��list��size������Ҫ��֤��ĳ�ʼ������ȷ�ԡ�
	@desc			����map<string,string> vItemProList;
	@exception		none
	*/
	int getItemListSize();
	/*********************************************************************
	Description:	��ȡҵ�����Ѱ��Ʒ��list�Ƿ�����ƶ�item_id��
	@desc			����map<string,string> vItemProList;
	@exception		none
	*/
	bool checkItemNeedProc(string iItem_id);
	/*********************************************************************
	Description:	��ȡҵ�����Ѱ��Ʒ��list����Ʒ�����ԡ�
	@desc			����map<string,string> vItemProList;
	@exception		none
	*/
	std::map<string,string> getItemValueLevel();

	bool IsNeedFind(string strItemID);
	/*********************************************************************
	Description:	��ȡgetRoleItemFlowList()����Ʒ��ˮ��
	@desc			���������ڸ�������µĶ�ȡ
	@exception		none
	*/
	int getRoleItemFlowList(std::vector< Item_Flow_List > &rob_Item_List,std::vector< Rob_SLOT> &rob_data,string vip="0");

	/*********************************************************************
	Description:	��Ʒguid��λ������
	@desc			
	@exception		none
	*/
	int getRobItemLocation(const string &ics_id, const string &robed_to_uin, const string &area, const string &GUID, string &location);

	/*********************************************************************
	Description:	��ȡgetRobItemTrace()��Ʒ׷����־����guid��
	@				��Ϊ��NoTracking �� ByTracking���������
	@desc			��������ʱ�������µĶ���Ʒ׷�١�
	@exception		none
	*/
	int getRobItemTraceNoTracking(std::vector< Item_Trace_List > &TraceResult,Item_Flow_List &FlowParams, vector< map<string,string> >& vecItemFirstLast);

	int getRobItemTraceNoTracking(std::vector< Item_Trace_List > &TraceResult,std::vector< Item_Flow_List > &FlowParams, string strLogin="0", string strRobed="0");
	/*********************************************************************
	Description:	������Ʒ��ˮ��¼ĳ��Ʒguid���Ҹ���Ʒ���һ�֣��ж��Ƿ�����Ϸ����
	@				��Ϊ��������������������Ϸ���У���׷�٣���������(p2p���ʼ���)�������׷��
	@desc			������guid��Ʒ���һ����ˮ�ӿ�
	@exception		none
	*/
	int robItemTraceJudge(int &iTraceProcFlag,Item_Flow_List &ItemFlow, vector< map<string,string> >& vecItemFlowLast);
	/*********************************************************************
	Description:	������Ʒ��ˮ��¼ĳ��Ʒguid���Ҹ���Ʒ���н�����ˮ������p2p���ʼ�����̯��
	@
	@desc			������guid��Ʒ������ˮ�ӿ�
	@exception		none
	*/
	int robItemTraceByGuid(vector <Item_Trace_List> &vecItemTrace,Item_Flow_List &ItemFlow, vector< map<string,string> >& vecItemFirstLast);
	/*********************************************************************
	Description:	������Ʒ׷�ٽ�����������Ϣ
	@desc			
	@exception		none
	*/	
	int SaveItemTrace(const Item_Flow_List& ItemFlow, map<string, string>& mapItemRes, Item_Trace_List& ItemTrace);
	/*********************************************************************
	Description:	ɾ��������ϻ�ֿ���Ʒ
	@desc			
	@exception		none
	@retun			0:ɾ���ɹ���	��0:ɾ��ʧ��
	*/	
	int PlayerItemDel(Item_Trace_List& ItemTrace, const char* strOperFlag);
	/*********************************************************************
	Description:	�������һ�ֶ���id��ɾ����Ҽ����С��ʼ�������Ʒ
	@desc			
	@exception		none
	@retun			0:ɾ���ɹ���	��0:ɾ��ʧ��
	*/	
	int PlayerItemDelMailorConsi(Item_Trace_List& ItemTrace);
	/*********************************************************************
	Description:	��ȡdoRobItemSend()��Ʒ���ͽӿ�
	@				��Ϊ������ҵ����Ҫ�����������Լ������̣���ϸ�ļ�����
	@desc			��������ʱ�������µ���Ʒ���ͽӿڡ�
	@exception		none
	*/
	int doRobItemSend(std::vector< Item_Trace_List > &ItemList, int &iWarnFlag);
	/*********************************************************************
	Description:	��Ʒɾ���ܽӿ�  added by v_zhtang on 2012-10-11;
	@				��Ϊ������ҵ����Ҫ�����������Լ������̣���ϸ�ļ�����
	@desc			
	@exception		none
	*/
	int doRobItemDelete(Item_Trace_List &ItemList);//modified by v_zhtang on 2012-12-19
	/*********************************************************************
	Description:	��¼������־
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
	/* Description:	 ��ȡ��Ʒblob����һ������                                                                     */
	   
	/************************************************************************/
	int FetchItemBlob(Item_Trace_List &ItemList,vector < map<string, string> > &theItemBlobResult);

	/*********************************************************************
	Description:	���ȼ���Ʒ�ĵ��߰���90+level+ItemId����,��������900xxxxx���������ַ���
	@				
	@desc			
	@exception		none
	*/
	string ItemIdLevelTransfer(Item_Trace_List &ItemList);


	/*********************************************************************
	Description:	��ȡdoReplayIcsResult()���ε��ݻظ�������
	@				���ݲ�ͬ�Ľ��������WEB�ӿڻظ�
	@desc			��������ʱ�������µ���������Ĵ���ظ�
	@exception		none
	*/
	int doReplayIcsResult(Rob_Ics_Complaint& autoReplayICS, string& sSource);

	/*********************************************************************
	Description:	���ʼ�
	@				
	@desc			
	@exception		none
	*/
	int SendWarnMail(const string& mailTitle, const string& mailContext);

	/*********************************************************************
	Description:	��ͣ���QQ
	@				
	@desc			type: 0��ȫ����ͣ�ʺ�
	@exception		none
	*/
	int BanQQ(Item_Trace_List& ItemTrace, const string& sMemo, const unsigned int iTime, const int type=0);

	/*********************************************************************
	Description:	��ѯ���������Ϣ
	@				
	@desc			��ֵ���ѯʧ�ܣ�1�������ߣ�0��������
	@exception		none
	*/
	int CheckOnline(Item_Trace_List& ItemTrace,const string& uin, const string& roleId, const string& roleName);
	
	/****************************added by v_zhtang on 2012-12-12*****************************************
	Description:	�����һط�Χ��Ʒ��������ת���ȡʧ�ܵ���Ʒ������ȼ��������
	@param			sIcsId: ��������
	@return			0���ɹ�����0��ʧ��
	@exception		none
	*/
	int DoGiftCompensate(Rob_Ics_Complaint &sIcsId);

	/*****************************added by v_zhtang on 2012-12-18****************************************
	Description:	��ѯ��ӡ�ȼ�������ˮʱ��˳���¼�����ķ�ӡ�ȼ�IDIP
	@param			
					SealLevel: ��ѯ��ӡ�ȼ����
	@return			0���ɹ�����0��ʧ��
	@exception		none
	*/
	int QuerySealLevel(const string &sICSID,const string &sUin,const string &sArea,string &SealLevel);

	/*****************************added by v_zhtang on 2013-1-5****************************************
	Description:	ͳ�Ƹ�ics�������и�ͳ���б�ļ�ֵ
	@param			
				robItemFlowInfo:		��ͳ���б�
				ItemValueTotal��		    ���صļ�ֵ����λRMB
	@return			��ֵ�����صļ�ֵ ����ʧ��
	@exception		none
	*/
	double GetICSItemValue(vector < Item_Flow_List > &robItemFlowInfo);

	/*****************************added by v_zhtang on 2013-1-16****************************************
	Description:	��ȡ����װ�����쳣����ǰ������Ǽ�
	@param			
				rob_slot:		�쳣ʱ���
				item_guid��		װ��guid
				cur_star:	���ص��Ǽ�
	@return			0���ɹ�����0��ʧ��
	@exception		none
	*/
	int GetItemCurStarBeforeLogin(Rob_SLOT &rob_slot, string &item_guid, string &cur_star);

	/*****************************added by v_zhtang on 2013-1-25****************************************
	Description:	�жϲ�������Ĵ���
	@param			
				Rob_Ics_Complaint:		Ͷ�ߵ���
			
	@return			0���ɹ�����0��ʧ��
	@exception		none
	*/
	int CheckGiftSendCount(Rob_Ics_Complaint &info);
	
	/*********************************************************************
	Description:	���¶��β�����Ʒ
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
	std::map<string,string> mReplyContentList;//�ظ�����map
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