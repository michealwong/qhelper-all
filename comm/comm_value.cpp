#include "comm_value.h"
#include "comm_strings.h"
#include <iostream>
#include <fstream>
#include <sstream>

/*把文件数据读到一个map<string, string>结构中，文件一般是id，name的数据*/
void    LoadTab(const  string& TabFileName, map<string, string>& mBuff)
{
    /*     ifstream * tabStream;
     
        tabStream = new ifstream(TabFileName.c_str());
        string id;
     
        if(*tabStream)
        {
            while( *tabStream >> id )
                *tabStream >> mBuff[id];
        }
     
        delete  tabStream; */

    ifstream  inStream(TabFileName.c_str());
    string tmpStr;
    while(getline(inStream,tmpStr))
    {
        istringstream tmpStream(tmpStr);
        tmpStr="";
        int i=0;
        string sId = "";
        while(tmpStream >> tmpStr)
        {
            //cout << tmpStr << " ";
            if(i==0)
                sId = tmpStr;
            else
                mBuff[sId] +=" " +  tmpStr;
            i++;
        }
    }
}


std::string CharToHex(char c)
{
    std::string sValue;
    static char MAPX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    sValue += MAPX[(c >> 4) & 0x0F];
    sValue += MAPX[c & 0x0F];
    return sValue;

}

char HexToChar(const std::string & sHex)
{
    unsigned char c=0;
    for ( unsigned int i=0; i<std::min<unsigned int>(sHex.size(), (unsigned int)2); ++i )
    {
        unsigned char c1 = std::toupper(sHex[i]);
        unsigned char c2 = (c1 >= 'A') ? (c1 - ('A' - 10)) : (c1 - '0');
        (c <<= 4) += c2;
    }
    return c;
}

std::string GbkToUnicode(const std::string & sSrc)
{
    std::string result;
    std::string::const_iterator pos;

    for(pos = sSrc.begin(); pos != sSrc.end(); ++pos)
    {

        if ( *pos >= '0' && *pos <= '9' ||
                *pos >= 'A' && *pos <= 'Z' ||
                *pos >= 'a' && *pos <= 'z'
           )
        {
            result.append(1, *pos);
        }
        else
        {
            result.append("%" + CharToHex(*pos));
        }
    }
    return result;
}

std::string  UnicodeToGbk(const std::string & sSrc)
{
    std::string result;
    std::string::const_iterator pos;

    for(pos = sSrc.begin(); pos != sSrc.end(); ++pos)
    {

        if ( *pos == '%' && std::distance(pos, sSrc.end()) > 2 )
        {
            if ( std::tolower(*(pos+1)) == 'u' &&
                    std::distance(pos, sSrc.end()) > 5 &&
                    std::isxdigit(*(pos + 2)) &&
                    std::isxdigit(*(pos + 3)) &&
                    std::isxdigit(*(pos + 4)) &&
                    std::isxdigit(*(pos + 5))
               )
            {
                // string like %uABCD
                pos = pos +2;

                unsigned short UnicodeWord;
                UnicodeWord = HexToChar(string(pos, pos+2));
                UnicodeWord <<= 8;
                UnicodeWord += (unsigned char)HexToChar(string(pos+2, pos+4));
                //       result.append(ChrsetTools::USC2GB(string((char *)&UnicodeWord, 2)));

                pos = pos + 3;
            }
            else if ( std::distance(pos, sSrc.end()) > 2 &&
                      std::isxdigit(*(pos + 1)) &&
                      std::isxdigit(*(pos + 2))
                    )
            {
                // string like %AB
                ++pos;
                result.append(1, HexToChar(string(pos,pos+2)));
                ++pos;
            }

            else
            {
                result.append(1, '%');
            }
        }
        else
        {
            result.append(1, *pos);
        }
    }

    return result;
}


//代码转换:从一种编码转为另一种编码
int     code_convert(char * from_charset,char * to_charset,char * inbuf,int inlen,char * outbuf,int outlen)
{
    iconv_t cd;
    int     rc;
    char ** pin = &inbuf;
    char ** pout = &outbuf;

    if ((cd = iconv_open(to_charset,from_charset)) == 0)
        return  -1;

    memset(outbuf,0,outlen);

    if (iconv(cd,pin,(size_t*)&inlen,pout,(size_t*)&outlen)==-1)
        return -1;

    iconv_close(cd);

    return 0;
}

//GB2312码转为utf8
char *  GbkToUtf8(char * s)
{
    static  char    code[1024*1024];

    code_convert("gb18030","utf-8", s, strlen(s), code, 1024*1024);

    return code;
}

//utf8码转为GB2312
char *  Utf8ToGbk(char * s)
{
    static  char    code[1024*1024];

    code_convert("utf-8","gb18030", s, strlen(s), code, 1024*1024);

    return code;
}
char *  Utf8ToLt(char * s)
{
    static  char    code[1024*2];

    code_convert("utf-8","latin1", s, strlen(s), code, 1024*2);

    return code;
}
/**
* @brief 进行base64编码
*
* @param buf   [out]保存编码结果
* @param text  [in]要编码的串
* @param size  [in]text的长度
*
* @return 编码长度
**/
int Base64Enc(char *buf,const char*text,int size) 
{ 
   static char *base64_encoding = 
       "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   int buflen = 0; 

   while(size>0){
       *buf++ = base64_encoding[ (text[0] >> 2 ) & 0x3f];
       if(size>2){
           *buf++ = base64_encoding[((text[0] & 3) << 4) | (text[1] >> 4)];
           *buf++ = base64_encoding[((text[1] & 0xF) << 2) | (text[2] >> 6)];
           *buf++ = base64_encoding[text[2] & 0x3F];
       }else{
           switch(size){
               case 1:
                   *buf++ = base64_encoding[(text[0] & 3) << 4 ];
                   *buf++ = '=';
                   *buf++ = '=';
                   break;
               case 2: 
                   *buf++ = base64_encoding[((text[0] & 3) << 4) | (text[1] >> 4)]; 
                   *buf++ = base64_encoding[((text[1] & 0x0F) << 2) | (text[2] >> 6)]; 
                   *buf++ = '='; 
                   break; 
           } 
       } 

       text +=3; 
       size -=3; 
       buflen +=4; 
   } 

   *buf = 0; 
   return buflen; 
} 

char GetBase64Value(char ch)
{
   if ((ch >= 'A') && (ch <= 'Z')) 
       return ch - 'A'; 
   if ((ch >= 'a') && (ch <= 'z')) 
       return ch - 'a' + 26; 
   if ((ch >= '0') && (ch <= '9')) 
       return ch - '0' + 52; 
   switch (ch) { 
       case '+': 
           return 62; 
       case '/': 
           return 63; 
       case '=': /* base64 padding */ 
           return 0; 
       default: 
           return 0; 
   } 
}

/**
* @brief base64解码
*
* @param buf   [out]解码结果
* @param text  [in]要解码的串,必须是4的倍数
* @param size  [in]text大小
*
* @return -1出错,>=0解码缓冲区使用长度
**/
int Base64Dec(char *buf,const char*text,int size) 
{
   if(size%4)
       return -1;
   char chunk[4];
   int parsenum=0;

   while(size>0){
       chunk[0] = GetBase64Value(text[0]); 
       chunk[1] = GetBase64Value(text[1]); 
       chunk[2] = GetBase64Value(text[2]); 
       chunk[3] = GetBase64Value(text[3]); 

       *buf++ = (chunk[0] << 2) | (chunk[1] >> 4); 
       *buf++ = (chunk[1] << 4) | (chunk[2] >> 2); 
       *buf++ = (chunk[2] << 6) | (chunk[3]);

       text+=4;
       size-=4;
       parsenum+=3;
   }

   return parsenum;
} 


std::string URLDecode(const std::string & sSrc)
{   
        std::string result;
        std::string::const_iterator pos;
        
        for(pos = sSrc.begin(); pos != sSrc.end(); ++pos) {
        
                if ( *pos == '%' && std::distance(pos, sSrc.end()) > 2 ) {
                        if ( std::tolower(*(pos+1)) == 'u' && 
                                std::distance(pos, sSrc.end()) > 5 &&
                                std::isxdigit(*(pos + 2)) && 
                                std::isxdigit(*(pos + 3)) &&
                                std::isxdigit(*(pos + 4)) &&
                                std::isxdigit(*(pos + 5))
                        ) {
                                // string like %uABCD                        
                                pos = pos +2;
    
                                unsigned short UnicodeWord;
                                UnicodeWord = HexToChar(string(pos, pos+2));
                                UnicodeWord <<= 8;
                                UnicodeWord += (unsigned char)HexToChar(string(pos+2, pos+4));
                         //       result.append(ChrsetTools::USC2GB(string((char *)&UnicodeWord, 2)));

                                pos = pos + 3;
                        }
                        else if ( std::distance(pos, sSrc.end()) > 2 &&
                                std::isxdigit(*(pos + 1)) &&
                                std::isxdigit(*(pos + 2))
                        ) {
                                // string like %AB
                                ++pos;
                                result.append(1, HexToChar(string(pos,pos+2)));
                                ++pos;
                        }

                        else {
                                result.append(1, '%');
                        }
                }
                else {
                        result.append(1, *pos);
                }
        }

        return result;
}

//url code
std::string URLEncode(const std::string & sSrc)
{
        std::string result;
        std::string::const_iterator pos;

        for(pos = sSrc.begin(); pos != sSrc.end(); ++pos) {

                if ( *pos >= '0' && *pos <= '9' ||
                        *pos >= 'A' && *pos <= 'Z' ||
                        *pos >= 'a' && *pos <= 'z'
                ) {
                        result.append(1, *pos);
                }
                else {
                        result.append("%" + CharToHex(*pos));
                }
        }

        return result;
}

// 获取随机序号
std::string GetSerial()
{
	static unsigned int rnd = 1;
	char serial[36] = {0};
	char sTime[16] = {0};
	time_t tNow = time(0);					// 当前时间戳
	strftime(sTime, sizeof(sTime), "%Y%m%d%H%M%S", localtime(&tNow));
	//srand((unsigned)(clock() + getpid()));	// 初始化随机数种子
	//sprintf(serial, "20-QX-%s-%08d", sTime, rand()%100000000);	// 20-QX-20130614150346-12345678
	sprintf(serial, "20-DNF-%s-%05d%03d", sTime, getpid()%100000,(rnd++)%1000);	// 20-QX-20130614150346-12345678

	return serial;
}
//拼接request串
std::string RequestStr(std::map <string, string > &inParams)
{
	vector<string> theVarPairList;
	for ( map<string,string>::iterator it = inParams.begin() ; it != inParams.end(); it++ )
	{
		string theVarPair = (*it).first + "=" + (*it).second;
		theVarPairList.push_back(theVarPair);
	}
	string theParamListString;
	Join(theVarPairList,'&',theParamListString);
	theParamListString = Utf8ToGbk((char*)theParamListString.c_str());

	return theParamListString;
}