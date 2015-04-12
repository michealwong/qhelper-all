/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       udp_dgram.h
 *  @brief      udp输入输出处理器头文件 
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

/*! \brief udp输入输出处理器 
 */
class UdpDgram : public Socket
{
public:

        /*! \brief 定义了最大超时时间 */
        enum { MAX_TIMEOUT_SEC = -1 };
        
public:

        /*! \brief 缺省构造函数
        */
        UdpDgram();


        /*! \brief 创建一个UdpDgram，并绑定到本地地址
        * \param[in] stLocalAddr 本地地址
        * \param[in] bReuseAddr  是否允许地址重用
        * \return 0:成功 -1:失败 
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的         
        */
        int Open(const INetAddr & stLocalAddr=INetAddr::ANY_ADDR, 
                bool bReuseAddr = true);


        /*! \brief 接收一个Udp数据报。退出条件(接收到数据报 | 超时)
        * \param[out] szBuffer     接收缓冲区
        * \param[in] iMaxLen       最大接收字节数
        * \param[out] stRemoteAddr 对端地址
        * \param[in] iTimeoutSec   超时秒数。iTimeout==MAX_TIMEOUT_SEC为一直阻塞，直到接收到数据报为止。
        * \param[in] iFlag         对应 recvfrom 的 flag 参数              
        * \return >=0:实际接收的字节数 -1:失败 
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的         
        */
        ssize_t RecvFrom(void * szBuffer, size_t iMaxLen, INetAddr & stRemoteAddr, 
                time_t iTimeoutSec=MAX_TIMEOUT_SEC, int iFlag=0);


        /*! \brief 发送一个Udp数据报 (非阻塞)
        * \param[in] szBuffer      发送缓冲区
        * \param[in] iLen       发送字节数
        * \param[in] stRemoteAddr  对端地址
        * \param[in] iFlag         对应 sendto 的 flag 参数              
        * \return >=0:实际发送的字节数 -1:失败 
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的         
        */
        ssize_t SendTo(const void * szBuffer, 
                size_t iLen, const INetAddr & stRemoteAddr, int iFlag=0);

protected:

        /*! \brief 阻塞接收一个Udp数据报。退出条件(接收到数据报 | 超时)
        * \param[out] szBuffer     接收缓冲区
        * \param[in] iMaxLen       最大接收字节数
        * \param[in] stRemoteAddr  对端地址
        * \param[in] iFlag         对应 recvfrom 的 flag 参数              
        * \return >=0:实际接收的字节数 -1:失败 
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的         
        */
        ssize_t BlockRecvFrom(void * szBuffer, 
                size_t iMaxLen, INetAddr & stRemoteAddr, int iFlag);        


        /*! \brief 非阻塞接收一个Udp数据报。退出条件(接收到数据报 | 超时)
        * \param[out] szBuffer     接收缓冲区
        * \param[in] iMaxLen       最大接收字节数
        * \param[in] stRemoteAddr  对端地址
        * \param[in] iTimeoutSec   超时秒数
        * \param[in] iFlag         对应 recvfrom 的 flag 参数              
        * \return >=0:实际接收的字节数 -1:失败 
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的         
        */
        ssize_t NonBlockRecvFrom(void * szBuffer, 
                size_t iMaxLen, INetAddr & stRemoteAddr, time_t iTimeoutSec, int iFlag);
};

}

#endif //___UDP_DGRAM_H
