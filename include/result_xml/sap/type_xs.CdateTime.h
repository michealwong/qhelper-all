#ifndef _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CdateTime
#define _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CdateTime



namespace sap
{

namespace xs
{	

class CdateTime : public TypeBase
{
public:
	sap_EXPORT CdateTime(xercesc::DOMNode* const& init);
	sap_EXPORT CdateTime(CdateTime const& init);
	void operator=(CdateTime const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CdateTime); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DateTimeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_CdateTime
