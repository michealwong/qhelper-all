/** @defgroup global ȫ�ֽӿ�
 *  ȫ��ͷ����
 *  @{
 */

#ifndef SAP_H
#define SAP_H


#ifdef __cplusplus
extern "C" {
#endif


/////////////////////////////////////////////////////////////////////////
/*
	ȫ��ID��ṹ����
*/
//////////////////////////////////////////////////////////////////////////
#define SAP_API_VERSION					101028						/*!< SAP�汾 */
#define SAP_MAX_NAME_LENGTH				256							/*!< ������ֳ��� */
#define SAP_MAX_ATTRIBUTE_NAME_SIZE		64							/*!< ������������� */
#define SAP_MAX_PATH_NAME_LENGTH		64							/*!< ���·������ */
#define MAXUPLOADFILESIZE				20480000					/*!< �ϴ��ļ����ߴ� */
#define SAFEDELETE(p) if( p != NULL ){delete p;p = NULL;}			/*!< ��ȫɾ�� */


// ����ͳ������
#define SAP_STAT_ACCESS			1	// ���ܷ��ʴ���ͳ��
#define SAP_STAT_Elapsed_Time	2	// ������Ӧʱ��ͳ��
#define SAP_STAT_WARN			3	// ���ܱ�������ͳ��

// SAPƽ̨�Ƿ������֤Ȩ��(����sapmanager��sas)
#define SAP_IGNORE_AUTH	0


typedef void*  SAP_Object;											/*!< �ն��� */
typedef int	   SAP_ErrCode;											/*!< �����������*/

//! �������
enum
{
	// ���ô����붨��
    SAP_NoErr              	= 0,				/*!< �޴��� */
	SAP_Failed				= -1,				/*!< ʧ�� */
	SAP_Exception			= -2,			/*!< �쳣 */
	SAP_Unknown				= -99,				/*!< δ֪����*/

	// ƽ̨������
	//////////////////////////////////////////////////////////////////////
	// ƽ̨�߼��������,��ѯ����
	SAP_FailedReadConf			= -10000,				/*!<��ȡ����ʧ�� */
	SAP_FuncIdNull				= -10001,				/*!<����IdΪ�� */
	SAP_FailedQueryFuncInfo		= -10002,				/*!<��ѯ����������Ϣʧ�� */
	SAP_NoFuncIdFound			= -10003,				/*!<δ�ҵ��ù������� */
	SAP_NoRight					= -10004,				/*!<�û��޴˲���Ȩ�� */
	SAP_FailedParseFuncRule		= -10005,				/*!<���������߼�����ʧ��	*/	
	SAP_InvalidFuncRule			= -10006,				/*!<��Ч�����߼����� */	
	SAP_LackInputParam			= -10007,				/*!<ȱ�ٴ������ */	
	SAP_FailedCallInterface		= -10008,				/*!<���ò�ѯ�ӿ�ʧ�� */	
	SAP_ErrForDataQuery			= -10009,				/*!<���ݲ��ѯ���� */	
	SAP_EmptyCookie				= -10010,				/*!<CookieΪ�� */	
	SAP_EmptyUser				= -10011,				/*!<��Ч�û��� */	


	// ƽ̨���ݲ������,��ѯ����
	SAP_InvalidQueryInputParam	= -20000,				/*!<��Ч��ѯ������� */
	SAP_NoFindDbRecord			= -20001,				/*!<δ�ҵ������ݿ�ļ�¼*/
	SAP_InvalidDbName			= -20002,				/*!<��Ч���ݿ����� */
	SAP_ErrSQLQuery				= -20003,				/*!<SQL��ѯ���� */
	SAP_DBQueryException		= -20004,				/*!<DB��ѯ�쳣 */
	SAP_FailedParseDbname		= -20005,				/*!<�������ݿ���ʧ��*/	
	SAP_FailedQueryMultiTb		= -20006,				/*!<����ѯʧ�� */	
	SAP_InvalidXmlDoc			= -20007,				/*!<��Чdb XML�ĵ� */	
	SAP_InvalidXmlDbRule		= -20008,				/*!<��ЧXML���� */	
	SAP_NoFindParam				= -20009,				/*!<���������� */	
	SAP_FailedParseDBID			= -20010,				/*!<����DBIDʧ�� */	
	SAP_FailedParseSQL			= -20011,				/*!<����SQLʧ�� */	
	SAP_FailedQueryTb			= -20012,				/*!<�����ѯʧ�� */	
	SAP_InvalidDbType			= -20013,				/*!<��ЧDB���� */	
	SAP_FailedCallIDIP			= -20014,				/*!<����IDIP�ӿ�ʧ�� */	
	SAP_InvalidQueryId			= -20015,				/*!<��Ч��ѯID */	
	SAP_NoFindQueryRecord		= -20016,				/*!<δ�ҵ��ýӿڼ�¼ */	
	SAP_InvalidQueryType		= -20017,					/*!<��Ч��ѯ���� */	
	//////////////////////////////////////////////////////////////////////


	// ƽ̨����˴�����
	//////////////////////////////////////////////////////////////////////
	// ���ô����붨��
	SAP_DBErr				= -4,				/*!< ���ݿ���� */
	SAP_FMErr				= -5,				/*!< �ļ�������� */
	SAP_SMErr				= -6,				/*!< ͬ��������� */

	// ��ģ��������
	// ���ݿ����ģ��(DatabaseManage)
	SAP_FailedInit			= -50,				/*!<��ʼ�� ʧ�� */
	SAP_FailedConnect		= -51,				/*!<��ʼ�� ʧ�� */
	SAP_InvalidParms		= -52,				/*!<��Ч���� */
	SAP_NotExist			= -54,				/*!<��¼������ */
	SAP_HasExist			= -55,				/*!<��¼�Ѵ��� */
	SAP_FailedQuery			= -56,				/*!<��ѯʧ��	*/	
	SAP_LackConn			= -57,				/*!<����ȱ������ */	


	// �ļ�����ģ��(FileManage)
	SAP_FailedCreatePath			= 	-101,		/*!<����Ŀ¼ ʧ�� */

	// ͬ������ģ��(SyncManage)
	SAP_FailedDeleteFile		= 	-201,			/*!<ɾ���ļ�ʧ�� */
	SAP_HasReleased				= -202,				/*!<������������Ҫ�ٷ��� */	
	SAP_UnUpload				= -203,				/*!<δ�ϴ������ܷ��� */	
	SAP_NeedTestOk				= -204				/*!<δͨ�����ԣ����ܷ��� */	
	//////////////////////////////////////////////////////////////////////
};
typedef int SAP_Error;
//////////////////////////////////////////////////////////////////////////

// ��������
enum
{
	kNoneOpt	=	0,
	kQuery		=	1,		//< ��ѯ����
	kViewVer	=	2,		//< �鿴�汾
	kTest		=	3,		//< ���Բ���
	kDelete		=	4,		//< ɾ������
	kRelease	=	5,		//< ��������
	kApplyFeedback	=	6,		//< ���뷴��
	kSubmitFeedback	=	7,		//< �ύ����
	kCreateDir		=	8,		//< ����Ŀ¼
	kBuiltEnv		=	9,		//< �����
	kUploadFile		=	10,		//< �ϴ��ļ�
	kAddDB			=	11,		//< ������ݿ�
	kModifyDB		=	12,		//< �޸����ݿ�
	kDeleteDB		=	13,		//< ɾ�����ݿ�
	kOptIDIP	   	=	14		//< ����IDIP
};typedef int OptType;


// ����˺궨��
#define SAPTopPath "/data/home/sapmanager/release/"					/*!< ���ض���Ŀ¼ */
#define SAPRemoteTopPath "/usr/local/sap/release/"					/*!< Զ�˶���Ŀ¼ */

// ����Ȩ�����Ĳ���Ȩ��ID����
#define SAPMG_GROUP_ID		214	// sap manager��ҵ��ID
#define FUNC_VIEW			83	// ҵ�����б�鿴
#define FUNC_DELETE			43	// ҵ����ɾ��
#define FUNC_MOD			4	// ҵ�����޸�
#define FUNC_CM_MOD			7	// ҵ��ȫ�����޸�
#define UI_VIEW				82	// ҵ��UI�б�鿴
#define UI_MOD				3	// ҵ��ǰ���޸�
#define UI_DELETE			42	// ҵ��ǰ��ɾ��
#define UI_DEBUG			47	// ҵ��ǰ�˵���
#define QI_VIEW				84	// ҵ���ѯ�ӿ��б�鿴
#define QI_MOD				5	// ҵ���ѯ�ӿ��޸�
#define QI_DELETE			44	// ҵ���ѯ�ӿ�ɾ��
#define QI_IDIP_DEBUG		49	// ҵ��IDIP�ӿڵ���
#define QI_DB_DEBUG			48	// ҵ�����ݽӿڵ���
#define DB_VIEW				85	// ҵ�����ݿ��б�鿴
#define DB_MOD				6	// ҵ�����ݿ������޸�
#define DB_DELETE			45	// ҵ�����ݿ�����ɾ��
#define DB_DEBUG			50	// ҵ�����ݿ����
#define SERVICE_VIEW		81	// ҵ����Ϣ�鿴
#define SERVICE_DELETE		41	// ҵ����Ϣɾ��
#define SERVICE_MOD			1	// ҵ����Ϣ�޸�
#define LOG_VIEW			86	// ������־�鿴




#ifdef __cplusplus
}

#endif	// __cplusplus

#endif	// SAP_H



/** @} */










































