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
class friendfunction;
class friendlyclass;
class adt;

void c11stl(void);


<<<<<<< HEAD:tcpp.h
};
template <typename T> 
using twin = std::pair<T, T>;
template <typename T>
int compare(const T& b1, const T& v2)
{
	if (v1 < v2) return -1;
	if (v2 < v1) return 1;
	return 0;
}
template <typename T>
class Blob
{
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	//constructors
	Blob();
	Blob(std::initializer_list<T> i1);

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	void push_back(const T& t) { data->push_back(t); }
	void push_back(T &&t) { data->push_back(std::move(t)); }
	void pop_back();

	T& back();
	T& operator[](size_type i);
private:
	std::shared_ptr<vector<T>> data;
	void check(size_type i, const string &msg) const;
};
template <typename T>
void Blob<T>::check(size_type i, const string &msg) const
{
	if (i >= data->size())
	{
		throw std::out_of_range(msg);
	}
}
template <typename T>
T& Blob<T>::back()
{
	check(0, "back on empty Blob");
	return data->back();
}
template <typename T>
T& Blob<T>::operator[](size_type i)
{
	check(i, "sunscript out of range");
	return (*data)[i];
}
template <typename T>
Blob<T>::Blob() :data(std::make_shared<vector<T>>()) {}
template <typename T>
Blob<T>::Blob(std::initializer_list<T> i1) :
	data(std::make_shared<vector<T>>(i1)) {}
template <typename T>
class hasStaticMember
{
public:
	static std::size_t count() { return ctr; }
private:
	static std::size_t ctr;
};
template <typename T>
std::size_t typename hasStaticMember<T>::ctr = 0;
=======
>>>>>>> a7d2ec80c9248451f1d0c1b7b1b754d80403edac:try.h
#endif
