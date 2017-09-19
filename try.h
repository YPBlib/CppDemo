#pragma once
#include<string>
#ifndef TTRY_H
#define TTRY_Y
using std::string;
using std::istream;
class data
{
	friend istream& readit(istream& is, data& it);
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


#endif
