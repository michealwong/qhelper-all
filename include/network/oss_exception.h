/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       oss_exception.h
 *  @brief      Oss���쳣����ͷ�ļ�
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
 *  \brief Oss���쳣���ࡣ����̳���std::exception
 */
class OssException : public std::exception
{
public:
        /*! \brief ȱʡ������Ϣ */  
        static const std::string DEFAULT_ERROR_MSG;

public:

        /*! \brief ���캯��
        * \param[in] szFile �׳��쳣���ļ���
        * \param[in] iLine �׳��쳣������
        * \param[in] sErrMsg �쳣��Ϣ
        * \param[in] iErrno �쳣������
        */
        OssException(const char * szFile, int iLine, 
                const std::string & sErrMsg = DEFAULT_ERROR_MSG, int iErrno = -1);

        /*! \brief ���캯��
        * \param[in] sFile �׳��쳣���ļ���
        * \param[in] iLine �׳��쳣������
        * \param[in] sErrMsg �쳣��Ϣ
        * \param[in] iErrno �쳣������
        */
        OssException(const std::string & sFile, int iLine, 
                const std::string & sErrMsg = DEFAULT_ERROR_MSG, int iErrno = -1);

        /*! \brief ��������
        */
        virtual ~OssException() throw();

        /*! \brief ���ش�����Ϣ
        * \return ������Ϣ
        */
        inline const std::string & GetErrMsg() const
                { return _sErrMsg; }

        /*! \brief ���ش�����
        * \return ������
        */        
        inline int GetErrno() const
                { return _iErrno; }

        /*! \brief ���ظ�ʽ���õĴ�����Ϣ
        * \return ��ʽ���õĴ�����Ϣ
        */          
        virtual const char * what() const throw();

private:

        /*! \brief �׳��쳣���ļ��� */  
        std::string _sFile;

        /*! \brief �׳��쳣������ */  
        int _iLine;

        /*! \brief �쳣��Ϣ */  
        std::string _sErrMsg;

        /*! \brief �쳣������ */  
        int _iErrno;

};

} //namespace OssBase

#endif  //___OSS_EXCEPTION_H
