#include "common.h"

using namespace std;


/*
所谓 stream _iterator 提供了 = 运算，即输出。
初始化时可以有一个 delimiter
*运算和++ -- 运算暂时没用
结合 std::copy 可以实现序列IO
*/
int test_os_it()
{
	vector<int> v{ 1,2,3,4,5 };
	ostream_iterator<int> oit(cout, ",");
	copy(v.begin(), v.end(), oit);
	oit = 56;
	oit = 2008;
	++oit;
	++oit;
	oit = 66;
	*oit = 99;
	return 0;
}