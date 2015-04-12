#ifndef _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_Cdate
#define _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_Cdate



namespace sap
{

namespace xs
{	

class Cdate : public TypeBase
{
public:
	sap_EXPORT Cdate(xercesc::DOMNode* const& init);
	sap_EXPORT Cdate(Cdate const& init);
	void operator=(Cdate const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cdate); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DateFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA_xs_ALTOVA_Cdate
