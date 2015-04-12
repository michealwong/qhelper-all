/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       socket.h
 *  @brief      socket基类头文件
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
 *  \brief socket基类。定义了一组公用方法
 */
class Socket : public NonCopyable
{
public:

        /*! \brief 定义了为初始化的socket值 */
        enum { INVALID_HANDLE = -1 };
        
public:

        /*! \brief 关闭套接口
        * \return 0:正确 -1:失败
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */        
        int Close();


        /*! \brief 获取当前套接口本地inet地址
        * \param[out] stLocalAddr 本地inet地址
        * \return 0:正确 -1:失败
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        int GetLocalAddr(INetAddr & stLocalAddr) const;


        /*! \brief 判断当前套接口是否初始化成功
        * \return true:初始化成功 false:为初始化或初始化失败
        */
        inline bool IsOpen() const
                { return _iHandle!=INVALID_HANDLE?true:false; }


        /*! \brief 判断当前套接口是否初始化成功
        * \return true:初始化成功 false:为初始化或初始化失败
        */
        inline operator bool() const
                { return IsOpen(); }


        /*! \brief 设置套接口属性。参数定义可参考setsockopt
        * \param[in] iLevel 属性级别
        * \param[in] iOption 属性名
        * \param[in] pOptVal 属性值指针
        * \param[in] iOptLen 属性值字节数
        * \return 0:正确 -1:失败
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */        
        int SetSockOption(int iLevel, int iOption, const void *pOptVal, socklen_t iOptLen);


        /*! \brief 获取套接口属性。参数定义可参考getsockopt
        * \param[in] iLevel 属性级别
        * \param[in] iOption 属性名
        * \param[out] pOptVal 属性值指针
        * \param[out] pOptLen 属性值字节数
        * \return 0:正确 -1:失败
        * \throw OssException        
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        int GetSockOption(int iLevel, int iOption, void * pOptVal, socklen_t * pOptLen) const;

protected:

        /*! \brief 构造函数
        * \param[in] iType 套接口类型 SOCK_STREAM or SOCK_DGRAM or SOCK_RAW
        * \param[in] iFamily 地址族
        * \param[in] iProtocal 同系统socket()调用的protocol参数
        */             
        Socket(int iType, int iFamily=AF_INET, int iProtocal=0);


        /*! \brief 析够函数
        */     
        ~Socket();


        /*! \brief 用一个已经打开的套接口来初始化
        * \param[in] iHandle 已经打开的套接口
        * \return 0:正确 -1:失败
        * \throw OssException
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        int Open(int iHandle);


        /*! \brief 在本地指定地址上打开一个套接口
        * \param[in] stLocalAddr 本地地址
        * \param[in] bReuseAddr 地址是否重用
        * \return 0:正确 -1:失败
        * \throw OssException
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        int Open(const INetAddr & stLocalAddr, bool bReuseAddr=true);


        /*! \brief 设置阻塞(非阻塞)
        * \param[in] bBlock 是否阻塞
        * \return 0:正确 -1:失败
        * \throw OssException
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */
        int SetBlock(bool bBlock);


        /*! \brief 返回当前套接口描述字
        * \return 当前套接口描述字
        */        
        inline int GetHandle() const
                { return _iHandle; }

private:

        /*! \brief 绑定本地地址
        * \param[in] stLocalAddr 本地地址
        * \return 0:正确 -1:失败
        * \throw OssException
        * \note 出错时是抛异常还是返回结果值是由库编译宏 OSS_NO_EXCEPTIONS 决定的
        */        
        int Bind(const INetAddr & stLocalAddr);
        
private:      

        /*! \brief 套接口类型 SOCK_STREAM or SOCK_DGRAM or SOCK_RAW */        
        int _iType;

        /*! \brief 地址族 */        
        int _iFamily;

        /*! \brief 协议 */        
        int _iProtocal;

        /*! \brief 套接口描述字 */        
        int _iHandle;
};

}

#endif // ___SOCKET_H
