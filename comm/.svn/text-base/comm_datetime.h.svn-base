/*************************************************************
* 文件描述：日期时间的常 用操作类
**************************************************************/
#ifndef _COMM_DATETIME_H_
#define _COMM_DATETIME_H_

#include <utility>
#include "comm_strings.h"
#include <string>
#include <time.h>
#include <sys/types.h>

using namespace std ;

#ifdef __cplusplus
#define DATETIME_API extern
extern "C"
{
#else
#define STRING_API
#endif

    //时间格式宏定义
#define SDBL_FORMAT_UNIX 1  //形如"1970-01-01 00:00:00"unix时间格式
#define SDBL_FORMAT_CONT 2  //形如"19700101000000"不间隔时间格式
#define SDBL_FORMAT_SECOND 3  //形如"1187577006"秒格式

    //时间显示内容宏
#define SDBL_CONTENT_YEAR 1  //年
#define SDBL_CONTENT_MONTH 2  //月
#define SDBL_CONTENT_DAY 4  //日
#define SDBL_CONTENT_HOUR 8  //小时
#define SDBL_CONTENT_MINUTE 16  //分钟
#define SDBL_CONTENT_SECOND 32  //秒钟
#define SDBL_CONTENT_YMD SDBL_CONTENT_YEAR|SDBL_CONTENT_MONTH|SDBL_CONTENT_DAY //年月日
#define SDBL_CONTENT_ALL SDBL_CONTENT_YEAR|SDBL_CONTENT_MONTH|SDBL_CONTENT_DAY\
                                              |SDBL_CONTENT_HOUR|SDBL_CONTENT_MINUTE\
                                              |SDBL_CONTENT_SECOND //年月日时分秒


    /*************************************************************
    * 函数名：GetCurDateTime
    * 功能： 计算当前日期，格式：%Y-%m-%d %H:%M:%S
    * 参数：
    *              参数名       参数类型       传入方式   参数说明
    *              strDateTime       string&                     IN/OUT               当前时间
    * 返回值：void
    **************************************************************/
    DATETIME_API void GetCurDateTime(string& strDateTime);
	
	DATETIME_API string GetCurDateDay();
    /*************************************************************
    * 函数名：DiffDateTime
    * 功能： 计算当前日期与指定时间的相差时间值，格式：%Y-%m-%d %H:%M:%S
    * 参数：
    *              参数名       参数类型       传入方式   参数说明
    *              strDateTime       string&                     IN/OUT               当前时间
    *              iValue                 long                          IN                        指定的差值
    * 返回值：void
    *说明：当iValue为正时，表示比当前晚；反之比当前
    *              时间要早，iValue的单位为秒
    **************************************************************/
    DATETIME_API void DiffDateTime(string& strDateTime, long iValue);
    
    /***************************************************************************
    * 函数名：GetTime
    * 功能： 根据指定的时间格式及时间内容获取当前时间及
                    从当前时间起前后n天时间
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              day             int                   IN                       从当天开始的天数
                                                                                        默认值: 0   表示当天时间
    *              fmtflg          int                   IN                       指定的时间格式
                                                                                       默认值: SDBL_FORMAT_UNIX
    *              content        int                   IN                       指定时间内容
                                                                                        默认值: SDBL_CONTENT_YMD
    * 返回值：string   返回获取的时间字符串
    * 修订记录：
    *              修改人        修改日期       修改方式
    *              alfred                2007-08-20            create
    *****************************************************************************/
    DATETIME_API string GetTime(int day = 0, int fmtflg = SDBL_FORMAT_UNIX , int content =SDBL_CONTENT_ALL );
    
    /***************************************************************************
    * 函数名：GetTimeByDay
    * 功能： 根据指定的时间格式及时间内容获取当前时间及
                    从当前时间起前后n天时间
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              day             int                   IN                       从当天开始的天数
                                                                                        默认值: 0   表示当天时间
    *              fmtflg          int                   IN                       指定的时间格式
                                                                                       默认值: SDBL_FORMAT_UNIX，格式：%Y-%m-%d %H:%M:%S
    *              content        int                   IN                       指定时间内容
                                                                                        默认值: SDBL_CONTENT_YMD
    * 返回值：string   返回获取的时间字符串
     
    *****************************************************************************/
    DATETIME_API string GetTimeByDay(int day = 0, int fmtflg = SDBL_FORMAT_UNIX , int content =SDBL_CONTENT_ALL );
    

    /***************************************************************************
    * 函数名：GetTmsecFromUnxfmt
    * 功能： 从形如"1970-01-01 00:00:00"unix时间格式装换成time_t类型
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              time_sec      time_t &           in/out                 返回经转换后的秒数
    *              unxcontent  const char *      IN                      待转换的时间字符串
    *              content        int                   IN                       指定时间内容
                                                                                        默认值: SDBL_CONTENT_ALL
    * 返回值：函数返回值 0  :成功，其它转换失败
    *****************************************************************************/
    DATETIME_API int GetTmsecFromUnxfmt(time_t & time_sec , const char * unxcontent,
                                  int content =SDBL_CONTENT_ALL );
    

    /***************************************************************************
    * 函数名：GetTmsecFromContfmt
    * 功能： 从形如"19700101000000"时间格式装换成time_t类型
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              time_sec      time_t &           in/out                 返回经转换后的秒数
    *              contcontent  const char *      IN                      待转换的时间字符串
    *              content        int                   IN                       指定时间内容
                                                                                        默认值: SDBL_CONTENT_ALL
    * 返回值：函数返回值 0  :成功，其它转换失败
    *****************************************************************************/
    DATETIME_API int GetTmsecFromContfmt(time_t & time_sec , const char * contcontent,
                                   int content =SDBL_CONTENT_ALL );
   
    /***************************************************************************
    * 函数名：GetUnxfmtFromTmsec
    * 功能： 从time_t类型类型转换成形如"1970-01-01 00:00:00"unix时间格式
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              unxfmt         string &          in/out                 返回经转换后的时间字符串
    *              tmsec          time_t              IN                      待转换的time_t 数值
    *              context        int                   IN                       指定时间内容
                                                                                        默认值: SDBL_CONTENT_ALL
    * 返回值：函数返回值 0  :成功，其它转换失败
    *****************************************************************************/
    DATETIME_API int GetUnxfmtFromTmsec(string & unxfmt , const time_t  tmsec,
                                  int content =SDBL_CONTENT_ALL );
  
    /***************************************************************************
    * 函数名：GetUnxfmtFromContfmt
    * 功能： 从形如"19700101000000"时间格式装换成形如"1970-01-01 
    *                   00:00:00"时间格式字符串
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              unxcontent  string &            in/out                 形如"1970-01-01  00:00:00"
    *              contcontent  const char *     IN                      待转换的时间字符串
    *              content        int                   IN                       指定时间内容
                                                                                        默认值: SDBL_CONTENT_ALL
    * 返回值：函数返回值 0  :成功，其它转换失败
    *****************************************************************************/
    DATETIME_API int GetUnxfmtFromContfmt(string & unxcontent , const char * contcontent,
                                    int content =SDBL_CONTENT_ALL );
    

    /***************************************************************************
    * 函数名：GetContfmtFromUnxfmt
    * 功能： 从形如"1970-01-01 00:00:00"unix时间格式装换成time_t类型
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              contcontent      string &           in/out             返回形如"19700101000000"
                                                                                       形式字符串
    *              unxcontent  const char *      IN                      待转换的时间字符串
    *              content        int                   IN                       指定时间内容
                                                                                        默认值: SDBL_CONTENT_ALL
    * 返回值：函数返回值 0  :成功，其它转换失败
    *****************************************************************************/
    DATETIME_API int GetContfmtFromUnxfmt(string & contcontent , const char * unxcontent,
                                    int content =SDBL_CONTENT_ALL );
    
    /***************************************************************************
    * 函数名：GetDiffTime
    * 功能： 获取两个时间差值(即间隔) time1-time2
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              time1          const char *      in                        时间参数1                 
    *              time2          const char *      in                        时间参数2
    *              content       int                    in                        在计算时间差值需要用到
                                                                                        时间的内容bitset,默认值为
                                                                                        SDBL_CONTENT_ALL
    *              fmtflag        int                   IN                         指定比较两时间的格式
                                                                                        默认值: SDBL_FORMAT_UNiX
    * 返回值：返回两时间差值 ，为int类型,返回值0表示失败
    *****************************************************************************/
    DATETIME_API int GetDiffTime(const char * time1 , const char * time2 , int content = SDBL_CONTENT_ALL ,
                           int fmtflag = SDBL_FORMAT_UNIX);
   

    /***************************************************************************
    * 函数名：GetFirsttimeMonth
    * 功能： 获取指定时间(默认当天)所在月的月首时间
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              firsttime      string &             in/out                 返回指定格式月首时间                 
    *              intime         const char *       in                        指定时间，默认当天
    *              fmtflag        int                     in                        指定时间格式
    * 返回值：函数调用是否成功标志，非0失败
    *****************************************************************************/
    DATETIME_API int GetFirsttimeMonth(string & firsttime , const char * intime = NULL , int  fmtflag =
                                     SDBL_FORMAT_UNIX);
   
    /***************************************************************************
    * 函数名：GetLasttimeMonth
    * 功能： 获取指定时间(默认当天)所在月的月末时间
    * 参数：
    *              参数名 参数类型 传入方式    参数说明
    *              lasttime      string &             in/out                 返回指定格式月首时间                 
    *              intime         const char *       in                        指定时间，默认当天
    *              fmtflag        int                     in                        指定时间格式
    * 返回值：函数调用是否成功标志，非0失败
    *****************************************************************************/
    DATETIME_API int GetLasttimeMonth(string & lasttime , const char * intime = NULL , int  fmtflag =
                                    SDBL_FORMAT_UNIX);
    

    /*根据传入的时间(格式:1970-01-01 00:00:00),获取星期*/
    DATETIME_API string GetWeek(string s);
    
#ifdef __cplusplus
}
#endif

#endif

