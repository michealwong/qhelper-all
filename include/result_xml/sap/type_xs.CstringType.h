#ifndef _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CstringType
#define _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CstringType



namespace sap
{

namespace xs
{	

class CstringType : public TypeBase
{
public:
	sap_EXPORT CstringType(xercesc::DOMNode* const& init);
	sap_EXPORT CstringType(CstringType const& init);
	void operator=(CstringType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CstringType); }
	sap_EXPORT void operator=(const string_type& value);
	sap_EXPORT operator string_type();
	sap_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CstringType
