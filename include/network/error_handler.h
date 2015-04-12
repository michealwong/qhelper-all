/* -*- C++ -*- */
//=============================================================================
/**
 *  @file       error_handler.h
 *  @brief      Oss库错误处理头文件
 *  @version    1.1.0
 *  @author     Sunbird
 *  @date       2007/03/08
 */
//=============================================================================

#ifndef ___ERROR_HANDLER_H
#define ___ERROR_HANDLER_H

#include "oss_exception.h"
#include "string_tools.h"


#define OSS_THROW_EXCEPTON(ERRNO, ...) \
        throw OssBase::OssException(__FILE__, __LINE__, StringTools::Format(__VA_ARGS__), (ERRNO));


#ifndef OSS_NO_EXCEPTIONS

        #define OSS_ERROR_RETURN(ERRNO,  ...) \
                OSS_THROW_EXCEPTON(ERRNO, __VA_ARGS__);

        #define OSS_ERROR_RETURN_VAL(RETURN_VAL, ERRNO, ...) \
                OSS_THROW_EXCEPTON(ERRNO, __VA_ARGS__);

#else

        #define OSS_ERROR_RETURN_VAL(RETURN_VAL, ERRNO, ...) \
                return (RETURN_VAL);
        
        #define OSS_ERROR_RETURN(ERRNO, ...) \
                OSS_ERROR_RETURN_VAL(ERRNO, ERRNO, __VA_ARGS__);

#endif


#endif //___ERROR_HANDLER_H
