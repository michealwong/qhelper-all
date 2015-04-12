#ifndef _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CgDay
#define _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CgDay



namespace sap
{

namespace xs
{	

class CgDay : public TypeBase
{
public:
	sap_EXPORT CgDay(xercesc::DOMNode* const& init);
	sap_EXPORT CgDay(CgDay const& init);
	void operator=(CgDay const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CgDay); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::GDayFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CgDay
