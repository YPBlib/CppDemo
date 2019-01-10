#include "concurrency.h"
#include "async.h"
#include "shared_future.h"
#include "promise.h"
#include "data_race.h"
#include "mutex.h"



#include<intrin.h>
using namespace std;

namespace tcpp_concurrency
{
	int doSomething(char c)
	{
		std::default_random_engine dre(c);
		std::uniform_int_distribution<int> id(10, 1000);
		for (int i = 0; i < 10; ++i)
		{
			this_thread::sleep_for(chrono::milliseconds(id(dre)));
			std::cout.put(c).flush();
		}
		return c;
	}

	int foo1()
	{
		return doSomething('*');
//		_AddressOfReturnAddress();
	}

	int foo2()
	{
		return doSomething('+');
	}

	int test_async()
	{
		
		cout << __FUNCTION__ << endl;
		std::cout << "starting foo1() in background, foo2() in foreground" << std::endl;

		//std::future<int> result1(std::async(foo1));
		std::future<int> result1(std::async(std::launch::async, foo1));
		//std::future<int> result1(std::async(std::launch::deferred,foo1));
		int result = 0;

		// version 1 :async
		// call early and return late
		 int result2 = foo2();
		 result = result1.get() + result2;

		// version 2 : may cause sequential exec
		// result =result1.get()+ foo2();
		// result = foo2() + result1.get();
		std::cout << "\nfoo1() + foo2(): " << result << std::endl;
		return 0;
	}

	static int i = 0;
	int f_throw()
	{
		
		for (; i < 10;)
		{
			++i;
			f_utils();
			if (i > 6)throw runtime_error("excep!\n");
		}
		return i;
	}
	void f_utils()
	{
		cout << "f_utils:"<<i << endl;
	}

	void test_async_excep()
	{
		cout << __FUNCTION__ << endl;
		auto f1 = std::async(std::launch::async,f_throw);
		f_utils();
		try
		{
			f1.get();
		}
		catch(const exception& e)
		{
			cerr << e.what() << endl;
		}
	}

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
		cout << this_thread::get_id() << endl;

	}
}

int main()
{
	//tcpp_concurrency::test_async();
	//tcpp_concurrency::test_async_excep();
	tcpp_concurrency::test_async_member_func();
	
	return 0;
}


int main()
{
	//test_shared_ref();
	//test_shared();
	//test_thread();
	/* as a whole !!!
	//auto r = test_race();
	//cout << r << endl;
	*/
	
	return 0;
}