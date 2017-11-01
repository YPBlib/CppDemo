#pragma once
#ifndef TTRY_H
#define TTRY_Y
#include<cstdio>
#include<iostream>
#include<ios>
#include<fstream>
#include<sstream>
#include<cctype>
#include<cstdlib>
#include<typeinfo>
#include<iterator>
#include<cstddef>
#include<stdexcept>
#include<vector>
#include<deque>
#include<list>
#include<forward_list>
#include<array>
#include<string>
#include<memory>
#include"try.h"
//#include "Draft\\Draft\\tty.h"
//using namespace::std;
using std::vector;
using std::deque;
using std::list;
using std::forward_list;
using std::array;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::begin;
using std::end;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;
using std::nounitbuf;
using std::runtime_error;

class adt
{
	string fetchname() const { return this->name; }
	adt& merge(const adt& a);

	static constexpr double commonvalue = 0;
	string name;
	int integer;
	double f;
};

adt addadt(const adt& a, const adt& b);
ostream& printadt(ostream& os, const adt& a);
istream& readit(istream& is, const adt& a);

adt& adt::merge(const adt& a)
{
	this->name += a.name;
}









class data
{
	friend istream& readit(istream& is, data& it);
	friend ostream& putit(ostream& os, data& it);
	//	constructors
public:
	data() = default;
	data(const string&s) :str(s) {}
	data(const string&s, int i, double p) :str(s), a(i), d(p*i) {}
	data(std::istream&is);
	data& merge(const data& dat);

	string fetchstr() const { return str; }
	double fetchd() const { return d; }
	int fetcha() const { return  a; }

private:
	int a;
	double d;
	string str;
};


class canvas
{
public:
	typedef string::size_type word;
	//canvas() = default;
	canvas(word ht, word wd, char c) :height(ht), width(wd), contents(ht*wd, c) { ; }
	char getit() const { return contents[cursor]; }
	inline char getit(word ht, word wd) const;
	canvas& moveit(word r, word s);

private:
	word cursor = 0;
	word height = 0, width = 0;
	string contents;

};


/*******************template************************/	
	//function template
template <typename T>
int comparetp(const T &v1,const T &v2)
{
	if(v1<v2) return -1;
	if(v2<v1) return 1;		// without '>', we have fewer limits on types
	return 0;
}

//nontype template paramaters
template <unsigned m,unsigned n>
int comparetp2(const char(&p1)[m],const char (&p2)[n] )
{
	return strcmp(p1,p2);
}

	//class template
	template <typename T> class mytpclass
	{
	public:
		typedef T value_type;
		typedef typename std::vector<T>::size_type size_type;
		//constructos
		mytpclass();
		mytpclass(std::initializer_list<T> il);
		size_type size() const{ return data->size();}
		bool empty() const {return data->empty();}
		void push_back(T &&t){data->push_back(std::move(t));}
		void pop_back();
		T& back();
		T& operator[](size_type i);
	private:
		std::shared_ptr<std::vector<T> >data;
		void check(size_type i,const std::string &msg) const;


	};


#endif
