#ifndef _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CanyType
#define _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CanyType



namespace sap
{

namespace xs
{	

class CanyType : public TypeBase
{
public:
	sap_EXPORT CanyType(xercesc::DOMNode* const& init);
	sap_EXPORT CanyType(CanyType const& init);
	void operator=(CanyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CanyType); }
	sap_EXPORT void operator=(const string_type& value);
	sap_EXPORT operator string_type();
	sap_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CanyType
