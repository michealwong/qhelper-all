/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       tcp_acceptor.h
 *  @brief      acceptorͷ�ļ� 
 *  @version    1.0
 *  @author     Sunbird
 *  @date       2006/06/19
 */
//=============================================================================

#ifndef ___TCP_ACCEPTOR_H
#define ___TCP_ACCEPTOR_H

#include <sys/types.h>
#include <sys/socket.h>

#include "inet_addr.h"
#include "socket.h"
#include "tcp_stream.h"

/*! \namespace OssBase
 */
namespace OssBase
{

/*! \class TcpAcceptor
 *  \brief tcp���ӽ�����
 */
class TcpAcceptor : public Socket
{
public:

        /*! \brief ȱʡbacklogֵ */
        enum { DEFAULT_BACKLOG = 5 };

        /*! \brief ���������ʱʱ�� */
        enum { MAX_TIMEOUT_SEC = -1 };

        /*! \brief ȱʡ���ջ������ֽ��� */
        enum { DEFAULT_RECV_BUFF_SIZE = -1 };

public:

        /*! \brief ȱʡ���캯�� 
        */        
        TcpAcceptor();


        /*! \brief ��һ��TcpAcceptor���󶨵����ص�ַ������ʼ����
        * \param[in] stLocalAddr    ���ص�ַ
        * \param[in] bReuseAddr     �Ƿ��ַ����
        * \param[in] iRecvBuffSize  ���ܻ�������С
        * \param[in] iBackLog       backlog��С
        * \return 0:�ɹ� -1:ʧ��
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������
        */
        int Open(const INetAddr & stLocalAddr, 
                bool bReuseAddr = true,
                int iRecvBuffSize = DEFAULT_RECV_BUFF_SIZE,
                int iBackLog = DEFAULT_BACKLOG);


        /*! \brief ����һ����������
        * \param[out] NewStream   ����һ���µ�TcpStream
        * \param[in] iTimeoutSec  ��ʱ����
        * \return 0:�ɹ� -1:ʧ�� 
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������         
        */
        int Accept(TcpStream & NewStream, 
                time_t iTimeoutSec=MAX_TIMEOUT_SEC);

protected:

        /*! \brief 
        * \param[in] iBackLog ͬϵͳ����listen��backlog����
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������        
        */
        int Listen(int iBackLog);

        /*! \brief �������ա�\n
        *       ������NonBlockAccept�ġ���Ⱥ�����⣬�ʺ϶����ʹ��
        * \param[in] NewStream ����һ���µ�TcpStream
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������        
        */
        int BlockAccept(TcpStream & NewStream);


        /*! \brief ���������ա�\n
        *       �ڶ���̵���ʱ������һ�����ӻᾪ�Ѷ��ͬʱ������select�Ͻ��̣���ɡ���Ⱥ��\n
        *       �����ʹ��ʱ ��ý�������<=cpu����
        * \param[in] NewStream ����һ���µ�TcpStream
        * \param[in] iTimeoutSec ��ʱ����         
        * \throw OssException        
        * \note ����ʱ�����쳣���Ƿ��ؽ��ֵ���ɿ����� OSS_NO_EXCEPTIONS ������        
        */
        int NonBlockAccept(TcpStream & NewStream, time_t iTimeoutSec);

};

}

#endif //___TCP_ACCEPTOR_H
