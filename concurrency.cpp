#include "concurrency.h"
#include "async.h"
#include "shared_future.h"
#include "promise.h"





void test_promise()
{
	cout << __FUNCTION__ << endl; 
	cout << std::this_thread::get_id() << endl;

}



int main()
{
	//test_shared_ref();
	//test_shared();
	test_thread();
	return 0;
}