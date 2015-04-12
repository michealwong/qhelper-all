/**
@file iplib.cpp

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		GunLi
@version	1.0
@date		2010/10/12

history:
<PRE>
History ID	:	1
Author    	:	GunLi
DateTime	:	2010/10/12
Description :	Create
</PRE>
*/

#include "iplib.h"
#include "comm_iptools.h"
#include "comm_strings.h"
#include "conf.h"
#include "comm_datetime.h"

std::map< std::string, std::string > IPLib::m_iplib;



IPLib::IPLib(){
	sIpLOG="./logs/"+GetCurDateDay()+"GIPInterfaceLog.log";
	IpLOG = new CLog((const char*)sIpLOG.c_str());
	IpLOG->LogOn();
	udp.Open();
	//vip信息初始化
	vip_ip=CRobConf::getConf()->GetCommonInterface()["vip_ip"];
	vip_port=CRobConf::getConf()->GetCommonInterface()["vip_port"];
	vip_cmd=CRobConf::getConf()->GetCommonInterface()["vip_cmd"];
}
IPLib::~IPLib(){
	if (IpLOG)
	{
		delete IpLOG;
	}
	udp.Close();
}

int IPLib::getVipByUin(const string& uin){
	//发送VIP查询请求
	map<string,string> vipInfo;
	string s_cmd="cmd="+vip_cmd+"&user=safe&uin="+uin+"\n";

	if(false==sendMsg(vip_ip,StrToInt(vip_port),s_cmd))
	{
		IpLOG->WriteLog("[ERROR]: PLib::getVipByUin->sendMsg->return->[False]\n");
		return -1;
	}
	if(false==revMsg(vipInfo))
	{
		IpLOG->WriteLog("[ERROR]: PLib::getVipByUin->revMsg->return->[False]\n");
		return -1;
	}
	return vipInfo["level"]!=""?StrToInt(vipInfo["level"]):-1;
}


std::string IPLib::getAreaByIP(const std::string &ip)
{
	string sIP	= ip;
	//如果IP库不存在，要先进行查找
	if(!(m_iplib.find(sIP) != m_iplib.end()))
	{		
		static TAreaInfo area;
		ipToArea(sIP, area);
		m_iplib[sIP] = area.strProvince + " " + area.strCity;
	}

	return m_iplib[sIP];
}

bool IPLib::sendMsg( string m_sHost,int m_iPort, string scmd)
{
	if(udp.SendTo((void*)scmd.c_str(),(size_t)scmd.length(),INetAddr(m_sHost,m_iPort)))
	{
		IpLOG->WriteLog("[ERROR]:sendMsg:%s&ip=%s&ip_port=%d|成功\n",scmd.c_str(),m_sHost.c_str(),m_iPort);
		return true;
	}
	else
	{
		IpLOG->WriteLog("[ERROR]:sendMsg:%s&ip=%s&ip_port=%d|失败\n",scmd.c_str(),m_sHost.c_str(),m_iPort);
		return false;
	}
}



bool IPLib::revMsg( map<string,string> &opData )
{
	char sBuffer[5024] = {0};	
	INetAddr stRemoteAddr;
	//stRemoteAddr = INetAddr(vip_ip,StrToInt(vip_port));
	if(udp.RecvFrom((void*)sBuffer,(size_t)5024,stRemoteAddr,10))
	{
		if (strlen(sBuffer) > 0)
		{
			IpLOG->WriteLog("[INFO]: IPLib::revMsg->returnData: [%s]\n",sBuffer);
			string flag="&=";
			string sStr = string(sBuffer);
			SplitToMap(sStr,opData,flag,(unsigned int)2);			
		}
		
		return true;
	}
	else//超时退出
	{
		IpLOG->WriteLog("[ERROR]: IPLib::revMsg->returnData: [TIME OUT]\n");
		return false;
	}
}


