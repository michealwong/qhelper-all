/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       inet_addr.h
 *  @brief      internet地址类头文件
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
 * \brief internet 地址类
 */
class INetAddr
{
public:

        /*! \brief 任意地址 */
        static const INetAddr ANY_ADDR;

public:

        /*!
        * \brief 缺省构造函数
        * \param[in] uPort 端口号
        */
        INetAddr(unsigned short uPort=0)
                { Init("0.0.0.0", uPort); }

        /*!
        * \brief 构造函数
        * \param[in] sIP IP
        * \param[in] uPort 端口号
        */        
        INetAddr(const std::string & sIP, unsigned short uPort)
                { Init(sIP, uPort); }

        /*!
        * \brief 构造函数
        * \param[in] stSockAddr sockaddr_in结构体
        */        
        INetAddr(const struct sockaddr_in & stSockAddr)
                : _stSockAddr(stSockAddr)
                {}

        /*! \brief 返回IP
        * \return IP
        */
        inline std::string GetIP() const
                { char szIP[16]; return inet_ntop(AF_INET, &_stSockAddr.sin_addr, szIP, sizeof(szIP))==NULL?"":szIP; }

        /*! \brief 返回端口号
        * \return 端口号
        */
        inline unsigned short GetPort() const
                { return ntohs(_stSockAddr.sin_port); }

        /*! \brief 返回sockaddr的指针
        * \return sockaddr的指针
        */
        inline const struct sockaddr * GetSockAddrPtr() const
                { return (struct sockaddr *)&_stSockAddr; }

        /*! \brief 返回sockaddr_in的大小
        * \return sockaddr_in的大小
        */
        inline size_t GetSockAddrSize() const
                { return sizeof(_stSockAddr); }

protected:

        /*! \brief 初始化函数
        * \param[in] sIP IP
        * \param[in] uPort 端口
        */        
        void Init(const std::string & sIP, unsigned short uPort);

private:

        /*! \brief inet地址 */
        struct sockaddr_in _stSockAddr;

};


/*!
 * \brief 重载了operator<<
 * \param[in] out 输出流对象
 * \param[in] cINetAddr INet地址类
 * \return: 输出流对象的引用
 */     
std::ostream & operator<< (std::ostream & out, const INetAddr & cINetAddr);


}

#endif // ___INET_ADDR_H
