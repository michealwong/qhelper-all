/**
@file rule_flow.cpp

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		GunLi
@version	1.0
@date		2010/10/14

history:
<PRE>
History ID	:	1
Author    	:	GunLi
DateTime	:	2010/10/14
Description :	Create
</PRE>
*/

// SYSTEM INCLUDES
#include <iostream>
// STANDERD INCLUDES
// APPLICATION INCLUDES
#include "rule_flow.h"
// USING NAMESPACES
// DEFINES
// MACROS
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STRUCTS
// TYPEDEFS
// FORWARD DECLARATIONS

map<string,string> RuleFlow::mActionIn;
map<string,string> RuleFlow::mActionIn2;
map<string,string> RuleFlow::mActionOut;

RuleFlow::RuleFlow()
{
/*
0-拾取
1-销毁
2-存入银行
3-从银行取出
4-交易获得
5-交易失去
6-摆摊获得
7-摆摊失去
*/
	// 获取
	mActionIn["2"] = "2";			/*存入银行(2)*/
	mActionIn["3"] = "3";			/*银行取出(3)*/
	mActionIn["6"] = "6";			/*29是摆摊买*/
	mActionIn["0"] = "0";			/*拾取(0)*/

	// 获取
	mActionIn2["4"] = "4";			/*交易获得(4)*/	

	// 失去
	mActionOut["1"] = "1";			/*销毁(9)*/
	mActionOut["5"] = "5";			/*交易失去(5)*/
	mActionOut["7"] = "7";			/*摆摊失去(7)*/

	cout << "rule flow struct function" << endl;
	for (map<string,string>::iterator it=mActionIn2.begin(); it!=mActionIn2.end(); it++)
	{
		cout << it->second << endl;
	}
}

RuleFlow& RuleFlow::GetInstance()
{
	static RuleFlow _rule;
	return _rule;
}

int RuleFlow::checkEnd(vector<map<string,string> > &in_data)
{
	//string sAction0 = in_data[0]["iAction"];
	//string sAction1 = in_data[1]["iAction"];

	// 如果第一条记录即为获取，则返回索引0
	// 0 获取，1 失去
	if (in_data.size()<=0)
	{
		return -1;
	}
	else if (mActionIn.find(in_data[0]["iAction"]) != mActionIn.end())
	{
		return 0;
	}	
	else if (in_data.size() > 1
		&& mActionIn.find(in_data[1]["iAction"]) != mActionIn.end()		
		&& in_data[0]["dtEventTime"]==in_data[1]["dtEventTime"])
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int RuleFlow::checkHead(vector< map<string,string> >& in_data)
{
	cout << in_data.size() << endl;

	/*for (int i=1; in_data.size()-i>=0; i++)*/
	/*bug in_data.size()-i>=0 恒真*/
	for (int i=1; i<in_data.size(); i++)
	{
		//cout << in_data.size()-i << endl;
		string sAction = in_data[in_data.size()-i]["iAction"];		
		if (mActionIn2.find(sAction) != mActionIn2.end())
		{
			return in_data.size()-i;
		}
	}
	return -1;
}

int RuleFlow::checkFlow(vector< map<string,string> >& in_data)
{
	return 0;
}