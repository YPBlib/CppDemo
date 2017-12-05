#pragma once
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
class Quote
{
public:
	Quote() = default;
	Quote(const string& book,double sales_price):bookNo(book),price(sales_price){}
	string isbn()const { return bookNo; }
	virtual double net_price(std::size_t n)const { return n*price; }
//	virtual void fakeVirtual(int a) const final {}		//?????
	virtual ~Quote() = default;
private:
	string bookNo;
protected:
	double price = 0.;
};
class Bulk_quote :public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const string& book, double p, std::size_t qty, double disc) :Quote(book, p), min_qty(qty), discount(disc) {}
	double net_price(std::size_t)const override;
private:
	std::size_t min_qty;
	double discount = 0.;
};


double Bulk_quote::net_price(std::size_t cnt)const
{
	return cnt *price * (cnt >= min_qty ? (1 - discount) : 1.);
}
class Disc_quote :public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const string& book,double price,std::size_t qty,double disc):Quote(book,price),quantity(qty),discount(disc){}
	double net_price(std::size_t)const = 0;		// pure virtual
protected:
	std::size_t quantity = 0;
	double discount = 0;
};

class Base
{
public:
	static void statmem(){}
};

class Derived :public Base
{
	void f(const Derived&);
};

void Derived::f(const Derived& derived_obj)
{
	Base::statmem();
	Derived::statmem();

	derived_obj.statmem();
	statmem();
}

class Last final :Base
{
	int last;
};
















