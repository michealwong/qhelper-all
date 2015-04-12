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


#include <string>
#include <vector>
#include <map>
#include <iostream>



#include "log.h"
#include "conf.h"

#define GETROLENAME 584



using namespace std;

/** 
@class GLog
@brief 
@details 
*/
class GLog
{
public:
	GLog();
	~GLog();
	
	/* add by asherzhou
	*	����GetLog,��Ӧ��SAP��ܵĲ�ѯ��������д��std::vector
	*	��Ҫ�����þ��ǵ���SAP�Ľӿڲ�
		modified by v_zhtang,2012-9-27,����tlogƽ̨
	*/
	int GetLog(
		const ics_log_header& header,
		const int id,
		std::map<string,string>& theParam,
		std::vector< std::map<std::string,std::string> >& result);
	 		
	 
	/* add by asherzhou
	*	GetLogicLog,��Ӧ��SAP��ܵĲ�ѯ��������д��std::vector
	*	��Ҫ�����þ��ǵ���SAP���߼���
	*   ������Ҫ������ʲô��������鿴rob.conf��ȷ������
		modified by v_zhtang,2012-9-27,����tlogƽ̨
	*/
	int GetFunction(
		const ics_log_header& header,//tlog header
		std::map<string,string>& theParamIn,
		const char* functionName,
		std::vector< map<string,string> >& result);

	/*
	*	added by v_zhtang
	*  �õ���������������
	*/
	std::string GetReachableEndPoint();

protected:

private:
	//������־
	CLog*  TraceLOG;
	std::string	MAKEFACELOG;

	//
	std::map< std::string, std::string > mapHosts;
}; 


#endif	//__GLOG_H__
