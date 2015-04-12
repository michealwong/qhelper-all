#ifndef _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_CresultType
#define _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_CresultType



namespace sap
{

class CresultType : public TypeBase
{
public:
	sap_EXPORT CresultType(xercesc::DOMNode* const& init);
	sap_EXPORT CresultType(CresultType const& init);
	void operator=(CresultType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CresultType); }
	MemberElement<xs::CintType, _altova_mi_altova_CresultType_altova_errcode> errcode;
	struct errcode { typedef Iterator<xs::CintType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CresultType_altova_desc> desc;
	struct desc { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CdataheadType, _altova_mi_altova_CresultType_altova_datahead> datahead;
	struct datahead { typedef Iterator<CdataheadType> iterator; };
	MemberElement<xs::CintType, _altova_mi_altova_CresultType_altova_datanum> datanum;
	struct datanum { typedef Iterator<xs::CintType> iterator; };
};


}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_CresultType
