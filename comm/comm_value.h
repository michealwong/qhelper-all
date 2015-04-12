/*************************************************************
* 文件描述：常用函数
**************************************************************/
#ifndef _COMM_VALUE_H_
#define _COMM_VALUE_H_

#include <utility>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

/*把文件数据读到一个map<string, string>结构中，文件一般是id，name的数据*/
extern void    LoadTab(const  string& TabFileName, map<string, string>& mBuff);
extern  std::string CharToHex(char c);
extern char HexToChar(const std::string & sHex);
extern std::string GbkToUnicode(const std::string & sSrc);
extern std::string  UnicodeToGbk(const std::string & sSrc);
//代码转换:从一种编码转为另一种编码
extern int     code_convert(char * from_charset,char * to_charset,char * inbuf,int inlen,char * outbuf,int outlen);
//GB2312码转为utf8
extern char *  GbkToUtf8(char * s);
//utf8码转为GB2312
extern char *  Utf8ToGbk(char * s);
extern char *  Utf8ToLt(char * s);
//** 进行base64编码
extern int Base64Enc(char *buf,const char*text,int size);
extern char GetBase64Value(char ch);
extern int Base64Dec(char *buf,const char*text,int size);
//**URL编码
extern std::string URLEncode(const std::string & sSrc);
extern std::string URLDecode(const std::string & sSrc);

// 生成流水号
extern std::string GetSerial();

extern std::string RequestStr(std::map <string, string > &inParams);
#endif

