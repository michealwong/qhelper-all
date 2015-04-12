/**
@file iplib.h

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

#ifndef __IPLIB_H__
#define	__IPLIB_H__


#include <string>
#include <map>
#include "udp_dgram.h"
#include "log.h"
using namespace OssBase;
using namespace std;


/** 
@class IPLib
@brief 
@details 
*/
class IPLib
{
public:
	/**
	Description:	Default constructor
	@exception		none
	*/
	IPLib();

	/**
	Description:	Destructor
	*/
	~IPLib();

	/**
	Description:	根据IP查询地区
	@param	[in]	ip
	@return			std::string
	@exception		none
	*/
	static std::string getAreaByIP(const string& ip);

	/**
	Description:	根据玩家是否是VIP
	@param	[in]	vip
	@return			std::string
	@exception		none
	*/
	int getVipByUin(const string& uin);


protected:
	bool sendMsg(string m_sHost,int m_iPort,string scmd);
	bool revMsg(map<string,string> &opData);
	
private:
	string vip_ip;
	string vip_port;
	string vip_cmd;
	static std::map< std::string, std::string > m_iplib;
	UdpDgram		udp;
	CLog*  IpLOG;
	string sIpLOG;
}; //end IPLib


#endif	//__IPLIB_H__
