#ifndef _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_CfieldType
#define _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_CfieldType

#include "type_xs.CstringType.h"


namespace sap
{

class CfieldType : public ::sap::xs::CstringType
{
public:
	sap_EXPORT CfieldType(xercesc::DOMNode* const& init);
	sap_EXPORT CfieldType(CfieldType const& init);
	void operator=(CfieldType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CfieldType); }
	sap_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_altova_CfieldType_altova_name, 0, 0> name;	// name Cstring
	sap_EXPORT void SetXsiType();
};


}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_CfieldType
