/*************************************************************
* 文件描述：日期时间的常 用操作类
**************************************************************/
#include "comm_datetime.h"


void GetCurDateTime(string& strDateTime)
{
	// 计算
	time_t tCurTime = time(0);
	tm* pTime = localtime(&tCurTime);
	char aryTime[64] = {0};
	strftime(aryTime, 64, "%Y-%m-%d %H:%M:%S", pTime);
	strDateTime = aryTime;
}

string GetCurDateDay()
{
	// 计算
	string strDateTime;
	time_t tCurTime = time(0);
	tm* pTime = localtime(&tCurTime);
	char aryTime[64] = {0};
	strftime(aryTime, 64, "%Y-%m-%d", pTime);
	strDateTime = aryTime;
	return strDateTime;
}
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
void DiffDateTime(string& strDateTime, long iValue)
{
	// 计算
	time_t tCurTime = time(0);
	tCurTime += iValue;
	tm* pTime = localtime(&tCurTime);
	char aryTime[64] = {0};
	strftime(aryTime, 64, "%Y-%m-%d %H:%M:%S", pTime);
	strDateTime = aryTime;
}

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
string GetTime(int day , int fmtflg  , int content )
{
	char timevalue[32];
	memset(timevalue,0,sizeof(timevalue));
	char * pos ;
	int num;
	pos = timevalue ;
	time_t value;
	struct tm * pTm ;
	int valuetmp = 0 ;
	time(&value);
	value = value - day * 86400 ;
	pTm = localtime(&value);

	switch ( fmtflg )
	{
	case SDBL_FORMAT_UNIX :
		if ( (content & SDBL_CONTENT_YEAR) )
		{
			num = sprintf(pos,"%04d",pTm->tm_year + 1900);
			pos += num ;
			strcat(pos,"-01-01 00:00:00");
		}
		if ( (content & SDBL_CONTENT_MONTH) )
		{
			num = sprintf(pos,"-%02d",pTm->tm_mon + 1);
			pos += num ;
			strcat(pos,"-01 00:00:00");
		}
		if ( (content & SDBL_CONTENT_DAY) )
		{
			num = sprintf(pos , "-%02d" , pTm->tm_mday);
			pos += num ;
			strcat(pos," 00:00:00");
		}
		if ( (content & SDBL_CONTENT_HOUR) )
		{
			num = sprintf(pos , " %02d",pTm->tm_hour);
			pos += num ;
			strcat(pos ,":00:00");
		}
		if ( (content & SDBL_CONTENT_MINUTE) )
		{
			num = sprintf(pos , ":%02d",pTm->tm_min);
			pos += num ;
			strcat(pos,":00");
		}
		if ( (content & SDBL_CONTENT_SECOND) )
		{
			num = sprintf(pos , ":%02d" , pTm->tm_sec);
			pos += num ;
		}
		break ;
	case SDBL_FORMAT_CONT :
		if ( (content & SDBL_CONTENT_YEAR) )
		{
			num = sprintf(pos,"%04d",pTm->tm_year + 1900);
			pos +=  num ;
		}
		if ( (content & SDBL_CONTENT_MONTH) )
		{
			num = sprintf(pos,"%02d",pTm->tm_mon + 1);
			pos +=  num ;
		}
		if ( (content & SDBL_CONTENT_DAY) )
		{
			num = sprintf(pos , "%02d" , pTm->tm_mday);
			pos += num ;
		}
		if ( (content & SDBL_CONTENT_HOUR) )
		{
			num = sprintf(pos , "%02d",pTm->tm_hour);
			pos += num ;
		}
		if ( (content & SDBL_CONTENT_MINUTE) )
		{
			num = sprintf(pos , "%02d",pTm->tm_min);
			pos += num ;
		}
		if ( (content & SDBL_CONTENT_SECOND) )
		{
			num = sprintf(pos , "%02d" , pTm->tm_sec);
			pos += num ;
		}
		break ;
	case SDBL_FORMAT_SECOND :
		if ( (content & SDBL_CONTENT_YEAR) )
		{
			valuetmp = (int)value - pTm->tm_yday * 86400 - pTm->tm_hour * \
				3600 - pTm->tm_min * 60 - pTm->tm_sec ;
		}
		if ( (content & SDBL_CONTENT_MONTH) )
		{
			valuetmp = (int)value - (pTm->tm_mday - 1) * 86400 - pTm->tm_hour * \
				3600 - pTm->tm_min * 60 - pTm->tm_sec ;
		}
		if ( ( content & SDBL_CONTENT_DAY) )
		{
			valuetmp = (int)value - pTm->tm_hour * 3600 - pTm->tm_min * 60 - \
				pTm->tm_sec ;
		}
		if ( (content & SDBL_CONTENT_HOUR) )
		{
			valuetmp = (int)value - pTm->tm_min * 60 - pTm->tm_sec ;
		}
		if ( (content & SDBL_CONTENT_MINUTE) )
		{
			valuetmp = (int)value - pTm->tm_sec ;
		}
		if ( (content & SDBL_CONTENT_SECOND) )
		{
			valuetmp = (int)value ;
		}
		sprintf(pos , "%d",valuetmp);
		break ;
	default :
		break ;
	}

	return string(timevalue) ;

}

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
string GetTimeByDay(int day , int fmtflg  , int content )
{
	char timevalue[32];
	memset(timevalue,0,sizeof(timevalue));
	char * pos ;
	int num;
	pos = timevalue ;
	time_t value;
	struct tm * pTm ;
	int valuetmp = 0 ;
	time(&value);
	value = value - day * 86400 ;
	pTm = localtime(&value);

	switch ( fmtflg )
	{
	case SDBL_FORMAT_UNIX :  //格式：%Y-%m-%d %H:%M:%S
		if ( (content & SDBL_CONTENT_YEAR) )
		{
			num = sprintf(pos,"%04d",pTm->tm_year + 1900);
			pos += num ;
			strcat(pos,"-01-01 00:00:00");
		}
		if ( (content & SDBL_CONTENT_MONTH) )
		{
			num = sprintf(pos,"-%02d",pTm->tm_mon + 1);
			pos += num ;
			strcat(pos,"-01 00:00:00");
		}
		if ( (content & SDBL_CONTENT_DAY) )
		{
			num = sprintf(pos , "-%02d" , pTm->tm_mday);
			pos += num ;
			strcat(pos," 00:00:00");
		}
		if ( (content & SDBL_CONTENT_HOUR) )
		{
			num = sprintf(pos , " %02d",pTm->tm_hour);
			pos += num ;
			strcat(pos ,":00:00");
		}
		if ( (content & SDBL_CONTENT_MINUTE) )
		{
			num = sprintf(pos , ":%02d",pTm->tm_min);
			pos += num ;
			strcat(pos,":00");
		}
		if ( (content & SDBL_CONTENT_SECOND) )
		{
			num = sprintf(pos , ":%02d" , pTm->tm_sec);
			pos += num ;
		}
		break ;
	case SDBL_FORMAT_CONT :  //形如"%Y%m%d%H%M%S"不间隔时间格式
		if ( (content & SDBL_CONTENT_YEAR) )
		{
			num = sprintf(pos,"%04d",pTm->tm_year + 1900);
			pos +=  num ;
		}
		if ( (content & SDBL_CONTENT_MONTH) )
		{
			num = sprintf(pos,"%02d",pTm->tm_mon + 1);
			pos +=  num ;
		}
		if ( (content & SDBL_CONTENT_DAY) )
		{
			num = sprintf(pos , "%02d" , pTm->tm_mday);
			pos += num ;
		}
		if ( (content & SDBL_CONTENT_HOUR) )
		{
			num = sprintf(pos , "%02d",pTm->tm_hour);
			pos += num ;
		}
		if ( (content & SDBL_CONTENT_MINUTE) )
		{
			num = sprintf(pos , "%02d",pTm->tm_min);
			pos += num ;
		}
		if ( (content & SDBL_CONTENT_SECOND) )
		{
			num = sprintf(pos , "%02d" , pTm->tm_sec);
			pos += num ;
		}
		break ;
	case SDBL_FORMAT_SECOND :
		if ( (content & SDBL_CONTENT_YEAR) )
		{
			valuetmp = (int)value - pTm->tm_yday * 86400 - pTm->tm_hour * \
				3600 - pTm->tm_min * 60 - pTm->tm_sec ;
		}
		if ( (content & SDBL_CONTENT_MONTH) )
		{
			valuetmp = (int)value - (pTm->tm_mday - 1) * 86400 - pTm->tm_hour * \
				3600 - pTm->tm_min * 60 - pTm->tm_sec ;
		}
		if ( ( content & SDBL_CONTENT_DAY) )
		{
			valuetmp = (int)value - pTm->tm_hour * 3600 - pTm->tm_min * 60 - \
				pTm->tm_sec ;
		}
		if ( (content & SDBL_CONTENT_HOUR) )
		{
			valuetmp = (int)value - pTm->tm_min * 60 - pTm->tm_sec ;
		}
		if ( (content & SDBL_CONTENT_MINUTE) )
		{
			valuetmp = (int)value - pTm->tm_sec ;
		}
		if ( (content & SDBL_CONTENT_SECOND) )
		{
			valuetmp = (int)value ;
		}
		sprintf(pos , "%d",valuetmp);
		break ;
	default :
		break ;
	}

	return string(timevalue) ;

}

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
int GetTmsecFromUnxfmt(time_t & time_sec , const char * unxcontent,
					   int content )
{
	//传入参数合法性校验
	string tmpstr(unxcontent);
	Trim( tmpstr) ;
	int length = (int)tmpstr.size() ;
	if ( length > 19 )
	{
		return 1 ; //输入时间参数unxfmt太长
	}
	else
	{
		string alphacontent("0123456789-: ") ;
		for(int i = 0 ; i < length ; i++)
		{
			if(std::string::npos == alphacontent.find(tmpstr[i]))
			{
				return 2 ; //输入时间参数unixfmt含有非法字符
			}
		}
		if( (length < 4) ||((length > 4) &&(tmpstr.at(4) != '-' ) )|| ((length > 7) &&(tmpstr.at(7) != '-')) \
			||((length >10)&&(tmpstr.at(10) != ' '))||((length > 13) && (tmpstr.at(13) != ':')) \
			||((length >16) && (tmpstr.at(16) != ':') ))
		{
			return 3 ; //输入时间函数unxfmt格式不正确
		}

	}

	struct tm tm_value ;
	memset(&tm_value,0,sizeof(tm_value));

	//时间转换
	if( (content & SDBL_CONTENT_YEAR) && (length >= 4))
	{
		int year = StrToInt(tmpstr.substr(0,4)) -1900 ;
		if( 70 <= year && 138 >= year)
		{
			tm_value.tm_year = year ;
			tm_value.tm_mday = 1 ;
		}
		else
		{
			return 4 ; //时间中年超过范围
		}
	}
	if( (content & SDBL_CONTENT_MONTH) && (length >= 7))
	{
		int mon = StrToInt(tmpstr.substr(5,2)) -1 ;
		if( 0 <= mon && 11 >= mon)
		{
			tm_value.tm_mon = mon ;
			tm_value.tm_mday = 1 ;
		}
		else
		{
			return 5 ; //月份超过0-11范围
		}
	}
	if ( (content & SDBL_CONTENT_DAY) && (length >=10))
	{
		int day = StrToInt(tmpstr.substr(8,2))  ;
		if( 1 <= day && 31 >= day )
		{
			tm_value.tm_mday = day ;
		}
		else
		{
			return 6 ; //每天天数超过1-31范围
		}
	}
	if ( (content & SDBL_CONTENT_HOUR) && (length >= 13))
	{
		int hour = StrToInt(tmpstr.substr(11,2)) ;
		if( 0 <= hour && 23 >= hour )
		{
			tm_value.tm_hour = hour ;
		}
		else
		{
			return 7 ; //小时超过0-23范围
		}

	}
	if ( (content & SDBL_CONTENT_MINUTE) && (length >= 16))
	{
		int min = StrToInt(tmpstr.substr(14,2)) ;
		if( 0 <= min && 59 >= min )
		{
			tm_value.tm_min = min ;
		}
		else
		{
			return 8 ; //分钟超过0-59范围
		}

	}
	if ( (content & SDBL_CONTENT_SECOND) && (length >= 19))
	{
		int sec = StrToInt(tmpstr.substr(17,2)) ;
		if( 0 <= sec && 59 >= sec)
		{
			tm_value.tm_sec = sec ;
		}
		else
		{
			return 9 ; //秒钟超过0-59范围
		}

	}
	time_sec = mktime(&tm_value);

	return 0 ;

}

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
int GetTmsecFromContfmt(time_t & time_sec , const char * contcontent,
						int content )
{
	//传入参数合法性校验
	string tmpstr(contcontent);
	Trim( tmpstr) ;
	int length = (int)tmpstr.size() ;
	if ( length > 14 )
	{
		return 1 ; //输入时间参数contfmt太长
	}
	else
	{
		string alphacontent("0123456789") ;
		for(int i = 0 ; i < length ; i++)
		{
			if(std::string::npos == alphacontent.find(tmpstr[i]))
			{
				return 2 ; //输入时间参数contfmt含有非法字符
			}
		}
	}

	struct tm tm_value ;
	memset(&tm_value,0,sizeof(tm_value));

	//时间转换
	if( (content & SDBL_CONTENT_YEAR) && (length >= 4))
	{
		int year = StrToInt(tmpstr.substr(0,4)) -1900 ;
		if( 70 <= year && 138 >= year)
		{
			tm_value.tm_year =  year ;
			tm_value.tm_mday = 1 ;
		}
		else
		{
			return 3 ; //时间中年超过70-138范围
		}

	}
	if( (content & SDBL_CONTENT_MONTH) && (length >= 6))
	{
		int mon = StrToInt(tmpstr.substr(4,2)) -1 ;
		if( 0 <= mon && 11 >= mon )
		{
			tm_value.tm_mon =  mon ;
			tm_value.tm_mday = 1 ;
		}
		else
		{
			return 4 ; //月份超过0-11范围
		}

	}
	if ( (content & SDBL_CONTENT_DAY) && (length >= 8))
	{
		int day = StrToInt(tmpstr.substr(6,2))  ;
		if( 1 <= day && 31 >= day )
		{
			tm_value.tm_mday = day ;
		}
		else
		{
			return 5 ; //天数超过1-31范围
		}

	}
	if ( (content & SDBL_CONTENT_HOUR) && (length >= 10))
	{
		int hour = StrToInt(tmpstr.substr(8,2)) ;
		if( 0 <= hour && 23 >= hour )
		{
			tm_value.tm_hour = hour ;
		}
		else
		{
			return 6 ; //小时超过0-23范围
		}
	}
	if ( (content & SDBL_CONTENT_MINUTE) && (length >= 12))
	{
		int min = StrToInt(tmpstr.substr(10,2)) ;
		if ( 0 <= min && 59 >= min )
		{
			tm_value.tm_min = min ;
		}
		else
		{
			return 7 ; //分钟超过0-59范围
		}
	}
	if ( (content & SDBL_CONTENT_SECOND) && (length >= 14))
	{
		int sec = StrToInt(tmpstr.substr(12,2)) ;
		if ( 0 <= sec && 59 >= sec )
		{
			tm_value.tm_sec = sec ;
		}
		else
		{
			return 8 ; //秒钟超过0-59范围
		}
	}

	time_sec = mktime(&tm_value);

	return 0 ;

}

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
int GetUnxfmtFromTmsec(string & unxfmt , const time_t  tmsec,
					   int content )
{
	struct tm * ptm ;
	ptm = localtime(&tmsec);

	char szTime[20];
	memset(szTime,0,sizeof(szTime));
	char * pos = szTime ;
	int num = 0 ;

	//时间转换
	if( (content & SDBL_CONTENT_YEAR) )
	{
		num = sprintf(pos,"%04d" , ptm->tm_year + 1900);
		pos += num ;
		strcat(pos,"-01-01 00:00:00");
	}
	if( (content & SDBL_CONTENT_MONTH) )
	{
		num = sprintf(pos , "-%02d",ptm->tm_mon + 1) ;
		pos += num ;
		strcat(pos,"-01 00:00:00");
	}
	if ( (content & SDBL_CONTENT_DAY) )
	{
		num = sprintf(pos , "-%02d" , ptm->tm_mday) ;
		pos += num ;
		strcat(pos," 00:00:00");
	}
	if ( (content & SDBL_CONTENT_HOUR) )
	{
		num = sprintf(pos , " %02d" , ptm->tm_hour) ;
		pos += num ;
		strcat(pos,":00:00");
	}
	if ( (content & SDBL_CONTENT_MINUTE) )
	{
		num = sprintf(pos , ":%02d" , ptm->tm_min);
		pos += num ;
		strcat(pos,":00");
	}
	if ( (content & SDBL_CONTENT_SECOND) )
	{
		num = sprintf(pos , ":%02d",ptm->tm_sec);
	}

	unxfmt = szTime ;

	return 0 ;

}

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
int GetUnxfmtFromContfmt(string & unxcontent , const char * contcontent,
						 int content )
{
	//传入参数合法性校验
	string tmpstr(contcontent);
	Trim( tmpstr) ;
	int length = (int)tmpstr.size() ;
	if ( length > 14 )
	{
		return 1 ; //输入时间参数contfmt太长
	}
	else
	{
		string alphacontent("0123456789") ;
		for(int i = 0 ; i < length ; i++)
		{
			if(std::string::npos == alphacontent.find(tmpstr[i]))
			{
				return 2 ; //输入时间参数contfmt含有非法字符
			}
		}
	}

	char szTime[20] ;
	memset(szTime , 0 , sizeof(szTime));
	char * pos = szTime ;
	int num ;

	//时间转换
	if ( length < 4 )
	{
		return 3 ; //长度不够
	}
	if( (content & SDBL_CONTENT_YEAR) && (length >= 4))
	{
		int year = StrToInt(tmpstr.substr(0,4)) -1900 ;
		if( 70 <= year && 138 >= year)
		{
			num = sprintf(pos , "%s" , tmpstr.substr(0,4).c_str()) ;
			pos += num ;
			strcat(pos,"-01-01 00:00:00");
		}
		else
		{
			return 4 ; //时间中年超过70-138范围
		}

	}
	if( (content & SDBL_CONTENT_MONTH) && (length >= 6))
	{
		int mon = StrToInt(tmpstr.substr(4,2)) -1 ;
		if( 0 <= mon && 11 >= mon )
		{
			num = sprintf(pos , "-%s" , tmpstr.substr(4,2).c_str());
			pos += num ;
			strcat(pos,"-01 00:00:00");
		}
		else
		{
			return 5 ; //月份超过0-11范围
		}

	}
	if ( (content & SDBL_CONTENT_DAY) && (length >= 8))
	{
		int day = StrToInt(tmpstr.substr(6,2))  ;
		if( 1 <= day && 31 >= day )
		{
			num = sprintf(pos , "-%s",tmpstr.substr(6,2).c_str());
			pos += num ;
			strcat(pos," 00:00:00");
		}
		else
		{
			return 6 ; //天数超过1-31范围
		}

	}
	if ( (content & SDBL_CONTENT_HOUR) && (length >= 10))
	{
		int hour = StrToInt(tmpstr.substr(8,2)) ;
		if( 0 <= hour && 23 >= hour )
		{
			num = sprintf(pos," %s" , tmpstr.substr(8,2).c_str());
			pos += num ;
			strcat(pos,":00:00");
		}
		else
		{
			return 7 ; //小时超过0-23范围
		}
	}
	if ( (content & SDBL_CONTENT_MINUTE) && (length >= 12))
	{
		int min = StrToInt(tmpstr.substr(10,2)) ;
		if ( 0 <= min && 59 >= min )
		{
			num = sprintf(pos , ":%s" , tmpstr.substr(10,2).c_str());
			pos += num ;
			strcat(pos,":00");
		}
		else
		{
			return 8 ; //分钟超过0-59范围
		}
	}
	if ( (content & SDBL_CONTENT_SECOND) && (length >= 14))
	{
		int sec = StrToInt(tmpstr.substr(12,2)) ;
		if ( 0 <= sec && 59 >= sec )
		{
			num = sprintf(pos , ":%s" , tmpstr.substr(12,2).c_str());
			pos += num ;
		}
		else
		{
			return 9 ; //秒钟超过0-59范围
		}
	}

	unxcontent = szTime;

	return 0 ;

}

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
int GetContfmtFromUnxfmt(string & contcontent , const char * unxcontent,
						 int content  )
{
	//传入参数合法性校验
	string tmpstr(unxcontent);
	Trim( tmpstr) ;
	int length = (int)tmpstr.size() ;
	if ( length > 19 )
	{
		return 1 ; //输入时间参数unxfmt太长
	}
	else
	{
		string alphacontent("0123456789-: ") ;
		for(int i = 0 ; i < length ; i++)
		{
			if(std::string::npos == alphacontent.find(tmpstr[i]))
			{
				return 2 ; //输入时间参数unixfmt含有非法字符
			}
		}
		if( (length < 4) ||((length > 4) &&(tmpstr.at(4) != '-' ) )|| ((length > 7) &&(tmpstr.at(7) != '-')) \
			||((length >10)&&(tmpstr.at(10) != ' '))||((length > 13) && (tmpstr.at(13) != ':')) \
			||((length >16) && (tmpstr.at(16) != ':') ))
		{
			return 3 ; //输入时间函数unxfmt格式不正确
		}

	}

	char szTime[20] ;
	memset(szTime , 0, sizeof(szTime));
	char * pos = szTime ;
	int num = 0 ;

	//时间转换
	if( (content & SDBL_CONTENT_YEAR) && (length >= 4))
	{
		int year = StrToInt(tmpstr.substr(0,4)) -1900 ;
		if( 70 <= year && 138 >= year)
		{
			num = sprintf(pos, "%s" , tmpstr.substr(0,4).c_str());
			pos += num ;
		}
		else
		{
			return 4 ; //时间中年超过范围
		}
	}
	if( (content & SDBL_CONTENT_MONTH) && (length >= 7))
	{
		int mon = StrToInt(tmpstr.substr(5,2)) -1 ;
		if( 0 <= mon && 11 >= mon)
		{
			num = sprintf(pos , "%s" , tmpstr.substr(5,2).c_str()) ;
			pos += num ;
		}
		else
		{
			return 5 ; //月份超过0-11范围
		}
	}
	if ( (content & SDBL_CONTENT_DAY) && (length >=10))
	{
		int day = StrToInt(tmpstr.substr(8,2))  ;
		if( 1 <= day && 31 >= day )
		{
			num = sprintf(pos , "%s", tmpstr.substr(8,2).c_str());
			pos += num ;
		}
		else
		{
			return 6 ; //每天天数超过1-31范围
		}
	}
	if ( (content & SDBL_CONTENT_HOUR) && (length >= 13))
	{
		int hour = StrToInt(tmpstr.substr(11,2)) ;
		if( 0 <= hour && 23 >= hour )
		{
			num = sprintf(pos , "%s" , tmpstr.substr(11,2).c_str());
			pos += num ;
		}
		else
		{
			return 7 ; //小时超过0-23范围
		}

	}
	if ( (content & SDBL_CONTENT_MINUTE) && (length >= 16))
	{
		int min = StrToInt(tmpstr.substr(14,2)) ;
		if( 0 <= min && 59 >= min )
		{
			num = sprintf(pos , "%s" , tmpstr.substr(14,2).c_str());
			pos += num ;
		}
		else
		{
			return 8 ; //分钟超过0-59范围
		}

	}
	if ( (content & SDBL_CONTENT_SECOND) && (length >= 19))
	{
		int sec = StrToInt(tmpstr.substr(17,2)) ;
		if( 0 <= sec && 59 >= sec)
		{
			num = sprintf(pos , "%s" , tmpstr.substr(17,2).c_str());
			pos += num ;
		}
		else
		{
			return 9 ; //秒钟超过0-59范围
		}

	}

	contcontent = szTime ;

	return 0 ;

}

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
int GetDiffTime(const char * time1 , const char * time2 , int content ,
				int fmtflag )
{
	if ( SDBL_FORMAT_UNIX == fmtflag )
	{
		time_t t1 , t2 ;
		if( 0 != GetTmsecFromUnxfmt(t1, time1, content) )
		{
			return 0 ;
		}
		if( 0 != GetTmsecFromUnxfmt(t2, time2, content) )
		{
			return 0 ;
		}

		return (int)t1 - (int)t2 ;
	}
	else if ( SDBL_FORMAT_CONT == fmtflag )
	{
		time_t t1 , t2 ;
		if( 0 != GetTmsecFromContfmt(t1, time1, content ) )
		{
			return 0 ;
		}
		if( 0 != GetTmsecFromContfmt(t2, time2, content ) )
		{
			return 0 ;
		}

		return (int)t1 - (int)t2 ;
	}

	return 0 ;
}

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
int GetFirsttimeMonth(string & firsttime , const char * intime , int  fmtflag )
{
	if ( SDBL_FORMAT_UNIX == fmtflag )
	{
		if ( NULL == intime)
		{
			firsttime = GetTime(0, fmtflag, SDBL_CONTENT_YEAR|SDBL_CONTENT_MONTH) ;
		}
		else
		{
			time_t tmptime ;
			if ( 0 == GetTmsecFromUnxfmt(tmptime, intime) )
			{
				struct tm * ptm ;
				ptm = localtime(&tmptime) ;
				ptm->tm_mday = 1;
				char sztime[20];
				sprintf(sztime , "%04d-%02d-%02d 00:00:00" , ptm->tm_year + 1900 ,
					ptm->tm_mon +1 , ptm->tm_mday);
				firsttime = sztime ;
			}
			else
			{
				return 1 ; //时间转换错误
			}
		}
	}
	else if ( SDBL_FORMAT_CONT == fmtflag)
	{
		if ( NULL == intime )
		{
			firsttime = GetTime(0, fmtflag,SDBL_CONTENT_YEAR|SDBL_CONTENT_MONTH) ;
			firsttime += "01" ;
		}
		else
		{
			time_t tmptime ;
			if( 0 == GetTmsecFromContfmt(tmptime, intime) )
			{
				struct tm * ptm ;
				ptm = localtime(&tmptime) ;
				ptm->tm_mday = 1;
				char sztime[20];
				sprintf(sztime , "%04d%02d%02d" ,  ptm->tm_year + 1900 ,ptm->tm_mon +1 ,
					ptm->tm_mday);
				firsttime = sztime ;
			}
			else
			{
				return 1 ; //时间转换错误
			}
		}
	}
	else
	{
		return 2 ; //时间格式错误，不同该函数得到结果
	}

	return 0 ;

}

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
int GetLasttimeMonth(string & lasttime , const char * intime  , int  fmtflag )
{
	if ( SDBL_FORMAT_UNIX == fmtflag )
	{
		string transtime ;
		if ( NULL == intime)
		{
			transtime = GetTime(0, fmtflag, SDBL_CONTENT_ALL) ;
		}
		else
		{
			transtime = intime ;
		}

		time_t tmptime ;
		if ( 0 == GetTmsecFromUnxfmt(tmptime, transtime.c_str()) )
		{
			struct tm * ptm ;
			ptm = localtime(&tmptime) ;
			if( ptm->tm_mon == 11 )
			{
				ptm->tm_year += 1 ;
				ptm->tm_mon = 0 ;
			}
			else
			{
				ptm->tm_mon += 1 ;
			}
			ptm->tm_mday = 1 ;
			ptm->tm_hour = 0 ;
			ptm->tm_min = 0 ;
			ptm->tm_sec = 0 ;
			time_t tt ;
			tt = mktime(ptm) ;
			tt -= 1 ;

			ptm = localtime(&tt) ;
			char sztime[20];
			sprintf(sztime , "%04d-%02d-%02d %02d:%02d:%02d" , ptm->tm_year + 1900 ,
				ptm->tm_mon +1 , ptm->tm_mday , ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
			lasttime = sztime ;
		}
		else
		{
			return 1 ; //时间转换错误
		}
	}
	else if ( SDBL_FORMAT_CONT == fmtflag)
	{
		string transtime ;
		if( NULL == intime)
		{
			transtime = GetTime(0, fmtflag, SDBL_CONTENT_ALL) ;
		}
		else
		{
			transtime = intime ;
		}

		time_t tmptime ;
		if( 0 == GetTmsecFromContfmt(tmptime, transtime.c_str()) )
		{
			struct tm * ptm ;
			ptm = localtime(&tmptime) ;
			if( ptm->tm_mon == 11 )
			{
				ptm->tm_year += 1 ;
				ptm->tm_mon = 0 ;
			}
			else
			{
				ptm->tm_mon += 1 ;
			}
			ptm->tm_mday = 1 ;
			ptm->tm_hour = 0 ;
			ptm->tm_min = 0 ;
			ptm->tm_sec = 0 ;
			time_t tt ;
			tt = mktime(ptm) ;
			tt -= 1 ;

			ptm = localtime(&tt) ;
			char sztime[20];
			sprintf(sztime ,"%04d%02d%02d",ptm->tm_year + 1900 , ptm->tm_mon + 1 ,
				ptm->tm_mday);
			lasttime = sztime ;

		}
		else
		{
			return 1 ; //时间转换错误
		}
	}


	return 0 ;

}


/*根据传入的时间(格式:1970-01-01 00:00:00),获取星期*/
string GetWeek(string s)
{
	time_t curr;
	struct tm* currTime;
	GetTmsecFromUnxfmt( curr, (char*)s.c_str() );
	currTime = localtime(&curr);
	char buf[16];
	strftime(buf,sizeof(buf),"%w",currTime);

	string week = buf;
	switch( atoi(week.c_str()) )
	{
	case 0:
		week = "七";
		break;
	case 1:
		week = "一";
		break;
	case 2:
		week = "二";
		break;
	case 3:
		week = "三";
		break;
	case 4:
		week = "四";
		break;
	case 5:
		week = "五";
		break;
	case 6:
		week = "六";
		break;
	default:
		break;
	}
	return week;
}


