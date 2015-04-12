
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

    string m_strip;                        //http服务器IP
    int    m_iport;                        //http服务器端口
    char m_ccurlerrorinfo[CURL_ERROR_SIZE];//curl返回的错误信息
    string m_strtaskresult;                //任务结果，字符串形式保存
    CURLcode m_curlcode;                   //存放curl库操作的返回的结果码
    CURL * m_pcurl;                        //CURL对象指针
    string m_strtaskfile;                  //要上传的任务文件
    string m_strtaskresultfile;            //任务结果文件
};


#endif


