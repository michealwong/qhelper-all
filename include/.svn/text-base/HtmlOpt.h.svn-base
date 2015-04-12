#ifndef _HTMLOPT_H
#define _HTMLOPT_H

using namespace std;
#include "NDS_exception.h"
using namespace NDS;

class HtmlOpt {
	typedef map<string,string> KeyMap ;
	string _sBeg ,_sEnd ;
	string _sTemplate;
	
	string FillLine( const string &sSourLine , const KeyMap &mKeyMap , const KeyMap &mKeyMap2 = KeyMap() )
	{	
		string::size_type tBeg ,tEnd, tDest = 0;
		string sDest;
		
		tBeg =  sSourLine.find(_sBeg);
		tEnd =  sSourLine.find(_sEnd);
	
		while (tBeg != string::npos)
		{
			//copy前段
			sDest += sSourLine.substr(tDest , tBeg-tDest);
			//替换
			string sKey = sSourLine.substr(tBeg+_sBeg.length(),tEnd-tBeg-_sBeg.length());
			if(mKeyMap.count(sKey))
				sDest += mKeyMap.find(sKey)->second;
			else if(mKeyMap2.count(sKey))
				sDest += mKeyMap2.find(sKey)->second;
			//计算下一次查找起始点
			tDest = tEnd + _sEnd.length();		
			//查找下一个替换点
			tBeg =  sSourLine.find( _sBeg , tDest);
			tEnd =  sSourLine.find( _sEnd , tDest);
		}
		//copy其余的部分
		sDest += sSourLine.substr(tDest);	
		//给sour赋新值
		return sDest ;
	}
	
    public:
   	
    	HtmlOpt(const string sTemplateFile)
    	    :_sBeg("<%$"), _sEnd("$%>")
    	{
    		ifstream fsTemplate(sTemplateFile.c_str()) ;
    		
    		string sLine ;
    		//将模板存入_sTemplate
    		if( fsTemplate.is_open() )
    		{
    			while(getline( fsTemplate , sLine ))
    			{
				_sTemplate += sLine ;
				//cout << _sTemplate << endl ;
			}
		}
		else
		{
			throw ( NDS_exception(__FILE__, __LINE__, string("open template file error!")) );
		}
    	}
    	
    	string FillTemplate( const string &sTokenName ,const KeyMap &mKeyMap = KeyMap(), const KeyMap &mKeyMap2 = KeyMap())
    	{
    		static map <string , pair<string::size_type , string::size_type> > mTemplateMap ;
    		
    		if( _sTemplate.empty() )
    		{
    			throw ( NDS_exception(__FILE__, __LINE__, string("template length is 0 ! " )));
    		}
    		
    		//如果不设sTemplateName,则表示输出整个模板	
    		mTemplateMap[""].first = 0;
    		mTemplateMap[""].second = string::npos ;
    				
		//将模板起始位置存入mTemplateMap
		if(!mTemplateMap.count(sTokenName))
		{
			string::size_type tSize;
			
			if((tSize = _sTemplate.find(_sBeg + sTokenName + _sEnd)) == string::npos)
			{
				throw ( NDS_exception(__FILE__, __LINE__, string("find begin flag error : " + _sBeg + sTokenName + _sEnd)) );
			}
			else
			{
				mTemplateMap[sTokenName].first = tSize + _sBeg.size() + sTokenName.size() + _sEnd.size();
			}
			
			if((tSize = _sTemplate.find( _sBeg + sTokenName + _sEnd , mTemplateMap[sTokenName].first)) == string::npos)
			{
				throw ( NDS_exception(__FILE__, __LINE__, string("find end flag error: " + _sBeg + sTokenName + _sEnd)) );
			}
			else
			{
				mTemplateMap[sTokenName].second = tSize ;
			}
		}
		
		string sSubTemplate;
		sSubTemplate = _sTemplate.substr(mTemplateMap[sTokenName].first , mTemplateMap[sTokenName].second - mTemplateMap[sTokenName].first);
		return (FillLine( sSubTemplate , mKeyMap , mKeyMap2));
    	}
    	
    	static void GoUrl(string sUrl = "" )
    	{
		if( sUrl.empty() )
    			HtmlUrlBack();
    		else
    			HtmlRedirect(sUrl.c_str());
    	}
    	
    	static void MessageBox(string sMsg)
    	{
    		HtmlMessageBox(sMsg.c_str());
    	}
};

//const string HtmlOpt::_sBeg = "<%$";
//const string HtmlOpt::_sEnd = "$%>";

#endif
