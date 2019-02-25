#include "common.h"

using namespace std;


template <typename T=int>
int foo(const T& a)
{
	return 2 * a;
}



int main()
{
	vector<int> v{ 1,2,3,4,5 };

	auto f = for_each(v.begin(), v.end(), foo<>);
	cout << f(45) << endl;
	
    return 0;
}

