#include <type_traits>
#include <typeinfo>
#include <iostream>

using namespace std;

template <typename T>T compare(const T & a, const T&b)
{
	return a + b;
}

int test_trait()
{
	int(*pf)(const int&, const int&) = compare;
	int(*pf1)(const int&, const int&) = compare<int>;
	add_pointer<decltype(compare<int>)>::type pf2 = compare;
	add_pointer<decltype(compare<int>)>::type pf3 = compare<int>;
	auto pf4 = compare<int>;
	// auto pf5 = compare;	// error
	cout << typeid(pf).name() << endl;
	cout << typeid(pf1).name() << endl;
	cout << typeid(pf2).name() << endl;
	cout << typeid(pf3).name() << endl;
	cout << typeid(pf4).name() << endl;
	return 0;
}