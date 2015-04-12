/**
@file rob_anlys_ip.h

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

#ifndef __ROB_ANLYS_IP_H__
#define	__ROB_ANLYS_IP_H__


#include <string>
#include <map>
#include <vector>

#include "glog.h"
#include "log.h"
#include "msg.h"
#include "conf.h"

using namespace std;


/** 
@class RobAnlysIP
@brief 
@details 
*/
class RobAnlysIP
{
public:
	/**
	Description:	Default constructor
	@exception		none
	*/
	RobAnlysIP();

	/**
	Description:	Destructor
	*/
	~RobAnlysIP();

	
	/**
	Description:	��¼��־���ڴ�ģ��
	*/
	Rob_SLOT LogInOutSlotList;

	/**
	Description:	������������еĵ�½��־������ȫ�����أ������ֶ�
	@param	[in]	t_begin
	@param	[in]	t_end
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	world
	@param	[in]	map<string
	@param	[in]	data
	@return			void
	@exception		none
	*/
	int getRobLogInOutLog(Rob_Ics_Complaint& Ics_Loginout,
		vector< Rob_SLOT >& rob_data);

	/**
	Description:	������Ʒ��ˮ��־
	@param	[in]	t_begin
	@param	[in]	t_end
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	world
	@param	[in]	map<string
	@param	[in]	data
	@return			void
	@exception		none
	*/

	int getItemFlowLog(const std::string &t_begin,\
		const std::string &t_end, \
		const std::string &uin, \
		const std::string &roleid, \
		const std::string &world, \
		std::vector<map<string,string> > &rob_item_data);



		/**
	Description:	����������ˮ��־
	@param	[in]	t_begin
	@param	[in]	t_end
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	world
	@param	[in]	map<string
	@param	[in]	data
	@return			void
	@exception		none
	*/
	int getPetFlowLog(const std::string &t_begin, \
		const std::string &t_end, \
		const std::string &uin, \
		const std::string &roleid, \
		const std::string &world, \
		std::vector<map<string,string> > &rob_item_data);

		/**
	Description:	����װ����ˮ��־
	@param	[in]	t_begin
	@param	[in]	t_end
	@param	[in]	uin
	@param	[in]	roleid
	@param	[in]	world
	@param	[in]	map<string
	@param	[in]	data
	@return			void
	@exception		none
	*/
	int getArmFlowLog(const std::string &t_begin, \
		const std::string &t_end, \
		const std::string &uin, \
		const std::string &roleid, \
		const std::string &world, \
		std::vector<map<string,string> > &rob_item_data);


protected:
	
private:
	GLog		api_log;	//< ��ѯ��Ϸ��־�ӿڶ���
	CLog*		LogInOutLOG;   //< ������־
	std::string sLOGINOUTLOG;
	/**
	Description:	��������Ϸ�����֤
	@param	[in]	begin
	@param	[in]	end
	@return			bool
	@exception		none
	*/
	bool checkValid(time_t begin, time_t end);

	/*
	�жϵ���ʱ���������ʱ������12Сʱ����Ϊ����������true�����򷵻�false
	*/
	bool checkRobedTime(time_t t_lastlogin, time_t t_robed, string logouttime);

	/**
	Description:	��Ϸ��½��־�����߼�
	@param	[in]	string
	@param	[in]	in_data
	@param	[in]	string
	@param	[in]	err_area
	@return			void
	@exception		none
	*/
	int anaylseData(Rob_Ics_Complaint& Ics_Loginout, vector< map< string,string > >& LogInOutData, vector< Rob_SLOT >& PutOutData);

	/**
	Description:	�жϸ�����־�Ƿ��з�����
	@param	[in]	in_data
	@return			bool 1:�з�����   0������������
	@exception		none
	*/
	bool filterChangeSvrLogin(std::vector< Rob_SLOT > &rob_data);
}; //end RobAnlysIP



#endif	//__ROB_ANLYS_IP_H__
