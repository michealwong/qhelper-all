/*************************************************************
* �ļ�����������ʱ��ĳ� �ò�����
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

    //ʱ���ʽ�궨��
#define SDBL_FORMAT_UNIX 1  //����"1970-01-01 00:00:00"unixʱ���ʽ
#define SDBL_FORMAT_CONT 2  //����"19700101000000"�����ʱ���ʽ
#define SDBL_FORMAT_SECOND 3  //����"1187577006"���ʽ

    //ʱ����ʾ���ݺ�
#define SDBL_CONTENT_YEAR 1  //��
#define SDBL_CONTENT_MONTH 2  //��
#define SDBL_CONTENT_DAY 4  //��
#define SDBL_CONTENT_HOUR 8  //Сʱ
#define SDBL_CONTENT_MINUTE 16  //����
#define SDBL_CONTENT_SECOND 32  //����
#define SDBL_CONTENT_YMD SDBL_CONTENT_YEAR|SDBL_CONTENT_MONTH|SDBL_CONTENT_DAY //������
#define SDBL_CONTENT_ALL SDBL_CONTENT_YEAR|SDBL_CONTENT_MONTH|SDBL_CONTENT_DAY\
                                              |SDBL_CONTENT_HOUR|SDBL_CONTENT_MINUTE\
                                              |SDBL_CONTENT_SECOND //������ʱ����


    /*************************************************************
    * ��������GetCurDateTime
    * ���ܣ� ���㵱ǰ���ڣ���ʽ��%Y-%m-%d %H:%M:%S
    * ������
    *              ������       ��������       ���뷽ʽ   ����˵��
    *              strDateTime       string&                     IN/OUT               ��ǰʱ��
    * ����ֵ��void
    **************************************************************/
    DATETIME_API void GetCurDateTime(string& strDateTime);
	
	DATETIME_API string GetCurDateDay();
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
    DATETIME_API void DiffDateTime(string& strDateTime, long iValue);
    
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
    DATETIME_API string GetTime(int day = 0, int fmtflg = SDBL_FORMAT_UNIX , int content =SDBL_CONTENT_ALL );
    
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
    DATETIME_API string GetTimeByDay(int day = 0, int fmtflg = SDBL_FORMAT_UNIX , int content =SDBL_CONTENT_ALL );
    

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
    DATETIME_API int GetTmsecFromUnxfmt(time_t & time_sec , const char * unxcontent,
                                  int content =SDBL_CONTENT_ALL );
    

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
    DATETIME_API int GetTmsecFromContfmt(time_t & time_sec , const char * contcontent,
                                   int content =SDBL_CONTENT_ALL );
   
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
    DATETIME_API int GetUnxfmtFromTmsec(string & unxfmt , const time_t  tmsec,
                                  int content =SDBL_CONTENT_ALL );
  
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
    DATETIME_API int GetUnxfmtFromContfmt(string & unxcontent , const char * contcontent,
                                    int content =SDBL_CONTENT_ALL );
    

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
    DATETIME_API int GetContfmtFromUnxfmt(string & contcontent , const char * unxcontent,
                                    int content =SDBL_CONTENT_ALL );
    
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
    DATETIME_API int GetDiffTime(const char * time1 , const char * time2 , int content = SDBL_CONTENT_ALL ,
                           int fmtflag = SDBL_FORMAT_UNIX);
   

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
    DATETIME_API int GetFirsttimeMonth(string & firsttime , const char * intime = NULL , int  fmtflag =
                                     SDBL_FORMAT_UNIX);
   
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
    DATETIME_API int GetLasttimeMonth(string & lasttime , const char * intime = NULL , int  fmtflag =
                                    SDBL_FORMAT_UNIX);
    

    /*���ݴ����ʱ��(��ʽ:1970-01-01 00:00:00),��ȡ����*/
    DATETIME_API string GetWeek(string s);
    
#ifdef __cplusplus
}
#endif

#endif

