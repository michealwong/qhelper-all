#ifndef _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CQName
#define _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CQName



namespace sap
{

namespace xs
{	

class CQName : public TypeBase
{
public:
	sap_EXPORT CQName(xercesc::DOMNode* const& init);
	sap_EXPORT CQName(CQName const& init);
	void operator=(CQName const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CQName); }
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CQName
