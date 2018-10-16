#include "concurrency.h"
#include "async.h"







struct X
{
	int x = 0;
	X(int x):x(x){}
	int incre(int i) { return x += i; }
};

void test_async_member_func()
{
	cout << __FUNCTION__ << endl; 
	X x(1);
	auto result=std::async(&X::incre, std::ref(x), 2);
	cout << result.get() << endl;
}

void test_promise()
{
	cout << __FUNCTION__ << endl; 
	cout << std::this_thread::get_id() << endl;

}



int main()
{
	test_async_pass_ref();
	return 0;
}