#ifndef zjusct2019_sharedfuture
#define zjusct2019_sharedfuture

#include <stdexcept>
#include "concurrency.h"



int getDigit(int n);
void t_shared(char c, std::shared_future<int> f);
void test_shared();
void shared_mutable(int& i, std::shared_future<int>& f);
void test_shared_ref();
#endif 