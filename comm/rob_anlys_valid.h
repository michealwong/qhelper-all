/**
@file rob_anlys_valid.h

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		Darrenqiu
@version	1.0
@date		2010/10/22

history:
<PRE>
History ID	:	2
Author    	:	asherzhou
DateTime	:	2011/05/01
Description :	Create
</PRE>
*/

#ifndef __ROB_ANLYS_VALID_H__
#define	__ROB_ANLYS_VALID_H__


#include <iostream>
#include "glog.h"
#include "log.h"

#include "comm_value.h"
#include "conf.h"
#include "msg.h"
#include "iplib.h"
/** 
@class RobRuleValid

	-----------------------------------------
	���ݺϷ�����֤�ձ��Թ���
	1. �ȼ�С��role_level���Ϸ���
	2. ���߳���create_due���Ϸ���
	3. ����½ʱ��С�ڱ���ʱ�䲻�Ϸ���
	4. receive_doble�����ظ�����������
	5. ��ɫ���ⶳ����block_day���Ϸ���
	-----------------------------------------

@brief 
@details 
*/
class RobRuleValid
{
public:
	/**
	Description:	Default constructor
	@exception		none
	*/
	RobRuleValid();

	/**
	Description:	Destructor
	*/
	virtual ~RobRuleValid();



	/**
	Description:	��֤���ݵĺϷ���
	@param	[in]	info
	@return			int
	@exception		none
	*/
	virtual int DoICSCheckPro(Qhelper_Ics_Complaint& ics_info);

	/**
	Description:	��ҵĽ�ɫ������Ϣ����
	@param	[in]	info
	@return			int
	@exception		none
	*/
	virtual int DoICSSetRoleInfoPro(Qhelper_Ics_Complaint& ics_info);

	/**   ����idip�ӿڲ���vip��Ϣ
	* 		params:		ics_info
	* 		return:		int
	*/
	int ProCheckVIPInfo(Qhelper_Ics_Complaint& info);

	/**		��ѯlog�Ƿ���ת����¼
	*		params:		ics_info
	*		return:		int 
	*
	*/
	int ProCheckTransSvrInfo(Qhelper_Ics_Complaint& info);

	/**	����Master��ics��check���˺���, ������Ϣ��ѯ
	*   params:		ics_info
	* 	return:		int
	*/
	int ProCheckIsMaster(Qhelper_Ics_Complaint& ics_info);


	/**   receive_doble�����ظ����������� ��ͨ�û��ݶ�Ϊ180�죬VIPΪ90��
	* 		params:		ics_info
	* 		return:		int
	*/
	int ProCheckDobleQuest(Qhelper_Ics_Complaint& info);

	/**	����LEVEL��ics��check���˺���
	*   params:		ics_info
	* 	return:		int
	*/
	int ProCheckRoleLevel(Qhelper_Ics_Complaint& info);

	/************************************************************************/
	/********************************************************************* */
	/************************************************************************/

/**************************V1.01************************************/
	/**
	Description:	��ҵĽ�ɫ������Ϣ����
	@param	[in]	info
	@return			int
	@exception		none
	*/
	virtual int DoICSSetRoleInfoPro(Rob_Ics_Complaint& ics_info);

	/**
	Description:	��֤���ݵĺϷ���
	@param	[in]	info
	@return			int
	@exception		none
	*/
	virtual int DoICSCheckPro(Rob_Ics_Complaint& ics_info);

	
/**************************V1.00************************************/
	/**
	Description:	��֤���ݵĺϷ���
	@param	[in]	info
	@return			int
	@exception		none
	*/
	virtual int DoICSCheck(ics_info& info);


	/**
	Description:	����ҵ��Ĳ����Ƿ���˸߼�ֵ��Ʒ
	@param	[in]	info
	@return			in_size������ǰ����Ʒ������ out_size�����˺����Ʒ������ fliter_item_flag �Ƿ���и߼�ֵ��Ʒ���˵ı�־λ
	@exception		none
	*/
	virtual int DoGetItemsToPresent(spoil_info all_item_info[],spoil_info get_item_info[],const unsigned int in_size,unsigned int& out_size,int fliter_item_flag);

	/**
	Description:	�趨������Ʒ�Ƿ�ת�˹�����
	@param			[in]	info
	@				(a):    ��Ʒ�Ƿ����
	@return			int     �ӿ���ȷ���
	@exception		none
	*/
	virtual int DoSetItemsToPresent(spoil_info all_item_info[],const unsigned int in_size);
	

	
	CLog *ValidLOG;
	GLog valid_parse;


	



protected:
	/**	����LEVEL��ics��check���˺���
	*   params:		ics_info
	* 	return:		int
	*/
	int ProCheckRoleLevel(Rob_Ics_Complaint& info);
	/**	����BLOCK��ics��check���˺���
	*   params:		ics_info
	* 	return:		int
	*/
	int ProCheckBlockTime(Rob_Ics_Complaint& info);

	/**  ����ʱ�䳬������Ҫ��, ��ͨ�û��ݶ�Ϊ15�죬VIPΪ20��
	* 		params:		ics_info
	* 		return:		int
	*/
	int ProCheckRobedTime(Rob_Ics_Complaint& info);
	/**  ����ʱ�䳬������¼��ʱ��, �����Ϲ���
	* 		params:		ics_info
	* 		return:		int
	*/
	int ProCheckLastTime(Rob_Ics_Complaint& info);
	/**   receive_doble�����ظ����������� ��ͨ�û��ݶ�Ϊ180�죬VIPΪ90��
	* 		params:		ics_info
	* 		return:		int
	*/
	int ProCheckDobleQuest(Rob_Ics_Complaint& info);
	/**   ����idip�ӿڲ���vip��Ϣ
	* 		params:		ics_info
	* 		return:		int
	*/
	int ProCheckVIPInfo(Rob_Ics_Complaint& info);

	bool ProIsSendMail(Rob_Ics_Complaint& info);
private:
	string MAKEVALIDLOG;
	IPLib ipInterface;
	std::map<string,string> mapMergeArea; 
	std::map<string,string> mapMergeTime; 
	int  iRet;
	
}; //end RobIcsValid


#endif	//__ROB_ANLYS_VALID_H__
