/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       non_copyable.h
 *  @brief      不能复制接口头文件
 *  @note       摘自IceUtil::::noncopyable
 *  @version    1.0
 *  @author     Sunbird
 *  @date       2006/07/14
 */
//=============================================================================

#ifndef ___NONCOPYABLE_H
#define ___NONCOPYABLE_H

namespace OssBase
{

/*! \brief 所有要求不可赋值(拷贝构造)的类都可以继承于此
 *  \note 摘自IceUtil::::noncopyable
 */
class NonCopyable
{

protected:
    NonCopyable() {}
    ~NonCopyable() {}

private:
    NonCopyable(const NonCopyable &);
    const NonCopyable & operator=(const NonCopyable &);
};

}

#endif // ___NONCOPYABLE_H
