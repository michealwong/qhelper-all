/*************************************************************
* 文件名：comm_iptools.h
* 文件描述：封装IP各种常用的操作
* 作者：stanjiang
* 日期：2008-03-28
* 版本：OssL-SDBL v1.2.0
* 版权：深圳腾迅计算机系统有限公司
**************************************************************/
#ifndef _IPTOOLS_H_
#define _IPTOOLS_H_

#include <pthread.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <map>
#include <stdlib.h>

#include "comm_strings.h"


#ifdef __cplusplus
#define IPTOOLS_API extern
extern "C"
{
#else
#define IPTOOLS_API
#endif

using namespace std;

#define IPV4    AF_INET
#define IPV6    AF_INET6
const unsigned short  SOCK_SIZE = 16;
const unsigned short BUF_SIZE = 512;
const unsigned short THREAD_NUM = 10; // 查询 地域的线程数
const unsigned short THREAD_UIN = 10; // 查询 Uin的线程数
const unsigned short THREAD_PARAM = 32;
const unsigned int THREAD_STACK_SIZE = 32*1024*1024; // 线程堆栈大小

// IP查询查询后的结果数据结构
struct TAreaInfo
{
    std::string strIP;           // IP信息
    std::string strProvince; // 省份名称
    std::string strCity;         // 市级名称

    void clear(void)
    {
        strIP.clear();
        strProvince.clear();
        strCity.clear();
    }
};


// IP位置所属信息
struct TIpLocInfo
{
    std::string    strLocation;  //省份
    unsigned int  uiCount;       //该省份IP地址个数
};

//QQ IP信息
struct  TIpUinInfo
{
    int iUin; //qq号码
    unsigned int uiIp; // 无符号整形IP地址
};

// QQ位置信息
struct TUinLocInfo
{
    int  iUin;  //qq号码
    std::string strLocation; //省份
};


//点字符串到 整数 的转换  的std::string 版本 
IPTOOLS_API unsigned int ipStrToInt(const string& strIP, int pro);

// 整数到点字符串的转换的std::string 版本
IPTOOLS_API string ipIntToStr(unsigned int uiIP, int pro=IPV4 );

// 查询IP所对应的省、市信息

IPTOOLS_API int ipToArea(const string& szIP, TAreaInfo& tArea);

// 处理区域查询的线程函数
IPTOOLS_API void * FindArea(void* pParam);

// 处理Uin查询的线程函数
IPTOOLS_API void * FindUin(void* pParam);

#ifdef __cplusplus
}
#endif

#endif




