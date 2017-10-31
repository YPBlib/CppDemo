#pragma once
#include<string>
#include<memory>
#ifndef TTRY_H
#define TTRY_Y
using std::string;
using std::istream;
using std::ostream;
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
