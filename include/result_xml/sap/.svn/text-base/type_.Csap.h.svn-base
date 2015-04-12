#ifndef _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_Csap
#define _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_Csap



namespace sap
{

class Csap : public TypeBase
{
public:
	sap_EXPORT Csap(xercesc::DOMNode* const& init);
	sap_EXPORT Csap(Csap const& init);
	void operator=(Csap const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_Csap); }
	MemberElement<CsaprootType, _altova_mi_altova_Csap_altova_saproot> saproot;
	struct saproot { typedef Iterator<CsaprootType> iterator; };
	sap_EXPORT void SetXsiType();

	// document functions
	sap_EXPORT static Csap LoadFromFile(const string_type& fileName);
	sap_EXPORT static Csap LoadFromString(const string_type& xml);
	sap_EXPORT static Csap LoadFromBinary(const std::vector<unsigned char>& data);
	sap_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint );
	sap_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint, const string_type& encoding );
	sap_EXPORT void SaveToFile( const string_type& fileName, bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM );
	sap_EXPORT string_type SaveToString(bool prettyPrint);
	sap_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint);
	sap_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint, const string_type& encoding);
	sap_EXPORT std::vector<unsigned char> SaveToBinary(bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM);
 	sap_EXPORT static Csap CreateDocument();
	sap_EXPORT void DestroyDocument();
	sap_EXPORT void SetDTDLocation(const string_type& dtdLocation);
	sap_EXPORT void SetSchemaLocation(const string_type& schemaLocation);
protected:
	XercesTreeOperations::DocumentType GetDocumentNode() { return (XercesTreeOperations::DocumentType)m_node; }
};


}	// namespace sap

#endif // _ALTOVA_INCLUDED_sap_ALTOVA__ALTOVA_Csap
