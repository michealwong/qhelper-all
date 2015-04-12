/** @defgroup global 全局接口
 *  全局头定义
 *  @{
 */

#ifndef SAP_H
#define SAP_H


#ifdef __cplusplus
extern "C" {
#endif


/////////////////////////////////////////////////////////////////////////
/*
	全局ID或结构定义
*/
//////////////////////////////////////////////////////////////////////////
#define SAP_API_VERSION					101028						/*!< SAP版本 */
#define SAP_MAX_NAME_LENGTH				256							/*!< 最大名字长度 */
#define SAP_MAX_ATTRIBUTE_NAME_SIZE		64							/*!< 最大属性名长度 */
#define SAP_MAX_PATH_NAME_LENGTH		64							/*!< 最大路径长度 */
#define MAXUPLOADFILESIZE				20480000					/*!< 上传文件最大尺寸 */
#define SAFEDELETE(p) if( p != NULL ){delete p;p = NULL;}			/*!< 安全删除 */


// 访问统计类型
#define SAP_STAT_ACCESS			1	// 功能访问次数统计
#define SAP_STAT_Elapsed_Time	2	// 功能响应时长统计
#define SAP_STAT_WARN			3	// 功能报警次数统计

// SAP平台是否忽略验证权限(包括sapmanager和sas)
#define SAP_IGNORE_AUTH	0


typedef void*  SAP_Object;											/*!< 空对象 */
typedef int	   SAP_ErrCode;											/*!< 错误代码类型*/

//! 错误代码
enum
{
	// 常用错误码定义
    SAP_NoErr              	= 0,				/*!< 无错误 */
	SAP_Failed				= -1,				/*!< 失败 */
	SAP_Exception			= -2,			/*!< 异常 */
	SAP_Unknown				= -99,				/*!< 未知错误*/

	// 平台错误码
	//////////////////////////////////////////////////////////////////////
	// 平台逻辑层错误码,查询错误
	SAP_FailedReadConf			= -10000,				/*!<读取配置失败 */
	SAP_FuncIdNull				= -10001,				/*!<功能Id为空 */
	SAP_FailedQueryFuncInfo		= -10002,				/*!<查询功能配置信息失败 */
	SAP_NoFuncIdFound			= -10003,				/*!<未找到该功能配置 */
	SAP_NoRight					= -10004,				/*!<用户无此操作权限 */
	SAP_FailedParseFuncRule		= -10005,				/*!<解析功能逻辑规则失败	*/	
	SAP_InvalidFuncRule			= -10006,				/*!<无效功能逻辑规则 */	
	SAP_LackInputParam			= -10007,				/*!<缺少传入参数 */	
	SAP_FailedCallInterface		= -10008,				/*!<调用查询接口失败 */	
	SAP_ErrForDataQuery			= -10009,				/*!<数据层查询错误 */	
	SAP_EmptyCookie				= -10010,				/*!<Cookie为空 */	
	SAP_EmptyUser				= -10011,				/*!<无效用户名 */	


	// 平台数据层错误码,查询错误
	SAP_InvalidQueryInputParam	= -20000,				/*!<无效查询输入参数 */
	SAP_NoFindDbRecord			= -20001,				/*!<未找到该数据库的记录*/
	SAP_InvalidDbName			= -20002,				/*!<无效数据库名称 */
	SAP_ErrSQLQuery				= -20003,				/*!<SQL查询错误 */
	SAP_DBQueryException		= -20004,				/*!<DB查询异常 */
	SAP_FailedParseDbname		= -20005,				/*!<解析数据库名失败*/	
	SAP_FailedQueryMultiTb		= -20006,				/*!<多表查询失败 */	
	SAP_InvalidXmlDoc			= -20007,				/*!<无效db XML文档 */	
	SAP_InvalidXmlDbRule		= -20008,				/*!<无效XML规则 */	
	SAP_NoFindParam				= -20009,				/*!<参数不存在 */	
	SAP_FailedParseDBID			= -20010,				/*!<解析DBID失败 */	
	SAP_FailedParseSQL			= -20011,				/*!<解析SQL失败 */	
	SAP_FailedQueryTb			= -20012,				/*!<单表查询失败 */	
	SAP_InvalidDbType			= -20013,				/*!<无效DB类型 */	
	SAP_FailedCallIDIP			= -20014,				/*!<调用IDIP接口失败 */	
	SAP_InvalidQueryId			= -20015,				/*!<无效查询ID */	
	SAP_NoFindQueryRecord		= -20016,				/*!<未找到该接口记录 */	
	SAP_InvalidQueryType		= -20017,					/*!<无效查询类型 */	
	//////////////////////////////////////////////////////////////////////


	// 平台管理端错误码
	//////////////////////////////////////////////////////////////////////
	// 常用错误码定义
	SAP_DBErr				= -4,				/*!< 数据库错误 */
	SAP_FMErr				= -5,				/*!< 文件管理错误 */
	SAP_SMErr				= -6,				/*!< 同步管理错误 */

	// 各模块错误代码
	// 数据库管理模块(DatabaseManage)
	SAP_FailedInit			= -50,				/*!<初始化 失败 */
	SAP_FailedConnect		= -51,				/*!<初始化 失败 */
	SAP_InvalidParms		= -52,				/*!<无效参数 */
	SAP_NotExist			= -54,				/*!<记录不存在 */
	SAP_HasExist			= -55,				/*!<记录已存在 */
	SAP_FailedQuery			= -56,				/*!<查询失败	*/	
	SAP_LackConn			= -57,				/*!<操作缺乏条件 */	


	// 文件管理模块(FileManage)
	SAP_FailedCreatePath			= 	-101,		/*!<创建目录 失败 */

	// 同步管理模埠(SyncManage)
	SAP_FailedDeleteFile		= 	-201,			/*!<删除文件失败 */
	SAP_HasReleased				= -202,				/*!<己发布，无需要再发布 */	
	SAP_UnUpload				= -203,				/*!<未上传，不能发布 */	
	SAP_NeedTestOk				= -204				/*!<未通过测试，不能发布 */	
	//////////////////////////////////////////////////////////////////////
};
typedef int SAP_Error;
//////////////////////////////////////////////////////////////////////////

// 操作类型
enum
{
	kNoneOpt	=	0,
	kQuery		=	1,		//< 查询操作
	kViewVer	=	2,		//< 查看版本
	kTest		=	3,		//< 测试操作
	kDelete		=	4,		//< 删除操作
	kRelease	=	5,		//< 发布操作
	kApplyFeedback	=	6,		//< 申请反馈
	kSubmitFeedback	=	7,		//< 提交反馈
	kCreateDir		=	8,		//< 创建目录
	kBuiltEnv		=	9,		//< 搭建环境
	kUploadFile		=	10,		//< 上传文件
	kAddDB			=	11,		//< 添加数据库
	kModifyDB		=	12,		//< 修改数据库
	kDeleteDB		=	13,		//< 删除数据库
	kOptIDIP	   	=	14		//< 操作IDIP
};typedef int OptType;


// 管理端宏定义
#define SAPTopPath "/data/home/sapmanager/release/"					/*!< 本地顶层目录 */
#define SAPRemoteTopPath "/usr/local/sap/release/"					/*!< 远端顶层目录 */

// 敏感权限中心操作权限ID定义
#define SAPMG_GROUP_ID		214	// sap manager的业务ID
#define FUNC_VIEW			83	// 业务功能列表查看
#define FUNC_DELETE			43	// 业务功能删除
#define FUNC_MOD			4	// 业务功能修改
#define FUNC_CM_MOD			7	// 业务安全配置修改
#define UI_VIEW				82	// 业务UI列表查看
#define UI_MOD				3	// 业务前端修改
#define UI_DELETE			42	// 业务前端删除
#define UI_DEBUG			47	// 业务前端调试
#define QI_VIEW				84	// 业务查询接口列表查看
#define QI_MOD				5	// 业务查询接口修改
#define QI_DELETE			44	// 业务查询接口删除
#define QI_IDIP_DEBUG		49	// 业务IDIP接口调试
#define QI_DB_DEBUG			48	// 业务数据接口调试
#define DB_VIEW				85	// 业务数据库列表查看
#define DB_MOD				6	// 业务数据库配置修改
#define DB_DELETE			45	// 业务数据库配置删除
#define DB_DEBUG			50	// 业务数据库调试
#define SERVICE_VIEW		81	// 业务信息查看
#define SERVICE_DELETE		41	// 业务信息删除
#define SERVICE_MOD			1	// 业务信息修改
#define LOG_VIEW			86	// 功能日志查看




#ifdef __cplusplus
}

#endif	// __cplusplus

#endif	// SAP_H



/** @} */










































