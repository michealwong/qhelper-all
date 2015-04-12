/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       tcp_acceptor.h
 *  @brief      acceptor头文件 
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
 *  \brief tcp连接接收器
 */
class TcpAcceptor : public Socket
{
public:

        /*! \brief 缺省backlog值 */
        enum { DEFAULT_BACKLOG = 5 };

        /*! \brief 定义了最大超时时间 */
        enum { MAX_TIMEOUT_SEC = -1 };

        /*! \brief 缺省接收缓存区字节数 */
        enum { DEFAULT_RECV_BUFF_SIZE = -1 };

public:

        /*! \brief 缺省构造函数 
        */        
        TcpAcceptor();


        /*! \brief 打开一个TcpAcceptor，绑定到本地地址，并开始监听
        * \param[in] stLocalAddr    本地地址
        * \param[in] bReuseAddr     是否地址重用
        * \param[in] iRecvBuffSize  接受缓存区大小
        * \param[in] iBackLog       backlog大小
        * \return 0:成功 -1:失败
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        int Open(const INetAddr & stLocalAddr, 
                bool bReuseAddr = true,
                int iRecvBuffSize = DEFAULT_RECV_BUFF_SIZE,
                int iBackLog = DEFAULT_BACKLOG);


        /*! \brief 接受一个连接请求
        * \param[out] NewStream   生成一个新的TcpStream
        * \param[in] iTimeoutSec  超时秒数
        * \return 0:成功 -1:失败 
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的         
        */
        int Accept(TcpStream & NewStream, 
                time_t iTimeoutSec=MAX_TIMEOUT_SEC);

protected:

        /*! \brief 
        * \param[in] iBackLog 同系统调用listen的backlog参数
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的        
        */
        int Listen(int iBackLog);

        /*! \brief 阻塞接收。\n
        *       不存在NonBlockAccept的“惊群”问题，适合多进程使用
        * \param[in] NewStream 生成一个新的TcpStream
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的        
        */
        int BlockAccept(TcpStream & NewStream);


        /*! \brief 非阻塞接收。\n
        *       在多进程调用时，新来一个连接会惊醒多个同时阻塞在select上进程，造成“惊群”\n
        *       多进程使用时 最好进程数量<=cpu数量
        * \param[in] NewStream 生成一个新的TcpStream
        * \param[in] iTimeoutSec 超时秒数         
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的        
        */
        int NonBlockAccept(TcpStream & NewStream, time_t iTimeoutSec);

};

}

#endif //___TCP_ACCEPTOR_H
