/**
@file rule_flow.h

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		Darrenqiu
@version	1.0
@date		2010/10/14

history:
<PRE>
History ID	:	1
Author    	:	Darrenqiu
DateTime	:	2010/10/14
Description :	Create
</PRE>
*/

#ifndef __RULE_FLOW_H__
#define	__RULE_FLOW_H__

// SYSTEM INCLUDES
#include <vector>
#include <string>
#include <map>
// STANDERD INCLUDES
// APPLICATION INCLUDES
// USING NAMESPACES
using namespace std;
// DEFINES
// MACROS
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
// STRUCTS
// TYPEDEFS
// FORWARD DECLARATIONS

/** 
@class RuleFlow
@brief 
@details 
*/
class RuleFlow
{
public:
	/**
	Description:	Default constructor
	@exception		none
	*/
	RuleFlow();

	/**
	Description:	Destructor
	*/
	~RuleFlow(){};

	static RuleFlow& GetInstance();

	static int checkFlow(vector< map<string,string> >& in_data);

	static int checkEnd(vector< map<string,string> >& in_data);

	static int checkHead(vector< map<string,string> >& in_data);

protected:
	
private:
	static map<string,string> mActionIn;
	static map<string,string> mActionIn2;
	static map<string,string> mActionOut;

}; //end RuleFlow


#endif	//__RULE_FLOW_H__
