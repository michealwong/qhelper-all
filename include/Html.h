#ifndef __HTML_H__
#define __HTML_H__

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unistd.h>
#include "../comm/comm_c_flags.h"

using namespace std;

inline	void	HtmlMessageBox(const char*	sMsg)
{
        int i;
        char sBuffer[1024];

        strncpy(sBuffer, sMsg, sizeof(sBuffer)-1);
        sBuffer[sizeof(sBuffer)-1] = 0;
        
        for (i = 0; i < strlen(sBuffer); i++)
        {
                if (sBuffer[i] == '\r' || sBuffer[i] == '\n' || sBuffer[i] == '\t'
                                || ((unsigned)sBuffer[i] < 0x20))
                {
                        sBuffer[i] = ' ';
                }
                else if (sBuffer[i] == '\'')
                {
                        sBuffer[i] = '`';
                }
        }

        cout << "<script LANGUAGE='JavaScript'>";
        cout << "\n<!--";
        cout << "\nalert('" << sBuffer << "');";
        cout << "\n//--></script>";
}

inline	void	HtmlUrlBack()
{
        cout << "<script LANGUAGE='JavaScript'>";
        cout << "\n<!--";
        cout << "\nhistory.back();";
        cout << "\n//--></script>";
}

inline	void	HtmlRedirect(const char*	sURL)
{
/*      
        HTTP/1.1 302 Object moved
        Server: Microsoft-IIS/4.0
        Date: Sun, 17 Oct 1999 09:23:21 GMT
        Location: http://www.oicq.com
        Content-Type: text/html
        Set-Cookie: ASPSESSIONIDQGGQGQAZ=OCHBOKFBHPFEPNJDJDOJDEBM; path=/
        Cache-control: private
*/

        //改用直接输出ＪＡＶＡ脚本刷新，因为下面原来的方法用后会导致ＣＧＩ执行不正常。 
        //注意被刷新的页面应避免被CACHE，如在页头加入<meta http-equiv="pragma" content="no-cache"> (
        //在所导向的URL后面加上一个按时间生成的唯一参数， 形成不同的URL，避免浏览器读CACHE。 （AGONG

        time_t ltime;
        char url[2048];

        time(&ltime);

        strncpy(url, sURL, 500);

        if (strstr(url, "?") == NULL)
                strcat(url, "?");
        else
                strcat(url, "&");

        cout << "<script language=javascript>\n";
        cout << "window.location.href='" << url << "PcacheTime=" << ltime << "';\n";
        cout << "</script>\n";
}

#endif
