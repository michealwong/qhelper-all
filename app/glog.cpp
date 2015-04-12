/**
@file glog.cpp

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		Darrenqiu
@version	1.0
@date		2010/10/12

history:
<PRE>
History ID	:	1
Author    	:	Darrenqiu
DateTime	:	2010/10/12
Description :	Create
</PRE>
*/

#ifndef __GLOG_CPP__
#define	__GLOG_CPP__

// SYSTEM INCLUDES
#include <iostream>
// STANDERD INCLUDES
// APPLICATION INCLUDES
#include "msg.h"
#include "comm.h"
#include "glog.h"
#include "conf.h"
#include "DataOper.h"
// USING NAMESPACES
// DEFINES
// MACROS
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STRUCTS
// TYPEDEFS
// FORWARD DECLARATIONS

int GLog::GetLog(const std::string &world, const std::string& sql, std::vector<std::map<std::string,std::string> > &result)
{
	/*
	string sSql		= sql;
	DBNode db_node	= CRobConf::getConf()->db_node[world];
	string s_host	= db_node.m_host;
	string s_user	= db_node.m_user;
	string s_pwd	= db_node.m_passwd;
	string s_db		= db_node.m_dbname;
	DispDBNode(db_node);
	cout << "GetLog: " << sSql << endl;
	if (DbOper(s_host,s_user,s_pwd,s_db,sSql,result))
	{
		return 0;
	}
	else
	{
		return 1;
	}*/

	//172.27.129.173-usap_auto_rob-pauto#20101019 dbAutoRob

	string sSql		= sql;

	string s_host	= "172.27.129.173";
	string s_user	= "sap_auto_rob";
	string s_pwd	= "auto#20101019";
	string s_db		= "dbAutoRob";
	//DispDBNode(db_node);
	cout << "GetLog: " << sSql << endl;
	if (DbOper(s_host,s_user,s_pwd,s_db,sSql,result))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int GLog::GetLogoutLog(const string& world, const string& uin, const string& roleid, const string& begintime, const string& endtime, std::vector< std::map<std::string, std::string> >& result)
{
	string db_key	= "log_"+world;
	string sSql		= "select convert(vRoleName using binary) as vRoleName,iRoleId as RoleId,dtLoginTime as LoginTime,dtEventTime as LogoutTime,vClientIp as IP,iOnlineTime as OnLineTime from RoleLogout where iUin=" + uin + " and iRoleId="+ roleid +" and dtEventTime between '" + begintime + "' and '" + endtime + "' order by dtEventTime asc";
	cout << "GetLogoutLog" << sSql << endl;
	DispDBNode(CRobConf::getConf()->db_node[db_key]);
	bool iRes = DbOper(CRobConf::getConf()->db_node[db_key].m_host, 
		CRobConf::getConf()->db_node[db_key].m_user, 
		CRobConf::getConf()->db_node[db_key].m_passwd, 
		CRobConf::getConf()->db_node[db_key].m_dbname, 
		sSql, 
		result);
	
	if ( !iRes || result.size()==0 )
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

int GLog::GetFlowLog(const string& world, spoil_info &info, std::vector<std::map<std::string,std::string> > &result)
{
	string s_dbkey	= "log_" + world;
	string s_table	= info.RobType;
 
	//必须按时间降序查询
	string sSql		= "select " + CRobConf::getConf()->SpoilAnaylse[s_table].sCols 
		+ " from " + CRobConf::getConf()->SpoilAnaylse[s_table].sTable 
		+ " where " + CRobConf::getConf()->SpoilAnaylse[s_table].sColTime 
		+ ">='" + info.EventTime + "' and " + CRobConf::getConf()->SpoilAnaylse[s_table].sColTime 
		+ "<=now() and " + CRobConf::getConf()->SpoilAnaylse[s_table].sColGid 
		+ "=" + info.ItemGuid + "  order by " + CRobConf::getConf()->SpoilAnaylse[s_table].sColTime 
		+ " desc";
	cout << "get flow log -----------" << endl;
	cout << sSql << endl;
	cout << s_dbkey << endl;
	DispDBNode(CRobConf::getConf()->db_node[s_dbkey]);
	
	return GetLog(s_dbkey, sSql, result);	
}

int GLog::GetSpoilLog(const std::string &world, const std::string &sql, std::vector<map<string,string> > &result)
{
	string s_sql	= sql;
	string s_world	= "log_" + world;
	return GetLog(s_world, s_sql, result);
}



int GLog::GetIcsInfoByID(const string& icsid, vector< map<string,string> >& result, const string& hand_res, const string& anaylse_res)
{
	string s_worldflag	= CRobConf::getConf()->sRobDB;
	string sSql = "select * from tbICSInfo where iHandRes=" + hand_res + " and iAnaylseRes=" + anaylse_res + " and iID=" + icsid;
	return GetLog(s_worldflag, sSql, result);
}

int GLog::GetIcsInfo(vector< map<string,string> >& result)
{
	string s_worldflag	= "auto_rob";//CRobConf::getConf()->sRobDB;
	string sSql = "select * from tbICSInfo where iAnaylseRes=0";
	return GetLog(s_worldflag, sSql, result);
	//return 0;
}

int GLog::GetRobSpoil(ics_info &info, std::vector<std :: map<std::string,std :: string> > &result)
{
	string s_worldflag	= CRobConf::getConf()->sRobDB;
	string sSql = "select * from tbSpoil where iICSId='"+info.ICSID+"' and iUin="+info.UserID+" and (iTraceRes=0 or iTraceRes=3)";
	return GetLog(s_worldflag, sSql, result);
}

int GLog::SaveTracedSpoil(const string& world, spoil_info &info, const string& flag)
{
	vector< map<string,string> > vResult;
	string s_worldflag	= CRobConf::getConf()->sRobDB;

	string sSql = "delete from tbTracedSpoil where iSpoilId=" + info.ID + " and iItemGuid=" + info.ItemGuid;
	int ires	= GetLog(s_worldflag, sSql, vResult);
	//cout << "ires: " << ires << endl;
	//if (0 != ires)
	//{
	//	return 1;
	//}

	sSql = "insert into tbTracedSpoil(iSpoilId,\
		   iOwner,\
		   iOwnerRoleId,\
		   iWorldId,\
		   dtEventTime,\
		   iItemGuid,\
		   iItemId,\
		   iItemType,\
		   iItemNum,\
		   iEventType,\
		   iOpType) values(" + 
		   info.ID + "," +
		   info.Rober + "," +
		   info.RobRoleID + "," +
		   world + ",'" +
		   info.EventTime + "'," +
		   info.ItemGuid + "," +
		   info.ItemId + "," +
		   info.ItemType + "," +
		   info.ItemCou + "," +
		   info.RobType + "," +
		   flag + ")";

	return GetLog(s_worldflag, sSql, vResult);
}

int GLog::SaveSpoil(ics_info &ics, spoil_info &spoil)
{
	string s_worldflag	= CRobConf::getConf()->sRobDB;
	string sSql = "select count(*) as cou from tbSpoil where iICSId='"+ics.ICSID+"' and iUin="+spoil.Rober+" and iItemGuid="+spoil.ItemGuid;
	cout << "SaveSpoil sql: " << sSql << endl;
	vector< map<string,string> > vTemp;
	GetLog(s_worldflag, sSql, vTemp);
	cout << "save spoil size:" << vTemp.size() << endl;
	if(vTemp.size()>0 && vTemp[0]["cou"]=="0")
	{
		sSql = "insert into tbSpoil(iICSId,iUin,iRoleId,iWorldId,dtEventTime,iItemGuid,iItemId,iItemType,iItemNum,vOutFlowType) values('"+
			ics.ICSID +"',"+
			spoil.Rober +","+
			spoil.RobRoleID +","+
			ics.WorldID+",'"+
			spoil.EventTime+"',"+
			spoil.ItemGuid+","+
			spoil.ItemId+","+
			spoil.ItemType+","+
			spoil.ItemCou+",'"+
			spoil.RobType+"')";

		vTemp.clear();
		GetLog(s_worldflag, sSql, vTemp);
		return 0;
	}
	else if (vTemp.size()>0 && vTemp[0]["cou"]=="1")
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void GLog::WriteSpoilFromFlow(map<string,string>& in_data, spoil_info& out_data)
{
	/*
	//dtEventTime,iUin,iRoleId,iArmGID iItemGuid,iResID iItemId,
	iArmNum iItemNum,iResType iItemType,iArmColor as iItemQuality,
	'ArmFlow' as sLogType,iEventId,iAction,iGetOrLost	
	*/
	out_data.ID			= in_data["iEventId"];		// 事件ID
	out_data.Rober		= in_data["iUin"];
	out_data.RobRoleID	= in_data["iRoleId"];
	out_data.EventTime	= in_data["dtEventTime"];
	out_data.ItemGuid	= in_data["iItemGuid"];
	out_data.ItemId		= in_data["iItemId"];
	out_data.ItemType	= in_data["iItemType"];
	out_data.ItemCou	= in_data["iItemNum"];
	out_data.ItemAttr	= in_data["iItemQuality"];
	out_data.RobType	= in_data["iAction"];		// 动作
	out_data.Status		= in_data["iGetOrLost"];	// 流入流出
	out_data.Result		= "";
	out_data.TracedTime	= in_data["dtEventTime"];
}

int GLog::SaveSpoilState(const std::string &spoilid, const std::string &datetime, const std::string &state)
{
	string s_worldflag	= CRobConf::getConf()->sRobDB;
	string sSql = "update tbSpoil set iTraceRes=" + state + ",dtTracedTime='" + datetime + "' where iID=" + spoilid;
	vector< map<string,string> > vTemp;
	return GetLog(s_worldflag, sSql, vTemp);
}

int GLog::SaveIcsInfo(const std::string &world, const std::string &uin, const std::string &roleid, const std::string &rolelevel, const std::string &lastlogintime, const std::string &createTime, const std::string &roberedtime, const std::string &icsid)
{
	string s_worldflag	= CRobConf::getConf()->sRobDB;
	string sSql = "insert into tbICSInfo(iID,\
				  iUin,\
				  iWorld,\
				  dtBookTime,\
				  dtLastLogin,\
				  dtRobedTime,\
				  iRoleId,\
				  iRoleLevel) values('" 
				  + icsid + "','"
				  + uin + "','"
				  + world + "','"
				  + createTime + "','"
				  + lastlogintime + "','"
				  + roberedtime + "','"
				  + roleid + "','"
				  + rolelevel +"')";
	vector< map<string,string> > vTemp;
	return GetLog(s_worldflag, sSql, vTemp);
}

int GLog::UpdateIcsState(const std::string &incsid, const std::string &state)
{
	string s_worldflag	= CRobConf::getConf()->sRobDB;
	string sSql = "select count(*) as cou from tbSpoil where iICSId='" + incsid + "'";
	vector< map<string,string> > vResult;
	GetLog(s_worldflag, sSql, vResult);

	sSql = "update tbICSInfo set iHandRes=" + state + ",iRobTotle=" + vResult[0]["cou"] + " where iID='" + incsid + "'";
	vResult.clear();
	return GetLog(s_worldflag, sSql, vResult);
}

int GLog::UpdateIcsAnlse(const string& icsid, const string& state/* = */)
{

}
#endif	//__GLOG_CPP__
