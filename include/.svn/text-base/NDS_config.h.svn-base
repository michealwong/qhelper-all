#ifndef _NDS_CONFIG_H
#define _NDS_CONFIG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>
using namespace std;

#include "NDS_trim.h"
#include "NDS_exception.h"
using namespace NDS;

namespace NDS
{

class NDS_multi_config_node
{
public:
	typedef multimap< string, string > node_type;
	typedef multimap< string, NDS_multi_config_node* > tree_type;
	typedef pair<node_type::iterator,node_type::iterator> node_ret_type;
	typedef pair<tree_type::iterator,tree_type::iterator> tree_ret_type;
private:
	node_type content;
public:
	virtual node_type& get_node()
	{
		return content;
	}
	virtual tree_type& get_tree()
	{
		throw NDS_exception(__FILE__,__LINE__,"can't get_tree() in node!");
	}
	tree_ret_type operator[](const string& s)
	{
		if (get_tree().count(s)==0)
			throw NDS_exception(__FILE__,__LINE__,"tree key "+s+" not found!");
		return get_tree().equal_range(s);
	}
	node_ret_type operator()(const string& s="")
	{
		if (get_node().count(s)==0)
			throw NDS_exception(__FILE__,__LINE__,"node key "+s+" not found!");
		return get_node().equal_range(s);
	}
	virtual ~NDS_multi_config_node()
	{
	}
};

class NDS_single_config_node
{
public:
	typedef map< string, string > node_type;
	typedef map< string, NDS_single_config_node* > tree_type;
	typedef NDS_single_config_node& tree_ret_type;
	typedef string& node_ret_type;
	const static bool bIsNode = true;
private:
	node_type content;
public:
	virtual node_type& get_node()
	{
		return content;
	}
	virtual tree_type& get_tree()
	{
		throw NDS_exception(__FILE__,__LINE__,"can't get_tree() in node!");
	}
	tree_ret_type operator[](const string& s)
	{
		if (get_tree().count(s)==0)
			throw NDS_exception(__FILE__,__LINE__,"tree key "+s+" not found!");
		return *(get_tree()[s]);
	}
	node_ret_type operator()(const string& s="")
	{
		if (get_node().count(s)==0)
			throw NDS_exception(__FILE__,__LINE__,"node key "+s+" not found!");
		return get_node()[s];
	}
	virtual ~NDS_single_config_node()
	{
	}
};

template <typename T> class NDS_config_tree:public T
{
private:
	typename T::tree_type content;
public:
    const static bool bIsNode = false;

	typename T::tree_type& get_tree()
	{
		return content;
	}
	virtual ~NDS_config_tree()
	{
		for (typename T::tree_type::iterator ti=content.begin(); ti!=content.end(); ti++)
			delete ti->second;
	}
};

template <typename T> class Base_config
{
public:
	NDS_config_tree<T> root;
public:
	virtual ~Base_config()
	{
	}
	typename T::tree_ret_type operator[](string name)
	{
		return root[name];
	}
};

template <typename T=NDS_single_config_node> class XML_config:public Base_config<T>
{
	using Base_config<T>::root;
public:
	explicit XML_config(istream& is)
	{
		parse_elem(is,root,"");
	}
	explicit XML_config(const string& fname)
	{
		ifstream is(fname.c_str());
		if (!is)
			throw NDS_exception(__FILE__,__LINE__,"file "+fname+" can't open.");
		parse_elem(is,root,"");
	}
private:
	XML_config();
	XML_config(XML_config &);
	NDS_config_tree<T> *mknode(const string &buf, string &key)
	{
		NDS_config_tree<T> *p=new NDS_config_tree<T>;
		string::const_iterator t=buf.begin();
		while (isspace(*t))
			t++;
		string::const_iterator st=std::find_if(t,buf.end(),static_cast<int(*)(int)>(isspace));
		key.assign(t,st);
		try
		{
			while (st<buf.end())
			{
				st++;
				while (isspace(*st))
					st++;
				string::const_iterator e=find(st,buf.end(),'=');
				if (e==buf.end())
					break;
				string attr(st,e);
				t=find(e+1,buf.end(),'\"');
				if (t==buf.end())
					throw NDS_exception(__FILE__,__LINE__,"\" of value not found.");
				st=find(t+1,buf.end(),'\"');
				if (st==buf.end())
					throw NDS_exception(__FILE__,__LINE__,"\" of value not found.");
				string value(t+1,st);
				(p->get_node()).insert(make_pair(attr,value));
			}
		}
		catch (NDS_exception &e)
		{
			delete p;
			throw;
		}
		return p;
	}
	bool parse_elem(istream &is, NDS_config_tree<T> &parent, string treestr="")
	{
		const int BUFSIZE=4096;
		char buf[BUFSIZE];
		bool treeflag=false;
		int ch,len;
		string key;
		T *p;
		NDS_config_tree<T> *q;

		while (is.get(buf,BUFSIZE,'<'))
		{
			int count=is.gcount();
			if (count!=0)
				(parent.get_node()).insert(make_pair(string(""),string(buf)));
			if (is.get()==EOF)	// '<'
				if (treestr=="")
					break;
				else
					throw NDS_exception(__FILE__,__LINE__,"eof error in tree "+treestr);
			switch (ch=is.peek())
			{
				case '!':
					// not judge -- and -->
					is.ignore(INT_MAX,'>');
					if (is.eof())
						throw NDS_exception(__FILE__,__LINE__,"<! ... > not match!");
					break;
				case '?':
					// must judge ?>
					is.ignore();
					is.get(buf,BUFSIZE,'>');
					len=is.gcount();
					if (len==0 || buf[len-1]!='?')		// ?>
						throw NDS_exception(__FILE__,__LINE__,"unmatched ?> "+treestr+".");
					buf[len-1]='\0';
					if (is.get()!='>')
						throw NDS_exception(__FILE__,__LINE__,"unmatched ?> "+treestr+".");
					// key {att="val"}...
					p=mknode(buf,key);
					(parent.get_tree()).insert(make_pair(key,p));
					treeflag=true;
					break;
				case '/':
					if (treestr=="")
						throw NDS_exception(__FILE__,__LINE__,"unmatched </...> "+treestr+".");
					else
						is.putback('<');
					break;
				case EOF:
					throw NDS_exception(__FILE__,__LINE__,"uncompleted file "+treestr+".");
					break;
				default:
					// normal <key>
					// <key {att="val"}... />
					// <key {att="val"}... > {content} </key>
					is.get(buf,BUFSIZE,'>');
					len=is.gcount();
					if (is.get()!='>')
						throw NDS_exception(__FILE__,__LINE__,"unmatched > "+treestr+".");
					if (buf[len-1]!='/')
					{
						// key {att="val"}...
						q=mknode(buf,key);
						try
						{
							if (parse_elem(is,*q,key)==false)
							{
								p=new T;
								p->get_node()=q->get_node();
								(parent.get_tree()).insert(make_pair(key,p));
								delete q;
							}
							else
								(parent.get_tree()).insert(make_pair(key,q));
						}
						catch (NDS_exception &e)
						{
							delete q;
							throw;
						}
						is.get(buf,BUFSIZE,'>');
						if (is.get()!='>')
							throw NDS_exception(__FILE__,__LINE__,"unmatched > in </"+key+"> "+treestr+".");
						if ("</"+key!=buf)
							throw NDS_exception(__FILE__,__LINE__,"unmatched </"+key+"> "+treestr+".");
					}
					else
					{
						// key {att="val"}...
						buf[len-1]='\0';
						p=mknode(buf,key);
						(parent.get_tree()).insert(make_pair(key,p));
					}
					treeflag=true;
					break;
			}
			if (ch=='/')
				break;
		}
		return treeflag;
	}
};

template <typename T=NDS_single_config_node> class UNIX_config:public Base_config<T>
{
	using Base_config<T>::root;
public:
	explicit UNIX_config(istream& is)
	{
		parse_elem(is);
	}
	explicit UNIX_config(const string& fname)
	{
		ifstream is(fname.c_str());
		if (!is)
			throw NDS_exception(__FILE__,__LINE__,"file "+fname+" can't open.");
		parse_elem(is);
	}
private:
	UNIX_config();
	UNIX_config(UNIX_config &);
	bool parse_elem(istream &is)
	{
		T *seg=&root;
		string linebuf;
		while (getline(is,linebuf))
		{
			trim(linebuf);
			if (linebuf=="" || linebuf[0]=='#')
				continue;
			if (linebuf[0]=='[')
			{
				string::iterator i=linebuf.end()-1;
				if (*i!=']')
					throw NDS_exception(__FILE__,__LINE__,"[ and ] not match.");
				string key(linebuf.begin()+1,i);
				trim(key);
				T *p=new T;
				(root.get_tree()).insert(make_pair(key,p));
				seg=p;
			}
			else
			{
				string::size_type pos0=linebuf.find('=');
				if (pos0==string::npos)
					(seg->get_node()).insert(make_pair(linebuf,string("")));
				else
				{
					string key(linebuf,0,pos0);
					string value(linebuf,pos0+1);
					rtrim(key);
					ltrim(value);
					(seg->get_node()).insert(make_pair(key,value));
				}
			}
		}
		return true;
	}
};

}

#endif

