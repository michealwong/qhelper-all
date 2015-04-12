#include "rob_rule_logic.h"
#include "msg.h"
#include "iplib.h"
#include "comm_datetime.h"
#include "comm_strings.h"
#include "comm_value.h"
#include "conf.h"
#include "comm.h"
#include "comm_logmanager.h"
#include "rob_ics_oper.h"
RobRuleLogic::RobRuleLogic()
{
	ROBRULELOG ="./logs/"+GetCurDateDay()+"RobRuleGlog.log";
	RuleLOG = new CLog((char*)ROBRULELOG.c_str());
	RuleLOG->LogOn();
	iRet=0;
	vItemProList.clear();
	mReplyContentList.clear();
	vetNeedFindIDs.clear();
	mapIDandNames.clear();

	//加载道具过滤库、动作过滤库

	_rob_httpRpc_proxy =CRobConf::getConf()->GetCommonInterface()["web_http_proxy_O"];
	_rob_httpRpc_url = CRobConf::getConf()->GetCommonInterface()["web_http_url_O"];
	_rob_httpRpc.SetProxy(_rob_httpRpc_proxy);

	_rob_httpRpc_proxy_R = CRobConf::getConf()->GetCommonInterface()["web_http_proxy_R"];
	_rob_httpRpc_url_R = CRobConf::getConf()->GetCommonInterface()["web_http_url_R"];
	_rob_httpRpc_R.SetProxy(_rob_httpRpc_proxy_R);

	//added by v_zhtang on 2013-1-7
	_rob_httpRpc_proxy_T = CRobConf::getConf()->GetCommonInterface()["web_http_proxy_T"];
	_rob_httpRpc_url_T = CRobConf::getConf()->GetCommonInterface()["web_http_url_T"];
	_rob_httpRpc_T.SetProxy(_rob_httpRpc_proxy_T);
	//end add

	LoadItemProcList();
}

RobRuleLogic::~RobRuleLogic()
{
	if(RuleLOG!=NULL)
	{
		delete RuleLOG;
	}
}
/*********************************************************************
	Description:	获取业务的找寻物品的list
	@desc			存在map<string,string> vItemProList;
	@exception		none
*/
void RobRuleLogic::LoadItemProcList()
{
	/*这里直接LoadTab来实现*/
	string filepath = "";
#if dzs
	filepath = "./cfg/NeeFindIDs.conf";
	LoadNeedFindIDs(filepath, vetNeedFindIDs);
	filepath = "./cfg/IDandNames.conf";
	LoadTabToNamevsID(filepath, mapIDandNames);
#endif
// 
// 	int i = mapIDandNames.size();
// 	string strName = mapIDandNames["450400"];
// 
// 	for (map<string, string>::iterator it=mapIDandNames.begin(); it!=mapIDandNames.end(); it++)
// 	{
// 		RuleLOG->WriteLog("size:[%s]   strName:[%s]\n",it->first.c_str(),it->second.c_str());
// 	}
// 	RuleLOG->WriteLog("size:[%d]\t strName:[%s]\n",i,strName.c_str());
}
/*********************************************************************
	Description:	获取业务的找寻物品的list的size（）主要验证类的初始化的正确性。
	@desc			存在map<string,string> vItemProList;
	@exception		none
*/
int RobRuleLogic::getItemListSize()
{
	return vItemProList.size();
}
/*********************************************************************
	Description:	获取业务的找寻物品的list是否存在制定item_id。
	@desc			存在map<string,string> vItemProList;
	@exception		none
*/
bool RobRuleLogic::checkItemNeedProc(string iItem_id)
{
	return vItemProList.find((char*)iItem_id.c_str()) == vItemProList.end() ? false : true;
}

bool RobRuleLogic::IsNeedFind(string strItemID)
{
	vector< string >::iterator iteBegin = vetNeedFindIDs.begin();
	vector< string >::iterator iteEnd   = vetNeedFindIDs.end();

	vector< string >::iterator itePos   = find(iteBegin, iteEnd, strItemID);
	return itePos==iteEnd ? false : true;
}
/*********************************************************************
	Description:	获取业务的找寻物品的list的size（）主要验证类的无凭初始化的正确性。
	@desc			存在map<string,string> vItemProList;
	@exception		none
*/
std::map<string,string> RobRuleLogic::getItemValueLevel()
{
	return vItemValueList;
}

int RobRuleLogic::getRoleItemFlowList(std::vector< Item_Flow_List > &rob_Item_List,std::vector< Rob_SLOT> &rob_data,string vip)
{
	map<string,string> inParams;
	vector < map<string, string> > theItemListResult;
	int iSlotCouFlag = rob_data.size();
	rob_Item_List.clear();
	RuleLOG->WriteLog("获取玩家的异常登录条数【%d】\n",iSlotCouFlag);
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "获取玩家的异常登录条数【%d】\n", iSlotCouFlag );

	for(int j=0;j<rob_data.size();j++)
	{
		inParams.clear();
		inParams["uin"]            = rob_data[j].UserID;
		inParams["area"]           = rob_data[j].WorldID;
		inParams["start_datetime"] = rob_data[j].LoginTime;
		inParams["end_datetime"]   = rob_data[j].LogoutTime;
		inParams["rolename"]       = GbkToUtf8((char*)rob_data[j].RoleName.c_str());
		//inParams["action"] = "(7,13,15,61,6)";

		RuleLOG->WriteLog("--->单号【%s】数据：uin=%s&area=%s&role_name=%s&start_time=%s&end_time=%s\n",rob_data[j].ICSID.c_str(),\
							inParams["uin"].c_str(),\
							inParams["area"].c_str(),\
							inParams["rolename"].c_str(),\
							inParams["start_datetime"].c_str(),\
							inParams["end_datetime"].c_str());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, rob_data[j].ICSID.c_str(), rob_data[j].UserID.c_str(), TLOG_LEVEL_INFO, __FUNCTION__,\
						 "--->单号【%s】数据：uin=%s&area=%s&role_name=%s&start_time=%s&end_time=%s\n",rob_data[j].ICSID.c_str(),\
							inParams["uin"].c_str(),\
							inParams["area"].c_str(),\
							inParams["rolename"].c_str(),\
							inParams["start_datetime"].c_str(),\
							inParams["end_datetime"].c_str());

			string str1 =  inParams["uin"];
			string str2 =  inParams["area"];
			string str3 =  inParams["start_datetime"];
			string str4 =  inParams["end_datetime"];
			string str5 =  inParams["rolename"];

			string str6 = CRobConf::getConf()->GetGroupInfo()["group_id"];
			

		iRet = RuleGet.GetFunction(ics_log_header(rob_data[j].ICSID,rob_data[j].UserID,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									inParams,"ics_role_item_flow_query",theItemListResult);
		if (0 != iRet)
		{
			RuleLOG->WriteLog("Get getRoleItemFlowList Glog Interface Error Res(%d) and DataResult'Size(%d)\n",iRet,theItemListResult.size());
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, rob_data[j].ICSID.c_str(), rob_data[j].UserID.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "Get getRoleItemFlowList Glog Interface Error Res(%d) and DataResult'Size(%d)\n",iRet,theItemListResult.size() );
			continue;
		}
		if(theItemListResult.size()==0&&iSlotCouFlag!=1)
		{
			RuleLOG->WriteLog("循环的大小【%d】判断FLAG数据大小【%d】\n",theItemListResult.size(),iSlotCouFlag);
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, rob_data[j].ICSID.c_str(), rob_data[j].UserID.c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "循环的大小【%d】判断FLAG数据大小【%d】\n",theItemListResult.size(),iSlotCouFlag );
			iSlotCouFlag--;
			RuleLOG->WriteLog("循环的大小【%d】判断FLAG数据大小变为【%d】\n",theItemListResult.size(),iSlotCouFlag);
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, rob_data[j].ICSID.c_str(), rob_data[j].UserID.c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "循环的大小【%d】判断FLAG数据大小变为【%d】\n",theItemListResult.size(),iSlotCouFlag );
			continue;
		}
		else if(theItemListResult.size()==0&&iSlotCouFlag==1)
		{
			RuleLOG->WriteLog("theItemListResult的大小【0】判断FLAG数据大小变为【1】\n");
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, rob_data[j].ICSID.c_str(), rob_data[j].UserID.c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "theItemListResult的大小【0】判断FLAG数据大小变为【1】\n" );
			return STEP_ITEMFLOW_RUN_STAT_ERROR_NO_FLOW;
		}
		else
		{
			RuleLOG->WriteLog("获得物品流水数据接口返回【%d】数据大小【%d】\n",iRet,theItemListResult.size());
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, rob_data[j].ICSID.c_str(), rob_data[j].UserID.c_str(), TLOG_LEVEL_DEBUG, __FUNCTION__, "获得物品流水数据接口返回【%d】数据大小【%d】\n",iRet,theItemListResult.size() );
			for(int k=0;k<theItemListResult.size();k++)
			{	
				struTempItemFlow.iServiceID      = rob_data[j].ServiceID;
				struTempItemFlow.iWordId         = rob_data[j].WorldID;
				struTempItemFlow.ICSID           = rob_data[j].ICSID;
				struTempItemFlow.vRobed_RoleId   = rob_data[j].RoleID;
				struTempItemFlow.iRobed_Uin      = rob_data[j].UserID;
				struTempItemFlow.vRobed_RoleName = rob_data[j].RoleName;
				//这里为以后版本流接口
				struTempItemFlow.iItem_Type      = theItemListResult[k]["iItemType"];
				struTempItemFlow.iRobTo_Uin      = "0";
				struTempItemFlow.vRobTo_RoleName = "0";
				struTempItemFlow.vRobTo_RoleId   = "0";
				struTempItemFlow.iFlowAction     = theItemListResult[k]["iAction"];
				//struTempItemFlow.vFlowDsc      = theItemListResult[k]["iFlowType"];//动作性质描述: 0= , 1= , 2= 
				//这里为以后版本流接口
				struTempItemFlow.iDefineProc     = "1"; //需要处理
#ifdef dzs
				//a.只处理基础等级物品，高等级物品不处理---针对全体用户适用
				//b.只处理强化等级<=15等级的物品---针对权限用户适用
				//c.对于加强物品且小于15级的,VIP用户补送，基础用户不补送
				/*d.iDefineProc的定义
					0 未处理定义
					1 需要处理
					2 人工处理
					3 处理完成
					14 高等级物品，不需要处理或者转人工
					15 高加强物品，不需要处理或者转人工
					16 非VIP用户，无法处理VIP补送物品
					40 物品价值更新完毕 */
				
				struTempItemFlow.dtEventTime          = theItemListResult[k]["dtEventTime"];
				string strNum                         = theItemListResult[k]["iItemNum"];
				struTempItemFlow.iItem_Num            = IntToStr(abs(StrToInt(strNum)));
				struTempItemFlow.iItem_Id             = theItemListResult[k]["iItemId"];
				struTempItemFlow.iItem_Unique_Id      = theItemListResult[k]["iItemGuid"];
				struTempItemFlow.iItem_Name           = mapIDandNames[theItemListResult[k]["iItemName"]];
				struTempItemFlow.iItem_Level          = "0";
				struTempItemFlow.iItem_Price_Value    = "0";	
				struTempItemFlow.iItem_Attribute_1    = "0";
				struTempItemFlow.iItem_Attribute_2    = "0";
				struTempItemFlow.iItem_Attribute_blob = theItemListResult[k]["vItemBlob"];
#endif
				//added by v_zhtang on 2013-1-21 check the unique of items
				string strGuidTmp = theItemListResult[k]["iItemGuid"];
				bool bExist = false;
				for (int m=0; m<rob_Item_List.size(); m++)
				{
					if (rob_Item_List[m].iItem_Unique_Id == strGuidTmp)
					{
						bExist = true;
					}
				}
				if (!bExist) 
				{
					rob_Item_List.push_back(struTempItemFlow);
				}
				//end added.
			}
		}
	}
	return 0;
}
/*********************************************************************
	Description:	获取物品guid位置
	@desc			pos: 物品所在位置（0 背包 1衣橱 2任务包 3个人仓库 4账号仓库 5骑宠插槽 6插槽 7回购列表 8其它位置)
	@exception		none
*/
int RobRuleLogic::getRobItemLocation(const string &ics_id, const string &robed_to_uin, const string &area, const string &GUID, string &pos)
{
	map<string,string> inParams;
	vector < map<string, string> > theLocationResult;
	int iRet = 0;

	inParams["area"] = area;
	inParams["item_id"] = GUID;

	iRet = RuleGet.GetFunction(ics_log_header(ics_id,robed_to_uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								inParams,"ics_rob_item_location",theLocationResult);
	if (0 != iRet)
	{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ics_id.c_str(),robed_to_uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, 
			"Glog Interface Error Res(%d) and DataResult'Size(%d)\n",iRet,theLocationResult.size());
	}else
	{
		if (theLocationResult.size() > 0)
		{
			pos = theLocationResult[0]["pos"];
		}
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ics_id.c_str(),robed_to_uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, 
			"Glog Interface Error Res(%d) and DataResult'Size(%d)\n",iRet,theLocationResult.size());
	}	
	return iRet;
}
/*********************************************************************
Description:	根据物品流水记录某物品guid查找该物品最后一手，判断是否还在游戏当中
@				分为：若丢弃、销毁则不在游戏当中，不追踪；若交易中(p2p、邮件等)，则继续追踪
@desc			包括按guid物品最后一手流水接口
				
@exception		none
*/
int RobRuleLogic::robItemTraceJudge(int &iTraceProcFlag,Item_Flow_List &ItemFlow, vector< map<string,string> >& vecItemFlowLast)
{
	/******按guid查物品流水最后一手*****/
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(),ItemFlow.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, 
				"Begin to Call [robItemTraceJudge]:按guid[%s]查物品流水最后一手 \n",ItemFlow.iItem_Unique_Id.c_str());
	map<string,string> mapInParam;
	map<int,string> mapDisappear;
	int iRet = 0;

	//接口入参
	mapInParam.clear();
	mapInParam["guid"] = ItemFlow.iItem_Unique_Id;
	mapInParam["area"] = ItemFlow.iWordId;
	mapInParam["dtEventTime"] = ItemFlow.dtEventTime;
	
	iRet = RuleGet.GetFunction(ics_log_header(ItemFlow.ICSID,ItemFlow.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								mapInParam,"ics_flow_info_by_guid",vecItemFlowLast);
	if (0 != iRet)
	{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(),ItemFlow.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"End to Call [robItemTraceJudge]:获取该物品【%s】最后一手流转失败,返回值为：iRet=%d \n",ItemFlow.iItem_Unique_Id.c_str(),iRet);
		return iRet;
	}
	else
	{
		//正确获取最后一手流转记录
		if (vecItemFlowLast.size() >= 1)
		{
			ItemFlow.iLastFlowAction = vecItemFlowLast[0]["iAction"];//找到最后一手流转动作
			//ItemFlow.vFlowDsc = vecItemFlowLast[0]["iFlowType"];//动作类型
			//ItemFlow.vRobTo_RoleLevel = vecItemFlowLast[0]["iRoleLevel"];//找到最后一手玩家等级//added by v_zhtang on 2012-12-20
			ItemFlow.iRobTo_Uin = vecItemFlowLast[0]["qqid"] == "" ? "0" : vecItemFlowLast[0]["qqid"];
			ItemFlow.vRobTo_RoleId = vecItemFlowLast[0]["idofRole"] == "" ? "0" : vecItemFlowLast[0]["idofRole"];
			ItemFlow.vRobTo_RoleName = vecItemFlowLast[0]["vRoleName"] == "" ? "0" : vecItemFlowLast[0]["vRoleName"];

			//用iItem_Attribute_3字段记录该guid物品所属类型或所属表（普通道具、重要道具、装备）
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(),ItemFlow.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"[robItemTraceJudge]:按guid[%s]查物品最后一流水[%s]\n",ItemFlow.iItem_Unique_Id.c_str(),ItemFlow.iLastFlowAction.c_str());
			ItemFlow.iItem_Attribute_3 = vecItemFlowLast[0]["ItemTypeFlow"];//注意：该字段是sql查询时自定义的
		
 			if ("1" != ItemFlow.vFlowDsc)// 还在游戏中
 			{
 				iTraceProcFlag = 1;
 				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(),ItemFlow.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
 					"End to Call [robItemTraceJudge]:按guid[%s]查物品流水最后一手结束：【需要继续追踪】 \n",ItemFlow.iItem_Unique_Id.c_str());
 				return 0;
 			}
 			else
 			{//消耗掉，消失了
 				iTraceProcFlag = 0;
 				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(),ItemFlow.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
 					"End to Call [robItemTraceJudge]:按guid[%s]查物品流水最后一手结束: 【不需要追踪】 \n",ItemFlow.iItem_Unique_Id.c_str());
 				return 0;
 			}
		}
		return -5;//无日志
	}
}
/*********************************************************************
Description:	根据物品流水记录某物品guid查找该物品所有交易流水，包括p2p、邮件、摆摊、开始寄售等表
@
@desc			包括按guid物品交易流水接口
@exception		none
*/
int RobRuleLogic::robItemTraceByGuid(vector <Item_Trace_List> &vecItemTrace,Item_Flow_List &ItemFlow, vector< map<string,string> >& vecItemFirstLast)
{
	const string strp2pFlag = "2";//p2p
	const string strStallBuyFlag = "50";//摆摊交易售出
	const string strSendMailFlag = "301";//邮件附件发送
	//const string strConsignmentFlag = "136";//开始寄售物品
	int iRet = 0;

	//数据层接口入参
	map<string,string> mapInParams;
	mapInParams.clear();
	mapInParams["dtEventTime"] = ItemFlow.dtEventTime;
	mapInParams["guid"] = ItemFlow.iItem_Unique_Id;
	mapInParams["area"] = ItemFlow.iWordId;
	//接口出参
	vector< map<string,string> > vecItemTradeResult;
	vector< map<string,string> > vecItemConsResult;

	iRet = RuleGet.GetFunction(ics_log_header(ItemFlow.ICSID,ItemFlow.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								mapInParams,"ics_trade_info_list",vecItemTradeResult);
	if (0 != iRet)
	{
		return iRet;
	}
	
	int iResultSize = vecItemTradeResult.size();
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(),ItemFlow.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
		"追踪函数【robItemTraceByGuid】按guid查询物品交易[p2p/stallbuy/]交易记录成功，交易记录条数为:%d \n",iResultSize);


	if (iResultSize > 0)
	{
		bool flag = iResultSize > 1 ? true : false;

		if (flag)
		{
			// 如果流转超过1手，不需要进行补送，分别保存第一手信息及最后一手信息
			ItemFlow.iDefineProc = "2";//不需处理
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(),ItemFlow.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"单据【%s】物品【%s】流转超过1手，不需要补送\n",ItemFlow.ICSID.c_str(), ItemFlow.iItem_Unique_Id.c_str());

			//2 最后一手交易
			Item_Trace_List LastItemTrace;
			SaveItemTrace(ItemFlow, vecItemTradeResult[vecItemTradeResult.size() - 1], LastItemTrace);
			LastItemTrace.iTraceHand = "-1";//最后一手交易信息
			LastItemTrace.iSendAction = IntToStr(STEP_ITEMTRACE_RUN_STAT_RESULT_SALE_NO_SEND);//流转超过1手，不需补送
			LastItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NO_DEAL);//补送结果：不需处理
			LastItemTrace.iTraceResult = "1";//追踪有结果，在人身上
			vecItemTrace.push_back(LastItemTrace);

			//1 保存第一手交易
			//Item_Trace_List FirstItemTrace;
			//SaveItemTrace(ItemFlow, vecItemTradeResult[0], FirstItemTrace);
			LastItemTrace.iTraceHand = "1";//第一手交易信息
			if (vecItemFirstLast.size() >= 2)
			{//iUin,ullRoleID as iRoleId,vRoleName  记录第一手目的者，以便后续封号处理
				LastItemTrace.iRobTo_Uin = vecItemFirstLast[vecItemFirstLast.size() - 2]["iUin"];
				LastItemTrace.vRobTo_RoleId =  vecItemFirstLast[vecItemFirstLast.size() - 2]["iRoleId"];
				LastItemTrace.vRobTo_RoleName = vecItemFirstLast[vecItemFirstLast.size() - 2]["vRoleName"];
				//LastItemTrace.iItem_Attribute_2 = vecItemFirstLast[vecItemFirstLast.size() - 2]["iRoleLevel"];

				LastItemTrace.dtEventTime = vecItemFirstLast[vecItemFirstLast.size() - 2]["dtEventTime"];
				LastItemTrace.iFlowAction = vecItemFirstLast[vecItemFirstLast.size() - 2]["iAction"];

				LastItemTrace.iSendAction = IntToStr(STEP_ITEMSEND_RUN_STAT_BAN_NO);
				LastItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NO_DEAL);//不需处理
				
			}
			LastItemTrace.iTraceResult = "1";//追踪有结果，在人身上
			//doRobItemDelete(LastItemTrace);//若符合条件
			vecItemTrace.push_back(LastItemTrace);

			return 0;
		}
		else
		{
			// 如为只有1手，则需要进行补送 ，分别保存第一手信息及最后一手信息
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(),ItemFlow.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"单据【%s】物品【%s】只有1手，需要补送\n",ItemFlow.ICSID.c_str(), ItemFlow.iItem_Unique_Id.c_str());
			
			//2 最后一手交易
			Item_Trace_List LastItemTrace;
			SaveItemTrace(ItemFlow, vecItemTradeResult[vecItemTradeResult.size() - 1], LastItemTrace);//sql按时间升序
			LastItemTrace.iTraceHand = "-1";//最后一手交易信息
			//可叠加物品，STEP_ITEMTRACE_RUN_STAT_NO_DEL_NO_SEND，在游戏中，可叠加物品交易流出，不删不补
			if (vItemAddableList[(char*)ItemFlow.iItem_Id.c_str()] != "")//find it
			{
				LastItemTrace.iSendAction = IntToStr(STEP_ITEMTRACE_RUN_STAT_NO_DEL_NO_SEND);//可叠加物品不补送
				LastItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NO_DEAL);
			}
			else if (LastItemTrace.iItem_Attribute_1 == "No")
			{
				LastItemTrace.iSendAction = IntToStr(STEP_ITEMTRACE_RUN_STAT_UNIMPORTANT_NO_SEND);//普通道具不补送
				LastItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NO_DEAL);
			}
			else
			{
				LastItemTrace.iSendAction = IntToStr(STEP_ITEMTRACE_RUN_STAT_RESULT_DEL_SEND);
				LastItemTrace.iSendResult = IntToStr(STEP_ITEMTRACE_RUN_STAT_RESULT_DEL_SEND);//"0";modified by v_zhtang; 稍后删除成功后再置为0；
			}
			LastItemTrace.iTraceResult = "1";//追踪有结果，在人身上

			//追踪到某物品，立即拔取该物品操作，防止盗号者利用缝隙时间转移赃物；@@added by v_zhtang on 2012 -12-19
			iRet = doRobItemDelete(LastItemTrace);
			if(iRet == 0)
			{
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(), LastItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, 
					"单据【%s】，删除目的者物品成功\n",ItemFlow.ICSID.c_str());
			}
			else
			{
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemFlow.ICSID.c_str(), LastItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, 
					"单据【%s】，删除目的者物品失败\n",ItemFlow.ICSID.c_str());
			}
			vecItemTrace.push_back(LastItemTrace);

			//1 保存第一手交易
			//Item_Trace_List FirstItemTrace;
			//SaveItemTrace(ItemFlow, vecItemTradeResult[0], FirstItemTrace);
			LastItemTrace.iTraceHand = "1";//第一手交易信息
			if (vecItemFirstLast.size() >= 2 && ItemFlow.iRobed_Uin != vecItemFirstLast[vecItemFirstLast.size() - 2]["iUin"])//modifed by v_zhtang on 2012-12-6;
			{//iUin,ullRoleID as iRoleId,vRoleName  记录第一手目的者，以便后续封号处理
				LastItemTrace.iRobTo_Uin = vecItemFirstLast[vecItemFirstLast.size() - 2]["iUin"];//sql按时间降序
				LastItemTrace.vRobTo_RoleId =  vecItemFirstLast[vecItemFirstLast.size() - 2]["iRoleId"];
				LastItemTrace.vRobTo_RoleName = vecItemFirstLast[vecItemFirstLast.size() - 2]["vRoleName"];
				LastItemTrace.iItem_Attribute_2 = vecItemFirstLast[vecItemFirstLast.size() - 2]["iRoleLevel"];

				LastItemTrace.dtEventTime = vecItemFirstLast[vecItemFirstLast.size() - 2]["dtEventTime"];
				LastItemTrace.iFlowAction = vecItemFirstLast[vecItemFirstLast.size() - 2]["iAction"];

				LastItemTrace.iSendAction = IntToStr(STEP_ITEMSEND_RUN_STAT_BAN_NO);
				LastItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NO_DEAL);//不需处理

			}
			else if (vecItemFirstLast.size() == 1)//目的者没收取，如发邮件扣除
			{
				//reserved,暂不处理这种情况
				LastItemTrace.iSendAction = IntToStr(STEP_ITEMSEND_RUN_STAT_BAN_NO);
				LastItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NO_DEAL);//不需处理
			}
			LastItemTrace.iTraceResult = "1";//追踪有结果，在人身上
			//doRobItemDelete(LastItemTrace);//若符合条件，立即封号@@added by v_zhtang on 2012-12-21;
			vecItemTrace.push_back(LastItemTrace);

			return 0;
		}
	}
else
{
		return STEP_ITEMTRACE_RUN_STAT_ERROR_NO_TRADE;
}
}
/*********************************************************************
Description:	获取getRobItemTrace()物品追踪日志
@				分为： NoTracking和 ByTracking的两种情况
				vecItemFirstLast：  降序排序的当前所有流水
@desc			包括盗号时间段情况下的读物品追踪。
@exception		none
*/
int RobRuleLogic::getRobItemTraceNoTracking(std::vector< Item_Trace_List > &TraceResult,Item_Flow_List &FlowParams, vector< map<string,string> >& vecItemFirstLast)
{
	RuleLOG->WriteLog("不需追踪函数【getRobItemTraceNoTracking】按guid获取玩家的物品流水guid:%s|lastAction:%s\n",FlowParams.iItem_Unique_Id.c_str(),FlowParams.iLastFlowAction.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, FlowParams.ICSID.c_str(),FlowParams.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
		"不需追踪函数【getRobItemTraceNoTracking】按guid获取玩家的物品流水guid:%s|lastAction:%s\n",FlowParams.iItem_Unique_Id.c_str(),FlowParams.iLastFlowAction.c_str());

	struTempItemTrace.dtEventTime = FlowParams.dtEventTime;
	struTempItemTrace.ICSID = FlowParams.ICSID;
	struTempItemTrace.iFlowAction = FlowParams.iFlowAction;
	struTempItemTrace.iItem_Attribute_1 = vItemProList[(char*)FlowParams.iItem_Id.c_str()] == "" ? "No" : "Yes";//
	struTempItemTrace.iItem_Attribute_3 = FlowParams.iItem_Attribute_3;
	struTempItemTrace.iItem_Id = FlowParams.iItem_Id;
	struTempItemTrace.iItem_Level = FlowParams.iItem_Level;
	struTempItemTrace.iItem_Name = FlowParams.iItem_Name;
	struTempItemTrace.iItem_Num =  FlowParams.iItem_Num;
	struTempItemTrace.iItem_Type =  FlowParams.iItem_Type;
	struTempItemTrace.iItem_Unique_Id = FlowParams.iItem_Unique_Id;
	struTempItemTrace.iRobed_Uin = FlowParams.iRobed_Uin;
	struTempItemTrace.iRobTo_Uin = "0";
	struTempItemTrace.iWordId = FlowParams.iWordId;
	struTempItemTrace.vFlowDsc = FlowParams.vFlowDsc;
	struTempItemTrace.iServiceID = FlowParams.iServiceID;
	struTempItemTrace.vRobed_RoleId = FlowParams.vRobed_RoleId;
	struTempItemTrace.vRobed_RoleName = FlowParams.vRobed_RoleName;
	struTempItemTrace.vRobTo_RoleId =  "0";
	struTempItemTrace.vRobTo_RoleName = "0";
	struTempItemTrace.Undefined1 = FlowParams.iLastFlowAction == "" ? "0" : FlowParams.iLastFlowAction;
	struTempItemTrace.Undefined2 = "0";

	//7:丢弃  15：NPC卖店扣除   69：装备拆分扣除；若是这种情况的消失，则置直接补送标记(前提是重要道具)；否则，不处理了
	if ((FlowParams.iLastFlowAction == IntToStr(ABANDON_ACTION) 
		|| FlowParams.iLastFlowAction == IntToStr(EQUIP_SPLIT_ACTION) 
		|| FlowParams.iLastFlowAction == IntToStr(NPC_DEDUCT_ACTION)) && struTempItemTrace.iItem_Attribute_1 != "No")
	{
		struTempItemTrace.iSendAction = IntToStr(STEP_ITEMTRACE_RUN_STAT_RESULT_DIS_DIRECT_SEND);
		struTempItemTrace.iSendResult = "0";//未处理，暂未补送
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, FlowParams.ICSID.c_str(),FlowParams.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"不需追踪函数【getRobItemTraceNoTracking】按guid获取玩家的物品guid:%s|最后流水动作:%s|补送动作:%s|补送结果:%s\n",
			FlowParams.iItem_Unique_Id.c_str(),
			FlowParams.iLastFlowAction.c_str(),
			struTempItemTrace.iSendAction.c_str(),
			struTempItemTrace.iSendResult.c_str());
	}
	else
	{
		struTempItemTrace.iSendAction = IntToStr(STEP_ITEMTRACE_RUN_STAT_RESULT_DIS_NO_SEND);
		struTempItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NO_DEAL);//补送最终结果状态：不需处理
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, FlowParams.ICSID.c_str(),FlowParams.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"不需追踪函数【getRobItemTraceNoTracking】按guid获取玩家的物品guid:%s|最后流水动作:%s|补送动作:%s|补送结果:%s\n",
			FlowParams.iItem_Unique_Id.c_str(),
			FlowParams.iLastFlowAction.c_str(),
			struTempItemTrace.iSendAction.c_str(),
			struTempItemTrace.iSendResult.c_str());
	}
	//0 初始态;1 第一手;-1最后一手（当前在谁的身上）
	struTempItemTrace.iTraceHand = "-1";
	struTempItemTrace.iTraceResult = "3";//已消失
	TraceResult.push_back(struTempItemTrace);

	struTempItemTrace.iTraceHand = "1";//第一手
	if (vecItemFirstLast.size() >= 2 && FlowParams.iRobed_Uin != vecItemFirstLast[vecItemFirstLast.size() - 2]["iUin"])//added by v_zhtang 2012-11-21
	{//iUin,ullRoleID as iRoleId,vRoleName  记录第一手目的者，以便后续封号处理
		struTempItemTrace.iRobTo_Uin = vecItemFirstLast[vecItemFirstLast.size() - 2]["iUin"];
		struTempItemTrace.vRobTo_RoleId =  vecItemFirstLast[vecItemFirstLast.size() - 2]["iRoleId"];
		struTempItemTrace.vRobTo_RoleName = vecItemFirstLast[vecItemFirstLast.size() - 2]["vRoleName"];
	//	struTempItemTrace.iItem_Attribute_2 = vecItemFirstLast[vecItemFirstLast.size() - 2]["iRoleLevel"];
		
		struTempItemTrace.dtEventTime = vecItemFirstLast[vecItemFirstLast.size() - 2]["dtEventTime"];
		struTempItemTrace.iFlowAction = vecItemFirstLast[vecItemFirstLast.size() - 2]["iAction"];

		struTempItemTrace.iSendAction = IntToStr(STEP_ITEMSEND_RUN_STAT_BAN_NO);
		struTempItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NO_DEAL);//不需处理
		
	}
	else
	{
		struTempItemTrace.iSendAction = IntToStr(STEP_ITEMSEND_RUN_STAT_BAN_NO);
		struTempItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NO_DEAL);//不需处理
	}
	//doRobItemDelete(struTempItemTrace);//若符合条件，立即封号@@added by v_zhtang on 2012-12-21;
	TraceResult.push_back(struTempItemTrace);
	return 0;
}


int RobRuleLogic::getRobItemTraceNoTracking(std::vector< Item_Trace_List > &TraceResult,std::vector< Item_Flow_List > &FlowParams, string strLogin, string strRobed)
{
	TraceResult.clear();
	RuleLOG->WriteLog("getRobItemTraceNoTracking获取玩家的物品补送流水FlowParams.size():%d",FlowParams.size());
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "getRobItemTraceNoTracking获取玩家的物品补送流水FlowParams.size():%d",FlowParams.size() );
	for(int i=0;i<FlowParams.size();i++)
	{
		if ( false == IsNeedFind(FlowParams[i].iItem_Id))
		{
			RuleLOG->WriteLog("物品ID【%s】\n",FlowParams[i].iItem_Id.c_str());
			continue;
		}

		if ((FlowParams[i].dtEventTime < strLogin) || (FlowParams[i].dtEventTime > strRobed))
		{
			continue;
		}
		struTempItemTrace.dtEventTime          = FlowParams[i].dtEventTime;
		struTempItemTrace.ICSID                = FlowParams[i].ICSID;
		struTempItemTrace.iFlowAction          = FlowParams[i].iFlowAction;
		struTempItemTrace.iItem_Attribute_1    = FlowParams[i].iItem_Attribute_1;
		struTempItemTrace.iItem_Attribute_2    = FlowParams[i].iItem_Attribute_2;
		struTempItemTrace.iItem_Attribute_blob = FlowParams[i].iItem_Attribute_blob;
		struTempItemTrace.iItem_Id             = FlowParams[i].iItem_Id;
		struTempItemTrace.iItem_Level          = FlowParams[i].iItem_Level;
		struTempItemTrace.iItem_Name           = FlowParams[i].iItem_Name;
		struTempItemTrace.iItem_Num            = FlowParams[i].iItem_Num;
		struTempItemTrace.iItem_Type           = FlowParams[i].iItem_Type;
		struTempItemTrace.iItem_Unique_Id      = FlowParams[i].iItem_Unique_Id;
		struTempItemTrace.iRobed_Uin           = FlowParams[i].iRobed_Uin;
		struTempItemTrace.iRobTo_Uin           = FlowParams[i].iRobTo_Uin;
		struTempItemTrace.iWordId              = FlowParams[i].iWordId;
		struTempItemTrace.vFlowDsc             = FlowParams[i].vFlowDsc;
		struTempItemTrace.iServiceID           = FlowParams[i].iServiceID;
		struTempItemTrace.vRobed_RoleId        = FlowParams[i].vRobed_RoleId;
		struTempItemTrace.vRobed_RoleName      = FlowParams[i].vRobed_RoleName;
		struTempItemTrace.vRobTo_RoleId        = FlowParams[i].vRobTo_RoleId==""?"0":FlowParams[i].vRobTo_RoleId;
		struTempItemTrace.vRobTo_RoleName      = FlowParams[i].vRobTo_RoleName==""?"0":FlowParams[i].vRobTo_RoleName;
		struTempItemTrace.iSendResult          = FlowParams[i].iTraceResult;
		struTempItemTrace.Undefined1           = "-1";
		
		//1 需要补送
		//2 不需要补送
		//3 补送完成
		struTempItemTrace.iSendAction = "1";

		//0 初始态
		//1 第一手
		//-1 最后一手（当前在谁的身上）
		struTempItemTrace.iTraceHand = "-1";
		/*
		0 待处理
		1 无须追踪，直接补送
		2 需要补送，手工补送
		3 追踪有结果，在人身上
		追踪有结果在NPC，商店，仓库
		4 追踪物品已消失，
		摧毁，炼化，扔地上……
		5 无法处理
		*/
		struTempItemTrace.iTraceResult = "1";
		TraceResult.push_back(struTempItemTrace);
	}
	return 0;
}
/*********************************************************************
Description:	根据物品追踪结果保存相关信息
@desc			
@exception		none
*/	
int RobRuleLogic::SaveItemTrace(const Item_Flow_List& ItemFlow, map<string, string>& mapItemRes, Item_Trace_List& ItemTrace)
{
	ItemTrace.ICSID = ItemFlow.ICSID;
	ItemTrace.iWordId = ItemFlow.iWordId;

	ItemTrace.iRobed_Uin = ItemFlow.iRobed_Uin;
	ItemTrace.vRobed_RoleId = ItemFlow.vRobed_RoleId;
	ItemTrace.vRobed_RoleName = ItemFlow.vRobed_RoleName;

	ItemTrace.iRobTo_Uin = ItemFlow.iRobTo_Uin;//目的者信息已从函数【robItemTraceJudge】取得
	ItemTrace.vRobTo_RoleId = ItemFlow.vRobTo_RoleId;
	ItemTrace.vRobTo_RoleName = ItemFlow.vRobTo_RoleName;

	ItemTrace.dtEventTime = mapItemRes["dtEventTime"];
	ItemTrace.iFlowAction = mapItemRes["FlowType"];//p2p/StallBuy

	//ItemTrace.Undefined2 = (mapItemRes["TradeID"] == "" ? "0" : mapItemRes["TradeID"]);//consignment id ...
	//由于P2p、摆摊交易特殊性质：同一时间，一个得到，一个失去，对于该物品查流水最后一手会不一致，这里从交易表中取目的者信息

	ItemTrace.iItem_Id = ItemFlow.iItem_Id;
	ItemTrace.iItem_Name = ItemFlow.iItem_Name;
	ItemTrace.iItem_Unique_Id = ItemFlow.iItem_Unique_Id;
	//ItemTrace.iItem_Attribute_blob = ItemFlow.iItem_Attribute_blob;//blob属性在补送时候从DR中获取
	ItemTrace.iItem_Level = ItemFlow.iItem_Level;
	if (1/*ItemFlow.iItem_Type == "0"*/)
	{
		ItemTrace.iItem_Attribute_1 = vItemProList[(char*)ItemFlow.iItem_Id.c_str()] == "" ? "No" : "Yes";//
	}
	ItemTrace.iItem_Num = ItemFlow.iItem_Num;
	ItemTrace.iItem_Type = ItemFlow.iItem_Type;
	ItemTrace.vFlowDsc = ItemFlow.vFlowDsc;
	ItemTrace.iServiceID = ItemFlow.iServiceID;
	ItemTrace.iItem_Attribute_3 = ItemFlow.iItem_Attribute_3;//注意：该字段用来保存 sql查询时自定义的，表明从哪个表查的、装备、道具、普通道具
	ItemTrace.Undefined1 = ItemFlow.iLastFlowAction;//最后一手流水(注意：该字段与undefined2一起用)
	//ItemTrace.iItem_Attribute_2 = ItemFlow.vRobTo_RoleLevel;//added by v_zhtang on 2012-12-20

	return 0;
}
/*********************************************************************
	Description:	删除玩家身上或仓库物品
	@desc			eg:cmd=71124&area=99&uin=258294191&charac_no=197942434050343215&charac_name=miles&item=1|1 2 3 4|
							item=类型个数|物品类型 物品唯一标识 道具数量 道具ID|
	@exception		none
	@retun			0:删除成功，	非0:删除失败
*/	
#define SLEEP_TIME_DELETE	10	//睡眠时间，用于间隔停歇
int RobRuleLogic::PlayerItemDel(Item_Trace_List& ItemTrace, const char* strOperFlag)
{
	vector < map<string, string> > theItemDelResult;//返回结果
	map<string,string> inParams;
	inParams["area"] = ItemTrace.iWordId;
	inParams["uin"]=ItemTrace.iRobTo_Uin; 
	inParams["charac_no"] =ItemTrace.vRobTo_RoleId;
	inParams["unique_id"] =ItemTrace.iItem_Unique_Id;
	inParams["item_count"] = ItemTrace.iItem_Num;

	string strName(strOperFlag);
	string strWhere("");
	string strCmd;
	if ("player_bag_item_del" == strName)
	{
		strWhere = "背包";
		strCmd = DEL_BAG_CMD;	
	}else if ("player_storage_item_del" == strName)
	{
		strWhere = "仓库";
		strCmd = DEL_STORAGE_CMD;
	}

	int iRet = RuleGet.GetFunction(ics_log_header(ItemTrace.ICSID,ItemTrace.iRobTo_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									inParams,strOperFlag,theItemDelResult);
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
		"删除玩家物品theItemDelResult.size(): %d\n",theItemDelResult.size());

	sleep(SLEEP_TIME_DELETE);//睡眠10s，待游戏服务器处理  added by v_zhtang on 2012-11-26;
	if (theItemDelResult.size() > 0 && iRet == 0)
	{
		if(theItemDelResult[0]["result"] == "0")
		{
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"删除玩家%s物品[%s]成功\n",strWhere.c_str(),ItemTrace.iItem_Unique_Id.c_str());
		}else if(theItemDelResult[0]["result"] != "0")
		{
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
				"删除玩家%s物品[%s]失败,IDIP接口返回错误码【%s】\n",strWhere.c_str(),ItemTrace.iItem_Unique_Id.c_str(),theItemDelResult[0]["result"].c_str());
			iRet = StrToInt(theItemDelResult[0]["result"]);
		}
	}else
	{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"删除玩家%s物品[%s]失败,SAP接口返回错误码【%d】\n",strWhere.c_str(),ItemTrace.iItem_Unique_Id.c_str(),iRet);
	}
	//记录敏感日志
	LogCM(ItemTrace,"删除物品",RequestStr(inParams),"删除盗号者"+strWhere+"物品:"+ItemTrace.iItem_Unique_Id,strName,
		ItemTrace.iRobTo_Uin,ItemTrace.vRobTo_RoleId,ItemTrace.vRobTo_RoleName,strCmd,iRet,inParams["serial"]);
	return iRet;
}
/*********************************************************************
	Description:	根据最后一手动作id，删除玩家寄售行、邮件附件物品
	@desc			
	@exception		none
	@retun			0:删除成功，	非0:删除失败
*/
int RobRuleLogic::PlayerItemDelMailorConsi(Item_Trace_List& ItemTrace)
{
	vector < map<string, string> > theItemDelResult;//返回结果
	map<string,string> inParams;
	inParams.clear();
	theItemDelResult.clear();
	inParams["area"] = ItemTrace.iWordId;
	//inParams["uin"]=ItemTrace.iRobTo_Uin; 
	inParams["charac_no"] =ItemTrace.vRobTo_RoleId;
	inParams["item_guid"] = ItemTrace.iItem_Unique_Id;

	string strWhere("");
	string strOperFlag("");
	string strCmd;
	string strAction = ItemTrace.Undefined1;//该字段暂定为保存某guid在追踪模块运行时刻起最后一手流转动作ID

	if (strAction == IntToStr(CONSIGNMENT_START_ACTION))//寄售行里
	{
		strWhere = "寄售行";
		strCmd = DEL_CONSIGNMENT_CMD;
		strOperFlag = "player_consignment_item_del";
		inParams["consignment_guid"] = ItemTrace.Undefined2;//存储交易id
	}//正式的发送邮件附件扣除、寄售退出、寄售购买、寄售超时等，都是从邮件附件里删除  add by v_zhtang on 2012-11-09
	else if (strAction == IntToStr(MAIL_ACCESSORY_ACTION) \
		   || strAction == IntToStr(CONSIGNMENT_PURCHASE_ACTION)\
		   || strAction == IntToStr(CONSIGNMENT_TIMEOUT_ACTION)\
		   || strAction == IntToStr(CONSIGNMENT_CANCEL_ACTION))
	{
		/*RuleLOG->WriteLog("[PlayerItemDelMailorConsi]删除玩家邮件物品暂停。。。\n");
		return -111;*/

		strWhere = "邮件附件";
		strCmd = DEL_MAIL_ACCESSORY_CMD;
		strOperFlag = "player_mail_item_del";
		inParams["mail_id"] = ItemTrace.Undefined2;//存储 交易id
	}

	int iRet = RuleGet.GetFunction(ics_log_header(ItemTrace.ICSID,ItemTrace.iRobTo_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									inParams,strOperFlag.c_str(),theItemDelResult);

	RuleLOG->WriteLog("[PlayerItemDelMailorConsi]删除玩家物品theItemDelResult.size(): %d\n",theItemDelResult.size());
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
		"删除玩家物品theItemDelResult.size(): %d\n",theItemDelResult.size());
	sleep(SLEEP_TIME_DELETE);//睡眠30s，待游戏服务器处理  added by v_zhtang on 2012-11-26;

	if (theItemDelResult.size() > 0 && iRet == 0)
	{
		if(theItemDelResult[0]["result"] == "0")
		{
			RuleLOG->WriteLog("[PlayerItemDelMailorConsi]删除玩家%s物品[%s]成功\n",strWhere.c_str(),ItemTrace.iItem_Unique_Id.c_str());
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"删除玩家%s物品[%s]成功\n",strWhere.c_str(),ItemTrace.iItem_Unique_Id.c_str());

		}else if(theItemDelResult[0]["result"] != "0")
		{
			RuleLOG->WriteLog("[PlayerItemDelMailorConsi]删除玩家%s物品[%s]失败,IDIP接口返回错误码【%s】\n",strWhere.c_str(),ItemTrace.iItem_Unique_Id.c_str(),theItemDelResult[0]["result"].c_str());
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
				"删除玩家%s物品[%s]失败,IDIP接口返回错误码【%s】\n",strWhere.c_str(),ItemTrace.iItem_Unique_Id.c_str(),theItemDelResult[0]["result"].c_str());
			iRet = StrToInt(theItemDelResult[0]["result"]);
		}
	}
	else
	{
		RuleLOG->WriteLog("[PlayerItemDelMailorConsi]删除玩家%s物品[%s]失败,SAP接口返回错误码【%d】\n",strWhere.c_str(),ItemTrace.iItem_Unique_Id.c_str(),iRet);
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"删除玩家%s物品[%s]失败,SAP接口返回错误码【%d】\n",strWhere.c_str(),ItemTrace.iItem_Unique_Id.c_str(),iRet);
	}
	//记录敏感日志
	LogCM(ItemTrace,"删除物品",RequestStr(inParams),"删除盗号者"+strWhere+"物品:"+ItemTrace.iItem_Unique_Id,strOperFlag,
		ItemTrace.iRobTo_Uin,ItemTrace.vRobTo_RoleId,ItemTrace.vRobTo_RoleName,strCmd,iRet,inParams["serial"]);
	return iRet;
}
/*********************************************************************
	Description:	获取doRobItemSend()物品补送接口
	@				分为：各个业务需要单独来定义自己的流程，详细的见代码
	@desc			包括盗号时间段情况下的物品补送接口。
	@exception		none
*/
#define		BAN_TIME_LAST	315360000	//永久封号10year
#define		BAN_TIME_PAUSE	300//短暂封停5min
int RobRuleLogic::doRobItemSend(std::vector< Item_Trace_List > &ItemList, int &iWarnFlag)
{
	iWarnFlag = 0;
	map<string,string> inParams;
	RobICSOper ics_oper;
	vector < map<string, string> > theItemSendResult;
	vector < map<string, string> > theItemBlobResult;
	vector < map<string, string> > theItemDelResult;
	std::vector< Item_Trace_List > vecNeedWarnItems;//需要邮件告警的物品列表，一起发出去
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, "","", TLOG_LEVEL_INFO, __FUNCTION__, 	"doRobItemSend获取玩家的物品列表大小ItemList.size():%d\n",ItemList.size());
	for(int i=0;i<ItemList.size();i++)
	{
		inParams.clear();
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList[i].ICSID.c_str(),ItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__,"--[%d]--原：uin=%s,role_id=%s,rolename=%s | 目的：uin=%s,role_id=%s,rolename=%s\n",i,
			ItemList[i].iRobed_Uin.c_str(),ItemList[i].vRobed_RoleId.c_str(),ItemList[i].vRobed_RoleName.c_str(),
			ItemList[i].iRobTo_Uin.c_str(),ItemList[i].vRobTo_RoleId.c_str(),ItemList[i].vRobTo_RoleName.c_str());

		//最后一手补送处理
		if ("-1" == ItemList[i].iTraceHand)
		{
			RobICSOper ics_oper;
			vector < map<string, string> > theItemSendResult;
			iRet = ics_oper.GetReSendList(ItemList[i], theItemSendResult);//按QQ、roleid、guid、dteventtime
			if ( iRet == 0 )//未补过
			{
				iRet = ics_oper.InsertSendInfo(ItemList[i], theItemSendResult);
				if ( iRet != 0 )
				{
					continue;
				}
			}
			else if ( iRet == 1 )//已补过
			{
				vecNeedWarnItems.push_back(ItemList[i]);
				ics_oper.UpdateWarnMailCount(ItemList[i], theItemSendResult);
				ItemList[i].iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_SEND_AGAIN);
				continue;
			}
			else
			{
				continue;
			}
			//end added
			//对卖给NPC的动作（2022）进行判定，需要判定是否有回购的动作，如果有则不补偿
			if ("2022" == ItemList[i].iFlowAction)
			{
				inParams.clear();
				theItemSendResult.clear();
				inParams["area"]     = ItemList[i].iWordId;
				inParams["guid"]     = ItemList[i].iItem_Unique_Id;
				inParams["datetime"] = ItemList[i].dtEventTime;
				iRet = RuleGet.GetFunction(ics_log_header(ItemList[i].ICSID,ItemList[i].iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),inParams,"check_is_buyback",theItemSendResult);
				if (0==iRet && 0==theItemSendResult.size())
				{
					RuleLOG->WriteLog("iFlowAction=%s,单据【%s】没有执行回购操作\n",ItemList[i].iFlowAction.c_str(), ItemList[i].ICSID.c_str());
					WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList[i].ICSID.c_str(),ItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__,"check_is_buyback|doRobItemSend 玩家没有执行回购操作！\n");
					//LogCM(ItemList[i],"查询玩家是否回购物品",RequestStr(inParams),"玩家没有执行回购操作","check_is_buyback",ItemList[i].iRobed_Uin,ItemList[i].vRobed_RoleId,ItemList[i].vRobed_RoleName,IntToStr(KICK_PLAYER_OFF_CMD),iRet);
				}
				else
				{
					RuleLOG->WriteLog("iFlowAction=%s,单据【%s】执行了回购操作，不做后续处理\n",ItemList[i].iFlowAction.c_str(), ItemList[i].ICSID.c_str());
					WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList[i].ICSID.c_str(),ItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__,"kick_player_off|doRobItemSend 踢玩家下线失败！\n");
					//LogCM(ItemList[i],"查询玩家是否回购物品",RequestStr(inParams),"玩家已经执行过回购操作","check_is_buyback",ItemList[i].iRobed_Uin,ItemList[i].vRobed_RoleId,ItemList[i].vRobed_RoleName,IntToStr(KICK_PLAYER_OFF_CMD),iRet);
					ItemList[i].iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_SEND_BUYBACK);
					continue;
				}
			}

			//1.2.1.1 踢玩家下线 IDIP=75501
			inParams.clear();
			theItemSendResult.clear();
			inParams["area"]      = ItemList[i].iWordId;
			inParams["uin"]       = ItemList[i].iRobed_Uin;
			inParams["charac_no"] = ItemList[i].vRobed_RoleId;
			iRet = RuleGet.GetFunction(ics_log_header(ItemList[i].ICSID,ItemList[i].iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),inParams,"kick_player_off",theItemSendResult);
			RuleLOG->WriteLog("执行踢玩家下线操作");
			if (0==iRet)
			{
				RuleLOG->WriteLog("踢玩家下线成功！！！\n");
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList[i].ICSID.c_str(),ItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__,"kick_player_off|doRobItemSend 踢玩家下线成功！\n");
				if ( 0 != LogCM(ItemList[i],"踢玩家下线",RequestStr(inParams),"盗号丢失找回，踢玩家下线成功","kick_player_off",
					ItemList[i].iRobed_Uin,ItemList[i].vRobed_RoleId,ItemList[i].vRobed_RoleName,IntToStr(KICK_PLAYER_OFF_CMD),iRet,inParams["serial"]))
				{
					iWarnFlag = -1;
				}
			}
			else if (-4000==iRet)
			{
				RuleLOG->WriteLog("踢玩家下线成功！！！  -4000\n");
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList[i].ICSID.c_str(),ItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__,"kick_player_off|doRobItemSend 踢玩家下线成功！\n");
				if (0 != LogCM(ItemList[i],"踢玩家下线",RequestStr(inParams),"盗号丢失找回，踢玩家下线成功","kick_player_off",
					ItemList[i].iRobed_Uin,ItemList[i].vRobed_RoleId,ItemList[i].vRobed_RoleName,IntToStr(KICK_PLAYER_OFF_CMD),iRet,inParams["serial"]))
				{
					iWarnFlag = -1;
				}
				
			}
			else
			{
				RuleLOG->WriteLog("！！！！！！！！！！！！！！踢玩家下线失败！！！\n");
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList[i].ICSID.c_str(),ItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__,"kick_player_off|doRobItemSend 踢玩家下线失败！\n");

				if (0 != LogCM(ItemList[i],"踢玩家下线",RequestStr(inParams),"盗号丢失找回，踢玩家下线失败","kick_player_off",
					ItemList[i].iRobed_Uin,ItemList[i].vRobed_RoleId,ItemList[i].vRobed_RoleName,IntToStr(KICK_PLAYER_OFF_CMD),iRet,inParams["serial"]))
				{
					iWarnFlag = -1;
				}
				
				ItemList[i].iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_SEND_KICKOUT_FAIL);	
				continue;
			}

			//1.2.1.3 补送物品
			inParams.clear();
			theItemSendResult.clear();
			inParams["uin"]         = ItemList[i].iRobed_Uin; 
			inParams["area"]        = ItemList[i].iWordId;
			inParams["charac_no"]   = ItemList[i].vRobed_RoleId;
			inParams["type"]        = "0";//附件类型 (0 物品，1金钱)
			inParams["subject"]     = string(GbkToUtf8("盗号受理反馈"));
			inParams["text"]        = string(GbkToUtf8("亲，由于游戏帐号被盗或其他原因，导致您的游戏道具丢失，系统现在将已查证的相关物品返还给您，祝您游戏愉快。"));
			inParams["money_type"]  = "4";
			inParams["money_count"] = "0";
			inParams["serial"]      = "test";
			inParams["source"]      = "0";
			inParams["name_0"]      = ItemList[i].iItem_Num;
			inParams["name_1"]      = ItemList[i].iItem_Unique_Id;
			inParams["name_2"]      = "1";
			inParams["name_3"]      = ItemList[i].iItem_Id;
			inParams["name_4"]      = ItemList[i].iItem_Attribute_blob;
			inParams["name_5"]      = "1";

			iRet = RuleGet.GetFunction(ics_log_header(ItemList[i].ICSID,ItemList[i].iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
				inParams,"ics_item_send_goods",theItemSendResult);

			if (0 != LogCM(ItemList[i],"补送装备",RequestStr(inParams),"盗号丢失找回:"+ItemList[i].iItem_Unique_Id,"ics_item_send_goods",
				ItemList[i].iRobed_Uin,ItemList[i].vRobed_RoleId,ItemList[i].vRobed_RoleName,IntToStr(SEND_EQUIP_CMD),iRet,inParams["serial"]))
			{
				iWarnFlag = -1;
			}
			
			if(iRet == 0 && theItemSendResult[0]["result"] == "0")
			{
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList[i].ICSID.c_str(),ItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
					"ics_item_send_equip|doRobItemSend获取玩家的物品[%s]补送结果成功\n",ItemList[i].iItem_Unique_Id.c_str());
				ItemList[i].iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_SEND_FINISH);	
			}
			else
			{
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList[i].ICSID.c_str(),ItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
					"ics_item_send_equip|doRobItemSend获取玩家的物品[%d]补送结果失败,IDIP接口返回错误码【%d】\n",i,iRet);
				ItemList[i].iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_SEND_EQUIP_FAIL);
			}	
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList[i].ICSID.c_str(),ItemList[i].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"装备直接补送：补送物品成功！补送完毕！\n");
			
			ics_oper.UpdateSendResult(ItemList[i], theItemSendResult);//@added by v_zhtang on 2012-11-15; 更新状态至 补送结果表
		}
	}

	//若有告警物品，则邮件告警
	if (0 != vecNeedWarnItems.size())
	{
		string title = "【dzs】物品重复补送预警";
		string ics = vecNeedWarnItems[0].ICSID;
		string uin = vecNeedWarnItems[0].iRobed_Uin;
		string mailInfo("");
		GetCurDateTime(mailInfo);
		mailInfo += ": 斗战神盗号自助系统监控到即将重复补送物品，不过已成功阻止！建议及时核查！谢谢！参考明细：</br>单号[";
		mailInfo += ics;
		mailInfo += "], </br>QQ[";
		mailInfo += uin;
		mailInfo += "], </br>物品列表(以|分隔)[";
		for (int i = 0; i < vecNeedWarnItems.size(); i++)
		{			
			mailInfo += "</br>item_id:"+vecNeedWarnItems[i].iItem_Id+",unique_id:"+vecNeedWarnItems[i].iItem_Unique_Id + "|";
		}
		mailInfo += "]";

		//发送告警邮件
		SendWarnMail(title, mailInfo);
	}
	RuleLOG->WriteLog("补送物品结束！！！\n");
	return 0;
}
/*********************************************************************
Description:	记录敏感日志
@				
@desc			
@exception		none
*/
int RobRuleLogic::LogCM(const Item_Trace_List &ItemList,
		  const string& strOptType, 
		  const string& strRequest, 
		  const string& strMemo,
		  const string& strFuntionName,
		  const string& iUin,
		  const string& iRoleId,
		  const string& vRoleName,
		  const string& strCmd,
		  const int& iResult,
		  const string& StrSerial)
{
	if (strFuntionName.empty())
	{
		return -1;
	}
	int optId=StrToInt(CRobConf::getConf()->GetIcsOper()[strFuntionName]);

	if( false == CLogManager::GetInstance().WriteCMLog(GbkToUtf8("盗号自助系统"),//操作者
		StrToInt(ItemList.iServiceID),//业务ID
		optId,//操作接口ID
		StrToLLong(iUin),//操作目标QQ
		StrToInt(ItemList.iWordId),
		iResult,//操作结果：成功或失败
		GbkToUtf8((char*)strOptType.c_str()),//操作类型
		"",//ip
		ItemList.ICSID,//seqId 单号
		iRoleId,//操作目标角色ID
		GbkToUtf8((char*)vRoleName.c_str()),//操作目标角色名
		StrToInt(ItemList.iItem_Id),//操作的道具
		StrToInt(ItemList.iItem_Num),//道具数量
		GbkToUtf8((char*)strRequest.c_str()),//itemDes 描述
		"5",//操作原因:投诉处理
		GbkToUtf8((char*)strMemo.c_str()),//备注
		strCmd,//cmd
		6,
		StrSerial))//需求来源。6：盗号系统
	{
		RuleLOG->WriteLog("sorry！记录敏感日志失败！操作目标用户【%s】| 操作角色id【%s】 | 操作目标角色名【%s】| 道具ID【%s】 | 道具数量【%s】 | 操作类型【%s】| 操作原因【%s】 | 操作接口id【%d】|操作结果【%d】|StrSerial【%s】\n",
			iUin.c_str(),iRoleId.c_str(),vRoleName.c_str(),ItemList.iItem_Id.c_str(),ItemList.iItem_Num.c_str(),strOptType.c_str(),strMemo.c_str(),optId,iResult,StrSerial.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),iUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"sorry！记录敏感日志失败！操作目标用户【%s】,操作角色id【%s】, 操作目标角色名【%s】, 道具ID【%s】 | 道具数量【%s】, 操作类型【%s】,操作原因【%s】,操作接口id【%d】,操作结果【%d】\n",
			iUin.c_str(),iRoleId.c_str(),vRoleName.c_str(),ItemList.iItem_Id.c_str(),ItemList.iItem_Num.c_str(),strOptType.c_str(),strMemo.c_str(),optId,iResult);

		return -1;
	}
	RuleLOG->WriteLog("记录敏感日志成功！操作目标用户【%s】, 操作角色id【%s】, 操作目标角色名【%s】, 道具ID【%s】, 道具数量【%s】,操作类型【%s】, 操作原因【%s】, 操作接口id【%d】,操作结果【%d】|StrSerial【%s】\n",
		iUin.c_str(),iRoleId.c_str(),vRoleName.c_str(),ItemList.iItem_Id.c_str(),ItemList.iItem_Num.c_str(),strOptType.c_str(),strMemo.c_str(),optId,iResult, StrSerial.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),iUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
		"记录敏感日志成功！操作目标用户【%s】, 操作角色id【%s】, 操作目标角色名【%s】, 道具ID【%s】, 道具数量【%s】, 操作类型【%s】, 操作原因【%s】, 操作接口id【%d】,操作结果【%d】\n",
		iUin.c_str(),iRoleId.c_str(),vRoleName.c_str(),ItemList.iItem_Id.c_str(),ItemList.iItem_Num.c_str(),strOptType.c_str(),strMemo.c_str(),optId,iResult);

	return 0;
}

int RobRuleLogic::FetchItemBlob(Item_Trace_List &ItemList,vector < map<string, string> > &theItemBlobResult)
{
	int iRet = 0;
	std::map< string, string > inParams;
	vector < map<string, string> > ItemLoginLogoutResult;
	std::string dtLoginTime("");
	//std::string dtLogoutTime("");
	theItemBlobResult.clear();

	//首先查找该物品丢失时所在登录、登出时间段
	inParams.clear();
	inParams["ics_id"] = ItemList.ICSID;
	inParams["guid"] = ItemList.iItem_Unique_Id;
	inParams["uin"] = ItemList.iRobed_Uin;

	iRet = RuleGet.GetFunction(ics_log_header(ItemList.ICSID,ItemList.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								inParams,"query_login_logout_time",ItemLoginLogoutResult);
	if (0 == iRet)
	{
		RuleLOG->WriteLog("[INFO][FetchItemBlob][1]>>>获取物品丢失所在登录时间段成功！ItemLoginLogoutResult.size()=%d\n",ItemLoginLogoutResult.size());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"[INFO][FetchItemBlob][1]>>>获取物品丢失所在登录时间段成功！ItemLoginLogoutResult.size()=%d\n",ItemLoginLogoutResult.size());

		if (ItemLoginLogoutResult.size() > 0)
		{
			dtLoginTime = ItemLoginLogoutResult[0]["dtLoginInTime"];
		}else
		{
			RuleLOG->WriteLog("[INFO][FetchItemBlob][1]>>>没有获取物品丢失所在登录时间段，为空！\n");
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
				"[INFO][FetchItemBlob][1]>>>没有获取物品丢失所在登录时间段，为空！\n");
			return -2;
		}
	}else
	{
		RuleLOG->WriteLog("[INFO][FetchItemBlob][1]>>>获取物品丢失所在登录时间段失败！\n");
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"[INFO][FetchItemBlob][1]>>>获取物品丢失所在登录时间段失败！\n");
		return iRet;
	}

	//分别按登入时间往前、登出时间往后推，取第一条blob，返回
	inParams.clear();
	inParams["item_uin"] = ItemList.iRobed_Uin;
	inParams["area"] = ItemList.iWordId;
	inParams["role_id"] = ItemList.vRobed_RoleId;
	inParams["guid"] = ItemList.iItem_Unique_Id;
	inParams["dtLoginTime"] = dtLoginTime;//登入时间

	iRet = RuleGet.GetFunction(ics_log_header(ItemList.ICSID,ItemList.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								inParams,"item_blob_before_login",theItemBlobResult);
	if (0 == iRet)
	{
		RuleLOG->WriteLog("[INFO][FetchItemBlob][2]>>>按登入时间往前获取物品最近blob成功！theItemBlobResult.size()=%d\n",theItemBlobResult.size());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"[INFO][FetchItemBlob][2]>>>按登入时间往前获取物品最近blob成功！theItemBlobResult.size()=%d\n",theItemBlobResult.size());

		if (theItemBlobResult.size() == 0)
		{
			iRet = RuleGet.GetFunction(ics_log_header(ItemList.ICSID,ItemList.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
										inParams,"item_blob_after_login",theItemBlobResult);
			if (0 == iRet)
			{
				RuleLOG->WriteLog("[INFO][FetchItemBlob][3]>>>按登入时间往后获取物品最近blob成功！theItemBlobResult.size()=%d\n",theItemBlobResult.size());
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
					"[INFO][FetchItemBlob][3]>>>按登入时间往后获取物品最近blob成功！theItemBlobResult.size()=%d\n",theItemBlobResult.size());

			}else
			{
				RuleLOG->WriteLog("[INFO][FetchItemBlob][3]>>>按登入时间往后获取物品最近blob失败！\n");
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
					"[INFO][FetchItemBlob][3]>>>按登入时间往后获取物品最近blob失败！\n");

				return iRet;
			}
		}
	}else
	{
		RuleLOG->WriteLog("[INFO][FetchItemBlob][2]>>>按登入时间往前获取物品最近blob失败！\n");
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"[INFO][FetchItemBlob][2]>>>按登入时间往前获取物品最近blob失败！\n");

		return iRet;
	}
	return 0;
}

/*********************************************************************
	Description:	将等级物品的道具按照90+level+ItemId整合,返回形如900xxxxx的虚拟编号字符串
	@				
	@desc			
	@exception		none
	*/
string RobRuleLogic::ItemIdLevelTransfer(Item_Trace_List &ItemList)
{
	if ("0" != ItemList.iItem_Level)
	{
		//9+绑定属性+等级+物品ID   绑定属性：1[绑定] 0[不绑定]
		return "91"+ItemList.iItem_Level+ItemList.iItem_Id;//绑定属性预留于ItemList.iItem_Attribute_2
	}
	
	return "";
}
/************************************************************************/
/* @@@added by v_zhtang on 20123-1-7;
	单据来源定义：
	source:
	10: O线客服单据
	30: R线Q游助手正式环境（即外网）单据
	40: R线Q游助手测试环境单据
	100: reserved...
*/
/************************************************************************/
int RobRuleLogic::doReplayIcsResult(Rob_Ics_Complaint& autoReplayICS, string& sSource)
{
	string reply = "";
	string title = string(GbkToUtf8("[斗战神]关于您盗号受理结果反馈"));
	RuleLOG->WriteLog("[STEP:PHSEA]:::RobRuleLogic::doReplayIcsResult:mReplyContentList.size()=[%d],ICSAnaylseStat=[%s]\n",mReplyContentList.size(),autoReplayICS.sICSAnaylseStat.c_str());
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__,
		"[STEP:PHSEA]:::RobRuleLogic::doReplayIcsResult:mReplyContentList.size()=[%d],ICSAnaylseStat=[%s]\n",mReplyContentList.size(),autoReplayICS.sICSAnaylseStat.c_str());
		
// 	RuleLOG->WriteLog("reply %s",mReplyContentList[(char*)autoReplayICS.sICSAnaylseStat.c_str()].c_str());
// 
// 	if(mReplyContentList[(char*)autoReplayICS.sICSAnaylseStat.c_str()] == "")
// 	{
// 		autoReplayICS.siReplyResult = IntToStr(STEP_Reply_WAITING_RESULT_ERROR);
// 		return STEP_Reply_WAITING_RESULT_ERROR;
// 	}
//	autoReplayICS.sContent = mReplyContentList[(char*)autoReplayICS.sICSAnaylseStat.c_str()];
	RuleLOG->WriteLog("[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:mReplyContentList:reply=%s&replay_content=%s\n",autoReplayICS.sICSAnaylseStat.c_str(),mReplyContentList[(char*)autoReplayICS.sICSAnaylseStat.c_str()].c_str());
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
		"[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:mReplyContentList:reply=%s&replay_content=%s\n",autoReplayICS.sICSAnaylseStat.c_str(),mReplyContentList[(char*)autoReplayICS.sICSAnaylseStat.c_str()].c_str());

	string paras = "";
	//paras="from=dnf&id="+autoReplayICS.sICSId+"&uin="+autoReplayICS.sUin+"&title="+title+"&content="+/*string(GbkToUtf8((char*)(*/mReplyContentList[(char*)autoReplayICS.sICSAnaylseStat.c_str()]/*.c_str())))*/;

	string resultStr = "";
// 	//paras = string(GbkToUtf8((char*)paras.c_str()));
// 	//公司O线填单
// 	if(sSource == "10"){
// 		//paras += "<br><script type%3d'text/javascript' src%3d'http://kf.qq.com/js/questionnaire.js?n_type%3d1' ></script>";
// 		RuleLOG->WriteLog("[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:[_rob_httpRpc_url=%s&paras=%s]\n",_rob_httpRpc_url.c_str(),paras.c_str());
// 		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
// 			"[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:[_rob_httpRpc_url=%s&paras=%s]\n",_rob_httpRpc_url.c_str(),paras.c_str());
// 
// 		iRet = _rob_httpRpc.Post(_rob_httpRpc_url,paras,resultStr);
// 		RuleLOG->WriteLog("[STEP:INFO]:::HttpRpc::Post:[resultStr=%s]\n",resultStr.c_str());
// 		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
// 			"[STEP:INFO]:::HttpRpc::Post:[resultStr=%s]\n",resultStr.c_str());
// rob-13110719340511977888
// 		if(iRet != 0){
// 			autoReplayICS.siReplyResult = IntToStr(STEP_Reply_WAITING_RESULT_ERROR);
// 			return STEP_Reply_WAITING_RESULT_ERROR;
// 		}
// 	}else 
	if(sSource == "30")
	{//互娱R产品填单(Q游)正式环境单据
		paras = "from=dzs&id=" + autoReplayICS.sICSId + "&uin=" + autoReplayICS.sUin + "&content=" + autoReplayICS.sICSAnaylseStat;
		RuleLOG->WriteLog("[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:[_rob_httpRpc_url_R=%s&paras=%s]\n",_rob_httpRpc_url_R.c_str(),paras.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:[_rob_httpRpc_url_R=%s&paras=%s]\n",_rob_httpRpc_url_R.c_str(),paras.c_str());

		iRet = _rob_httpRpc_R.Post(_rob_httpRpc_url_R,paras,resultStr);
		RuleLOG->WriteLog("[STEP:INFO]:::HttpRpc::Post:[resultStr=%s]\n",resultStr.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"[STEP:INFO]:::HttpRpc::Post:[resultStr=%s]\n",resultStr.c_str());

		if(iRet != 0)
		{
			autoReplayICS.siReplyResult=IntToStr(STEP_Reply_WAITING_RESULT_ERROR);
			return STEP_Reply_WAITING_RESULT_ERROR;
		}
	}
	else if (sSource == "40")//互娱R产品填单(Q游) test @@@added by v_zhtang on 2013-1-7;for the source of 'daohao.qq.com'
	{
		paras = "from=dzs&id=" + autoReplayICS.sICSId + "&uin=" + autoReplayICS.sUin + "&content=" + autoReplayICS.sICSAnaylseStat;
		RuleLOG->WriteLog("[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:[_rob_httpRpc_url_T=%s&paras=%s]\n",_rob_httpRpc_url_T.c_str(),paras.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:[_rob_httpRpc_url_T=%s&paras=%s]\n",_rob_httpRpc_url_T.c_str(),paras.c_str());

		iRet = _rob_httpRpc_T.Post(_rob_httpRpc_url_T,paras,resultStr);
		RuleLOG->WriteLog("[STEP:INFO]:::HttpRpc::Post:[resultStr=%s]\n",resultStr.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"[STEP:INFO]:::HttpRpc::Post:[resultStr=%s]\n",resultStr.c_str());

		if(iRet != 0){
			autoReplayICS.siReplyResult=IntToStr(STEP_Reply_WAITING_RESULT_ERROR);
			return STEP_Reply_WAITING_RESULT_ERROR;
		}///@@@end added.
	}
	else
	{
		//paras += "<br><script type%3d'text/javascript' src%3d'http://kf.qq.com/js/questionnaire.js?n_type%3d1' ></script>";
		RuleLOG->WriteLog("[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:[_rob_httpRpc_url=%s&paras=%s]\n",_rob_httpRpc_url.c_str(),paras.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"[STEP:INFO]:::RobRuleLogic::doReplayIcsResult:[_rob_httpRpc_url=%s&paras=%s]\n",_rob_httpRpc_url.c_str(),paras.c_str());

		iRet = _rob_httpRpc.Post(_rob_httpRpc_url,paras,resultStr);
		RuleLOG->WriteLog("[STEP:INFO]:::HttpRpc::Post:[resultStr=%s]\n",resultStr.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, autoReplayICS.sICSId.c_str(),autoReplayICS.sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"[STEP:INFO]:::HttpRpc::Post:[resultStr=%s]\n",resultStr.c_str());

		if(iRet != 0)
		{
			autoReplayICS.siReplyResult = IntToStr(STEP_Reply_WAITING_RESULT_ERROR);
			return STEP_Reply_WAITING_RESULT_ERROR;
		}
	}

	autoReplayICS.siReplyResult = IntToStr(STEP_Reply_WAITING_RESULT_SUCCESS);

	return STEP_Reply_WAITING_RESULT_SUCCESS;
}

/*********************************************************************
	Description:	发邮件
	@				
	@desc			
	@exception		none
	*/
int RobRuleLogic::SendWarnMail(const string& mailTitle, const string& mailContext)
{
	// 发邮件告警
	string mailTo("");// = "windhe@tencent.com";

	//发送邮件用户列表配置化 @modify by v_sjwang 2012/11/2 10:34:06
	int userNum = 0;
	map<string, string> userlist = CRobConf::getConf()->GetUserList();
	string name("");
	string flg("");
	for ( map<string, string>::iterator it = userlist.begin(); it != userlist.end(); it++ )
	{
		mailTo = "";
		name = it->first;
		flg = it->second;
		Trim(name);
		Trim(flg);
		if ( name.size() > 0 && 1 == StrToInt(flg) )
		{
			mailTo = mailTo + name + "@tencent.com ";
			//modified by v_zhtang on 2012-1-5;
			Trim(mailTo);
			bool result = CLogManager::SendEmail(mailTo, mailTitle, mailContext);
			if(result)
			{
				userNum++;		
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, "", "", TLOG_LEVEL_INFO, __FUNCTION__, "补送该物品记录已经存在，成功发送告警邮件到[%s]\n", mailTo.c_str() );
			}
			else
			{
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, "", "", TLOG_LEVEL_ERROR, __FUNCTION__, "补送该物品记录已经存在，发送告警邮件到[%s]失败\n", mailTo.c_str() );
			}
			//end modified.
		}
	}
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, "", "", TLOG_LEVEL_WARNING, __FUNCTION__, "补送该物品记录已经存在，成功发邮件告警人数为【%d】，邮件内容【%s】\n", userNum ,mailContext.c_str());

	return iRet;
}
/*********************************************************************
	Description:	物品删除总接口
	@				分为：各个业务需要单独来定义自己的流程，详细的见代码
	@desc			追踪完后，立即执行删除操作

	@exception		none
*/
int RobRuleLogic::doRobItemDelete(Item_Trace_List &ItemList)
{
	map<string,string> inParams;
	vector < map<string, string> > theItemDelResult;

	if(ItemList.iTraceHand == "-1")
	{
		//若是需 【先删除，再补送】
		if (StrToInt(ItemList.iSendAction) == STEP_ITEMTRACE_RUN_STAT_RESULT_DEL_SEND)
		{
			string strLastAction = ItemList.Undefined1;//最后一手流水动作
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"【INFO】准备删除寄售/邮件附件/仓库/身上物品，strLastAction【%s】\n",strLastAction.c_str());

			//1.2.2.1 踢盗号者下线 IDIP=2317 ###modified by v_zhtang on 2012-12-10;add chech player online or not.
			if (1 == CheckOnline(ItemList,ItemList.iRobTo_Uin,ItemList.vRobTo_RoleId,ItemList.vRobTo_RoleName))
			{
				inParams.clear();
				theItemDelResult.clear();
				inParams["area"] = ItemList.iWordId;
				inParams["uin"] = ItemList.iRobTo_Uin;
			//	inParams["charac_name"] = string(GbkToUtf8((char*)ItemList.vRobTo_RoleName.c_str()));

				iRet = RuleGet.GetFunction(ics_log_header(ItemList.ICSID,ItemList.iRobTo_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
					inParams,"kick_player_off",theItemDelResult);
				if (iRet == 0)
				{
					WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
						"1.2.2.1 kick_player_off|doRobItemDelete 踢玩家下线成功！\n");

					LogCM(ItemList,"踢玩家下线",RequestStr(inParams),"踢玩家下线成功","kick_player_off",
						ItemList.iRobTo_Uin,ItemList.vRobTo_RoleId,ItemList.vRobTo_RoleName,IntToStr(KICK_PLAYER_OFF_CMD),iRet,inParams["serial"]);

				}
				else if (iRet == -4000)//玩家不在线
				{
					WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
						"1.2.2.1 kick_player_off|doRobItemDelete 踢玩家下线失败，玩家本来就不在线！\n");

					LogCM(ItemList,"踢玩家下线",RequestStr(inParams),"玩家本来就不在线","kick_player_off",
						ItemList.iRobTo_Uin,ItemList.vRobTo_RoleId,ItemList.vRobTo_RoleName,IntToStr(KICK_PLAYER_OFF_CMD),0,inParams["serial"]);
				}
				else
				{
					WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
						"1.2.2.1 kick_player_off|doRobItemDelete 踢玩家下线失败，玩家本来就不在线！\n");
					LogCM(ItemList,"踢玩家下线",RequestStr(inParams),"接口错误！","kick_player_off",
						ItemList.iRobTo_Uin,ItemList.vRobTo_RoleId,ItemList.vRobTo_RoleName,IntToStr(KICK_PLAYER_OFF_CMD),iRet,inParams["serial"]);
					return -2;
				}
			}
			//1.2.2.2 短暂封停目的盗号者
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"@@@@@@被拔取玩家等级=【%s】\n",ItemList.iItem_Attribute_2.c_str());
			//BanQQ(ItemList,"拔取前短暂封停(s):"+IntToStr(BAN_TIME_PAUSE)+string("|大区:")+ItemList.iWordId,BAN_TIME_PAUSE/*,1*/);

			//1.2.2.3 删除目标物品（包括身上、仓库、寄售行、邮件附件） IDIP=4034|4035
			bool bDelFlag = false;
			string sPos = "";
			iRet = getRobItemLocation(ItemList.ICSID,ItemList.iRobTo_Uin,ItemList.iWordId,ItemList.iItem_Unique_Id,sPos);
			if (0 == iRet && "" != sPos)
			{
				if ("0" == sPos)//背包
				{
					int iDelBagRet = PlayerItemDel(ItemList,"player_bag_item_del");

					if (iDelBagRet == -4000)//-4000:error_info=[9,The searched object not exist]
					{
						ItemList.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NOT_FOUND_FAIL);//物品在身上或仓库找不到标记
						return -1;
					}else if ((iDelBagRet != 0 && iDelBagRet != -4000))
					{
						ItemList.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_DEL_INTERFACE_FAIL);//删除接口调用失败 标记
						return -1;
					}else if(iDelBagRet == 0)
					{
						bDelFlag = true;//删除成功
					}
				}else
				{

				}
			}else
			{
				ItemList.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_NOT_FOUND_FAIL);//物品在身上或仓库找不到标记
				return -1;
			}

			//删除成功，发送通知邮件
			if (bDelFlag)
			{
				ItemList.iSendResult = "0";//删除成功，置“暂未补送”状态，供后续补送模块读取处理

				inParams.clear();
				theItemDelResult.clear();
				inParams["area"] = ItemList.iWordId;
				inParams["uin"]=ItemList.iRobTo_Uin; 
				inParams["charac_no"] =ItemList.vRobTo_RoleId;
				inParams["subject"] = string(GbkToUtf8("[刀剑II]物品冻结"));
				inParams["text"] = string(GbkToUtf8("尊敬的玩家：你好！根据玩家投诉，经腾讯查证，您账号下有游戏物品属于其他玩家的被盗游戏物品。根据刀剑II《用户协议》，目前系统已经冻结了该游戏物品，如有疑问，请联系腾讯客服。谢谢！"));

				iRet = RuleGet.GetFunction(ics_log_header(ItemList.ICSID,ItemList.iRobTo_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
											inParams,"ics_item_send_mail_notice",theItemDelResult);
				if(iRet == 0 && theItemDelResult[0]["result"] == "0"){
					RuleLOG->WriteLog("1.2.2.3 ics_item_send_equip|doRobItemSend 删除物品后发送邮件成功\n");
					WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
						"1.2.2.3 ics_item_send_equip|doRobItemSend 删除物品后发送邮件成功\n");

				}else{
					RuleLOG->WriteLog("1.2.2.3 ics_item_send_equip|doRobItemSend 发送邮件失败,SAP接口返回错误码[%d]\n",iRet);
					WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
						"1.2.2.3 ics_item_send_equip|doRobItemSend 发送邮件失败,SAP接口返回错误码[%d]\n",iRet);
					return -2;
				}

				RuleLOG->WriteLog("1.2.2.3 装备转脏：删除物品成功！\n");
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemList.ICSID.c_str(),ItemList.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
					"1.2.2.3 装备转脏：删除物品成功！\n");
			}
		}
	}

	return 0;
}

/*********************************************************************
	Description:	封停玩家QQ、
	@				
	@desc			type: 0：全服封停帐号
	@exception		none
*/
int RobRuleLogic::BanQQ(Item_Trace_List& ItemTrace, const string& strMemo, const unsigned int ban_time, const int type)
{
	std::map< string, string > inParams;
	std::vector< map <string, string> > theBanResult;
	std::vector< map <string, string> > theBanResultEx;
	string strTime;
	int iRet2 = 0;
	bool bBanStatus = false;
	string sOriginalArea = ItemTrace.iWordId;
	//查询封号
	inParams["uin"] = ItemTrace.iRobTo_Uin;
	inParams["area"] = ItemTrace.iWordId;

	iRet = RuleGet.GetFunction(ics_log_header(ItemTrace.ICSID,ItemTrace.iRobTo_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
								inParams,"ics_get_role_ban_info",theBanResult);
	if (theBanResult.size() > 0)
	{
		/*
		<field name="reason"><![CDATA[0]]></field>
		<field name="result"><![CDATA[0]]></field>
		<field name="stop_time"><![CDATA[0]]></field>
		<field name="world_index"><![CDATA[4055947449]]></field>
		*/
		string stop_time = theBanResult[0]["stop_time"];
		if(stop_time != "0"){//如果查询到的时间大于0，则已封，表封停时间
			bBanStatus = true;//已封号
		//	ItemTrace.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_BAN_ALREADY);
			return STEP_ITEMSEND_RUN_STAT_BAN_ALREADY;
		}
	}

	if (0 == type && !bBanStatus)
	{
		//time_t tm = time(0);
		strTime = IntToStr(ban_time);
		//封13、14大区，即全服封号 @@@modified by v_zhtang on 2013-2-27;change area to 13/14
		inParams.clear();
		inParams["area"] = "13";//全服封号、封13、14大区
		inParams["uin"] = ItemTrace.iRobTo_Uin;
		inParams["lasting_sec"] = strTime;
		inParams["reason"] =  string(GbkToUtf8("633"));
		inParams["reason_remark"] =  string(GbkToUtf8((char*)strMemo.c_str()));

		iRet = RuleGet.GetFunction(ics_log_header(ItemTrace.ICSID,ItemTrace.iRobTo_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									inParams,"ics_rob_player_ban",theBanResult);
		ItemTrace.iWordId = "13";
		LogCM(ItemTrace,"封号",RequestStr(inParams),strMemo,"ics_rob_player_ban",\
			ItemTrace.iRobTo_Uin,\
			ItemTrace.vRobTo_RoleId,\
			ItemTrace.vRobTo_RoleName,\
			CRobConf::getConf()->GetIcsOper()["ics_rob_player_ban"],iRet,inParams["serial"]);

		inParams["area"] = "14";//全服封号、封13、14大区
		iRet2 = RuleGet.GetFunction(ics_log_header(ItemTrace.ICSID,ItemTrace.iRobTo_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
									inParams,"ics_rob_player_ban",theBanResultEx);
		ItemTrace.iWordId = "14";
		LogCM(ItemTrace,"封号",RequestStr(inParams),strMemo,"ics_rob_player_ban",\
			ItemTrace.iRobTo_Uin,\
			ItemTrace.vRobTo_RoleId,\
			ItemTrace.vRobTo_RoleName,\
			CRobConf::getConf()->GetIcsOper()["ics_rob_player_ban"],iRet2,inParams["serial"]);

		ItemTrace.iWordId = sOriginalArea;//还原
		if (0 == iRet && 0 == iRet2)
		{
			RuleLOG->WriteLog("[INFO]>> ics_rob_player_ban|banQQ  uin[%s]time[%s]全服封号成功\n",ItemTrace.iRobTo_Uin.c_str(),strTime.c_str());
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"[INFO]>> ics_rob_player_ban|banQQ  uin[%s]time[%s]全服封号成功\n",ItemTrace.iRobTo_Uin.c_str(),strTime.c_str());
		}else
		{
			RuleLOG->WriteLog("[ERROR]>> ics_rob_player_ban|banQQ uin[%s] 失败,IDIP接口返回错误码【iRet=%d|iRet2=%d】\n",ItemTrace.iRobTo_Uin.c_str(),iRet,iRet2);
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
				"[ERROR]>> ics_rob_player_ban|banQQ uin[%s] 失败,IDIP接口返回错误码【iRet=%d|iRet2=%d】\n",ItemTrace.iRobTo_Uin.c_str(),iRet,iRet2);

			return STEP_ITEMSEND_RUN_STAT_BAN_FAIL;
		}
	}else if (1 == type && !bBanStatus)//added by v-zhtang on 2012 -12-19;
	{
		//time_t tm = time(0);
		strTime = IntToStr(/*tm + */ban_time);
		
		inParams.clear();
		inParams["area"] = ItemTrace.iWordId;//封指定大区
		inParams["uin"] = ItemTrace.iRobTo_Uin;
		inParams["lasting_sec"] = strTime;
		inParams["reason"] =  string(GbkToUtf8("633"));
		inParams["reason_remark"] =  string(GbkToUtf8((char*)strMemo.c_str()));

		iRet = RuleGet.GetFunction(ics_log_header(ItemTrace.ICSID,ItemTrace.iRobTo_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
			inParams,"ics_rob_player_ban",theBanResult);

		LogCM(ItemTrace,"封号",RequestStr(inParams),strMemo,"ics_rob_player_ban",\
			ItemTrace.iRobTo_Uin,\
			ItemTrace.vRobTo_RoleId,\
			ItemTrace.vRobTo_RoleName,\
			CRobConf::getConf()->GetIcsOper()["ics_rob_player_ban"],iRet,inParams["serial"]);

		if (0 == iRet)
		{
			RuleLOG->WriteLog("[INFO]>> ics_rob_player_ban|banQQ  uin[%s]time[%s]封号成功\n",ItemTrace.iRobTo_Uin.c_str(),strTime.c_str());
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"[INFO]>> ics_rob_player_ban|banQQ  uin[%s]time[%s]封号成功\n",ItemTrace.iRobTo_Uin.c_str(),strTime.c_str());
		}else
		{
			RuleLOG->WriteLog("[ERROR]>> ics_rob_player_ban|banQQ uin[%s] 失败,IDIP接口返回错误码【iRet=%d|iRet2=%d】\n",ItemTrace.iRobTo_Uin.c_str(),iRet,iRet2);
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),ItemTrace.iRobTo_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
				"[ERROR]>> ics_rob_player_ban|banQQ uin[%s] 失败,IDIP接口返回错误码【iRet=%d|iRet2=%d】\n",ItemTrace.iRobTo_Uin.c_str(),iRet,iRet2);

			return STEP_ITEMSEND_RUN_STAT_BAN_FAIL;
		}//end added.
	}

	return 0;
}

/*********************************************************************
	Description:	查询玩家在线信息
	@				
	@desc			true返回在线，false返回表不在线
	@exception		none
*/
int RobRuleLogic::CheckOnline(Item_Trace_List& ItemTrace,const string& uin, const string& roleId, const string& roleName)
{
	int bOnline = 0;

	std::map< string, string > inParams;
	std::vector< map <string, string> > theOnlineResult;

	//查询在线
	inParams["uin"] = uin;
	inParams["area"] = ItemTrace.iWordId;
	inParams["charac_no"] = roleId;
	inParams["charac_name"] = string(GbkToUtf8((char*)roleName.c_str()));

	iRet = RuleGet.GetFunction(ics_log_header(ItemTrace.ICSID,uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
		inParams,"ics_get_role_online",theOnlineResult);
	if (0 == iRet)
	{
		RuleLOG->WriteLog("[INFO]>> ics_get_role_online|uin[%s]查询在线与否成功\n",uin.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"[INFO]>> ics_get_role_online|banQQ  uin[%s]查询在线与否成功\n",uin.c_str());
		
		bOnline = theOnlineResult.size() > 0 ? StrToInt(theOnlineResult[0]["online_flag"]) : -1;
		return bOnline;
	}else
	{
		RuleLOG->WriteLog("[ERROR]>> ics_get_role_online|uin[%s] 查询在线与否,IDIP接口返回错误码【iRet=%d】\n",uin.c_str(),iRet);
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemTrace.ICSID.c_str(),uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"[ERROR]>> ics_get_role_online|banQQ uin[%s] 失败,IDIP接口返回错误码【iRet=%d】\n",uin.c_str(),iRet);

		return -1;
	}
}

/****************************added by v_zhtang on 2012-12-12*****************************************
	Description:	对于找回范围物品，正常流转或拔取失败的物品，给与等价礼包赠送
	@param			ItemTrace: 待处理物品列表
	@return			0：成功，非0：失败
	@exception		none
	*/
int RobRuleLogic::DoGiftCompensate(Rob_Ics_Complaint &sIcsId)
{
	/*
	 *	1. 过滤条目：“未能找回”=可找回范围内正常流转 + 拔取失败  + 补送失败
			1.1 正常流转： 已消失，不补送(47)+ 重要道具字段（非NO） && 销赃（48）+重要道具（非NO）
			1.2 拔取失败： 补送结果=删除失败标记
		2. 根据规则等价换算；(各物品等级、星级、颜色、封印等要素从盗号流水表里获取)
		3. 补偿礼包；
		礼包id	礼包档次价值	礼包名称
		118601	0-50	被盗补偿礼包
		118602	50-100	被盗补偿礼包
		118603	100-200	被盗补偿礼包
		118604	200-500	被盗补偿礼包
		118605	500-1000	被盗补偿礼包
		118606	1000以上	被盗补偿礼包

	 */
	RobICSOper ics_oper;
	vector < Item_Flow_List > vecItemFlowInfo;
	map<string,string> inParams;
	vector < map<string, string> > theItemSendResult;
	double dTotalValue = 0;
	string strGiftId("");
	string strRobedUin("");
	string strRobedRoleId("");
	string strWorldId("");
	string strRoleName("");

	//0. 重复判断，是否已补过礼包：普通180，vip：90
	if (CheckGiftSendCount(sIcsId) > 0)
	{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, sIcsId.sICSId.c_str(),"", TLOG_LEVEL_INFO, __FUNCTION__, \
			"该单据QQ【%s】已补过礼包了。tks！\n",sIcsId.sICSId.c_str());
		return 0;
	}

	//1. 过滤条目
	iRet = ics_oper.ReadICSItemsCompensate(vecItemFlowInfo,sIcsId.sICSId);
	if (0 != iRet )
	{
		return -1;
	}else if (0 == vecItemFlowInfo.size())
	{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, sIcsId.sICSId.c_str(),"", TLOG_LEVEL_INFO, __FUNCTION__, \
			"该单据【%s】无需差价补偿\n",sIcsId.sICSId.c_str());
		return 0;
	}
	strRobedUin = vecItemFlowInfo[0].iRobed_Uin;
	strRobedRoleId = vecItemFlowInfo[0].vRobed_RoleId;
	strRoleName = vecItemFlowInfo[0].vRobed_RoleName;
	strWorldId = vecItemFlowInfo[0].iWordId;
	//2. 换算价值
	dTotalValue = GetICSItemValue(vecItemFlowInfo);
	//cout << "---------------------\n" << dTotalValue << endl;
	//3. 匹配礼包
	string sFlag="";
	if (dTotalValue > 0 && dTotalValue <= 50)
	{
		strGiftId = "118601";
		sFlag = "1";
	} else if (dTotalValue > 50 && dTotalValue <= 100)
	{
		strGiftId = "118602";
		sFlag = "2";
	} else if (dTotalValue > 100 && dTotalValue <= 200)
	{
		strGiftId = "118603";
		sFlag = "3";
	}else if (dTotalValue > 200 && dTotalValue <= 500)
	{
		strGiftId = "118604";
		sFlag = "4";
	}else if (dTotalValue > 500 && dTotalValue <= 1000)
	{
		strGiftId = "118605";
		sFlag = "5";
	}else if (dTotalValue > 1000)
	{
		strGiftId = "118606";
		sFlag = "6";
	}else
	{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, sIcsId.sICSId.c_str(),"", TLOG_LEVEL_INFO, __FUNCTION__, \
			"该单据【%s】无匹配礼包ID，请检查！\n",sIcsId.sICSId.c_str());
		return 0;
	}
	
	//4. 发送礼包
	inParams.clear();
	theItemSendResult.clear();
	inParams["area"] = strWorldId;
	inParams["uin"] = strRobedUin;
	inParams["charac_no"] = strRobedRoleId;
	inParams["item_id"] = strGiftId;
	inParams["item_num"] = "1";
	inParams["bind_status"] = "2";//1-不绑定，2-拾取绑定，3-使用后绑定
	inParams["title"] = string(GbkToUtf8("【御龙在天】被盗补偿礼包发放"));
	inParams["reason"] = string(GbkToUtf8("亲爱的御龙族，针对您本次提交的被盗的找回申请，我们已尽最大努力挽回您的损失，对于无法找回的装备物品，还请您谅解。感谢您一直以来对御龙的支持，最后给您赠送“被盗补偿礼包”，还请您查收。鉴于此次被盗情况的出现，请您对帐号的安全多加重视，可尝试通过多种方式保护游戏帐号：1、绑定密保开通游戏登录保护；2、尽量避免把帐号密码告知他人；3、避免接收陌生人的截图、文件。"));

	iRet = RuleGet.GetFunction(ics_log_header(sIcsId.sICSId,strRobedUin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
		inParams,"ics_item_send_goods",theItemSendResult);

	Item_Trace_List ItemList;
	ItemList.iItem_Id = strGiftId;
	ItemList.ICSID = sIcsId.sICSId;
	ItemList.iWordId = strWorldId;
	ItemList.iItem_Num = "1";
	ItemList.iServiceID = CRobConf::getConf()->GetGroupInfo()["group_id"];
	LogCM(ItemList,"赠送礼包",RequestStr(inParams),"被盗补偿礼包"+sFlag+": 价值"+DoubleToStr(dTotalValue),"ics_item_send_goods",
		strRobedUin,strRobedRoleId,strRoleName,IntToStr(SEND_GOODS_CMD),iRet,inParams["serial"]);

	if(iRet == 0 && theItemSendResult[0]["result"] == "0"){
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, sIcsId.sICSId.c_str(),strRobedUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"差价补偿礼包，补送结果成功\n");
	}else{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, sIcsId.sICSId.c_str(),strRobedUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"差价补偿礼包，补送结果失败【%d】\n",iRet);
		return iRet;
	}

	//5. 更新状态
	iRet = ics_oper.UpdateICSCompensateResult(sIcsId.sICSId,DoubleToStr(dTotalValue)+":"+strGiftId);
	if(iRet == 0){
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, sIcsId.sICSId.c_str(),strRobedUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"差价补偿礼包，更新补送结果状态成功\n");
	}else{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, sIcsId.sICSId.c_str(),strRobedUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"差价补偿礼包，更新补送结果状态失败【%d】\n",iRet);
	}

	return 0;
}

/*****************************added by v_zhtang on 2012-12-18*****************************
	Description:	查询封印等级；查流水时，顺便记录该区的封印等级IDIP
	@param			rob_data: 异常登录时间段
					SealLevel: 查询封印等级结果
	@return			0：成功，非0：失败
	@exception		none
*/
int RobRuleLogic::QuerySealLevel(const string &sICSID,const string &sUin,const string &sArea,string &SealLevel)
{
	std::map< string, string > inParams;
	std::vector< map <string, string> > theSealResult;
	std::vector< map <string, string> >::iterator iter;

	/************************************************************************/
	/*  m_iActivateTime：激活时间
		m_iLevel：等级
		m_iOpenTime：打开时间
		list：封印数量                                                        */
	/************************************************************************/
	//查询封印
	inParams["area"] = sArea;
	iRet = RuleGet.GetFunction(ics_log_header(sICSID,sUin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
		inParams,"ics_get_area_seal",theSealResult);
	if (0 == iRet)
	{
		if (theSealResult.size() > 0)
		{
			for (iter=theSealResult.begin(); iter!=theSealResult.end(); iter++)
			{
				if (theSealResult.size() > 1)
				{
					if (0 == StrToLong((*iter)["name_2"]) && 0 == StrToLong((*iter)["name_0"]))
					{
						SealLevel = (*--iter)["name_1"];
						break;
					}
					if (0 == StrToLong((*iter)["name_2"]) && 0 != StrToLong((*iter)["name_0"]))
					{
						SealLevel = (*iter)["name_1"];
						break;
					}
				}else
				{
					if (iter == theSealResult.end()-1)
					{
						SealLevel = (*iter)["name_1"];
						break;
					}
				}
			}
		}
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, sICSID.c_str(),sUin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"ics_get_area_seal|查询大区封印成功=【%s】\n",SealLevel.c_str());
	}else
	{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, sICSID.c_str(),sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"ics_get_area_seal|失败,IDIP接口返回错误码【iRet=%d】\n",iRet);

		return -1;
	}

	return 0;
}

/*****************************added by v_zhtang on 2013-1-5****************************************
	Description:	统计该ics单据所有该统计列表的价值
	@param			
				robItemFlowInfo:		被统计列表
				ItemValueTotal：		    返回的价值，单位RMB
	@return			0：成功，非0：失败
	@exception		none
*/
#define SEAL_LEVEL_INTERVAL		20//装备等级距封印等级间隔
double RobRuleLogic::GetICSItemValue(vector < Item_Flow_List > &robItemFlowInfo)
{
	double dItemsValue = 0;
	RobICSOper ics_oper;
	string sSealFlag;
	
	for (std::vector< Item_Flow_List >::iterator it=robItemFlowInfo.begin(); it!=robItemFlowInfo.end(); it++)
	{
		if ("1" == (*it).iItem_Type)//Equip
		{
			int iValue = StrToInt(vItemUseLevelList["iItem_Id"]) - StrToInt((*it).iItem_Attribute_1);
			if (iValue < SEAL_LEVEL_INTERVAL || iValue > -SEAL_LEVEL_INTERVAL)//距封印计算
			{
				sSealFlag = "0";
			}else
			{
				sSealFlag = "1";
			}
			//sSealFlag = (abs(StrToInt(vItemUseLevelList["iItem_Id"]) - StrToInt((*it).iItem_Attribute_1)) < SEAL_LEVEL_INTERVAL ? "0" : "1");
			dItemsValue += ics_oper.GetDefinedEquipValue(*it,sSealFlag);

			double dStarValue = 0;
			dStarValue = StrToDouble(vItemStarValueList[(*it).iItem_Price_Value]);//星级价值计算
			dItemsValue += dStarValue;
		}else//Goods
		{
			dItemsValue += ics_oper.GetDefinedGoodsValue(*it);
		}
	}
	WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, robItemFlowInfo[0].ICSID.c_str(),robItemFlowInfo[0].iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
		"该单据【%s】差价补偿总价值为【dItemsValue=%lf】\n",robItemFlowInfo[0].ICSID.c_str(),dItemsValue);

	return dItemsValue;
}

/*********************************************************************
Description:	重新二次补偿物品
@				
@desc			根据iSendResult结果码及物品类型，采取重补措施
@exception		none
*/
int RobRuleLogic::ReHandleSendItems(Item_Trace_List& ItemSend)
{
	std::map< string, string > inParams;
	std::vector< map <string, string> > theItemSendResult;
	std::vector< map <string, string> > theItemBlobResult;
	//接口传参
	inParams["uin"] = ItemSend.iRobed_Uin;
	inParams["area"] = ItemSend.iWordId;
	inParams["charac_no"] = ItemSend.vRobed_RoleId;

	//T下线
	/*iRet = RuleGet.GetFunction(ics_log_header(ItemList[i].ICSID,ItemList[i].iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
			inParams,"kick_player_off",theItemSendResult);*/

	if ("0" == ItemSend.iItem_Type)//道具
	{
		//开始补送道具
		inParams["item_id"] = ItemSend.iItem_Level == "0" ? ItemSend.iItem_Id : "91"+ItemSend.iItem_Level+ItemSend.iItem_Id;
		inParams["item_num"] =ItemSend.iItem_Num;
		inParams["bind_status"] ="2";//1-不绑定，2-拾取绑定，3-使用后绑定
		inParams["title"] = string(GbkToUtf8("【御龙在天】关于盗号受理结果反馈"));
		inParams["reason"] = string(GbkToUtf8("亲，由于游戏帐号被盗或其他原因，导致您的游戏道具丢失，系统现在将已查证的相关物品返还给您，祝您游戏愉快。"));

		iRet = RuleGet.GetFunction(ics_log_header(ItemSend.ICSID,ItemSend.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
		inParams,"ics_item_send_goods",theItemSendResult);

		LogCM(ItemSend,"补送道具",RequestStr(inParams),"[R]盗号丢失找回:"+ItemSend.iItem_Unique_Id,"ics_item_send_goods",
			ItemSend.iRobed_Uin,ItemSend.vRobed_RoleId,ItemSend.vRobed_RoleName,IntToStr(SEND_GOODS_CMD),iRet,inParams["serial"]);
		if(iRet == 0 && theItemSendResult[0]["result"] == "0")
		{
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemSend.ICSID.c_str(),ItemSend.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
				"获取玩家的道具[%s]补送结果成功\n",ItemSend.iItem_Unique_Id.c_str());
			ItemSend.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_SEND_FINISH);
		}else{
			WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemSend.ICSID.c_str(),ItemSend.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
				"获取玩家的道具[%s]补送结果失败,SAP接口返回错误码【%d】\n",ItemSend.iItem_Unique_Id.c_str(),iRet);
			return -1;
		}

	}else//装备
	{
		if ("0" == ItemSend.iSendResult)//表上次查找装备blob失败，导致补送中止
		{
			iRet = FetchItemBlob(ItemSend,theItemBlobResult);
			if (iRet == 0 && theItemBlobResult.size() > 0)
			{
				ItemSend.iItem_Attribute_blob = theItemBlobResult[0]["szBlobInfo"];//读取装备blob属性
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemSend.ICSID.c_str(),ItemSend.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
					"[guid: %s]blob属性获取成功【%s】！\n",ItemSend.iItem_Unique_Id.c_str(),ItemSend.iItem_Attribute_blob.c_str());
			}else
			{
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemSend.ICSID.c_str(),ItemSend.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
					"[guid: %s]blob属性获取失败！\n",ItemSend.iItem_Unique_Id.c_str());
				return -2;
			}
		}
		if ("0" != ItemSend.iItem_Attribute_blob)
		{
			//开始补送
			inParams.clear();
			theItemSendResult.clear();
			inParams["area"] = ItemSend.iWordId;
			inParams["uin"]=ItemSend.iRobed_Uin; 
			inParams["charac_no"] =ItemSend.vRobed_RoleId;
			inParams["item_str"] = ItemSend.iItem_Attribute_blob;

			iRet = RuleGet.GetFunction(ics_log_header(ItemSend.ICSID,ItemSend.iRobed_Uin,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
				inParams,"ics_item_send_equip",theItemSendResult);
			LogCM(ItemSend,"补送装备",RequestStr(inParams),"[R]盗号丢失找回:"+ItemSend.iItem_Unique_Id,"ics_item_send_equip",
				ItemSend.iRobed_Uin,ItemSend.vRobed_RoleId,ItemSend.vRobed_RoleName,IntToStr(SEND_EQUIP_CMD),iRet,inParams["serial"]);
			if(iRet == 0 && theItemSendResult[0]["result"] == "0")
			{
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemSend.ICSID.c_str(),ItemSend.iRobed_Uin.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
					"获取玩家的物品[%s]补送结果成功\n",ItemSend.iItem_Unique_Id.c_str());
				ItemSend.iSendResult = IntToStr(STEP_ITEMSEND_RUN_STAT_SEND_FINISH);
			}
			else
			{
				WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, ItemSend.ICSID.c_str(),ItemSend.iRobed_Uin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
					"获取玩家的物品[%s]补送结果失败,IDIP接口返回错误码【%d】\n",ItemSend.iItem_Unique_Id.c_str(),iRet);
				return -1;
			}	
		}
	}

	return 0;
}

/*****************************added by v_zhtang on 2013-1-16****************************************
	Description:	获取被盗装备的异常登入前的最后星级
	@param			
				rob_slot:		异常时间段
				item_guid：		装备guid
				cur_star:	返回的星级
	@return				0：成功，非0：失败
	@exception		none
*/
int RobRuleLogic::GetItemCurStarBeforeLogin(Rob_SLOT &rob_slot, string &item_guid, string &cur_star)
{
	std::map< string, string > inParams;
	std::vector< map <string, string> > theStarResult;

	//接口传参
	inParams["uin"] = rob_slot.UserID;
	inParams["area"] = rob_slot.WorldID;
	inParams["time"] = rob_slot.LoginTime;
	inParams["guid"] = item_guid;

	//按异常登录时间往前取最近一条流水
	iRet = RuleGet.GetFunction(ics_log_header(rob_slot.ICSID,rob_slot.UserID,CRobConf::getConf()->GetGroupInfo()["group_id"]),\
			inParams,"equip_star_before_login",theStarResult);

	if (0 == iRet)
	{
		if (theStarResult.size() > 0)
		{
			cur_star = theStarResult[0]["iCurStar"];
		}
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, rob_slot.ICSID.c_str(),rob_slot.UserID.c_str(), TLOG_LEVEL_INFO, __FUNCTION__, \
			"查询装备被盗前星级成功=【%s】\n",cur_star.c_str());
	}else
	{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, rob_slot.ICSID.c_str(),rob_slot.UserID.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, \
			"查询装备被盗前星级失败,IDIP接口返回错误码【iRet=%d】\n",iRet);

		return -1;
	}
	return 0;
}

/*****************************added by v_zhtang on 2013-1-25****************************************
	Description:	判断补偿礼包的次数
	@param			
				Rob_Ics_Complaint:		投诉单据
			
	@return			
	@exception		none
*/
int RobRuleLogic::CheckGiftSendCount(Rob_Ics_Complaint &info)
{
	map<string,string> theParamIn;
	theParamIn.clear();

	theParamIn["uin"] = info.sUin;
	theParamIn["role_id"] = info.sRoleID;
	theParamIn["apply_day_in"] = info.sIsVip == "0" ? CRobConf::getConf()->GetIcsValid()["receve_double"] :\
		CRobConf::getConf()->GetIcsValid()["receve_vip_double"];//vip用户
	theParamIn["service_id"] = info.sServiceID;
	//theParamIn["role_id"] = info.sRoleID;

	vector< map<string,string> > base_result;
	if(0 != RuleGet.GetFunction(ics_log_header(info.sICSId,info.sUin,info.sServiceID),\
		theParamIn,"gift_send_repeat_uin",base_result))
	{
		WriteLogsRUN(TLOG_TYPE_ROBRULELOGIC, info.sICSId.c_str(), info.sUin.c_str(), TLOG_LEVEL_ERROR, __FUNCTION__, "Find Uin 'gift_send_repeat_uin' happened error,not find info\n" );
		return -1;
	}
	if (base_result.size() > 0)
	{
		return StrToInt(base_result[0]["applyValueCount"]);
	}
}