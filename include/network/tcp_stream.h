/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       tcp_stream.h
 *  @brief      tcp流输入输出处理器头文件 
 *  @version    1.0
 *  @author     Sunbird
 *  @date       2006/06/19
 */
//=============================================================================

#ifndef ___TCP_STREAM_H
#define ___TCP_STREAM_H

#include <sys/types.h>

#include "inet_addr.h"
#include "socket.h"

namespace OssBase
{

class TcpAcceptor;
class TcpConnector;

/*! \brief tcp流输入输出处理器
 */
class TcpStream : public Socket
{
        friend class TcpAcceptor;
        friend class TcpConnector;

public:

        /*! \brief 定义了最大超时时间 */
        enum { MAX_TIMEOUT_SEC = -1 };
        
public:

        /*! \brief 缺省构造函数 */
        TcpStream();


        /*! \brief 创建一个TcpStream，并绑定到本地地址。
        * \param[in] stLocalAddr 本地地址
        * \param[in] bReuseAddr  是否允许地址重用
        * \return 0:成功 -1:失败 
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的     
        */
        int Open(const INetAddr & stLocalAddr=INetAddr::ANY_ADDR, 
                bool bReuseAddr = true);


        /*! \brief 取得对端inet地址
        * \param[out] stRomoteAddr 对方inet地址
        * \return 0:成功 -1:失败
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的     
        */
        int GetRemoteAddr(INetAddr & stRomoteAddr) const;


        /*! \brief 发送n字节信息。退出条件(成功发送iLen个字节 | 超时)
        * \param[in] szBuffer 发送缓冲区
        * \param[in] iLen     待发送字节数
        * \param[in] iTimeoutSec 超时秒数。iTimeoutSec==MAX_TIMEOUT_SEC为一直阻塞，直到发完n字节为止
        * \return >=0-实际发送的字节数 -1:失败 
        * \throw OssException
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        ssize_t SendN(const void * szBuffer, size_t iLen, time_t iTimeoutSec=MAX_TIMEOUT_SEC);


        /*! \brief 接收信息。退出条件(接收到字节 | 超时)
        * \param[out] szBuffer 接收缓冲区
        * \param[in] iMaxLen     最大接收字节数
        * \param[in] iTimeoutSec 超时秒数。iTimeoutSec==MAX_TIMEOUT_SEC为一直阻塞，直到接收到数据为止
        * \return >=0:实际接收的字节数 -1:失败 
        * \throw OssException
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        ssize_t Recv(void * szBuffer, size_t iMaxLen, time_t iTimeoutSec=MAX_TIMEOUT_SEC);


        /*! \brief 接收n字节信息。退出条件(成功接收iLen个字节 | 超时)
        * \param[out] szBuffer 接收缓冲区
        * \param[in] iLen     待接收字节数
        * \param[in] iTimeoutSec 超时秒数。iTimeoutSec==MAX_TIMEOUT_SEC为一直阻塞，直到接收完n字为止
        * \return >=0:实际接收的字节数 -1:失败 
        * \throw OssException
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        ssize_t RecvN(void * szBuffer, size_t iLen, time_t iTimeoutSec=MAX_TIMEOUT_SEC);


        /*! \brief 接收一行信息('\\n')。退出条件(成功接收一行 | 缓冲区满 | 超时)
        * \param[out] szBuffer 接收缓冲区,返回时包括\\n。如果iMaxLen字节内没有\\n，那就返回已接收的字节
        * \param[in] iMaxLen  最大接收字节数
        * \param[in] iTimeoutSec 超时秒数。iTimeoutSec==MAX_TIMEOUT_SEC为一直阻塞，直到(接收完一行|缓冲区满)为止
        * \return >=0:实际接收的字节数 -1:失败
        * \throw OssException
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        ssize_t RecvLine(void * szBuffer, size_t iMaxLen, time_t iTimeoutSec=MAX_TIMEOUT_SEC);

protected:

        /*! \brief 用一个描述符来创建一个TcpStream
        * \param[in] iHandle  描述符
        * \return 0:成功 -1:失败
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的              
        */
        int Open(int iHandle);
        
};

}

#endif //___TCP_STREAM_H
