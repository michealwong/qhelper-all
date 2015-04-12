/*************************************************************
* �ļ����������ú���
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

/*���ļ����ݶ���һ��map<string, string>�ṹ�У��ļ�һ����id��name������*/
extern void    LoadTab(const  string& TabFileName, map<string, string>& mBuff);
extern  std::string CharToHex(char c);
extern char HexToChar(const std::string & sHex);
extern std::string GbkToUnicode(const std::string & sSrc);
extern std::string  UnicodeToGbk(const std::string & sSrc);
//����ת��:��һ�ֱ���תΪ��һ�ֱ���
extern int     code_convert(char * from_charset,char * to_charset,char * inbuf,int inlen,char * outbuf,int outlen);
//GB2312��תΪutf8
extern char *  GbkToUtf8(char * s);
//utf8��תΪGB2312
extern char *  Utf8ToGbk(char * s);
extern char *  Utf8ToLt(char * s);
//** ����base64����
extern int Base64Enc(char *buf,const char*text,int size);
extern char GetBase64Value(char ch);
extern int Base64Dec(char *buf,const char*text,int size);
//**URL����
extern std::string URLEncode(const std::string & sSrc);
extern std::string URLDecode(const std::string & sSrc);

// ������ˮ��
extern std::string GetSerial();

extern std::string RequestStr(std::map <string, string > &inParams);
#endif

