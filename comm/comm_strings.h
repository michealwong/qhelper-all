/*************************************************************
* 文件描述：字符串的常 用操作类
**************************************************************/
#ifndef _COMM_STRINGS_H_
#define _COMM_STRINGS_H_

#include <string>
#include <vector>
#include "map"
using namespace std;


#ifdef __cpluscplus
#define STRING_API extern
#else
#define STRING_API
#endif

// 字符串转换成任意数据类型
template<typename T>
void StrTo(const std::string& str, T& t);

// 任意数据类型转换成字符串
template<typename T>
std::string ToStr(const T& t);

#ifdef __cplusplus
extern "C"
{
#endif

// 字符串转换成无符号整形
STRING_API  unsigned int StrToUi(const char* str);

// 无符号整形转换成字符串
STRING_API  char*  itoa(unsigned int in_int);

// 字符串转换成整形
STRING_API  int StrToInt(const string& str);

    // 整形转换成字符串
STRING_API   std::string IntToStr(int n);

    // 字符串转换成长整形
STRING_API   long StrToLong(const string& str);

    // 长整形转换成字符串
STRING_API  std::string LongToStr(long n);

    // 字符串转换成64长整形
STRING_API  long long StrToLLong(const string& str);

    // 64位长整形转换成字符串
STRING_API  std::string LLongToStr(long long n);

    // 字符串转换成Float
STRING_API  float StrToFloat(const string& str);

    //Float转换成字符串
STRING_API  std::string FloatToStr(float n);

    // 字符串转换成Double
STRING_API  double StrToDouble(const string& str);

    //Double转换成字符串
STRING_API  std::string DoubleToStr(double n);

STRING_API char* itoa64(unsigned long long i);

STRING_API unsigned long long atoi64(const char* s);

    /**************************************************************************
    * 函数名：TrimLeft
    * 功能：去掉字符串左边的空格、Tab字符
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
STRING_API  void TrimLeft(std::string& str);

    /**************************************************************************
    * 函数名：TrimRight
    * 功能：去掉字符串右边的空格、Tab字符
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
STRING_API  void TrimRight(std::string& str);

    /**************************************************************************
    * 函数名：Trim
    * 功能：去掉字符串左、右边的空格、Tab字符
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
STRING_API  void Trim(std::string& str);

    /**************************************************************************
    * 函数名：ToUpper
    * 功能：将字符串全部转换成大写的形式
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
STRING_API  void ToUpper(std::string& str);

    /**************************************************************************
    * 函数名：ToLower
    * 功能：将字符串全部转换成小写的形式
    * 参数：
    *              参数名       参数类型        传入方式    参数说明
    *              str                     string&                      IN/OUT                待处理的字符串
    ***************************************************************************/
STRING_API  void ToLower(std::string& str);

    /* 格式化C字符串并输出C++字符串
    * \param[in] szFmt 待格式化的C字符串
    * \return 格式化好的C++字符串
    */
STRING_API std::string Format(const char * szFmt, ...);

    /*从sSrc中取出sBegin＆sEnd之内的string
           * \param[in] sSrc           原始字符串
           * \param[in] sBegin        前分隔符
           * \param[in] sEnd          后分隔符
           * \return sBegin＆sEnd之内的string
           * \note 例如: \n
           *       input   sSrc="name: vvv;" sBegin="name: " sEnd=";" \n
           *       return  string("vvv");
           */
STRING_API std::string Inner(const std::string & sSrc,const std::string & sBegin, const std::string & sEnd);

    /*!  从sSrc中取出最多nSize个字符，并检查中文完整性
           * \param[in] sSrc         原始字符串
           * \param[in] nSize        字节数
           * \return 中文完整的字符串
           */
STRING_API std::string CutChinese(const std::string & sSrc, int nSize);

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
STRING_API  bool SplitByStr(std::string& src, const string& delim, std::vector<std::string>& dst);

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
STRING_API  bool Split(std::string& src, const char* delim, unsigned int num, std::vector<std::string>& dst);

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
STRING_API  bool SplitToMap(std::string& src, std::map<string,string>& dst, string delim="&=", unsigned int num=2);

    /**************************************************************************
    * 函数名：MapJoin
    * 功能：把两个map结构合成在一起，数据存放在第一个map里
    * 参数：
    *              参数名       参数类型             传入方式    参数说明
    *              first                     map<string,string>&             IN                
    *              second                map<string,string>&             IN                               
    * 返回值：true or false
    ************************************************************************** */
STRING_API  bool MapJoin(map<string,string>& first, map<string,string>& second);

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
STRING_API  bool Join(const vector<string>& vecSrc, char ch, string& strDst);

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
STRING_API  bool Replace(string& strSrc, const string& strOld, const string& strNew);

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
STRING_API void ReplaceString(string &strOperateContent, string searchString , string::size_type pos , string replaceString );

    /**************************************************************************
    * 函数名：Remove
    * 功能：删除串中所有的指定子串
    * 参数：
    *              参数名                 参数说明
    *              strSrc                         待处理的字符
    *              strSub                         被删除的字符
    * 返回值：bool
    ***************************************************************************/
STRING_API  bool Remove(string& strSrc, const string& strSub);

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
STRING_API  unsigned int MatchAfterSplit(const string& strSrc, const string& strSub, char ch);


#ifdef __cplusplus
}
#endif

#endif

