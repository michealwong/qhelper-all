/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       inet_addr.h
 *  @brief      internet��ַ��ͷ�ļ�
 *  @version    1.0
 *  @author     Sunbird
 *  @date       2006/06/13
 */
//=============================================================================

#ifndef ___INET_ADDR_H
#define ___INET_ADDR_H

#include <string>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*! \namespace OssBase
 */
namespace OssBase
{

/*! \class INetAddr
 * \brief internet ��ַ��
 */
class INetAddr
{
public:

        /*! \brief �����ַ */
        static const INetAddr ANY_ADDR;

public:

        /*!
        * \brief ȱʡ���캯��
        * \param[in] uPort �˿ں�
        */
        INetAddr(unsigned short uPort=0)
                { Init("0.0.0.0", uPort); }

        /*!
        * \brief ���캯��
        * \param[in] sIP IP
        * \param[in] uPort �˿ں�
        */        
        INetAddr(const std::string & sIP, unsigned short uPort)
                { Init(sIP, uPort); }

        /*!
        * \brief ���캯��
        * \param[in] stSockAddr sockaddr_in�ṹ��
        */        
        INetAddr(const struct sockaddr_in & stSockAddr)
                : _stSockAddr(stSockAddr)
                {}

        /*! \brief ����IP
        * \return IP
        */
        inline std::string GetIP() const
                { char szIP[16]; return inet_ntop(AF_INET, &_stSockAddr.sin_addr, szIP, sizeof(szIP))==NULL?"":szIP; }

        /*! \brief ���ض˿ں�
        * \return �˿ں�
        */
        inline unsigned short GetPort() const
                { return ntohs(_stSockAddr.sin_port); }

        /*! \brief ����sockaddr��ָ��
        * \return sockaddr��ָ��
        */
        inline const struct sockaddr * GetSockAddrPtr() const
                { return (struct sockaddr *)&_stSockAddr; }

        /*! \brief ����sockaddr_in�Ĵ�С
        * \return sockaddr_in�Ĵ�С
        */
        inline size_t GetSockAddrSize() const
                { return sizeof(_stSockAddr); }

protected:

        /*! \brief ��ʼ������
        * \param[in] sIP IP
        * \param[in] uPort �˿�
        */        
        void Init(const std::string & sIP, unsigned short uPort);

private:

        /*! \brief inet��ַ */
        struct sockaddr_in _stSockAddr;

};


/*!
 * \brief ������operator<<
 * \param[in] out ���������
 * \param[in] cINetAddr INet��ַ��
 * \return: ��������������
 */     
std::ostream & operator<< (std::ostream & out, const INetAddr & cINetAddr);


}

#endif // ___INET_ADDR_H
