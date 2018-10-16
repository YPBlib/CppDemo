#include "concurrency.h"
#include "async.h"

int print10(char c)
{
	std::default_random_engine dre(c);
	std::uniform_int_distribution<int> id(10, 1000);
	for (int i = 0; i < 10; ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
		//std::this_thread::yield
		//std::this_thread::get_id
		//std::this_thread::sleep_until
		std::cout.put(c).flush();
	}
	return c;
}

int print10a()
{
	return print10('a');
	//		_AddressOfReturnAddress();
}

int print10b()
{
	return print10('b');
}





int test_async()
{

	cout << __FUNCTION__ << ":" << endl;
	cout << "print10a in background, print10b in foreground" << endl;

	//std::future<int> result1(std::async(print10a));
	std::future<int> result1(std::async(std::launch::async, print10a));	// async
																		//std::future<int> result1(std::async(std::launch::deferred,print10a)); // b then a
	int result = 0;
#if 1
	// version 1 :async
	// call early and return late
	int result2 = print10b();
	//result = result1.get() + result2;
#else
	// version 2 : may cause sequential exec
	// eval order unspecified 
	//result = print10b() + result1.get();  // async
	result = result1.get() + print10b();	// a then b
#endif

											//std::cout << "\nfoo1() + foo2(): " << result << std::endl;
	return 0;
}



void f_utils(int i)
{
	cout << "i = " << i << endl;
}


int f_throw()
{
	int i = 10;
	while (--i)
	{
		f_utils(i);
		if (i < 2)throw runtime_error("intentionally throw! \n");
	}
	return i;
}


void test_async_excep()
{
	cout << __FUNCTION__ << ": " << endl;
#if 0	// catch

	auto f1 = std::async(std::launch::deferred, f_throw);
	try
	{
		f1.get();
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
	}
#else	// no catch
	auto f1 = std::async(std::launch::async, f_throw);
	f1.get();
#endif
}

/*

int quick();
int accurate_but_slow();

std::future<int> f;

int speculative_exec()
{
	// why not local f ???
	f = std::async(std::launch::async, quick);
	int guess = accurate_but_slow();
	std::future_status s = f.wait_for(std::chrono::milliseconds(1000));

	if (s == std::future_status::ready)
	{
		return f.get();
	}
	else
	{
		return guess; // accurate_but_slow() continues
	}
}

*///

/* poll

while(f.wait_for(chrono::seconds(0)
!= future_status::ready))
{
...
}

if (f.wait_for(chrono::seconds(0))!= future_status::deferred)
{
// do something while task has not finished
while(f.wait_for(chrono::seconds(0)!= future_status::ready))
{
...
}
}
*/


/// some notes
// 1. pass argument

int test_async_pass_value()
{
	auto fA = std::async(print10, 'A');
	auto fB = std::async(print10, 'B');

	if (fA.wait_for(std::chrono::seconds(0)) != std::future_status::deferred ||
		fB.wait_for(std::chrono::seconds(0)) != std::future_status::deferred)
	{
		while (fA.wait_for(std::chrono::seconds(0)) != std::future_status::ready&&
			fB.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
		{
			// why yield ???
			std::this_thread::yield();	//  hint  to reschedule to the  next  thread
		}
		cout.put('\n').flush();
		try
		{
			fA.get();
			fB.get();
		}
		catch(const exception& e)
		{
			;
		}
	}
	return 0;
}

int printByRef(char& c,int n)
{
	std::default_random_engine dre(c);
	std::uniform_int_distribution<int> id(10, 1000);
	for (int i = 0; i < 10; ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
		//std::this_thread::yield
		//std::this_thread::get_id
		//std::this_thread::sleep_until
		cout << (int)(c += n) << " ";
	}
	return c;
}

// data race
int test_async_pass_ref()
{
	char ch = '0';
	auto fA = std::async([&] {printByRef(std::ref(ch),1); });
	ch = '1';
	auto fB = std::async([&] {printByRef(std::ref(ch),2); });

	if (fA.wait_for(std::chrono::seconds(0)) != std::future_status::deferred ||
		fB.wait_for(std::chrono::seconds(0)) != std::future_status::deferred)
	{
		while (fA.wait_for(std::chrono::seconds(0)) != std::future_status::ready&&
			fB.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
		{
			// why yield ???
			std::this_thread::yield();	//  hint  to reschedule to the  next  thread
		}
		cout.put('\n').flush();
	}
	try
	{
		fA.get();
		fB.get();
	}
	catch (const exception& e)
	{
		;
	}
	return 0;
}