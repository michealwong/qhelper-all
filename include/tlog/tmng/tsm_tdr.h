#ifndef _TSM_TDR_H_
#define _TSM_TDR_H_
//============================================================================
// @Id:       $Id: tsm_tdr.h 30201 2012-01-05 01:46:04Z vinsonzuo $
// @Author:   $Author: vinsonzuo $
// @Date:     $Date:: 2012-01-05 09:46:04 +0800 #$
// @Revision: $Revision: 30201 $
// @HeadURL:  $HeadURL:: https://sz-svn4.tencent.com/ied/ied_tsf4g_rep/tsf4g#$
//----------------------------------------------------------------------------

/*!
 * \file tsm_tdr.h
 * \brief tsm for tdr api
 * \version 1.0
 * date 2010-09-13
 */

#include <sys/types.h>

#include "tdr/tdr_metalib_init.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * \brief
 * TSM_URI ��һ���������ߣ�������������λ�ã���ѯ�������
 * ���� Tdr��ʽ�Ĺ����ڴ������˵���б�Ҫ���� TsmUriTdr�ĸ�ʽ���ڲ���ʾ
 *
 * TSM URI for TDR ��ʽ:
 *      tsm-data://<bussi-id>/<proc-name>:<proc-id>/<func-name>/<...>
 *          ���ǵ�һ�ָ�ʽ������ data ��ʽ
 *
 * <1> bussi_id           ҵ��id������: ����ˣ�QQ���룻QQ�ɳ����ڲ���ʶ
 * <2> process_name       ������������: torm_server
 * <3> process_id         ���̺ţ���ͬ�������Ĳ�ͬʵ��
 *                        ����������ֽ��̣����λ�ÿ���Ϊ��
 * <4> function_name      ������������: config, status
 * <5> ...                ������ֶο����Զ���
 *
 *      tsm-meta://<bussi-id>/<lib>:<ver>:<build_ver>/<meta>:<ver>:<size>/<...>
 *          ���ǵڶ��ָ�ʽ������ meta ��ʽ
 *          ����
 * <1> bussi_id           ҵ��id������: ����ˣ�QQ���룻QQ�ɳ����ڲ���ʶ
 * <2> lib                �� metalib����
 * <3> ver                �� metalib�汾��
 * <4> build_ver          �� metalib�� build�汾��
 * <5> meta               �� meta ������
 * <6> ver                �� meta �İ汾
 * <7> size               �� meta �ĳߴ�
 * <8> ...                ������ֶο����Զ���
 *      ���ֻ�� tsm-meta://<bussi-id>/<lib-name>/ �����һ�� lib
 *
 * ���ָ�ʽ�У��κ�<>���������ֶζ����Ի���?(��ʾ��ѯ) ���� *(��ʾ������)
 *      һ����ѯ URI����ֻ��һ�� ?�ֶΣ������� 0������ *�ֶ�
 *      һ����ѯ URI������ *�ֶο���ʡ�Բ�д
 *          �������ѯϵͳ������Щ bussiness����ֱ���� tsm-data://?
 */

/*!
 * \brief   API һ��Ҫ�ṩ���ֹ��ܣ��ֱ���
 *          1 ������
 *          2 ��ĳ�� data ��ĳ�� meta �󶨣������趨һ�� data �ĳߴ�
 *          3 �� data ���� meta �����������ڴ���
 *          4 �ӹ����ڴ��л�� data ָ��
 *          5 �� data �ӹ����ڴ���ɾ��
 *          6 ȡ�ù����ڴ��е� data ���� meta ����
 *      ��ѯ����������ڴ����Ѿ����ڵ� data ���� meta
 */

/*!
 * \brief 0 ������ API
 *      Ϊ��ʹ API�������������е� API����һ����������
 *      ���� API�����þ�����ݴ�����
 *      ÿ�ε��� API֮ǰ����ؾ���еĴ�����Ϣ�������
 */
typedef void *TsmTdrHandleP;

/*!
 * \fn      int tsm_tdr_base_set(int a_iIndexKey, int a_iLibCap, int a_iUriCap);
 * \brief   �����ĸ��������Ժ�����Щ�������� index
 *          ���ĸ�������ֻ���� tsm_index_init  ֮ǰ����
 *          ����ʹ��ȱʡֵ��ȱʡֵ�� tsm_base  �е�����ʼ������������
 * \param
 *          \li a_iIndexKey �����������Ψһ��ʶһ�� index
 *          \li a_iLibCap   ÿ�� Index�����������ɶ����� Lib��¼
 *          \li a_iUriCap   ÿ�� Index�����������ɶ����� Uri��¼
 * \return  ��Ч�����ø���
 * \n
 */
int tsm_tdr_base_set(int a_iIndexKey, int a_iLibCap, int a_iUriCap);

/*!
 * \fn      int tsm_tdr_open(TsmTdrHandleP *a_pHandle);
 * \brief   ��� TsmTdrHandleP ���
 * \param   a_pHandle   ���صľ���洢λ��
 * \return  ʧ�ܷ��� TSM_TDR_HANDLE_NULL
 *          ���򷵻ؾ����������Ҳ���� tagTsmTdrHandleP�����һ������
 */
int tsm_tdr_open(TsmTdrHandleP *a_pHandle);

/*!
 * \fn      int tsm_tdr_init(TsmTdrHandleP a_pHandle);
 * \brief   ��ʼ�� TsmTdrHandleP �������������� tsm_tdr_open�ڲ����õ�
 *          �����������ʱ������Ŀռ�������Ѿ�������˵�
 *          ���� TsmTdrHandleP�� void * û�취֪��Ҫ������ٿռ�
 *          ��������������ʺ��û�������
 * \param   a_pHandle   ����ʼ���ľ��
 * \return  ʧ�ܷ��� TSM_TDR_HANDLE_NULL
 *          ���򷵻ؾ����������Ҳ���� tagTsmTdrHandleP�����һ������
 */
//int tsm_tdr_init(TsmTdrHandleP a_pHandle);

/*!
 * \fn      int tsm_tdr_close(TsmTdrHandleP *a_pHandle);
 * \brief   �ر�һ�� TsmTdrHandleP ���
 * \param   a_pHandle   ���رյľ��ָ��
 * \return  �ɹ����� 0
 * \n
 *          �����������
 *          \li -1  �������Ϊ��
 *          \li  1  ����ѱ��ƻ�
 */
int tsm_tdr_close(TsmTdrHandleP *a_pHandle);

/*!
 * \fn      int tsm_tdr_destroy(TsmTdrHandleP a_pHandle);
 * \brief   ����һ�� TsmTdrHandleP �������������� tsm_tdr_close �ڲ����õ�
 *          �����������ʱ������Ŀռ�������Ѿ�������˵�
 *          ���� TsmTdrHandleP�� void * û�취֪��Ҫ������ٿռ�
 *          ��������������ʺ��û�������
 * \param   a_pHandle   �������ľ��ָ��
 * \return  �ɹ����� 0
 * \n
 *          �����������
 *          \li -1  �������Ϊ��
 *          \li  1  ����ѱ��ƻ�
 */
//int tsm_tdr_destroy(TsmTdrHandleP a_pHandle);


/*!
 * \brief 1 ��������� API
 */
//typedef void *TErrorSetP;

/*!
 * \fn      TErrorSetP tsm_tdr_error(TsmTdrHandleP a_pHandle);
 * \brief   �����һ�� APIִ�й����еĴ���ջ���
 * \param   a_pHandle   tsm_tdr ���
 * \return  ���� NULL ����Ϊ tsm tdr�����ջʹ��ȱʡ����ջ
 */
//TErrorSetP tsm_tdr_error(TsmTdrHandleP a_pHandle);


/*!
 * \brief 2 ����� API
 *      һ������Ͽ��԰����ֲ�ͬ�ı���
 *      1  data ��ʽ�� URI
 *      2  meta ��ʽ�� URI
 *      3  data ��ʽ�� URIָ���Ľṹ��ߴ�
 *  �����ֱ����������ڣ����ǻ���֮����һ����Լ��
 */

/*!
 * \fn      int tsm_tdr_bind_data(TsmTdrHandleP  a_pHandle,
 *                                const char    *a_pszUri);
 * \brief   ��һ�� data ��ʽ�� URI�󶨵�����ϣ�����
 *          �Ӿ�������һ�� data ��ʽ (pszUri�� tsm-data://...)
 *          �ɹ�����ʱ�����ϵͳ���Ѿ�������� uri
 *          ����� api��ͬʱ���¾���� meta �󶨺� size ��
 *          ������� meta �󶨺����� size ��
 * \param
 *          \li a_pHandle   tsm_tdr ���
 *          \li a_pszUri    ϣ���󶨵�����ϵ� data URI
 * \return  �ɹ����� 0�����򷵻�
 *          \li -1  �������Ϊ��
 *          \li -2  �������״̬Ϊ�ر�
 *          \li -3  URI �ַ�����ʽ����
 *          \li -4  URI ���ʹ��󣬻����������̳���
 *          \li -5  �����ڵ����ʧ��
 */
int tsm_tdr_bind_data(TsmTdrHandleP a_pHandle, const char *a_pszUri);

/*!
 * \fn      int tsm_tdr_bind_meta(TsmTdrHandleP  a_pHandle,
 *                                const char    *a_pszUri);
 * \brief   ��һ�� meta ��ʽ�� URI�󶨵������
 *          ������� api֮ǰ����Ҫ���㼸������
 *          ������ָ��� meta ��ϵͳ���Ѿ����ڣ����߿����Զ�����
 *          ����� data �󶨲���Ϊ��
 *          ����� meta �󶨱���Ϊ�ջ����������ͬ
 *          ����� size ��Ϊ�㣬���ߵ��ڴ��󶨵� meta ����ȡ�ĳߴ�
 * \param
 *          \li a_pHandle   tsm_tdr ���
 *          \li a_pszUri    ϣ���󶨵�����ϵ� meta URI
 * \return  �ɹ����� 0�����򷵻�
 *          \li -1  �������Ϊ��
 *          \li -2  �������״̬Ϊ�ر�
 *          \li -3  ��Ҫ�� bind data
 *          \li -4  URI �ַ�����ʽ����
 *          \li -5  URI ���ʹ���
 *          \li -6  ����� Meta �ʹ����õ� Meta ��ƥ��
 *          \li -7  ���󶨵� meta ϵͳ�в�����
 *          \li -8  �����ڵ����ʧ��
 *          \li -9  ��ù����ڴ�ʧ��
 *          \li -10 �����ڴ�ߴ�Ϊ��
 *          \li -11 ����гߴ�����󶨵� Meta ��ƥ��
 */
int tsm_tdr_bind_meta(TsmTdrHandleP a_pHandle, const char *a_pszUri);

/*!
 * \fn      int tsm_tdr_bind_size(TsmTdrHandleP a_pHandle, size_t a_iSize);
 * \brief   ��һ���ߴ���Ϣ�󶨵������
 *          ������� api֮ǰ����Ҫ���㼸������
 *          ����� data �󶨲���Ϊ��
 *          ����� meta �󶨱���Ϊ��
 *          ����� size ��Ϊ�㣬�����������ͬ
 * \param
 *          \li a_pHandle   tsm_tdr ���
 *          \li a_iSize     ϣ���󶨵�����ϵĳߴ�
 * \return  �ɹ����� 0�����򷵻�
 *          \li -1  �������Ϊ��
 *          \li -2  �������״̬Ϊ�ر�
 *          \li -3  �������� a_iSize Ϊ��
 *          \li -4  ��Ҫ�� bind data
 *          \li -5  meta ���� size ��ͻ
 *          \li -6  ����� Size �ʹ����õ� Size ��ƥ��
 */
int tsm_tdr_bind_size(TsmTdrHandleP a_pHandle, size_t a_iSize);

/*!
 * \brief ȡ�þ���ϰ󶨹��� URI�ͽṹ��ߴ�
 */

/*!
 * \fn      const char *tsm_tdr_bind_get_data(TsmTdrHandleP a_pHandle);
 * \brief   ��þ���ϰ󶨵� data URI
 * \param   a_pHandle   tsm_tdr ���
 * \return  �ɹ����� data URI, ���򷵻� NULL �����ô����ջ
 */
const char *tsm_tdr_bind_get_data(TsmTdrHandleP a_pHandle);

/*!
 * \fn      const char *tsm_tdr_bind_get_meta(TsmTdrHandleP a_pHandle);
 * \brief   ��þ���ϰ󶨵� meta URI
 * \param   a_pHandle   tsm_tdr ���
 * \return  �ɹ����� meta URI, ���򷵻� NULL �����ô����ջ
 */
const char *tsm_tdr_bind_get_meta(TsmTdrHandleP a_pHandle);

/*!
 * \fn      const char *tsm_tdr_bind_get_size(TsmTdrHandleP a_pHandle);
 * \brief   ��þ���ϰ󶨵� size
 * \param   a_pHandle   tsm_tdr ���
 * \return  �ɹ����� size, ���򷵻� NULL �����ô����ջ
 */
size_t      tsm_tdr_bind_get_size(TsmTdrHandleP a_pHandle);


/*!
 * \brief 3 ������� API
 */

/*!
 * \fn      int tsm_tdr_load_data(TsmTdrHandleP  a_pHandle,
 *                                void          *a_pData,
 *                                int            a_iFlag);
 * \brief   ���� data ��ϵͳ��
 *          ������� api֮ǰ����Ҫ���㼸������
 *          ����� data �󶨲���Ϊ��
 *          ����� size �󶨲���Ϊ��
 * \param
 *          \li a_pHandle   tsm_tdr ���
 *          \li a_pData     ָ������������ݣ�����: (struct tagUserData *)
 *                          ���ݳ���Ϊ����� size ��
 *          \li a_iFlag     ��־����������ĺ�����ϵͳ���� open ���Ӽ�
 *                          ���� O_CREATE, O_EXCL, O_NONBLOCK or O_NDELAY
 * \return  �ɹ����� 0�����򷵻ش������
 *          \li  1          a_iFlag ��־��ͻ
 *          \li -1          ��ȡ size ʧ��
 *          \li -2          ��ȡ�����ڴ�ָ��ʧ��
 *          \li -3          �ͷŹ����ڴ�ָ��ʧ��
 */
int tsm_tdr_load_data(TsmTdrHandleP a_pHandle, void *a_pData, int a_iFlag);

/*!
 * \fn      int tsm_tdr_load_meta(TsmTdrHandleP a_pHandle,
 *                                LPTDRMETALIB  a_pData,
 *                                int           a_iBid);
 * \brief   ���� metalib��ϵͳ��
 * \param
 *          \li a_pHandle   tsm_tdr ���
 *          \li a_pData     LPTDRMETALIB ָ��һ�� metalib
 *          \li a_iBid      ҵ�� ID
 * \return  �ɹ����� 0�����򷵻ش������
 *          \li -1          tsm_tdr ���Ϊ��
 *          \li -2          tsm_tdr ����ѹر�
 *          \li -3          a_pData Ϊ��
 *          \li -4          �ڲ����� URI��ʽ����
 *          \li -5          �ڲ����� URI���ʹ���
 *          \li -6          URI ��ѯ����
 *          \li -7          �ҵ�����ƥ���¼
 *          \li -8          Meta Obj����ʧ��
 *          \li -9          �ڲ���������ʱ������Խ��
 *          \li -10         �ڲ���������ʱ�����ù����ڴ�ָ��ʧ��
 *          \li -11         �ڲ���������ʱ������ hash ���ʧ��
 */
int tsm_tdr_load_meta(TsmTdrHandleP a_pHandle,
                      LPTDRMETALIB  a_pData,
                      int           a_iBid);

/*!
 * \fn      int tsm_tdr_load_meta_file(TsmTdrHandleP  a_pHandle,
 *                                     const char    *a_pszPath,
 *                                     int            a_iBid);
 * \brief   ��һ���������ļ��е� metalib������ϵͳ��
 * \param
 *          \li a_pHandle   tsm_tdr ���
 *          \li a_pszPath   METALIB �ļ�·��
 *          \li a_iBid      ҵ�� ID
 * \return  �ɹ����� 0�����򷵻ش������
 *          \li -1          tsm_tdr ���Ϊ��
 *          \li -2          tsm_tdr ����ѹر�
 *          \li -3          װ�� metalib ʧ��
 *          \li -4          Lib ��ʽ����
 */
int tsm_tdr_load_meta_file(TsmTdrHandleP  a_pHandle,
                           const char    *a_pszPath,
                           int            a_iBid);


/*!
 * \brief 4 ����ȡ����� API
 */

typedef void *TsmObjPtrP;

/*!
 * \fn      TsmObjPtrP tsm_tdr_ptr(TsmTdrHandleP a_pHandle, int a_iFlag);
 * \brief   ��þ���а󶨵� data ��ʽ URI��ָ��ģ��ڹ����ڴ��е�ָ��ṹ
 * \param
 *          \li a_pHandle   tsm_tdr ���
 *          \li a_iFlag     ��־����������ĺ�����ϵͳ���� open ���Ӽ�
 *                          ���� O_CREAT, O_EXCL, O_NONBLOCK or O_NDELAY
 * \return
 *          \li NULL        ������������ѹ�����ջ
 *          \li -1          a_iFlag ������������
 *          \li �������    �ɹ�
 */
TsmObjPtrP tsm_tdr_ptr(TsmTdrHandleP a_pHandle, int a_iFlag);

/*!
 * \fn      void *tsm_tdr_at(TsmObjPtrP a_pPtr, int a_iReadOnly);
 * \brief   ���� PTR��ָ��ģ��ڹ����ڴ��еĽṹ
 * \param   a_iReadOnly     ��ʾ��δ򿪲���ȡ�õĿռ�
 * \return  NULL ����ʧ�ܣ�������ָ��ṹ��ָ��
 */
void *tsm_tdr_at(TsmObjPtrP a_pPtr, int a_iReadOnly);

/*!
 * \fn      int tsm_tdr_dt(void *a_pAt);
 * \brief   �ͷ� tsm_tdr_at ���ص�ָ��
 *          �����������֮�󣬲��ٱ�֤�Ǹ�ָ��ָ����ȷ�Ľṹ��
 *          �ڲ�ʵ����Ҫ�ǶԹ����ڴ����ݽ����Ĺ���
 *          �û�����Ӧ�óɶԵ�ʹ�� at, dt
 *          ������ at ֮�󾡿��ʹ�� dt (��ʹ������)
 * \param   a_pAt           ͨ�� tsm_tdr_ptr���û�õ�ָ��
 * \return  �ɹ����� 0�����򷵻ش������
 *          \li -1          �ڴ�ָ��Ϊ��
 *          \li -2          �ڴ�ָ��Ϊ -1
 *          \li -3          ָ����ָ����ڴ治ƥ��
 *          \li -4          Index ��ƥ��
 */
int tsm_tdr_dt(void *a_pAt);


/*!
 * \brief 5 ��ѯ��� API���ⲿ�� API��ģ�� MySQL
 */

typedef void *TsmTdrResultP;
typedef void *TsmTdrRowP;

/*!
 * \fn      int tsm_tdr_query(TsmTdrHandleP a_pHandle, const char *a_pszUri);
 * \brief   ִ��һ����ѯ
 * \param
 *          \li a_pHandle   tsm_tdr ���
 *          \li a_pszUri    ����ѯ�� URI
 * \return  ����ֵ��С���㣬��ʾ��ѯ���Ľ����������Ľ����Ŀ
 *          ���򣬷��ش������
 *          \li -1          tsm_tdr ���Ϊ��
 *          \li -2          URI ��ʽ����
 *          \li -3          ��ѯ����
 *          \li -4          �ڴ����ʧ��
 */
int tsm_tdr_query(TsmTdrHandleP a_pHandle, const char *a_pszUri);

/*!
 * \fn      TsmTdrResultP tsm_tdr_store_result(TsmTdrHandleP a_pHandle);
 * \brief   ������һ�� query��ѯ�Ľ����
 *          һ�β�ѯ֮������ظ����ô˺����������һ���⣬���涼���� NULL
 * \param   a_pHandle       tsm_tdr ���
 * \return  ����ɹ������ؽ����ָ�룬���򷵻� NULL
 */
TsmTdrResultP tsm_tdr_store_result(TsmTdrHandleP a_pHandle);

/*!
 * \fn      int tsm_tdr_num_rows(TsmTdrResultP a_pResult);
 * \brief   ���ؽ�����м�¼������
 * \param   a_pResult       �����ָ��
 * \return
 *          \li -1          �����ָ��Ϊ��
 *          \li �������    ������м�¼��
 */
int tsm_tdr_num_rows(TsmTdrResultP a_pResult);

/*!
 * \fn      int tsm_tdr_data_seek(TsmTdrResultP a_pResult, int a_iIndex);
 * \brief   �ڽ�����ж�λһ����¼
 * \param
 *          \li a_pResult   �����ָ��
 *          \li a_iIndex    ������м�¼����������ΧΪ [0, num_rows)
 * \return  �ɹ����� 0�����򷵻ش������
 *          \li -1          �����ָ��Ϊ��
 *          \li -2          ����Խ��
 */
int tsm_tdr_data_seek(TsmTdrResultP a_pResult, int a_iIndex);

/*!
 * \fn      int tsm_tdr_free_result(TsmTdrResultP a_pResult);
 * \brief   �ͷ�һ�������
 * \param   ���ͷŵĽ����
 * \return  ���� 0
 */
int tsm_tdr_free_result(TsmTdrResultP a_pResult);


/*!
 * \fn      TsmTdrRowP tsm_tdr_fetch_row(TsmTdrResultP a_pResult);
 * \brief   �ӽ�����з���һ�У�����Ѿ������β������ NULL
 * \param   a_pResult       �����ָ��
 * \return  �� a_pResult���ǿյ�ʱ�򣬷���һ����¼�� NULL(�Ѿ�����������β)
 */
TsmTdrRowP tsm_tdr_fetch_row(TsmTdrResultP a_pResult);

/*!
 * \fn      int tsm_tdr_row_unlink(TsmTdrRowP a_pRow, TsmTdrHandleP a_pHandle);
 * \brief   ɾ��һ�м�¼
 * \param
 *          \li a_pRow      ��¼ָ��
 *          \li a_pHandle   tsm_tdr ���
 * \return  �ɹ����� 0�����򷵻ش������
 *          \li -1          tsm_tdr ���Ϊ��
 *          \li -2          tsm_tdr ���Ϊ�ر�״̬
 *          \li -3          ��¼ָ��Ϊ�ջ�ɾ�� data  hash �ڵ�ʧ��
 *          \li -4          ɾ�� data �����ڴ�ʧ��
 *          \li -5          ɾ�� meta  hash ���ʧ��
 *          \li -6          ɾ�� meta �����ڴ�ʧ��
 */
int         tsm_tdr_row_unlink  (TsmTdrRowP a_pRow, TsmTdrHandleP a_pHandle);


/*!
 * \fn      int tsm_tdr_row_type(TsmTdrRowP a_pRow);
 * \brief   �Ӽ�¼����ȡ������
 * \param   a_pRow          ��¼ָ��
 * \return  ��¼ָ��Ϊ��ʱ���� -1 �����򷵻�������
 */
int         tsm_tdr_row_type    (TsmTdrRowP a_pRow);

/*!
 * \fn      int tsm_tdr_row_is_data(TsmTdrRowP a_pRow);
 * \brief   �жϼ�¼�Ƿ�Ϊ data ����
 * \param   a_pRow          ��¼ָ��
 * \return  �Ƿ��� 1�����򷵻� 0
 */
int         tsm_tdr_row_is_data (TsmTdrRowP a_pRow);

/*!
 * \fn      int tsm_tdr_row_is_meta(TsmTdrRowP a_pRow);
 * \brief   �жϼ�¼�Ƿ�Ϊ meta ����
 * \param   a_pRow          ��¼ָ��
 * \return  �Ƿ��� 1�����򷵻� 0
 */
int         tsm_tdr_row_is_meta (TsmTdrRowP a_pRow);

/*!
 * \fn      const char *tsm_tdr_row_meta_uri(TsmTdrRowP a_pRow);
 * \brief   ��ü�¼�� data URI �� meta URI ��
 * \param   a_pRow          ��¼ָ��
 * \return  �����¼�� data URI ���� meta URI �󶨹����򷵻���� meta URI
 *          ���򣬷��� NULL
 */
const char *tsm_tdr_row_meta_uri(TsmTdrRowP a_pRow);

/*!
 * \fn      const char *tsm_tdr_row_uri(TsmTdrRowP a_pRow);
 * \brief   ��ü�¼�� URI
 * \param   a_pRow          ��¼ָ��
 * \return  �����¼���ʹ��󣬷��� NULL �����򷵻ؼ�¼ URI
 */
const char *tsm_tdr_row_uri     (TsmTdrRowP a_pRow);

/*!
 * \fn      TsmObjPtrP tsm_tdr_row_meta_ptr(TsmTdrRowP a_pRow);
 * \brief   ��� meta �����ڴ�ָ��ṹ
 * \param   a_pRow          ��¼ָ��
 * \return  ��¼Ϊ�ջ����ڴ�ߴ�Ϊ�㣬���� NULL �����򷵻ؽṹָ��
 */
TsmObjPtrP  tsm_tdr_row_meta_ptr(TsmTdrRowP a_pRow);

/*!
 * \fn      TsmObjPtrP tsm_tdr_row_data_ptr(TsmTdrRowP a_pRow);
 * \brief   ��� data �����ڴ�ָ��ṹ
 * \param   a_pRow          ��¼ָ��
 * \return  ��¼Ϊ�ջ����ڴ�ߴ�Ϊ�㣬���� NULL �����򷵻ؽṹָ��
 */
TsmObjPtrP  tsm_tdr_row_data_ptr(TsmTdrRowP a_pRow);

/*!
 * \fn      LPTDRMETA tsm_tdr_row_meta(TsmTdrRowP a_pRow);
 * \brief   ��ü�¼�е� meta ָ��
 * \param   a_pRow          ��¼ָ��
 * \return  �����¼��Ϊ�գ��Ҽ�¼�д��� meta ָ�룬�������ָ�룻���򷵻� NULL
 */
LPTDRMETA   tsm_tdr_row_meta    (TsmTdrRowP a_pRow);

/*!
 * \fn      LPTDRMETA tsm_tdr_row_data(TsmTdrRowP a_pRow, int a_iReadOnly);
 * \brief   ��ü�¼�е� data ָ��
 * \param
 *          \li a_pRow          ��¼ָ��
 *          \li a_iReadOnly     ���ص�ָ����ָ��������Ƿ������޸�
 * \return  �����¼��Ϊ�գ��Ҽ�¼�д��� data ָ�룬�������ָ�룻���򷵻� NULL
 */
void       *tsm_tdr_row_data    (TsmTdrRowP a_pRow, int a_iReadOnly);

/*!
 * \fn      size_t tsm_tdr_row_size(TsmTdrRowP a_pRow);
 * \brief   ��ü�¼�� size
 * \param   a_pRow          ��¼ָ��
 * \return  �����¼ָ��Ϊ�ջ����ʹ��󣬷��� 0�����򷵻ؼ�¼�� size
 */
size_t      tsm_tdr_row_size    (TsmTdrRowP a_pRow);

/*!
 * \fn      TsmTdrRowP tsm_tdr_row_only(TsmTdrHandleP a_pHandle);
 * \brief   ��ʱ����������ȷ��֪����ѯ�ķ���ֻ��һ��
 *          ��ʱ�����ü򻯵� api������һ��
 *          ��һ����ѯ֮ǰ�����ص���������Ч��
 * \param   a_pHandle       tsm_tdr ���
 * \return  �������������ֻ��Ψһ��һ�У�������һ�У����򷵻� NULL
 */
TsmTdrRowP tsm_tdr_row_only(TsmTdrHandleP a_pHandle);

/*!
 * \fn      TsmTdrRowP tsm_tdr_row_first(TsmTdrHandleP a_pHandle);
 * \brief   ��ʱ��������ֻ�봦�������е�����һ��
 *          ��ʱ�����ü򻯵� api������һ��
 *          ��һ����ѯ֮ǰ�����ص���������Ч��
 * \param   a_pHandle       tsm_tdr ���
 * \return  ������������ǿգ����ص�һ�У����򷵻� NULL
 */
TsmTdrRowP tsm_tdr_row_first(TsmTdrHandleP a_pHandle);


/*!
 * \brief һЩ˵��
 * TSM TDR API ��Ŀ�����ڲ�ͬ�����й������ݣ����Թ��������������
 *
 *      1 Ԫ���� meta
 *           һ�� meta ������һ�� metalib��
 *           һ�� metalib��Ϊһ�����巢����ϵͳ��
 *           ϵͳͨ�� libname��metaname��version ���ֲ�ͬ��Ԫ����
 *           Ԫ����һ���������Ͳ���ɾ��
 *
 *      2 �ṹ�壬���Ǿ��������
 *           һ���ṹ�巢����ϵͳ�У��ḽ����������datauri��metauri��datasize
 *           ��� metauri�� datasize ͬʱ���ڣ����������Բ��ܳ�ͻ
 *           metauri ���ڵ�ʱ��datasize����ʡ�ԣ���Ϊ�� meta �п�����ȡsize
 *           datasize��������ʱ��ϵͳ֮��ĵĽ��̿��Կ�������ṹ��
 *           ����ֻ֪���ṹ��ĳߴ粻֪������ṹ��ĸ�ʽ���������������
 */


#ifdef __cplusplus
}
#endif


//----------------------------------------------------------------------------
// THE END
//============================================================================
#endif
