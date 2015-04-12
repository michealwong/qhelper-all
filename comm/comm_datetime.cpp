/*************************************************************
* �ļ�����������ʱ��ĳ� �ò�����
**************************************************************/
#include "comm_datetime.h"


void GetCurDateTime(string& strDateTime)
{
	// ����
	time_t tCurTime = time(0);
	tm* pTime = localtime(&tCurTime);
	char aryTime[64] = {0};
	strftime(aryTime, 64, "%Y-%m-%d %H:%M:%S", pTime);
	strDateTime = aryTime;
}

string GetCurDateDay()
{
	// ����
	string strDateTime;
	time_t tCurTime = time(0);
	tm* pTime = localtime(&tCurTime);
	char aryTime[64] = {0};
	strftime(aryTime, 64, "%Y-%m-%d", pTime);
	strDateTime = aryTime;
	return strDateTime;
}
/*************************************************************
* ��������DiffDateTime
* ���ܣ� ���㵱ǰ������ָ��ʱ������ʱ��ֵ����ʽ��%Y-%m-%d %H:%M:%S
* ������
*              ������       ��������       ���뷽ʽ   ����˵��
*              strDateTime       string&                     IN/OUT               ��ǰʱ��
*              iValue                 long                          IN                        ָ���Ĳ�ֵ
* ����ֵ��void
*˵������iValueΪ��ʱ����ʾ�ȵ�ǰ����֮�ȵ�ǰ
*              ʱ��Ҫ�磬iValue�ĵ�λΪ��
**************************************************************/
void DiffDateTime(string& strDateTime, long iValue)
{
	// ����
	time_t tCurTime = time(0);
	tCurTime += iValue;
	tm* pTime = localtime(&tCurTime);
	char aryTime[64] = {0};
	strftime(aryTime, 64, "%Y-%m-%d %H:%M:%S", pTime);
	strDateTime = aryTime;
}

/***************************************************************************
* ��������GetTime
* ���ܣ� ����ָ����ʱ���ʽ��ʱ�����ݻ�ȡ��ǰʱ�估
�ӵ�ǰʱ����ǰ��n��ʱ��
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              day             int                   IN                       �ӵ��쿪ʼ������
Ĭ��ֵ: 0   ��ʾ����ʱ��
*              fmtflg          int                   IN                       ָ����ʱ���ʽ
Ĭ��ֵ: SDBL_FORMAT_UNIX
*              content        int                   IN                       ָ��ʱ������
Ĭ��ֵ: SDBL_CONTENT_YMD
* ����ֵ��string   ���ػ�ȡ��ʱ���ַ���
* �޶���¼��
*              �޸���        �޸�����       �޸ķ�ʽ
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
* ��������GetTimeByDay
* ���ܣ� ����ָ����ʱ���ʽ��ʱ�����ݻ�ȡ��ǰʱ�估
�ӵ�ǰʱ����ǰ��n��ʱ��
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              day             int                   IN                       �ӵ��쿪ʼ������
Ĭ��ֵ: 0   ��ʾ����ʱ��
*              fmtflg          int                   IN                       ָ����ʱ���ʽ
Ĭ��ֵ: SDBL_FORMAT_UNIX����ʽ��%Y-%m-%d %H:%M:%S
*              content        int                   IN                       ָ��ʱ������
Ĭ��ֵ: SDBL_CONTENT_YMD
* ����ֵ��string   ���ػ�ȡ��ʱ���ַ���

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
	case SDBL_FORMAT_UNIX :  //��ʽ��%Y-%m-%d %H:%M:%S
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
	case SDBL_FORMAT_CONT :  //����"%Y%m%d%H%M%S"�����ʱ���ʽ
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
* ��������GetTmsecFromUnxfmt
* ���ܣ� ������"1970-01-01 00:00:00"unixʱ���ʽװ����time_t����
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              time_sec      time_t &           in/out                 ���ؾ�ת���������
*              unxcontent  const char *      IN                      ��ת����ʱ���ַ���
*              content        int                   IN                       ָ��ʱ������
Ĭ��ֵ: SDBL_CONTENT_ALL
* ����ֵ����������ֵ 0  :�ɹ�������ת��ʧ��
*****************************************************************************/
int GetTmsecFromUnxfmt(time_t & time_sec , const char * unxcontent,
					   int content )
{
	//��������Ϸ���У��
	string tmpstr(unxcontent);
	Trim( tmpstr) ;
	int length = (int)tmpstr.size() ;
	if ( length > 19 )
	{
		return 1 ; //����ʱ�����unxfmt̫��
	}
	else
	{
		string alphacontent("0123456789-: ") ;
		for(int i = 0 ; i < length ; i++)
		{
			if(std::string::npos == alphacontent.find(tmpstr[i]))
			{
				return 2 ; //����ʱ�����unixfmt���зǷ��ַ�
			}
		}
		if( (length < 4) ||((length > 4) &&(tmpstr.at(4) != '-' ) )|| ((length > 7) &&(tmpstr.at(7) != '-')) \
			||((length >10)&&(tmpstr.at(10) != ' '))||((length > 13) && (tmpstr.at(13) != ':')) \
			||((length >16) && (tmpstr.at(16) != ':') ))
		{
			return 3 ; //����ʱ�亯��unxfmt��ʽ����ȷ
		}

	}

	struct tm tm_value ;
	memset(&tm_value,0,sizeof(tm_value));

	//ʱ��ת��
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
			return 4 ; //ʱ�����곬����Χ
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
			return 5 ; //�·ݳ���0-11��Χ
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
			return 6 ; //ÿ����������1-31��Χ
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
			return 7 ; //Сʱ����0-23��Χ
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
			return 8 ; //���ӳ���0-59��Χ
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
			return 9 ; //���ӳ���0-59��Χ
		}

	}
	time_sec = mktime(&tm_value);

	return 0 ;

}

/***************************************************************************
* ��������GetTmsecFromContfmt
* ���ܣ� ������"19700101000000"ʱ���ʽװ����time_t����
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              time_sec      time_t &           in/out                 ���ؾ�ת���������
*              contcontent  const char *      IN                      ��ת����ʱ���ַ���
*              content        int                   IN                       ָ��ʱ������
Ĭ��ֵ: SDBL_CONTENT_ALL
* ����ֵ����������ֵ 0  :�ɹ�������ת��ʧ��
*****************************************************************************/
int GetTmsecFromContfmt(time_t & time_sec , const char * contcontent,
						int content )
{
	//��������Ϸ���У��
	string tmpstr(contcontent);
	Trim( tmpstr) ;
	int length = (int)tmpstr.size() ;
	if ( length > 14 )
	{
		return 1 ; //����ʱ�����contfmt̫��
	}
	else
	{
		string alphacontent("0123456789") ;
		for(int i = 0 ; i < length ; i++)
		{
			if(std::string::npos == alphacontent.find(tmpstr[i]))
			{
				return 2 ; //����ʱ�����contfmt���зǷ��ַ�
			}
		}
	}

	struct tm tm_value ;
	memset(&tm_value,0,sizeof(tm_value));

	//ʱ��ת��
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
			return 3 ; //ʱ�����곬��70-138��Χ
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
			return 4 ; //�·ݳ���0-11��Χ
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
			return 5 ; //��������1-31��Χ
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
			return 6 ; //Сʱ����0-23��Χ
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
			return 7 ; //���ӳ���0-59��Χ
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
			return 8 ; //���ӳ���0-59��Χ
		}
	}

	time_sec = mktime(&tm_value);

	return 0 ;

}

/***************************************************************************
* ��������GetUnxfmtFromTmsec
* ���ܣ� ��time_t��������ת��������"1970-01-01 00:00:00"unixʱ���ʽ
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              unxfmt         string &          in/out                 ���ؾ�ת�����ʱ���ַ���
*              tmsec          time_t              IN                      ��ת����time_t ��ֵ
*              context        int                   IN                       ָ��ʱ������
Ĭ��ֵ: SDBL_CONTENT_ALL
* ����ֵ����������ֵ 0  :�ɹ�������ת��ʧ��
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

	//ʱ��ת��
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
* ��������GetUnxfmtFromContfmt
* ���ܣ� ������"19700101000000"ʱ���ʽװ��������"1970-01-01 
*                   00:00:00"ʱ���ʽ�ַ���
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              unxcontent  string &            in/out                 ����"1970-01-01  00:00:00"
*              contcontent  const char *     IN                      ��ת����ʱ���ַ���
*              content        int                   IN                       ָ��ʱ������
Ĭ��ֵ: SDBL_CONTENT_ALL
* ����ֵ����������ֵ 0  :�ɹ�������ת��ʧ��
*****************************************************************************/
int GetUnxfmtFromContfmt(string & unxcontent , const char * contcontent,
						 int content )
{
	//��������Ϸ���У��
	string tmpstr(contcontent);
	Trim( tmpstr) ;
	int length = (int)tmpstr.size() ;
	if ( length > 14 )
	{
		return 1 ; //����ʱ�����contfmt̫��
	}
	else
	{
		string alphacontent("0123456789") ;
		for(int i = 0 ; i < length ; i++)
		{
			if(std::string::npos == alphacontent.find(tmpstr[i]))
			{
				return 2 ; //����ʱ�����contfmt���зǷ��ַ�
			}
		}
	}

	char szTime[20] ;
	memset(szTime , 0 , sizeof(szTime));
	char * pos = szTime ;
	int num ;

	//ʱ��ת��
	if ( length < 4 )
	{
		return 3 ; //���Ȳ���
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
			return 4 ; //ʱ�����곬��70-138��Χ
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
			return 5 ; //�·ݳ���0-11��Χ
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
			return 6 ; //��������1-31��Χ
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
			return 7 ; //Сʱ����0-23��Χ
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
			return 8 ; //���ӳ���0-59��Χ
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
			return 9 ; //���ӳ���0-59��Χ
		}
	}

	unxcontent = szTime;

	return 0 ;

}

/***************************************************************************
* ��������GetContfmtFromUnxfmt
* ���ܣ� ������"1970-01-01 00:00:00"unixʱ���ʽװ����time_t����
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              contcontent      string &           in/out             ��������"19700101000000"
��ʽ�ַ���
*              unxcontent  const char *      IN                      ��ת����ʱ���ַ���
*              content        int                   IN                       ָ��ʱ������
Ĭ��ֵ: SDBL_CONTENT_ALL
* ����ֵ����������ֵ 0  :�ɹ�������ת��ʧ��
*****************************************************************************/
int GetContfmtFromUnxfmt(string & contcontent , const char * unxcontent,
						 int content  )
{
	//��������Ϸ���У��
	string tmpstr(unxcontent);
	Trim( tmpstr) ;
	int length = (int)tmpstr.size() ;
	if ( length > 19 )
	{
		return 1 ; //����ʱ�����unxfmt̫��
	}
	else
	{
		string alphacontent("0123456789-: ") ;
		for(int i = 0 ; i < length ; i++)
		{
			if(std::string::npos == alphacontent.find(tmpstr[i]))
			{
				return 2 ; //����ʱ�����unixfmt���зǷ��ַ�
			}
		}
		if( (length < 4) ||((length > 4) &&(tmpstr.at(4) != '-' ) )|| ((length > 7) &&(tmpstr.at(7) != '-')) \
			||((length >10)&&(tmpstr.at(10) != ' '))||((length > 13) && (tmpstr.at(13) != ':')) \
			||((length >16) && (tmpstr.at(16) != ':') ))
		{
			return 3 ; //����ʱ�亯��unxfmt��ʽ����ȷ
		}

	}

	char szTime[20] ;
	memset(szTime , 0, sizeof(szTime));
	char * pos = szTime ;
	int num = 0 ;

	//ʱ��ת��
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
			return 4 ; //ʱ�����곬����Χ
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
			return 5 ; //�·ݳ���0-11��Χ
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
			return 6 ; //ÿ����������1-31��Χ
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
			return 7 ; //Сʱ����0-23��Χ
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
			return 8 ; //���ӳ���0-59��Χ
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
			return 9 ; //���ӳ���0-59��Χ
		}

	}

	contcontent = szTime ;

	return 0 ;

}

/***************************************************************************
* ��������GetDiffTime
* ���ܣ� ��ȡ����ʱ���ֵ(�����) time1-time2
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              time1          const char *      in                        ʱ�����1                 
*              time2          const char *      in                        ʱ�����2
*              content       int                    in                        �ڼ���ʱ���ֵ��Ҫ�õ�
ʱ�������bitset,Ĭ��ֵΪ
SDBL_CONTENT_ALL
*              fmtflag        int                   IN                         ָ���Ƚ���ʱ��ĸ�ʽ
Ĭ��ֵ: SDBL_FORMAT_UNiX
* ����ֵ��������ʱ���ֵ ��Ϊint����,����ֵ0��ʾʧ��
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
* ��������GetFirsttimeMonth
* ���ܣ� ��ȡָ��ʱ��(Ĭ�ϵ���)�����µ�����ʱ��
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              firsttime      string &             in/out                 ����ָ����ʽ����ʱ��                 
*              intime         const char *       in                        ָ��ʱ�䣬Ĭ�ϵ���
*              fmtflag        int                     in                        ָ��ʱ���ʽ
* ����ֵ�����������Ƿ�ɹ���־����0ʧ��
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
				return 1 ; //ʱ��ת������
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
				return 1 ; //ʱ��ת������
			}
		}
	}
	else
	{
		return 2 ; //ʱ���ʽ���󣬲�ͬ�ú����õ����
	}

	return 0 ;

}

/***************************************************************************
* ��������GetLasttimeMonth
* ���ܣ� ��ȡָ��ʱ��(Ĭ�ϵ���)�����µ���ĩʱ��
* ������
*              ������ �������� ���뷽ʽ    ����˵��
*              lasttime      string &             in/out                 ����ָ����ʽ����ʱ��                 
*              intime         const char *       in                        ָ��ʱ�䣬Ĭ�ϵ���
*              fmtflag        int                     in                        ָ��ʱ���ʽ
* ����ֵ�����������Ƿ�ɹ���־����0ʧ��
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
			return 1 ; //ʱ��ת������
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
			return 1 ; //ʱ��ת������
		}
	}


	return 0 ;

}


/*���ݴ����ʱ��(��ʽ:1970-01-01 00:00:00),��ȡ����*/
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
		week = "��";
		break;
	case 1:
		week = "һ";
		break;
	case 2:
		week = "��";
		break;
	case 3:
		week = "��";
		break;
	case 4:
		week = "��";
		break;
	case 5:
		week = "��";
		break;
	case 6:
		week = "��";
		break;
	default:
		break;
	}
	return week;
}


