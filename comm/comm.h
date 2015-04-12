/**
@file comm.h

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

#ifndef __COMM_H__
#define	__COMM_H__

#include <string>
#include <vector>
#include <map>
#include "msg.h"
#include "comm_strings.h"
/**
	Description:	辅助处理函数conf参数的Params变成Map
	@param	[string]	params		赃物记录ID
	@return			map<string,string>
	@exception		none
	*/
extern	map<string,string>  ConvertParamsToMap(string& params);
/**
Description:	加载tab文件，以ID对应Name的形式
@param	[in]	filename
@param	[in]	std::string
@param	[in]	result
@return			extern void
@exception		none
*/
extern void LoadTabToIDvsName(const std::string& filename, std::map< std::string, std::string >& result);

//extern int LoadTabToMap(const std::string &filename, std::map<std::string, std::string> &result);


/**
Description:	加载tab文件，以name对id的形式
@param	[in]	filename
@param	[in]	std::string
@param	[in]	result
@return			extern void
@exception		none
*/
extern void LoadTabToNamevsID(const std::string& filename, std::map< std::string, std::string >& result);

extern bool CheckAuth(std::vector<std::string>& list,const std::string& user);

extern bool isNonExist(const std::string &sRoleId, const std::string &sItemGuid, std::map< std::string, std::vector<ExistedItems> >& UserItemInfo);

//extern int split(const char *src, std::vector<std::string> &des, char sh = '\0');




#endif	//__COMM_H__
