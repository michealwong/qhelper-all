/**
@file conf.h

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		Darrenqiu
@version	1.0
@date		2010/10/09

history:
<PRE>
History ID	:	1
Author    	:	Darrenqiu
DateTime	:	2010/10/09
Description :	Create
</PRE>
*/

#ifndef __CONF_H__
#define	__CONF_H__


#include <map>
#include <vector>
#include <string>

#include "log.h"
#include "libxml/parser.h"
#include "libxml/tree.h"


/** 
@class CRobConf
@brief 
@details 
*/
class CRobConf
{
public:
	static CRobConf* getConf();
	~CRobConf();
protected:
	
private:
	//私有构造
	CRobConf();
	//conf读取，static的意思，防止重复获取？
	static CRobConf* RobConf;
	std::string MAKECONFLOG;
	std::string CONFPATH;

	//xml文档指针
	xmlDocPtr xmlPtr;

	//解析函数
	int ParseXmlConfig(xmlDocPtr xmlPtr);
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
	static int ParseComponentByNodeName(xmlNodePtr ptrCur,xmlChar* inputName,std::map< std::string, std::string >& theResult);
private:
	//调试日志
	static CLog* ConfLOG;
	//读取的文档的params
	std::vector<std::string> params_table;
	
	//ICS的单据的信息和过滤配置
	std::map< std::string, std::string > Ics_Valid;
	
	//业务信息配置
	std::map< std::string, std::string > GroupInfo;
	
	//权限人白名单
	std::map< std::string, std::string > Authority;

	//ICS的单据的信息和过滤配置
	std::map< std::string, std::string > Ics_Oper;

	//共用接口信息配置
	std::map< std::string, std::string > Common_Interf;

	// 日志信息配置 @add by v_sjwang
	std::map< std::string, std::string > Log_Info;

	// 重复补送物品，发送预警邮件用户列表 @add by v_sjwang 2012/11/2 9:59:37
	std::map< std::string, std::string > UserList;
public:
	std::map< std::string, std::string > GetCommonInterface() const;
	std::map< std::string, std::string > GetIcsValid() const;
	std::map< std::string, std::string > GetGroupInfo() const;
	std::map< std::string, std::string > GetUserList() const;	// @add by v_sjwang 2012/11/2 9:59:37
	std::map< std::string, std::string > GetLogInfo() const;	// @add by v_sjwang
	std::map< std::string, std::string > GetAuthority() const;
	std::map< std::string, std::string > GetIcsOper() const;

}; //end CRobConf

#endif	//__CONF_H__

