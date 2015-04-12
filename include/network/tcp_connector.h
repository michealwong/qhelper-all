/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       tcp_connector.h
 *  @brief      tcp连接器头文件
 *  @version    1.0
 *  @author     Sunbird
 *  @date       2006/06/20
 */
//=============================================================================

#ifndef ___TCP_CONNECTOR_H
#define ___TCP_CONNECTOR_H

#include <sys/types.h>

#include "inet_addr.h"
#include "tcp_stream.h"


namespace OssBase
{

/*! \brief tcp连接器类 
 */
class TcpConnector
{
public:

        /*! \brief 定义了最大超时时间 */       
        enum { MAX_TIMEOUT_SEC = -1 };

        /*! \brief 定义了发送缓冲区的字节数 */       
        enum { DEFAULT_SEND_BUFF_SIZE = -1 };
        
public:
        
        /*! \brief 创建tcp连接，并返回新创建的TcpStream
        * \param[out] NewStream    新生成的本地TcpStream。如果NewStream没有Open,那此函数会调用NewStream.Open
        * \param[in] stRemoteAddr  对端地址
        * \param[in] iTimeoutSec   超时秒数
        * \param[in] iSendBuffSize 发送缓冲区字节数
        * \return 0:成功 -1:失败 
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */        
        int Connect(TcpStream & NewStream, const INetAddr & stRemoteAddr, 
                time_t iTimeoutSec, int iSendBuffSize=DEFAULT_SEND_BUFF_SIZE);

protected:

        /*! \brief 真正的创建tcp连接的调用
        * \param[out] NewStream    新生成的本地TcpStream。如果NewStream没有Open,那此函数会调用NewStream.Open
        * \param[in] stRemoteAddr  对端地址
        * \param[in] iTimeoutSec   超时秒数
        * \param[in] iSendBuffSize 发送缓冲区字节数
        * \return 0:成功 -1:失败 
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        int NonBlockConnect(TcpStream & NewStream, const INetAddr & stRemoteAddr, 
                time_t iTimeoutSec, int iSendBuffSize);
         
};

}

#endif //___TCP_CONNECTOR_H
