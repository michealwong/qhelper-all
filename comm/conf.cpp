/**
@file conf.cpp

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		GunLi
@version	1.0
@date		2010/10/09

history:
<PRE>
History ID	:	1
Author    	:	GunLi
DateTime	:	2010/10/09
Description :	Create
</PRE>

Alert by asherzhou
2011/04/19
*/

#include "conf.h"
#include "msg.h"
#include "comm.h"
#include "comm_datetime.h"
//以下三个Include需要改造成系统库
#include "NDS_config.h"
#include "comm_strings.h"


CRobConf* CRobConf::RobConf = NULL;
CLog* CRobConf::ConfLOG=NULL;
/**
Description:	获取一个ConfNode对象
@return			
@exception		none
*/
CRobConf* CRobConf::getConf()
{
	if (RobConf==NULL)
	{
		RobConf = new CRobConf();
	}
	return RobConf;
}

/**
Description:	构造函数，读取所有的配置信息
@return			
@exception		none
@alert  asherzhou 修改一些读取配置信息，比如dr,log配置可以完全去掉了。优化rob.conf结构
@							加入配置死的信息；
*/
CRobConf::CRobConf()
{
	//读取rob.conf，#include "NDS_config.h"的类
	//下面的类初始化的时候如果出现问题，就会抛出异常；
	/*CONFPATH = "./cfg/rob.conf";
	UNIX_config<NDS_single_config_node> *stConf = new UNIX_config<NDS_single_config_node>((const char*)CONFPATH.c_str());*/
	
	MAKECONFLOG="./logs/"+GetCurDateDay()+"RobConf.log";
	ConfLOG = new CLog((const char*)MAKECONFLOG.c_str());
	ConfLOG->WriteLog("<<<Agin we new a Clog???>>>\n");

	ConfLOG->LogOn();
	ConfLOG->WriteLog("<<<Get rob.conf Begin>>>\n");

	if(Ics_Oper.size()>0) Ics_Oper.clear();
	if(Ics_Valid.size()>0) Ics_Valid.clear();
	if(GroupInfo.size()>0) GroupInfo.clear();
	if(Log_Info.size()>0) Log_Info.clear();
	if(UserList.size()>0) UserList.clear();
	if(Common_Interf.size()>0) Common_Interf.clear();
		
	CONFPATH = "./cfg/rob.xml";
	xmlPtr = xmlReadFile(CONFPATH.c_str(),"UTF-8",XML_PARSE_NOBLANKS);
	xmlKeepBlanksDefault(1);
	ParseXmlConfig(xmlPtr);

/*****************************v1.01***********************************************/	
	//try
	//{
	//		ConfLOG->WriteLog("============Read rob.conf Begin==========\n");
	//
	//		//comm读取
	//		GroupInfo["group_id"] = (*stConf)["common"]("group_id");
	//		GroupInfo["group_name"] = (*stConf)["common"]("group_name");
	//		//Vip信息
	//		GroupInfo["vip_ip"] = (*stConf)["common"]("vip_ip");
	//		GroupInfo["vip_port"] = (*stConf)["common"]("vip_port");
	//		GroupInfo["vip_cmd"] = (*stConf)["common"]("vip_cmd");
	//		//web二次回复接口
	//		GroupInfo["web_http_proxy"] = (*stConf)["common"]("web_http_proxy");
	//		GroupInfo["web_http_url"] = (*stConf)["common"]("web_http_url");
	//		GroupInfo["web_http_proxy_R"] = (*stConf)["common"]("web_http_proxy_R");
	//		GroupInfo["web_http_url_R"] = (*stConf)["common"]("web_http_url_R");
	//		//ics 配置读取
	//		Ics_Valid["size_of_ics_one"] = (*stConf)["ics_valid"]("size_of_ics_one");
	//		Ics_Valid["size_of_ics_two"] = (*stConf)["ics_valid"]("size_of_ics_two");
	//		Ics_Valid["size_of_ics_three"] = (*stConf)["ics_valid"]("size_of_ics_three");
	//		Ics_Valid["size_of_ics_four"] = (*stConf)["ics_valid"]("size_of_ics_four");
	//		Ics_Valid["size_of_ics_five"] = (*stConf)["ics_valid"]("size_of_ics_five");
	//		Ics_Valid["size_of_ics_six"] = (*stConf)["ics_valid"]("size_of_ics_six");
	//		Ics_Valid["role_level"] = (*stConf)["ics_valid"]("role_level");
	//		Ics_Valid["create_due"] = (*stConf)["ics_valid"]("create_due");
	//		Ics_Valid["receve_double"] = (*stConf)["ics_valid"]("receve_double");
	//		Ics_Valid["receve_vip_double"] = (*stConf)["ics_valid"]("receve_vip_double");
	//		Ics_Valid["block_day"] = (*stConf)["ics_valid"]("block_day");
	//		
	//		//读取权限人白名单
	//		Authority["query"] =  (*stConf)["authority"]("query");
	//		Authority["operate"] =  (*stConf)["authority"]("operate");


	//		//Ics_Info操作类信息读取
	//		Ics_Oper["ics_info_list"] = (*stConf)["ics_info_list"]("id");
	//		Ics_Oper["ics_states_update"] = (*stConf)["ics_states_update"]("id");
	//		Ics_Oper["ics_stat_add"] = (*stConf)["ics_stat_add"]("id");
	//		Ics_Oper["ics_rob_slot_insert"] = (*stConf)["ics_rob_slot_insert"]("id");
	//		Ics_Oper["ics_apply_repeat_uin"] = (*stConf)["ics_apply_repeat_uin"]("id");
	//		Ics_Oper["ics_apply_repeat_uin_extra"] = (*stConf)["ics_apply_repeat_uin_extra"]("id");
	//		Ics_Oper["ics_slot_runstat_update"] = (*stConf)["ics_slot_runstat_update"]("id");
	//		Ics_Oper["ics_stat_item_add"] = (*stConf)["ics_stat_item_add"]("id");
	//		Ics_Oper["ics_item_flow_query_proc"] = (*stConf)["ics_item_flow_query_proc"]("id");
	//		Ics_Oper["ics_item_trace_general"] = (*stConf)["ics_item_trace_general"]("id");
	//		Ics_Oper["ics_item_flow_runstat_update"] = (*stConf)["ics_item_flow_runstat_update"]("id");
	//		Ics_Oper["ics_item_send_query_proc"] = (*stConf)["ics_item_send_query_proc"]("id");
	//		Ics_Oper["ics_item_send_runstat_update"] = (*stConf)["ics_item_send_runstat_update"]("id");
	//		Ics_Oper["ics_stat_result_update"] = (*stConf)["ics_stat_result_update"]("id");
	//		
	//		//物品流水查询按guid
	//		Ics_Oper["ics_trade_info_list"] = (*stConf)["ics_trade_info_list"]("id");
	//		Ics_Oper["ics_flow_info_by_guid"] = (*stConf)["ics_flow_info_by_guid"]("id");
	//		
	//		Ics_Oper["ics_get_role_list"] = (*stConf)["ics_get_role_list"]("id");
	//		Ics_Oper["ics_info_role_update"] = (*stConf)["ics_info_role_update"]("id");
	//		Ics_Oper["ics_get_role_info"] = (*stConf)["ics_get_role_info"]("id");
	//		Ics_Oper["ics_get_role_ban_info"] = (*stConf)["ics_get_role_ban_info"]("id");
	//		Ics_Oper["login_logout_log"] = (*stConf)["login_logout_log"]("id");
	//		Ics_Oper["ics_rob_logout_proc_list"] = (*stConf)["ics_rob_logout_proc_list"]("id");
	//		Ics_Oper["ics_rob_player_ban"] = (*stConf)["ics_rob_player_ban"]("id");
	//	//	Ics_Oper["ics_item_conf_info"] = (*stConf)["ics_item_conf_info"]("id");
	//		Ics_Oper["ics_role_item_flow_query"] = (*stConf)["ics_role_item_flow_query"]("id");
	//		Ics_Oper["ics_item_flow_general"] = (*stConf)["ics_item_flow_general"]("id");
	//		//IDIP
	//		Ics_Oper["ics_item_send_goods"] = (*stConf)["ics_item_send_goods"]("id");
	//		Ics_Oper["ics_item_send_equip"] = (*stConf)["ics_item_send_equip"]("id");
	//		Ics_Oper["login_changesrv_query"] = (*stConf)["login_changesrv_query"]("id");
	//		Ics_Oper["ics_item_blob_get"] = (*stConf)["ics_item_blob_get"]("id");
	//		Ics_Oper["kick_player_off"] = (*stConf)["kick_player_off"]("id");
	//		Ics_Oper["player_bag_item_del"] = (*stConf)["player_bag_item_del"]("id");
	//		Ics_Oper["player_storage_item_del"] = (*stConf)["player_storage_item_del"]("id");
	//		Ics_Oper["ics_item_send_mail_notice"] = (*stConf)["ics_item_send_mail_notice"]("id");
	//		Ics_Oper["player_consignment_item_del"] = (*stConf)["player_consignment_item_del"]("id");
	//		Ics_Oper["player_mail_item_del"] = (*stConf)["player_mail_item_del"]("id");
	//		//单据读取指定一条，
	//		Ics_Oper["ics_id_send_only_one"] = (*stConf)["ics_id_send_only_one"]("id");//单据ID值
	//		Ics_Oper["ics_info_one"] = (*stConf)["ics_info_one"]("id");//操作接口id

	//		Ics_Oper["item_consignment_search"] = (*stConf)["item_consignment_search"]("id");//寄售购买日志

	//		Ics_Oper["query_login_logout_time"] = (*stConf)["query_login_logout_time"]("id");
	//		Ics_Oper["item_blob_before_login"] = (*stConf)["item_blob_before_login"]("id");
	//		Ics_Oper["item_blob_after_login"] = (*stConf)["item_blob_after_login"]("id");
	//		//reply
	//		Ics_Oper["rob_ics_need_reply_list"] = (*stConf)["rob_ics_need_reply_list"]("id");
	//		Ics_Oper["ics_reply_status_update"] = (*stConf)["ics_reply_status_update"]("id");
	//		Ics_Oper["rob_ics_need_reply_one"] = (*stConf)["rob_ics_need_reply_one"]("id");

	//		Ics_Oper["get_mail_id_by_event"] = (*stConf)["get_mail_id_by_event"]("id");
	//		Ics_Oper["get_vip_info"] = (*stConf)["get_vip_info"]("id");

	//		Ics_Oper["ics_item_send_result_select"] = (*stConf)["ics_item_send_result_select"]("id");
	//		Ics_Oper["ics_item_send_info_insert"] = (*stConf)["ics_item_send_info_insert"]("id");
	//		Ics_Oper["ics_item_send_warn_mail_update"] = (*stConf)["ics_item_send_warn_mail_update"]("id");
	//		Ics_Oper["ics_item_send_result_update"] = (*stConf)["ics_item_send_result_update"]("id");
	//}
	//catch (NDS::NDS_exception ex)
	//{
	//	ConfLOG->WriteLog("NDS::NDS_exception, %s\n", ex.get_message().c_str());
	//	delete stConf;
	//	stConf = NULL;
	//	delete ConfLOG;
	//	ConfLOG = NULL;
	//}
	//if (NULL != stConf)
	//{
	//	delete stConf;
	//	stConf = NULL;
	//}
}

CRobConf::~CRobConf()
{
  if(NULL!=ConfLOG)
  	{
  		delete ConfLOG;
  	}
  if(NULL != xmlPtr)
  {
	  xmlFreeDoc(xmlPtr);
	  xmlPtr = NULL;//防止二次释放
  }
}

int CRobConf::ParseXmlConfig(xmlDocPtr xmlPtr)
{
	xmlNodePtr ptrNode;
	xmlNodePtr ptrRoot;
	xmlNodePtr ptrCur;

	
	if(NULL != xmlPtr)
	{
		ConfLOG->WriteLog("[INFO]>>load xml success\n");
		WriteLogsRUN(TLOG_TYPE_ROBCONF, "", "",  TLOG_LEVEL_CONF + TLOG_LEVEL_INFO, __FUNCTION__, "[INFO]>>load xml success\n" );
		// locate the root node:<rob>
		ptrRoot = xmlDocGetRootElement(xmlPtr);
		if (!xmlStrcmp(ptrRoot->name,BAD_CAST"rob"))
		{
			// get all the children
			ptrCur = ptrRoot->xmlChildrenNode;
			//0 parse [common] node
			ParseComponentByNodeName(ptrCur,BAD_CAST"common",this->GroupInfo);
			
			//1 parse [userlist] node
			ptrCur = ptrCur->next;
			ParseComponentByNodeName(ptrCur,BAD_CAST"userlist",this->UserList);
			
			//1 parse [log] node
			ptrCur = ptrCur->next;
			ParseComponentByNodeName(ptrCur,BAD_CAST"log",this->Log_Info);

			// enter [interface] node,and locate the first node[common_interface]
			ptrCur = ptrCur->next;
			ptrCur = ptrCur->xmlChildrenNode;

			//2 parse [common_interface] node
			ParseComponentByNodeName(ptrCur,BAD_CAST"common_interface",this->Common_Interf);

			//3 parse [ics_oper] node
			ptrCur = ptrCur->next;
			ParseComponentByNodeName(ptrCur,BAD_CAST"ics_oper",this->Ics_Oper);

			//4 parse [ics_valid] node
			ptrCur = ptrCur->next;
			ParseComponentByNodeName(ptrCur,BAD_CAST"ics_valid",this->Ics_Valid);

			
			

			ConfLOG->WriteLog("[INFO]>>parse xml success,END!\n");
			WriteLogsRUN(TLOG_TYPE_ROBCONF, "", "",  TLOG_LEVEL_CONF + TLOG_LEVEL_INFO, __FUNCTION__, "[INFO]>>parse xml success,END!\n" );
		}else
		{
			ConfLOG->WriteLog("[ERROR]>>parse error,root name is wrong! Please check it!\n");
			WriteLogsRUN(TLOG_TYPE_ROBCONF, "", "",  TLOG_LEVEL_CONF + TLOG_LEVEL_ERROR, __FUNCTION__, "[ERROR]>>parse error,root name is wrong! Please check it!\n" );
		}
	}else
	{
		ConfLOG->WriteLog("[ERROR]>>Load %s fail! Please check it!\n",CONFPATH.c_str());
		WriteLogsRUN(TLOG_TYPE_ROBCONF, "", "",  TLOG_LEVEL_CONF + TLOG_LEVEL_ERROR, __FUNCTION__, "[ERROR]>>Load %s fail! Please check it!\n",CONFPATH.c_str() );
	}
	return 0;
}
/*******************************************************************
Description:	解析如下的结构的xml树形结构
				<common>
					<add key="group_id" value="225" desc="业务ID"/>
					<add key="group_name" value="c9" desc=""/>
				</common>

Params:			ptrCur :传入xml树形结构的根节点
				inputName: 传入节点的名字
				theResult:	解析所有根节点下的所有子节点key->value集合，输出
				
return:			正确与否
@exception		none
*/
int CRobConf::ParseComponentByNodeName(xmlNodePtr ptrCur,xmlChar* inputName,map< string, string >& theResult)
{
	ConfLOG->WriteLog("--------[INFO]>> begin to parse node[%s]---------\n",(char*)inputName);
	WriteLogsRUN(TLOG_TYPE_ROBCONF, "", "",  TLOG_LEVEL_CONF + TLOG_LEVEL_INFO, __FUNCTION__, "--------[INFO]>> begin to parse node[%s]---------\n",(char*)inputName );

	xmlNodePtr ptrNode;
	int i = 0;

	//std::cout << ptrCur->name << endl;
	if (!xmlStrcmp(ptrCur->name,inputName))
	{
		ptrNode = ptrCur->xmlChildrenNode;//开始add节点遍历
		if (!xmlStrcmp(ptrNode->name,BAD_CAST"add"))
		{
			xmlAttrPtr ptrAttr;
			while (ptrNode)
			{
				ptrAttr = ptrNode->properties;
				string strKey;
				string strValue;
				while(ptrAttr)
				{
					//	cout << "ptrAttr->name: " << ptrAttr->name << endl;
					if (!xmlStrcmp(ptrAttr->name,BAD_CAST"key"))
					{
						xmlChar* ucKey = xmlGetProp(ptrNode,BAD_CAST"key");
						strKey = string((char*)ucKey);
						xmlFree(ucKey);
						ucKey = NULL;
					}else if (!xmlStrcmp(ptrAttr->name,BAD_CAST"value"))
					{
						xmlChar* ucValue = xmlGetProp(ptrNode,BAD_CAST"value");
						strValue = string((char*)ucValue);
						xmlFree(ucValue);
						ucValue = NULL;
					}
					ptrAttr = ptrAttr->next;				
				}
				ConfLOG->WriteLog("[%d][key: %s=%s]\n",i,strKey.c_str(),strValue.c_str());
				WriteLogsRUN(TLOG_TYPE_ROBCONF, "", "",  TLOG_LEVEL_CONF + TLOG_LEVEL_INFO, __FUNCTION__, "[%d][key: %s=%s]\n", i, strKey.c_str(), strValue.c_str() );
				theResult[strKey] = strValue;
				ptrNode = ptrNode->next;
				i++;
			}
		}else
		{
			ConfLOG->WriteLog("[ERROR]:Parse error,node name[%s] is wrong,please check it!\n",(char*)ptrNode->name);
			WriteLogsRUN(TLOG_TYPE_ROBCONF, "", "",  TLOG_LEVEL_CONF + TLOG_LEVEL_ERROR, __FUNCTION__, "[ERROR]:Parse error,node name[%s] is wrong,please check it!\n", (char*)ptrNode->name );
			return -1;
		}
	}else
	{
		ConfLOG->WriteLog("[ERROR]:Parse error,node name[%s] is wrong,please check it!\n",(char*)ptrCur->name);
		WriteLogsRUN(TLOG_TYPE_ROBCONF, "", "",  TLOG_LEVEL_CONF + TLOG_LEVEL_ERROR, __FUNCTION__, "[ERROR]:Parse error,node name[%s] is wrong,please check it!\n", (char*)ptrCur->name );
		return -1;
	}
	ConfLOG->WriteLog("[PARSE RESULT]>> Node[%s]Children=[%d] \n",(char*)inputName,theResult.size());
	WriteLogsRUN(TLOG_TYPE_ROBCONF, "", "",  TLOG_LEVEL_CONF + TLOG_LEVEL_INFO, __FUNCTION__, "[PARSE RESULT]>> Node[%s]Children=[%d] \n", (char*)inputName, theResult.size() );

	return 0;
}

std::map< std::string, std::string > CRobConf::GetCommonInterface() const
{
	return this->Common_Interf;
}

std::map< std::string, std::string > CRobConf::GetIcsValid() const
{
	return this->Ics_Valid;
}

std::map< std::string, std::string > CRobConf::GetGroupInfo() const
{
	return this->GroupInfo;
}

std::map< std::string, std::string > CRobConf::GetUserList() const
{
	return this->UserList;
}

std::map< std::string, std::string > CRobConf::GetLogInfo() const
{
	return this->Log_Info;
}

std::map< std::string, std::string > CRobConf::GetAuthority() const
{
	return this->Authority;
}

std::map< std::string, std::string > CRobConf::GetIcsOper() const
{
	return this->Ics_Oper;
}