#ifndef _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_CresultsetType
#define _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_CresultsetType



namespace sap
{

class CresultsetType : public TypeBase
{
public:
	sap_EXPORT CresultsetType(xercesc::DOMNode* const& init);
	sap_EXPORT CresultsetType(CresultsetType const& init);
	void operator=(CresultsetType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CresultsetType); }

	MemberAttribute<string_type,_altova_mi_altova_CresultsetType_altova_name, 0, 0> name;	// name Cstring
	MemberElement<CitemsType, _altova_mi_altova_CresultsetType_altova_items> items;
	struct items { typedef Iterator<CitemsType> iterator; };
};


}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_CresultsetType
