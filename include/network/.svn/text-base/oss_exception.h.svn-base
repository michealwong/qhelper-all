/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       oss_exception.h
 *  @brief      Oss库异常基类头文件
 *  @version    1.0
 *  @author     Sunbird
 *  @date       2006/08/08
 */
//=============================================================================

#ifndef ___OSS_EXCEPTION_H
#define ___OSS_EXCEPTION_H

#include <string>
#include <exception>


/*! \namespace OssBase
 */
namespace OssBase
{

/*! \class OssException
 *  \brief Oss库异常基类。本类继承自std::exception
 */
class OssException : public std::exception
{
public:
        /*! \brief 缺省错误信息 */  
        static const std::string DEFAULT_ERROR_MSG;

public:

        /*! \brief 构造函数
        * \param[in] szFile 抛出异常的文件名
        * \param[in] iLine 抛出异常的行数
        * \param[in] sErrMsg 异常信息
        * \param[in] iErrno 异常错误码
        */
        OssException(const char * szFile, int iLine, 
                const std::string & sErrMsg = DEFAULT_ERROR_MSG, int iErrno = -1);

        /*! \brief 构造函数
        * \param[in] sFile 抛出异常的文件名
        * \param[in] iLine 抛出异常的行数
        * \param[in] sErrMsg 异常信息
        * \param[in] iErrno 异常错误码
        */
        OssException(const std::string & sFile, int iLine, 
                const std::string & sErrMsg = DEFAULT_ERROR_MSG, int iErrno = -1);

        /*! \brief 析够函数
        */
        virtual ~OssException() throw();

        /*! \brief 返回错误信息
        * \return 错误信息
        */
        inline const std::string & GetErrMsg() const
                { return _sErrMsg; }

        /*! \brief 返回错误码
        * \return 错误码
        */        
        inline int GetErrno() const
                { return _iErrno; }

        /*! \brief 返回格式化好的错误信息
        * \return 格式化好的错误信息
        */          
        virtual const char * what() const throw();

private:

        /*! \brief 抛出异常的文件名 */  
        std::string _sFile;

        /*! \brief 抛出异常的行数 */  
        int _iLine;

        /*! \brief 异常信息 */  
        std::string _sErrMsg;

        /*! \brief 异常错误码 */  
        int _iErrno;

};

} //namespace OssBase

#endif  //___OSS_EXCEPTION_H
