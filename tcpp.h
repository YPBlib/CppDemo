#pragma once
#ifndef TTRY_H
#define TTRY_Y

#include<cstdio>
#include<future>
#include<thread>
#include<chrono>
#include<random>
#include<iostream>
#include<exception>
#include<stdexcept>
#include<utility>
#include<functional>
#include<mutex>
#include<condition_variable>
#include<atomic>

namespace tcpp_concurrency
{
	int doSomething(char c);
	int foo1();
	int foo2();
	int test_async();
	void f_utils();
}

#endif
