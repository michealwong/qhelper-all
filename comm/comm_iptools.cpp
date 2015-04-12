/*************************************************************
* �ļ�����comm_iptools.h
* �ļ���������װIP���ֳ��õĲ���
* ���ߣ�stanjiang
* ���ڣ�2008-03-28
* �汾��OssL-SDBL v1.2.0
* ��Ȩ��������Ѹ�����ϵͳ���޹�˾
**************************************************************/
#include "comm_iptools.h"


using namespace std;


//���ַ����� ���� ��ת��  ��std::string �汾 
unsigned int ipStrToInt(const string& strIP, int pro)
{
    if(strIP.empty())
        return 0;
    const char* szIP = strIP.c_str();
    return ipStrToInt(szIP, pro);
}

// ���������ַ�����ת����std::string �汾
string ipIntToStr(unsigned int uiIP, int pro )
{
    char aryIP[32] = {0};


	unsigned long ulIP = htonl(uiIP);
	inet_ntop(pro, &ulIP, aryIP, SOCK_SIZE);
	
    return aryIP;
}


int ipToArea(const string& szIP, TAreaInfo& tArea)
{    
    string strParam = szIP;
    strParam = "curl http://10.132.74.108:8081/ipaddress?ip=" + strParam;

    char aryBuf[BUF_SIZE] = {0};
    string strBuf;
    vector<string> vecBuf;
    
    FILE* pFile = popen(strParam.c_str(), "r");
    fgets(aryBuf, BUF_SIZE, pFile);

    pclose(pFile);
    
    strBuf = aryBuf;
    if(strBuf.empty())
        return 1;
    Split(strBuf, "|", 1, vecBuf);
    if(vecBuf.size() == 2)
       {
	vecBuf.push_back("");
	} 
    if(vecBuf.size() != 3)
   	return 1;
    tArea.strIP = vecBuf.at(0);
    tArea.strProvince = vecBuf.at(1);
    if(tArea.strProvince.empty())
        tArea.strProvince = "δ֪IP";
    tArea.strCity = vecBuf.at(2);        

    return 0;
}


// ���������ѯ���̺߳���
void * FindArea(void* pParam)
{    
    TAreaInfo tItem;
    vector<string>* pVecIP = (vector<string>*)pParam;
    vector<string>::iterator it = pVecIP->begin();
    vector<string> vecRst;
    for(; it != pVecIP->end(); ++it)
    {
        ipToArea(*it, tItem);
        vecRst.push_back(tItem.strProvince);
    }
    pVecIP->clear();
    pVecIP->assign(vecRst.begin(), vecRst.end());
}

// ����Uin��ѯ���̺߳���
void * FindUin(void* pParam)
{    
    TAreaInfo tItem;
    map<int , string>* pUinMap = (map<int, string>*)pParam;
    map<int, string>::iterator it = pUinMap->begin();

    for(; it != pUinMap->end(); ++it) 
    {
        ipToArea(it->second, tItem);
       (*pUinMap)[it->first] = tItem.strProvince; // ���õ���ʡ����Ϣ�����Ӧ��Uinӳ����
    }
}




