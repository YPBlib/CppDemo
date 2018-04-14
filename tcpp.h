#pragma once
#ifndef TTRY_H
#define TTRY_Y
#include<cstdio>
#include<iostream>
#include<ios>
#include<fstream>
#include<sstream>
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
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::begin;


template <typename T> 
using twin = std::pair<T, T>;





template <typename T>
class longlonglongnameTemplate
{
	T a;
	T* n;
};

// template alias
template <typename T> using llnt = longlonglongnameTemplate<T>;
#endif
