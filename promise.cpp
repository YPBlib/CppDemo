#include "promise.h"

int util_callable(int n, char c)
{
	try
	{
		std::default_random_engine dre(n*c);
		std::uniform_int_distribution<int> id(10, 1000);
		for (int i = 0; i < n; ++i)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
			cout.put(c).flush();
		}
	}
	catch (const exception& e)
	{
		cerr << "excep: " << e.what() << endl;
	}
	return 0;
}

int test_thread()
{
	try
	{
		std::thread fg(util_callable, 10, 'A');
		cout << "foreground start" << fg.get_id() << endl;

		for (int i = 0; i < 5; ++i)
		{
			std::thread bg(util_callable, 5, 'A' + i+1);
			cout << " ?detach? background " << bg.get_id() << endl;
			bg.detach();
		}
		cin.get();
		cout << "join fg" << fg.get_id() << endl;
		fg.join();
	}
	catch (const exception& e)
	{
		cerr << "excep: " << e.what() << endl;
	}
	return 0;
}

int util_promise(std::promise<std::string>& p)
{
	try
	{
		cout << "cin a digit" << endl;
		char c = cin.get();
		if (isdigit(c))
		{
			string s = "accept " + c;
			p.set_value(std::move(s));
			return 0;
		}
	}
	catch (const exception& e)
	{
		p.set_exception(std::current_exception());
	}
	return 0;
}

int test_promise()
{
	try
	{
		std::promise<string> p;
		std::thread t(util_promise, std::ref(p));
		t.detach();

		auto f(p.get_future());
		cout << f.get() << endl;
	}
	catch (const exception& e)
	{
		cerr << "excep: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "excep" << endl;
	}
	return 0;
}

