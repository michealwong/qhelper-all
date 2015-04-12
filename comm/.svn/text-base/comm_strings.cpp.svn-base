/*************************************************************
* 文件描述：字符串的常 用操作类
**************************************************************/

#include <utility>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include "map"
#include <sstream>
#include <cctype>
#include "stdarg.h"
#include "stdio.h"
using namespace std;

// 字符串转换成任意数据类型
template<typename T>
void StrTo(const std::string& str, T& t)
{
    std::istringstream s(str);
    s >> t;
}

// 任意数据类型转换成字符串
template<typename T>
std::string ToStr(const T& t)
{
    std::ostringstream s;
    s << t;
    return s.str();
}

#ifdef __cplusplus
extern "C"
{
#endif

	// 字符串转换成无符号整形
	 unsigned int StrToUi(const char* str)
	{
	  unsigned int ui; 

	  ui= strtoul(str,NULL,10);
 
	  return ui;   

	}
	 char*  itoa(unsigned int in_int)
	{
		static char tmpStr[32];
		snprintf(tmpStr,32,"%u",in_int);
		return tmpStr;
	}

    // 字符串转换成整形
     int StrToInt(const string& str)
    {
        int n = 0;
        StrTo(str, n);
        return n;
    }

    // 整形转换成字符串
     std::string IntToStr(int n)
    {
        return ToStr(n);
    }

    // 字符串转换成长整形
     long StrToLong(const string& str)
    {
        long n = 0;
        StrTo(str, n);
        return n;
    }

    // 长整形转换成字符串
     std::string LongToStr(long n)
    {
        return ToStr(n);
    }

    // 字符串转换成64长整形
     long long StrToLLong(const string& str)
    {
        long long n = 0;
        StrTo(str, n);
        return n;
    }

    // 64位长整形转换成字符串
     std::string LLongToStr(long long n)
    {
        return ToStr(n);
    }

    // 字符串转换成Float
     float StrToFloat(const string& str)
    {
        float n = 0;
        StrTo(str, n);
        return n;
    }

    //Float转换成字符串
     std::string FloatToStr(float n)
    {
        return ToStr(n);
    }

    // 字符串转换成Double
     double StrToDouble(const string& str)
    {
        double n = 0;
        StrTo(str, n);
        return n;
    }

    //Double转换成字符串
     std::string DoubleToStr(double n)
    {
        return ToStr(n);
    }

	char* itoa64(unsigned long long i)
	{
		static char tmp[20];
		sprintf(tmp,"%llu",i);
		return tmp;
	}

	unsigned long long atoi64(const char* s)
	{
		return atoll(s);
	}

	

    /**************************************************************************
    * 函数名：TrimLeft
    * 功能：去掉字符串左边的空格、Tab字符
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
     void TrimLeft(std::string& str)
    {
        std::string::iterator it = str.begin();
        for(; it != str.end(); ++it)
        {
            if(std::isspace(*it) || *it == '\t')
                continue;
            str.erase(str.begin(), it);
            break;
        }
    }

    /**************************************************************************
    * 函数名：TrimRight
    * 功能：去掉字符串右边的空格、Tab字符
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
     void TrimRight(std::string& str)
    {
        std::string::iterator it = str.end();
        if(it == str.begin())
            return;
        while(it != str.begin() && (--it, std::isspace(*it) || *it == '\t'))
            ;
        if(*it != ' ')
            ++it;
        str.erase(it, str.end());
    }

    /**************************************************************************
    * 函数名：Trim
    * 功能：去掉字符串左、右边的空格、Tab字符
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
     void Trim(std::string& str)
    {
        TrimLeft(str);
        TrimRight(str);
    }


    /**************************************************************************
    * 函数名：ToUpper
    * 功能：将字符串全部转换成大写的形式
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
     void ToUpper(std::string& str)
    {
        std::string strBak;
        strBak.reserve(str.size());
        transform(str.begin(), str.end(), back_inserter(strBak), static_cast<int (*)(int)>(toupper));
        str = strBak;
    }


    /**************************************************************************
    * 函数名：ToLower
    * 功能：将字符串全部转换成小写的形式
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
     void ToLower(std::string& str)
    {
        std::string strBak;
        strBak.reserve(str.size());
        transform(str.begin(), str.end(), back_inserter(strBak), static_cast<int (*)(int)>(tolower));
        str = strBak;
    }

    /* 格式化C字符串并输出C++字符串
    * \param[in] szFmt 待格式化的C字符串
    * \return 格式化好的C++字符串
    */
    std::string Format(const char * szFmt, ...)
    {
        enum { ERRMSG_MAX_LENGTH = 1024 };

        char szErrMsg[ERRMSG_MAX_LENGTH+1] = {0};

        va_list ap;
        va_start(ap, szFmt);
        vsnprintf(szErrMsg, ERRMSG_MAX_LENGTH, szFmt, ap);
        va_end(ap);

        return std::string(szErrMsg);
    }


    /*从sSrc中取出sBegin＆sEnd之内的string
           * \param[in] sSrc           原始字符串
           * \param[in] sBegin        前分隔符
           * \param[in] sEnd          后分隔符
           * \return sBegin＆sEnd之内的string
           * \note 例如: \n
           *       input   sSrc="name: vvv;" sBegin="name: " sEnd=";" \n
           *       return  string("vvv");
           */
    std::string Inner(const std::string & sSrc,const std::string & sBegin, const std::string & sEnd)
    {
        string::size_type bpos = 0;
        string::size_type epos = sSrc.size();

        if ( sBegin.empty() == false )
        {
            if ( (bpos = sSrc.find(sBegin)) == string::npos )
            {
                return string("");
            }
        }

        bpos += sBegin.size();

        if ( sEnd.empty() == false )
        {
            if ( (epos = sSrc.find(sEnd, bpos)) == string::npos )
            {
                return sSrc.substr(bpos);
            }
        }

        return sSrc.substr(bpos, epos - bpos);
    }


    /*!  从sSrc中取出最多nSize个字符，并检查中文完整性
           * \param[in] sSrc         原始字符串
           * \param[in] nSize        字节数
           * \return 中文完整的字符串
           */
    std::string CutChinese(const std::string & sSrc, int nSize)
    {
        if (nSize >= (int)sSrc.size())
        {
            return sSrc;
        }

        int i;
        for ( i=0; i<nSize; ++i)
        {
            if ( sSrc.at(i) < 0 )
            {
                ++i;
            }
        }

        return i==nSize ? sSrc.substr(0, nSize) : sSrc.substr(0, nSize-1);
    }
    
    /**************************************************************************
    * 函数名：SplitByStr
    * 功能：字符串分隔
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     const string&             IN                       待处理的字符串
    *              delim                 string               IN                       分隔符串
    *              dst                    vector<string>           IN/OUT              分隔后的结果
    * 返回值：true or false
    ***************************************************************************/
     bool SplitByStr(std::string& src, const string& delim, std::vector<std::string>& dst)
    {
        size_t pos1 = 0, pos2 = 0;
        if(delim=="")
            return false;
            
        dst.clear();
        Trim(src);

        std::string sItem;

            while(std::string::npos != (pos2 = src.find(delim, pos1)))
            {
                sItem = src.substr(pos1, pos2 - pos1);
                pos1 = ++pos2;
                dst.push_back(sItem);
            }

        sItem = src.substr(pos1);
        dst.push_back(sItem);

        return true;
    }
    
    /**************************************************************************
    * 函数名：Split
    * 功能：字符串分隔
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     const string&             IN                       待处理的字符串
    *              delim                 const char*               IN                       分隔符串
    *              num                  unsigned int              IN                       分隔符个数
    *              dst                    vector<string>           IN/OUT              分隔后的结果
    * 返回值：true or false
    ***************************************************************************/
     bool Split(std::string& src, const char* delim, unsigned int num, std::vector<std::string>& dst)
    {
        size_t pos1 = 0, pos2 = 0;
        if(NULL == delim || 0 == num)
            return false;

        dst.clear();
        Trim(src);

        //最后一个字符如果是分隔符，删掉
        if(src[ src.length()-1 ] == *delim)
            src.erase(src.length()-1, 1);

        std::string sItem;

        for(unsigned int i = 0; i < num; ++i)
        {
            while(std::string::npos != (pos2 = src.find_first_of(delim[i], pos1)))
            {
                sItem = src.substr(pos1, pos2 - pos1);
                pos1 = ++pos2;
                dst.push_back(sItem);
            }
        }
        sItem = src.substr(pos1);
        dst.push_back(sItem);

        return true;
    }


    /**************************************************************************
    * 函数名：SplitToMap
    * 功能：字符串分隔，组成一个map结构返回，默认分隔符为&,=
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     const string&             IN                       待处理的字符串
    *              delim                 cstring               IN                               分隔符串,默认分隔符为&,=
    *              num                  unsigned int              IN                       分隔符个数,默认为2，目前必须为2个分隔符
    *              dst                    map<string,string>           IN/OUT              分隔后的结果
    * 返回值：true or false
    ***************************************************************************/
     bool SplitToMap(std::string& src, std::map<string,string>& dst, string delim, unsigned int num)
    {
        if( "" == delim || 2 != num )
            return false;

        Trim(src);

        vector<string> vTemp;

        Split(src,&delim[0],1,vTemp);

        for(int i=0;i<vTemp.size();i++)
        {
            vector<string> vSplitData;
            Split(vTemp[i],&delim[1],1,vSplitData);

            if(vSplitData.size() == 2)
            {
                dst[ vSplitData[0] ] = vSplitData[1];
            }
            // --- added by darrenqiu on 2010-02-02
						else if (vSplitData.size() == 1)
						{
							dst[vSplitData[0]] = "";
						}
						// --- end ---
            else
            {
                return false;
            }
        }

        return true;
    }


    /**************************************************************************
    * 函数名：MapJoin
    * 功能：把两个map结构合成在一起，数据存放在第一个map里
    * 参数：
    *              参数名       参数类型             传入方式    参数说明
    *              first                     map<string,string>&             IN                
    *              second                map<string,string>&             IN                               
    * 返回值：true or false
    ************************************************************************** */
     bool MapJoin(map<string,string>& first, map<string,string>& second)
    {
        map<string,string>::iterator it_fir, it_sec;

        for(it_sec=second.begin(); it_sec!=second.end();it_sec++)
        {
            first[ it_sec->first ] = it_sec->second;
        }

        return true;
    }
   

    /**************************************************************************
    * 函数名：Join
    * 功能：字符串合成
    * 参数：
    *              参数名       参数类型                   传入方式    参数说明
    *              vecSrc               const vector<string>&             IN                       待处理的字符串
    *              ch                      char                                      IN                       分隔符串
    *              strDst                string&                                     IN/OUT              分隔后的结果
    * 返回值：true or false
    ***************************************************************************/
     bool Join(const vector<string>& vecSrc, char ch, string& strDst)
    {
        if(ch == 0x00 || vecSrc.empty())
            return false;
        ostringstream os;
        vector<string>::const_iterator it = vecSrc.begin();
        for(; it != vecSrc.end(); ++it)
        {
            os << *it << ch;
        }
        strDst = os.str();
        strDst = strDst.substr(0, strDst.size()-1);  //去掉最后一个ch

        return true;
    }

    /**************************************************************************
    * 函数名：Replace
    * 功能：将用新的子串替换原串中所有指定的串
    * 参数：
    *              参数名       参数类型                   传入方式    参数说明
    *              strSrc               string&                                  IN                       待处理的字符串
    *              strOld               const string&                        IN                       被替换的字符
    *              strNew              const string&                       IN                       替换的字符
    * 返回值：bool
    ***************************************************************************/
     bool Replace(string& strSrc, const string& strOld, const string& strNew)
    {
		if( strOld == strNew  )
			return true;

        size_t pos = 0;
        if((pos = strSrc.find(strOld)) == string::npos || strOld.empty())
            return false;

        while(pos != string::npos)
        {
            strSrc.replace(pos, strOld.size(), strNew);
            pos = strSrc.find(strOld);
        }
        return true;
    }

    /*去掉一些常见的特殊字符，替换为空*/
#define REPLACE_STRING(strSrc)   Replace( strSrc ,"\n",  "" );\
                                            Replace( strSrc ,"\t",  "" );\
                                            Replace( strSrc ,"\b",  "" );\
                                           Replace( strSrc ,"\r", "" );\
                                            Replace( strSrc ,"\f",  "" );\
                                            Replace( strSrc ,"\\",  "" );\
                                           Replace( strSrc ,"\'", "" );\
                                            Replace( strSrc ,"\"",  "" );\
                                            Replace( strSrc ,"\ ",  "" );

    /**************************************************************************
    * 函数名：ReplaceString
    * 功能：从指定位置开始，将用新的子串替换原串中所有指定的串
    * 参数：
    *              参数名                      参数类型                  参数说明
    *              strOperateContent          string&                              待处理的字符串
    *              searchString                    string                                 被替换的字符
    *              pos                                  string::size_type               开始位置
    *              replaceString                   string                                 替换的字符
    * 返回值：bool
    ***************************************************************************/
    void ReplaceString(string &strOperateContent, string searchString , string::size_type pos , string replaceString )
    {
        while ( (pos = strOperateContent.find(searchString, pos)) != string::npos )
        {
            strOperateContent.replace( pos, searchString.size(), replaceString );
            pos++;
        }
    }

    /**************************************************************************
    * 函数名：Remove
    * 功能：删除串中所有的指定子串
    * 参数：
    *              参数名                 参数说明
    *              strSrc                         待处理的字符
    *              strSub                         被删除的字符
    * 返回值：bool
    ***************************************************************************/
     bool Remove(string& strSrc, const string& strSub)
    {
        size_t pos = 0;
        if((pos = strSrc.find(strSub)) == string::npos || strSub.empty())
            return false;

        while(pos != string::npos)
        {
            strSrc.erase(pos, strSub.size());
            pos = strSrc.find(strSub);
        }

        return true;
    }

    /**************************************************************************
    * 函数名：MatchAfterSplit
    * 功能：按指定字符分隔后的模式匹配
    * 参数：
    *              参数名         参数说明
    *              strSrc                 待处理的字符串
    *              strSub                待查找的字符串
    *              ch                       分隔符
    * 返回值：int
    * 说明: 比如string str1 = "1102|2|11|3", str2 = "11",则int n=MatchAfterSplit(str1, str2, '|')
    *                后，返回的n应为3,，即'|'分隔后的第三个子串，如没有
                      找到，则返回0
    ***************************************************************************/
     unsigned int MatchAfterSplit(const string& strSrc, const string& strSub, char ch)
    {
        unsigned int uiRet = 0;
        size_t pos1 = 0;
        while((pos1 = strSrc.find(strSub, pos1)) != string::npos)
        {
            if(strSrc[pos1+strSub.size()] == ch) // 判断该字符是否为ch分隔后的strSub串
            {
                string strSplit = strSrc.substr(0, pos1+strSub.size()+1);
                size_t pos2 = 0;
                while((pos2 = strSplit.find(ch, pos2)) != string::npos)
                {
                    ++pos2;
                    ++uiRet;
                }
                break;
            }
            ++pos1;
        }

        return uiRet;
    }


#ifdef __cplusplus
}
#endif
