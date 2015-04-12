

#include "HttpRpc.h"
#include <stdarg.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>



HttpRpc::HttpRpc()
{
	m_strtaskfile = "";
	m_strtaskresultfile = "";
	memset(m_ccurlerrorinfo,0,sizeof(m_ccurlerrorinfo));
	m_pcurl = NULL;
	m_strtaskresult = "";

	m_pcurl= curl_easy_init();
	if (m_pcurl == NULL)
	{
		PrintLog("Failed to create CURL connection\n");
		return;
	}
	m_curlcode = curl_easy_setopt(m_pcurl,CURLOPT_ERRORBUFFER,m_ccurlerrorinfo);
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to set error m_ccurlerror [%d]\n", m_curlcode);
		return;
	}
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_FOLLOWLOCATION, 1);
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to set redirect option [%s]\n",m_ccurlerrorinfo);
		return;
	}
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION, &write_callback);
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to set redirect option [%s]\n",m_ccurlerrorinfo);
		return;
	}
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, &m_strtaskresult);
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to set write data [%s]\n", m_ccurlerrorinfo);
		return;
	}
}

HttpRpc::~HttpRpc()
{
	if (NULL != m_pcurl)
	{
		curl_easy_cleanup(m_pcurl);
	}
}

void HttpRpc::PrintLog(const char *format, ...)
{
	char opString[3*1024];
	va_list args;

	va_start(args, format);
	vsprintf(opString, format, args);
	va_end(args);

	string logPath= "./logs/CurlRpc.log";

	unsigned long file_size = 0;
	struct stat file_stats;
	stat(logPath.c_str(), &file_stats);
	file_size = file_stats.st_size;
	ofstream * LogFile=NULL;
	if( file_size > 1024*1024*10)
	{
		LogFile = new ofstream(logPath.c_str());   //重新开始写
	}
	else
	{
		LogFile = new ofstream(logPath.c_str(),ios::app); // 追加
	}

	if (LogFile)
	{
		*LogFile << opString << endl;
	}
	delete LogFile;
}

int HttpRpc::SetProxy(const string& proxyIp)
{
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_PROXY, proxyIp.c_str());
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to set proxy ip.\n");
		return -1;
	}
	return 0;
}

int HttpRpc::write_callback(char *data, size_t size, size_t nmemb, string *writerData)
{
    unsigned long long sizes = static_cast<unsigned long long>(size) *
                               static_cast<unsigned long long>(nmemb);
    if (writerData == NULL)
        return 0;
    writerData->append(data, sizes);
    return sizes;
}

int HttpRpc::Post(const string& url,const string& requestparams,string& resultstring)
{
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_URL, url.c_str());
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to set URL [%s]\n",m_ccurlerrorinfo);
		return -1;
	}
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_POST,1);
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to exec curl_easy_setopt!");
		return -1;
	}
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_HTTP_VERSION,CURL_HTTP_VERSION_1_0);
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to exec curl_easy_setopt!");
		return -1;
	}
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDS,(char*)requestparams.c_str());
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to exec curl_easy_setopt!");
		return -1;
	}
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDSIZE,requestparams.length());
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to exec curl_easy_setopt!");
		return -1;
	}
	m_curlcode = curl_easy_perform(m_pcurl);
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to get '%s'\n", url.c_str());
		return -1;
	}

	PrintLog("err info:%s\n",m_ccurlerrorinfo);

	resultstring = m_strtaskresult;
	return 0;
}

int HttpRpc::UploadFile(const string& url,const string &taskfile,string &resultxmlstring,const string &taskresultfile,bool bwritefile)
{
    m_strtaskfile = taskfile;
    m_strtaskresultfile = taskresultfile;

    //读取文件内容
    char tempbuf[1024];
    int nread = 0;
    string strfilecontent;
    FILE *pfile = fopen(m_strtaskfile.c_str(),"r");
    if (NULL == pfile)
    {
        PrintLog("Failed to open file [%s]!\n",m_strtaskfile.c_str());
        return -1;
    }
    else
    {
        do
        {
            memset(tempbuf,0,sizeof(tempbuf));
            nread = fread(tempbuf, 1,sizeof(tempbuf)-1, pfile);
            strfilecontent += tempbuf;
        }
        while(nread);
    }

    fclose(pfile);

	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_URL, url.c_str());
	if (m_curlcode != CURLE_OK)
	{
		PrintLog("Failed to set URL [%s]\n",m_ccurlerrorinfo);
		return -1;
	}

    //发送文件
    m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_POST,1);
    if (m_curlcode != CURLE_OK)
    {
        PrintLog("Failed to exec curl_easy_setopt!");
        return -1;
    }
    m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_HTTP_VERSION,CURL_HTTP_VERSION_1_0);
    if (m_curlcode != CURLE_OK)
    {
        PrintLog("Failed to exec curl_easy_setopt!");
        return -1;
    }
    m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDS,(char*)strfilecontent.c_str());
    if (m_curlcode != CURLE_OK)
    {
        PrintLog("Failed to exec curl_easy_setopt!");
        return -1;
    }

    m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDSIZE,strfilecontent.length());
    if (m_curlcode != CURLE_OK)
    {
        PrintLog("Failed to exec curl_easy_setopt!");
        return -1;
    }
    
    m_curlcode = curl_easy_perform(m_pcurl);

    if (m_curlcode != CURLE_OK)
    {
        PrintLog("Failed to get '%s'\n", url.c_str());
        return -1;
    }

    //根据bwritefile判断时候需要写结果文件
    if (bwritefile)
    {
        //输出结果文件名为空
        if ("" == m_strtaskresultfile)
        {
            PrintLog("Failed to open file!");
            return -1;
        }

        pfile = fopen(m_strtaskresultfile.c_str(),"w+");
        if (NULL == pfile)
        {
            PrintLog("Failed to open file!");
            return -1;
        }
        else
        {
            fwrite(m_strtaskresult.c_str(),1,m_strtaskresult.length(),pfile);
        }
        fclose(pfile);
    }

    resultxmlstring = m_strtaskresult;
    return 0;
}

