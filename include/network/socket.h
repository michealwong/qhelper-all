/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       socket.h
 *  @brief      socket����ͷ�ļ�
 *  @version    1.0
 *  @author     Sunbird
 *  @date       2006/06/13
 */
//=============================================================================

#ifndef ___SOCKET_H
#define ___SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <map>

#include "non_copyable.h"
#include "inet_addr.h"

/*! \namespace OssBase
 */
namespace OssBase
{

/*! \class Socket
 *  \brief socket���ࡣ������һ�鹫�÷���
 */
class Socket : public NonCopyable
{
public:

        /*! \brief ������Ϊ��ʼ����socketֵ */
        enum { INVALID_HANDLE = -1 };
        
public:

        /*! \brief �ر��׽ӿ�
        * \return 0:��ȷ -1:ʧ��
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������
        */        
        int Close();


        /*! \brief ��ȡ��ǰ�׽ӿڱ���inet��ַ
        * \param[out] stLocalAddr ����inet��ַ
        * \return 0:��ȷ -1:ʧ��
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������
        */
        int GetLocalAddr(INetAddr & stLocalAddr) const;


        /*! \brief �жϵ�ǰ�׽ӿ��Ƿ��ʼ���ɹ�
        * \return true:��ʼ���ɹ� false:Ϊ��ʼ�����ʼ��ʧ��
        */
        inline bool IsOpen() const
                { return _iHandle!=INVALID_HANDLE?true:false; }


        /*! \brief �жϵ�ǰ�׽ӿ��Ƿ��ʼ���ɹ�
        * \return true:��ʼ���ɹ� false:Ϊ��ʼ�����ʼ��ʧ��
        */
        inline operator bool() const
                { return IsOpen(); }


        /*! \brief �����׽ӿ����ԡ���������ɲο�setsockopt
        * \param[in] iLevel ���Լ���
        * \param[in] iOption ������
        * \param[in] pOptVal ����ֵָ��
        * \param[in] iOptLen ����ֵ�ֽ���
        * \return 0:��ȷ -1:ʧ��
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������
        */        
        int SetSockOption(int iLevel, int iOption, const void *pOptVal, socklen_t iOptLen);


        /*! \brief ��ȡ�׽ӿ����ԡ���������ɲο�getsockopt
        * \param[in] iLevel ���Լ���
        * \param[in] iOption ������
        * \param[out] pOptVal ����ֵָ��
        * \param[out] pOptLen ����ֵ�ֽ���
        * \return 0:��ȷ -1:ʧ��
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������
        */
        int GetSockOption(int iLevel, int iOption, void * pOptVal, socklen_t * pOptLen) const;

protected:

        /*! \brief ���캯��
        * \param[in] iType �׽ӿ����� SOCK_STREAM or SOCK_DGRAM or SOCK_RAW
        * \param[in] iFamily ��ַ��
        * \param[in] iProtocal ͬϵͳsocket()���õ�protocol����
        */             
        Socket(int iType, int iFamily=AF_INET, int iProtocal=0);


        /*! \brief ��������
        */     
        ~Socket();


        /*! \brief ��һ���Ѿ��򿪵��׽ӿ�����ʼ��
        * \param[in] iHandle �Ѿ��򿪵��׽ӿ�
        * \return 0:��ȷ -1:ʧ��
        * \throw OssException
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������
        */
        int Open(int iHandle);


        /*! \brief �ڱ���ָ����ַ�ϴ�һ���׽ӿ�
        * \param[in] stLocalAddr ���ص�ַ
        * \param[in] bReuseAddr ��ַ�Ƿ�����
        * \return 0:��ȷ -1:ʧ��
        * \throw OssException
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������
        */
        int Open(const INetAddr & stLocalAddr, bool bReuseAddr=true);


        /*! \brief ��������(������)
        * \param[in] bBlock �Ƿ�����
        * \return 0:��ȷ -1:ʧ��
        * \throw OssException
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������
        */
        int SetBlock(bool bBlock);


        /*! \brief ���ص�ǰ�׽ӿ�������
        * \return ��ǰ�׽ӿ�������
        */        
        inline int GetHandle() const
                { return _iHandle; }

private:

        /*! \brief �󶨱��ص�ַ
        * \param[in] stLocalAddr ���ص�ַ
        * \return 0:��ȷ -1:ʧ��
        * \throw OssException
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������
        */        
        int Bind(const INetAddr & stLocalAddr);
        
private:      

        /*! \brief �׽ӿ����� SOCK_STREAM or SOCK_DGRAM or SOCK_RAW */        
        int _iType;

        /*! \brief ��ַ�� */        
        int _iFamily;

        /*! \brief Э�� */        
        int _iProtocal;

        /*! \brief �׽ӿ������� */        
        int _iHandle;
};

}

#endif // ___SOCKET_H
