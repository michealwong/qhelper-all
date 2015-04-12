/**
@file comm.cpp

@brief 

@details
Copyright (c) 2010 Tencent. All rights reserved.

@author		GunLi
@version	1.0
@date		2010/10/09

history:
<PRE>
History ID	:	1
Author    	:	GunLi
DateTime	:	2010/10/09
Description :	Create
</PRE>
*/

#include <fstream>
#include <sstream>
#include <iostream>

#include "comm.h"

using namespace std;
/**
	Description:	辅助处理函数conf参数的Params变成Map
	@param	[string]	params		赃物记录ID
	@return			map<string,string>
	@exception		none
	*/
map<string,string> ConvertParamsToMap(string& params)
{
 vector<string> pars;
 
 map<string,string> paramsMap;
 SplitByStr(params, "&", pars);
 for (unsigned int i=0; i<pars.size(); ++i)
 {
	 vector<string> keyValue;
  	 SplitByStr(pars[i], "|", keyValue);
 	 paramsMap[keyValue[0]]=keyValue[1];
 }
 return paramsMap;
}

void LoadTabToIDvsName(const std::string& filename, std::map< std::string, std::string >& result)
{
	ifstream * tabStream;

	tabStream = new ifstream(filename.c_str());
	string id;

	if(*tabStream)
	{
		while( *tabStream >> id )
			*tabStream >> result[id];
	}

	delete  tabStream;
}

/*int LoadTabToMap(const std::string &filename, std::map<std::string, std::string> &result)
{
	if ( 0 == filename.size() )
	{
		return -1;
	}
	FILE *fp = fopen(filename.c_str(), "r");
	if ( NULL == fp )
	{
		return -2;
	}
	if ( 0 != fseek(fp, 0, SEEK_SET) )
	{
		return -3;
	}
	char buf[128] = {0};
	vector<string> tmpVec;
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		if ( NULL == fgets(buf, 128, fp) )
		{
			// 判断EOF 或 。。break;
			//CLogicManager::PrintLog(QUERIERLOGPATH, "读取文件[%s]结束!", filename.c_str());
			break;
		}
		char *p = buf;
		while ( *p != '\0' )
		{
			if ( *p == '\r' || *p == '\n' )
			{
				*p = '\0';
				break;
			}
			p++;
		}
		split(buf, tmpVec, '\t');
		if ( tmpVec.size() >= 2 )
		{
			result[tmpVec[0]] = tmpVec[1];
		}
	}
	//cout<<"读取文件结果:filename["<<filename<<"],size["<<result.size()<<"]"<<endl;
	return 0;
}*/

void LoadTabToNamevsID(const std::string& filename, std::map< std::string, std::string >& result)
{
	result.clear();
	ifstream  inStream(filename.c_str());
	string tmpStr;
	std::map< std::string, std::string >  mData;
	while(getline(inStream,tmpStr))
	{
		istringstream tmpStream(tmpStr);
		tmpStr="";
		string valueTmp = "";
		std::map< std::string, std::string >  mData;
		while( tmpStream >> valueTmp )
		{
			mData.clear();
			mData["gameWorldId"] = valueTmp;

			valueTmp = "";
			tmpStream >> valueTmp;
			mData["worldName"] = valueTmp;

			//mBuff.push_back(mData);
			result[mData["worldName"]] = mData["gameWorldId"];
			valueTmp = "";
		}
	}
}

bool CheckAuth(vector<string>& list,const string& user)
{
	for (unsigned int i=0; i<list.size(); i++)
	{
		if (user == list[i])
		{
			return true;
		}
	}
	return false;
}

bool isNonExist(const std::string &sRoleId, const std::string &sItemGuid, std::map< std::string, std::vector<ExistedItems> >& UserItemInfo)
{
	string strRoleId	= sRoleId;
	//cout << "roleid: " << strRoleId << endl;	

	if (UserItemInfo.find(strRoleId) == UserItemInfo.end())
	{
		//cout << "no have." << endl;
		return true;
	}
	else
	{
		for (unsigned int i=0; i < UserItemInfo[strRoleId].size(); i++)
		{
			if (UserItemInfo[strRoleId][i].ItemGuid == sItemGuid)
			{
				return false;
			}
		}

		return true;
	}
}