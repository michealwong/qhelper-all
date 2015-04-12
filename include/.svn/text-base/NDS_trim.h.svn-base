#ifndef _NDS_TRIM_H
#define _NDS_TRIM_H

#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
using namespace std;

namespace NDS
{

inline string& ltrim(string &ss)
{
	long	pos;

	//
	//out << "ss:" << ss << "," << ss.length() << endl;
	
	for(pos = 0;pos < ss.length();pos++) {
		if (ss[pos] != ' ') {
			//ss = ss.substr(pos, ss.length()-pos);
			ss.erase(0, pos);
			break;
		}
	}
	//string::iterator p=find_if(ss.begin(),ss.end(),not1(ptr_fun(isspace)));
	//ss.erase(ss.begin(),p);
	//cout << "ltrim ss:" << ss << endl;
	
	return ss;
}

inline string& rtrim(string &ss)
{
	long	pos;

	//cout << "ss:" << ss << "," << ss.length() << endl;
	
	for(pos = ss.length() - 1; pos >= 0; pos--) {
		if (ss[pos] != ' ') {
			//ss = ss.substr(0, pos+1);
			ss.erase(pos+1, ss.length());
			break;
		}
	}
	//string::reverse_iterator p=find_if(ss.rbegin(),ss.rend(),not1(ptr_fun(isspace)));
	//ss.erase(p.base(),ss.end());
	//cout << "rtrim:" << ss << endl;
	
	return ss;
}

inline string& trim(string &st)
{
	ltrim(rtrim(st));
	return st;
}

}

#endif

