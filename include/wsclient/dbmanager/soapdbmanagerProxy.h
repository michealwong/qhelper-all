/* soapdbmanagerProxy.h
   Generated by gSOAP 2.7.15 from IDBManager.h
   Copyright(C) 2000-2009, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapdbmanagerProxy_H
#define soapdbmanagerProxy_H
#include "soapH.h"

class SOAP_CMAC dbmanagerProxy : public soap
{ public:
	/// Endpoint URL of service 'dbmanagerProxy' (change as needed)
	const char *soap_endpoint;
	/// Constructor
	dbmanagerProxy();
	/// Constructor with copy of another engine state
	dbmanagerProxy(const struct soap&);
	/// Constructor with engine input+output mode control
	dbmanagerProxy(soap_mode iomode);
	/// Constructor with engine input and output mode control
	dbmanagerProxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~dbmanagerProxy();
	/// Initializer used by constructors
	virtual	void dbmanagerProxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (uses soap_destroy and soap_end)
	virtual	void destroy();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Force close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
	virtual	void soap_stream_fault(std::ostream&);
	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'ExeSqlByDataOper' (returns error code or SOAP_OK)
	virtual	int ExeSqlByDataOper(int inDBId, char *inDBName, char *inSql, char *inDBCategory, int inDBPort, char *inEncode, char **outResult);

	/// Web service operation 'ExeSql' (returns error code or SOAP_OK)
	virtual	int ExeSql(char *inDBIP, char *inDBUser, char *inDBPwd, char *inDBName, char *inSql, char *inDBCategory, int inDBPort, char *inEncode, char **outResult);

	/// Web service operation 'ExeSqlByWorldId' (returns error code or SOAP_OK)
	virtual	int ExeSqlByWorldId(int inServiceId, int inWorldId, int inDBType, char *inDBName, char *inSql, char *inDBCategory, int inDBPort, char *inEncode, char **outResult);

	/// Web service operation 'ExeSqlFromMultiTable' (returns error code or SOAP_OK)
	virtual	int ExeSqlFromMultiTable(int inDBId, char *inDBName, char *inSQLFormat, LONG64 inStartTime, LONG64 inEndTime, LONG64 inStep, char *inEncode, char **outResult);

	/// Web service operation 'Querier' (returns error code or SOAP_OK)
	virtual	int Querier(int inQueryId, char *inParams, char **outResult);

	/// Web service operation 'QuerierByAlias' (returns error code or SOAP_OK)
	virtual	int QuerierByAlias(int inServiceId, char *inAlias, char *inParams, char **outResult);
};
#endif
