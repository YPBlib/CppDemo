#include "data_race.h"

vector<int> v(100, 0);
bool readyFlag = false;

int foo()
{
	while (!readyFlag);
	cout << v.size() << endl;
	return  v.size();
}

int test_race()
{
	auto f(std::async(std::launch::async, foo));
	std::default_random_engine dre;
	std::uniform_int_distribution<int> id(1, 100000);
	for (int i = 0; i < 2000; ++i)
	{
		if (id(dre) % 65537 < 50000)
			v.push_back(0);
		else
		{
			try
			{
				v.pop_back();
			}
			catch (...)
			{
				cout << "excep! " << endl;
			}
		}
	}
	readyFlag = true;
	for (int i = 0; i < 1000; ++i)
	{
		if (id(dre) % 65537 < 50000)
			v.push_back(0);
		else
		{
			try
			{
				v.pop_back();
			}
			catch (...)
			{
				cout << "excep! " << endl;
			}
		}
	}
	return f.get();
}

int test_starve()
{
	auto f(std::async(std::launch::async, foo));
	f.get();
	readyFlag = true;
	return 0;
}

