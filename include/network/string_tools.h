/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       string_tools.h
 *  @brief      字符串工具集头文件
 *  @version    1.0
 *  @author     Sunbird
 *  @date       2006/06/29
 */
//=============================================================================

#ifndef ___STRING_TOOLS_H
#define ___STRING_TOOLS_H

#include <string>
#include <vector>

namespace OssBase
{

/*! \brief 字符串工具类
 */
class StringTools
{
public:
        enum 
        {
                /*! \brief 最大分割数
             *  \sa Split
             */
                MAX_SPLIT_NUM = 0 
        };

        typedef std::vector<std::string> StringArray;

public:

        /*! \brief 替换字符串中的相应字符
        * \param[in,out] sSrc      字符串
        * \param[in] sSrcDelim     需要替换的字符串
        * \param[in] sDestDelim    欲替换的目标字符串
        */
        static void Replace(std::string & sSrc, const std::string & sSrcDelim, const std::string &sDestDelim);


        /*! \brief 替换字符串中的相应字符
        * \param[in,out] sSrc      字符串
        * \param[in] sSrcDelim     需要替换的字符串
        * \param[in] szDestDelim    欲替换的目标字符串
        */
        static void Replace(std::string & sSrc, const std::string & sSrcDelim, const char * szDestDelim);


        /*! \brief 替换字符串中的相应字符。 当发现sSrcDelim时，将sSrcDelim传给(仿)函数foo，将foo返回的值做为替换的值替换到sSrc中
        * \param[in,out] sSrc      字符串
        * \param[in] sSrcDelim     需要替换的字符串
        * \param[in] foo           类型为 T foo(const std::string & sSrcDelim) 的函数或者仿函数
        */
        template <typename F>
        static void Replace(std::string & sSrc, const std::string & sSrcDelim, F foo);
        

        /*! \brief 根据delim分割字符串，将分割后的字符串做为 vector返回
        * \param[in] src           要分割字符串
        * \param[in] delim         分隔符字符串
        * \param[out] dest         被分割后的字符串数组
        * \param[in] split_num     分割数
        * \note  其中split_num指定要分成几份。如果得到的字符串数量小于split_num，补填string("")。
        *        如果多余，多余的字符串将不再分割。\n
        *       例如: \n
        *       input   src="&&abc&de&&fgh&&" delim="&&" \n
        *       output  desc[0]="abc&de" desc[1]="fgh"
        */
        static void Split(const std::string & src, const std::string & delim, StringArray & dest, int split_num=MAX_SPLIT_NUM);


        /*! \brief 根据delim分割字符串，将分割的字符串做为参数传给函数foo，并将foo的返回值做为vector返回
        * \param[in] src           要分割字符串
        * \param[in] delim         分隔符字符串
        * \param[out] dest         被分割后的字符串数组
        * \param[in] foo           类型为 T foo(const std::string &) 的函数或者仿函数
        * \param[in] split_num     分割数
        * \note  其中split_num指定要分成几份。如果得到的字符串数量小于split_num，补填string("")。
        *        如果多余，多余的字符串将不再分割。\n
        *       例如: \n
        *       input   src="&&abc&de&&fgh&&" delim="&&" \n
        *       output  desc[0]="abc&de" desc[1]="fgh"
        */
        template <typename T, typename F>
        static void Split(const std::string& src, const std::string& delim, std::vector<T> & dest, F foo, int split_num=MAX_SPLIT_NUM);


        /*! \brief 从sSrc中取出sBegin＆sEnd之内的string
        * \param[in] sSrc           原始字符串
        * \param[in] sBegin        前分隔符
        * \param[in] sEnd          后分隔符
        * \return sBegin＆sEnd之内的string
        * \note 例如: \n
        *       input   sSrc="name: vvv;" sBegin="name: " sEnd=";" \n
        *       return  string("vvv");
        */
        static std::string Inner(const std::string & sSrc, const std::string & sBegin, const std::string & sEnd);


        /*! \brief 从sSrc中取出最多nSize个字符，并检查中文完整性
        * \param[in] sSrc         原始字符串
        * \param[in] nSize        字节数
        * \return 中文完整的字符串
        */
        static std::string CutChinese(const std::string & sSrc, int nSize);


        /*! \brief 将字符串中的英文字母转为大写
        * \param[in] sSrc           原始字符串
        * \return 全大写字符串
        */
        static std::string ToUpper(const std::string & sSrc);


        /*! \brief 将字符串中的英文字母转为小写
        * \param[in] sSrc           原始字符串
        * \return 全小写字符串
        */
        static std::string ToLower(const std::string & sSrc);


        /*! \brief 格式化C字符串并输出C++字符串
        * \param[in] szFmt 待格式化的C字符串
        * \return 格式化好的C++字符串
        */
        static std::string Format(const char * szFmt, ...);


        /*! \brief 将字符左边的多余字符除去
        * \param[in] ss 待整理的字符串
        * \param[in] pf 仿函数指针
        * \return 处理后的字符串
        */
        static std::string LeftTrim(const std::string & ss, int (*pf)(int)=std::isspace);


        /*! \brief 将字符右边的多余字符除去
        * \param[in] ss 待整理的字符串
        * \param[in] pf 仿函数指针
        * \return 处理后的字符串
        */
        static std::string RightTrim(const std::string &ss, int (*pf)(int)=std::isspace);


        /*! \brief 将字符左右两边的多余字符除去
        * \param[in] ss 待整理的字符串
        * \param[in] pf 仿函数指针
        * \return 处理后的字符串
        */
        static std::string Trim(const std::string &ss, int (*pf)(int)=std::isspace)
        {
                return RightTrim(LeftTrim(ss, pf), pf);
        }
        
};


template <typename F>
void StringTools::Replace(std::string & sSrc, const std::string & sSrcDelim, F foo)
{
        std::string::size_type pos = 0;
        std::string::size_type srclen = sSrcDelim.size();
        while( (pos = sSrc.find(sSrcDelim, pos)) != std::string::npos)
        {
                std::string sDestDelim = foo(sSrcDelim);
                sSrc.replace(pos, srclen, sDestDelim);
                pos += sDestDelim.size();
        }
        return;
}

template <typename T, typename F>
void StringTools::Split(const std::string& src, const std::string& delim, std::vector<T> & dest, F foo, int split_num)
{
        if ( split_num <= 0 ) {
                std::string::size_type idx, idx1;
                
                for( idx=0; idx<src.size(); idx=idx1+delim.size() ) {
                        idx1 = src.find(delim, idx);
                        if (idx == idx1)  {	
                                continue;   //如果是分隔符，则略过
                        }
                        if (idx1 == std::string::npos) {	
                                idx1 = src.size();  //如果没有找到,则取剩余的所有字符
                        }
                        dest.push_back(foo(src.substr(idx, idx1-idx)));
                }
        }
        else {
                std::string::size_type idx, idx1;
                for( idx=0; idx<src.size(); idx=idx1+delim.size() ) {
                        if ( split_num == 1 ) {
                                break;
                        }
                        idx1 = src.find(delim, idx);
                        if (idx == idx1) {	
                                continue;   //如果是分隔符，则略过
                        }
                        if (idx1 == std::string::npos) {	
                                idx1 = src.size();  //如果没有找到,则取剩余的所有字符
                        }

                        dest.push_back(foo(src.substr(idx, idx1-idx)));
                        --split_num;
                }
                if ( idx < src.size() ) {
                        dest.push_back(foo(src.substr(idx)));
                        --split_num;
                }
                for ( ;split_num>0; --split_num) {
                        std::string s;
                        dest.push_back(foo(s));
                }
        }
        return;                
}


};

#endif //___STRING_TOOLS_H
