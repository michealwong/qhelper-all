/**
@file glog.h

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

#ifndef __GLOG_H__
#define	__GLOG_H__

// SYSTEM INCLUDES
#include <string>
#include <vector>
#include <map>
// STANDERD INCLUDES
// APPLICATION INCLUDES
#include "conf.h"
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
@class GLog
@brief 
@details 
*/
class GLog
{
public:

	GLog(){};
	~GLog(){};

	/**
	Description:	�
	@param	[in]	world
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	rolelevel
	@param	[in]	lastlogintime
	@param	[in]	createTime
	@param	[in]	roberedtime
	@param	[in]	icsid
	@return			int
	@exception		none
	*/
	int SaveIcsInfo(const string& world,
		const string& uin,
		const string& roleid,
		const string& rolelevel,
		const string& lastlogintime,
		const string& createTime,
		const string& roberedtime,
		const string& icsid);

	/**
	Description:	����ICS������ȡ���Ϣ
	Ĭ����ȡδ�������Ǿ������ݺϷ������ĵ�����Ϣ
	@param	[in]	icsid		ICS����	
	@param	[in]	result		���ؽ��
	@param	[in]	hand_res	����״̬��0��ʾδ����
	@param	[in]	anaylse_res	����״̬��6��ʾ�����ݺϷ��Է��������Զ���������
	@return			int
	@exception		none
	*/
	int GetIcsInfoByID(const string& icsid, vector< map<string,string> >& result,const string& hand_res="0", const string& anaylse_res="6");

	int GetIcsInfo(vector< map<string,string> >& result);

	/**
	Description:	������Ʒ��ˮ�������״̬
	@param	[in]	spoilid		�����¼ID
	@param	[in]	datetime	��Ʒ׷�ٵ�ʱ���
	@param	[in]	state		��Ʒ׷�ٽ��״̬
	@return			int
	@exception		none
	*/
	int SaveSpoilState(const string& spoilid, const string& datetime, const string& state="1");

	int UpdateIcsState(const string& incsid, const string& state="1");

	int GetRobSpoil(ics_info& info, std::vector< std::map<std::string, std::string> >& result);

	int SaveTracedSpoil(const string& world, spoil_info& info, const string& flag="0");

	int SaveSpoil(ics_info& ics, spoil_info& spoil);

	void WriteSpoilFromFlow(map<string,string>& in_data, spoil_info& out_data);




	int GetLog(const string& world, const string& sql, std::vector< std::map<std::string, std::string> >& result);

	/**
	Description:	�õ���ɫ�ǳ���־
	@param	[in]	world
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	begintime
	@param	[in]	endtime
	@param	[in]	std::map<std::string
	@param	[in]	result
	@return			int
	@exception		none
	*/
	int GetLogoutLog(const string& world,\
		const string& uin, \
		const string& roleid, \
		const string& begintime, \
		const string& endtime, \
		std::vector< std::map<std::string, std::string> >& result);

	int GetFlowLog(const string& world, spoil_info& info, std::vector< std::map<std::string, std::string> >& result);

	int GetSpoilLog(const string& world, const string& sql, vector< map<string,string> >&result);

protected:
	
private:

}; //end GLog


#endif	//__GLOG_H__
