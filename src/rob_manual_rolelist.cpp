/**
@file rob_core_anaylse.cpp

@brief 

	---------------------------------------------------------
	盗号自助分析功能(IP异常分析、赃物分析和流水分析)
	
	分析的单据必须是单据合法的；是盗号处理过程中，删除赠送物品的前提
	盗号自助功能输入参数： ICS单号
	处理过程如下，
	1) 获取要分析的单据；
	2) 等级是否符合; 
	3) 时间控制判断;
	---------------------------------------------------------

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		darrenqiu
@version	1.0
@date		2010/10/29

history:
<PRE>
History ID	:	1
Author    	:	asherzhou
DateTime	:	2011/05/01
Description :	Create
</PRE>
*/
#include <iostream>
#include "log.h"
#include "msg.h"
#include "glog.h"
#include "rob_anlys_ip.h"
#include "comm_datetime.h"
#include "comm_strings.h"
#include "conf.h"

#define GETROLELISTLOG "/usr/local/games/sas/logs/qqhx/ManualRobGetRoleList.log"

int main(int argc, char** argv)
{
	return 0;

}
