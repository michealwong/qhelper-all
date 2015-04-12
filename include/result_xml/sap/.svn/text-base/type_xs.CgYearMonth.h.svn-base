#ifndef _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CgYearMonth
#define _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CgYearMonth



namespace sap
{

namespace xs
{	

class CgYearMonth : public TypeBase
{
public:
	sap_EXPORT CgYearMonth(xercesc::DOMNode* const& init);
	sap_EXPORT CgYearMonth(CgYearMonth const& init);
	void operator=(CgYearMonth const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CgYearMonth); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::GYearMonthFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CgYearMonth
