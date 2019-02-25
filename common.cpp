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
#ifdef __CPP17___

	// reduce might be unavailable

	plus<int>();
	multiplies<int>();
	divides<double>();
	//equal partial_sum,accumulate,transform,inner_product
	vector<int>vec{ 1,2,3,4,5 };
	for (int i = 0; i < 5000; ++i)
	{
		if (!std::equal_to<int>()(
			accumulate(vec.begin(), vec.end(), 100, minus<int>()),
			reduce(vec.begin(), vec.end(), 100, minus<int>())))
		{
			cout << "not associative or not commulative" << endl;
		}
	}

#endif // __CPP17___

	
    return 0;
}

