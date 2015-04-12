/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       udp_dgram.h
 *  @brief      udp�������������ͷ�ļ� 
 *  @version    1.0
 *  @author     Sunbird
 *  @date       2006/06/20
 */
//=============================================================================

#ifndef ___UDP_DGRAM_H
#define ___UDP_DGRAM_H

#include <sys/types.h>

#include "inet_addr.h"
#include "socket.h"

namespace OssBase
{

/*! \brief udp������������� 
 */
class UdpDgram : public Socket
{
public:

        /*! \brief ���������ʱʱ�� */
        enum { MAX_TIMEOUT_SEC = -1 };
        
public:

        /*! \brief ȱʡ���캯��
        */
        UdpDgram();


        /*! \brief ����һ��UdpDgram�����󶨵����ص�ַ
        * \param[in] stLocalAddr ���ص�ַ
        * \param[in] bReuseAddr  �Ƿ������ַ����
        * \return 0:�ɹ� -1:ʧ�� 
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������         
        */
        int Open(const INetAddr & stLocalAddr=INetAddr::ANY_ADDR, 
                bool bReuseAddr = true);


        /*! \brief ����һ��Udp���ݱ����˳�����(���յ����ݱ� | ��ʱ)
        * \param[out] szBuffer     ���ջ�����
        * \param[in] iMaxLen       �������ֽ���
        * \param[out] stRemoteAddr �Զ˵�ַ
        * \param[in] iTimeoutSec   ��ʱ������iTimeout==MAX_TIMEOUT_SECΪһֱ������ֱ�����յ����ݱ�Ϊֹ��
        * \param[in] iFlag         ��Ӧ recvfrom �� flag ����              
        * \return >=0:ʵ�ʽ��յ��ֽ��� -1:ʧ�� 
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������         
        */
        ssize_t RecvFrom(void * szBuffer, size_t iMaxLen, INetAddr & stRemoteAddr, 
                time_t iTimeoutSec=MAX_TIMEOUT_SEC, int iFlag=0);


        /*! \brief ����һ��Udp���ݱ� (������)
        * \param[in] szBuffer      ���ͻ�����
        * \param[in] iLen       �����ֽ���
        * \param[in] stRemoteAddr  �Զ˵�ַ
        * \param[in] iFlag         ��Ӧ sendto �� flag ����              
        * \return >=0:ʵ�ʷ��͵��ֽ��� -1:ʧ�� 
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������         
        */
        ssize_t SendTo(const void * szBuffer, 
                size_t iLen, const INetAddr & stRemoteAddr, int iFlag=0);

protected:

        /*! \brief ��������һ��Udp���ݱ����˳�����(���յ����ݱ� | ��ʱ)
        * \param[out] szBuffer     ���ջ�����
        * \param[in] iMaxLen       �������ֽ���
        * \param[in] stRemoteAddr  �Զ˵�ַ
        * \param[in] iFlag         ��Ӧ recvfrom �� flag ����              
        * \return >=0:ʵ�ʽ��յ��ֽ��� -1:ʧ�� 
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������         
        */
        ssize_t BlockRecvFrom(void * szBuffer, 
                size_t iMaxLen, INetAddr & stRemoteAddr, int iFlag);        


        /*! \brief ����������һ��Udp���ݱ����˳�����(���յ����ݱ� | ��ʱ)
        * \param[out] szBuffer     ���ջ�����
        * \param[in] iMaxLen       �������ֽ���
        * \param[in] stRemoteAddr  �Զ˵�ַ
        * \param[in] iTimeoutSec   ��ʱ����
        * \param[in] iFlag         ��Ӧ recvfrom �� flag ����              
        * \return >=0:ʵ�ʽ��յ��ֽ��� -1:ʧ�� 
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������         
        */
        ssize_t NonBlockRecvFrom(void * szBuffer, 
                size_t iMaxLen, INetAddr & stRemoteAddr, time_t iTimeoutSec, int iFlag);
};

}

#endif //___UDP_DGRAM_H
