#include"tcpp.h"
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
	}

	int foo2()
	{
		return doSomething('+');
	}

	int test()
	{
		std::cout << "starting foo1() in background, foo2() in foreground" << std::endl;

		std::future<int> result1(std::async(foo1));
		int result2 = foo2();
		int result = result1.get() + result2;
		std::cout << "\nfoo1() + foo2(): " << result << std::endl;
		return 0;
	}
}

int main()
{
	tcpp_concurrency::test();
	return 0;
}