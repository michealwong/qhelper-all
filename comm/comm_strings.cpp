/*************************************************************
* �ļ��������ַ����ĳ� �ò�����
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

// �ַ���ת����������������
template<typename T>
void StrTo(const std::string& str, T& t)
{
    std::istringstream s(str);
    s >> t;
}

// ������������ת�����ַ���
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

	// �ַ���ת�����޷�������
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

    // �ַ���ת��������
     int StrToInt(const string& str)
    {
        int n = 0;
        StrTo(str, n);
        return n;
    }

    // ����ת�����ַ���
     std::string IntToStr(int n)
    {
        return ToStr(n);
    }

    // �ַ���ת���ɳ�����
     long StrToLong(const string& str)
    {
        long n = 0;
        StrTo(str, n);
        return n;
    }

    // ������ת�����ַ���
     std::string LongToStr(long n)
    {
        return ToStr(n);
    }

    // �ַ���ת����64������
     long long StrToLLong(const string& str)
    {
        long long n = 0;
        StrTo(str, n);
        return n;
    }

    // 64λ������ת�����ַ���
     std::string LLongToStr(long long n)
    {
        return ToStr(n);
    }

    // �ַ���ת����Float
     float StrToFloat(const string& str)
    {
        float n = 0;
        StrTo(str, n);
        return n;
    }

    //Floatת�����ַ���
     std::string FloatToStr(float n)
    {
        return ToStr(n);
    }

    // �ַ���ת����Double
     double StrToDouble(const string& str)
    {
        double n = 0;
        StrTo(str, n);
        return n;
    }

    //Doubleת�����ַ���
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
    * ��������TrimLeft
    * ���ܣ�ȥ���ַ�����ߵĿո�Tab�ַ�
    * ������
    *              ������       ��������        ���뷽ʽ    ����˵��
    *              str                     string&                      IN/OUT                ��������ַ���
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
    * ��������TrimRight
    * ���ܣ�ȥ���ַ����ұߵĿո�Tab�ַ�
    * ������
    *              ������       ��������        ���뷽ʽ    ����˵��
    *              str                     string&                      IN/OUT                ��������ַ���
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
    * ��������Trim
    * ���ܣ�ȥ���ַ������ұߵĿո�Tab�ַ�
    * ������
    *              ������       ��������        ���뷽ʽ    ����˵��
    *              str                     string&                      IN/OUT                ��������ַ���
    ***************************************************************************/
     void Trim(std::string& str)
    {
        TrimLeft(str);
        TrimRight(str);
    }


    /**************************************************************************
    * ��������ToUpper
    * ���ܣ����ַ���ȫ��ת���ɴ�д����ʽ
    * ������
    *              ������       ��������        ���뷽ʽ    ����˵��
    *              str                     string&                      IN/OUT                ��������ַ���
    ***************************************************************************/
     void ToUpper(std::string& str)
    {
        std::string strBak;
        strBak.reserve(str.size());
        transform(str.begin(), str.end(), back_inserter(strBak), static_cast<int (*)(int)>(toupper));
        str = strBak;
    }


    /**************************************************************************
    * ��������ToLower
    * ���ܣ����ַ���ȫ��ת����Сд����ʽ
    * ������
    *              ������       ��������        ���뷽ʽ    ����˵��
    *              str                     string&                      IN/OUT                ��������ַ���
    ***************************************************************************/
     void ToLower(std::string& str)
    {
        std::string strBak;
        strBak.reserve(str.size());
        transform(str.begin(), str.end(), back_inserter(strBak), static_cast<int (*)(int)>(tolower));
        str = strBak;
    }

    /* ��ʽ��C�ַ��������C++�ַ���
    * \param[in] szFmt ����ʽ����C�ַ���
    * \return ��ʽ���õ�C++�ַ���
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


    /*��sSrc��ȡ��sBegin��sEnd֮�ڵ�string
           * \param[in] sSrc           ԭʼ�ַ���
           * \param[in] sBegin        ǰ�ָ���
           * \param[in] sEnd          ��ָ���
           * \return sBegin��sEnd֮�ڵ�string
           * \note ����: \n
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


    /*!  ��sSrc��ȡ�����nSize���ַ������������������
           * \param[in] sSrc         ԭʼ�ַ���
           * \param[in] nSize        �ֽ���
           * \return �����������ַ���
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
    * ��������SplitByStr
    * ���ܣ��ַ����ָ�
    * ������
    *              ������       ��������        ���뷽ʽ    ����˵��
    *              str                     const string&             IN                       ��������ַ���
    *              delim                 string               IN                       �ָ�����
    *              dst                    vector<string>           IN/OUT              �ָ���Ľ��
    * ����ֵ��true or false
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
    * ��������Split
    * ���ܣ��ַ����ָ�
    * ������
    *              ������       ��������        ���뷽ʽ    ����˵��
    *              str                     const string&             IN                       ��������ַ���
    *              delim                 const char*               IN                       �ָ�����
    *              num                  unsigned int              IN                       �ָ�������
    *              dst                    vector<string>           IN/OUT              �ָ���Ľ��
    * ����ֵ��true or false
    ***************************************************************************/
     bool Split(std::string& src, const char* delim, unsigned int num, std::vector<std::string>& dst)
    {
        size_t pos1 = 0, pos2 = 0;
        if(NULL == delim || 0 == num)
            return false;

        dst.clear();
        Trim(src);

        //���һ���ַ�����Ƿָ�����ɾ��
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
    * ��������SplitToMap
    * ���ܣ��ַ����ָ������һ��map�ṹ���أ�Ĭ�Ϸָ���Ϊ&,=
    * ������
    *              ������       ��������        ���뷽ʽ    ����˵��
    *              str                     const string&             IN                       ��������ַ���
    *              delim                 cstring               IN                               �ָ�����,Ĭ�Ϸָ���Ϊ&,=
    *              num                  unsigned int              IN                       �ָ�������,Ĭ��Ϊ2��Ŀǰ����Ϊ2���ָ���
    *              dst                    map<string,string>           IN/OUT              �ָ���Ľ��
    * ����ֵ��true or false
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
    * ��������MapJoin
    * ���ܣ�������map�ṹ�ϳ���һ�����ݴ���ڵ�һ��map��
    * ������
    *              ������       ��������             ���뷽ʽ    ����˵��
    *              first                     map<string,string>&             IN                
    *              second                map<string,string>&             IN                               
    * ����ֵ��true or false
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
    * ��������Join
    * ���ܣ��ַ����ϳ�
    * ������
    *              ������       ��������                   ���뷽ʽ    ����˵��
    *              vecSrc               const vector<string>&             IN                       ��������ַ���
    *              ch                      char                                      IN                       �ָ�����
    *              strDst                string&                                     IN/OUT              �ָ���Ľ��
    * ����ֵ��true or false
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
        strDst = strDst.substr(0, strDst.size()-1);  //ȥ�����һ��ch

        return true;
    }

    /**************************************************************************
    * ��������Replace
    * ���ܣ������µ��Ӵ��滻ԭ��������ָ���Ĵ�
    * ������
    *              ������       ��������                   ���뷽ʽ    ����˵��
    *              strSrc               string&                                  IN                       ��������ַ���
    *              strOld               const string&                        IN                       ���滻���ַ�
    *              strNew              const string&                       IN                       �滻���ַ�
    * ����ֵ��bool
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

    /*ȥ��һЩ�����������ַ����滻Ϊ��*/
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
    * ��������ReplaceString
    * ���ܣ���ָ��λ�ÿ�ʼ�������µ��Ӵ��滻ԭ��������ָ���Ĵ�
    * ������
    *              ������                      ��������                  ����˵��
    *              strOperateContent          string&                              ��������ַ���
    *              searchString                    string                                 ���滻���ַ�
    *              pos                                  string::size_type               ��ʼλ��
    *              replaceString                   string                                 �滻���ַ�
    * ����ֵ��bool
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
    * ��������Remove
    * ���ܣ�ɾ���������е�ָ���Ӵ�
    * ������
    *              ������                 ����˵��
    *              strSrc                         ��������ַ�
    *              strSub                         ��ɾ�����ַ�
    * ����ֵ��bool
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
    * ��������MatchAfterSplit
    * ���ܣ���ָ���ַ��ָ����ģʽƥ��
    * ������
    *              ������         ����˵��
    *              strSrc                 ��������ַ���
    *              strSub                �����ҵ��ַ���
    *              ch                       �ָ���
    * ����ֵ��int
    * ˵��: ����string str1 = "1102|2|11|3", str2 = "11",��int n=MatchAfterSplit(str1, str2, '|')
    *                �󣬷��ص�nӦΪ3,����'|'�ָ���ĵ������Ӵ�����û��
                      �ҵ����򷵻�0
    ***************************************************************************/
     unsigned int MatchAfterSplit(const string& strSrc, const string& strSub, char ch)
    {
        unsigned int uiRet = 0;
        size_t pos1 = 0;
        while((pos1 = strSrc.find(strSub, pos1)) != string::npos)
        {
            if(strSrc[pos1+strSub.size()] == ch) // �жϸ��ַ��Ƿ�Ϊch�ָ����strSub��
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
