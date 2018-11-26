#include "shared_future.h"

int getDigit(int n)
{
	if(n>=0 && n<=9)
	return n;
	else throw runtime_error("not digit");
}

void t_shared(char c, std::shared_future<int> f)
{
	cout << "^" << std::this_thread::get_id() << ": c= " << c++ << "$";
	try
	{
		auto n = f.get();
		for (int i = 0; i < n; ++i)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			cout.put(c).flush();
		}
	}
	catch (const exception& e)
	{
		cerr << "excep in pid" << std::this_thread::get_id() << ": " << e.what() << endl;
	}
}

void test_shared()
{
	try
	{
		//auto f = std::async(getDigit, 5).share();
		std::shared_future<int> f = std::async(getDigit,15);
		auto f1 = std::async(std::launch::async, t_shared, 'a', f);
		auto f2 = std::async(std::launch::async, t_shared, 'b', f);
		auto f3 = std::async(std::launch::async, t_shared, 'c', f);

		f1.get();
		f2.get();
		f3.get();
	}
	catch (const exception& e)
	{
		cerr << "excep: " << e.what() << endl;
	}

}

void shared_mutable(int& i, std::shared_future<int>& f)
{
	cout << "^" << std::this_thread::get_id() << ": i= " << i++ << "$";
}

void test_shared_ref()
{
	auto f = std::async(getDigit, 5).share();
	int i = 1;
	auto f1 = std::async(std::launch::async, shared_mutable, std::ref(i), std::ref(f));
	auto f2 = std::async(std::launch::async, shared_mutable, std::ref(i), std::ref(f));
	auto f3 = std::async(std::launch::async, shared_mutable, std::ref(i), std::ref(f));
}