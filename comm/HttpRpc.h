
#ifndef _HTTPRPC_H_
#define _HTTPRPC_H_

#include "curl/curl.h"
#include <string>
#include "comm_c_flags.h"

using namespace std;

class HttpRpc
{
public:
    HttpRpc();
    ~HttpRpc();
    
	int Post(const string& url,const string &requestparams,string& resultstring);
    int UploadFile(const string& url,const string &taskfile,string &resultxmlstring,const string &taskresultfile="",bool bwritefile = false);
	int SetProxy(const string& proxyIp);
private:
	void PrintLog(const char *format, ...);
    static int write_callback(char *data, size_t size, size_t nmemb, string *writerData);

    string m_strip;                        //http������IP
    int    m_iport;                        //http�������˿�
    char m_ccurlerrorinfo[CURL_ERROR_SIZE];//curl���صĴ�����Ϣ
    string m_strtaskresult;                //���������ַ�����ʽ����
    CURLcode m_curlcode;                   //���curl������ķ��صĽ����
    CURL * m_pcurl;                        //CURL����ָ��
    string m_strtaskfile;                  //Ҫ�ϴ��������ļ�
    string m_strtaskresultfile;            //�������ļ�
};


#endif


