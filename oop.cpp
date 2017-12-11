
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
#include<new>
#include<utility>
#include<functional>
#include"try.h"
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
using std::allocator;
using std::runtime_error;
class friendfunction
{
public:
	double fetchdouble(const adt& a);
	double fetchdouble(void);
};
class adt
{
public:
	friend double friendfunction::fetchdouble(const adt& a);
	friend class friendlyclass;
	typedef int adtint;
	string fetchname() const { return this->name; }
	static constexpr double commonvalue = 0;
private:
	string name;
	int integer;
	double f;
};
double friendfunction::fetchdouble(const adt& a)
{
	return a.f;
}
double friendfunction::fetchdouble(void)
{
	adt a;
	//  return a.f;		//Wrong
	return 0.;
}
class friendlyclass
{
public:
	int fetchinteger(adt& a) { return a.integer; }
};
class classcons
{
public:
	classcons(int j);
	explicit classcons();
private:
	int i;
	const int ci;

};




