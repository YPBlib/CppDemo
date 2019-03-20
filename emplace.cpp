#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <initializer_list>

using namespace std;

struct A
{
	vector<int> v;
	A() { cout << "A()" << endl; }
	A(int a) :v({a}) { cout << "A(int)" << endl; }
	A(initializer_list<int> a) :v(a) { cout<<"A(initializer_list<int>"<<endl; }
	A(const A& a) :v(a.v) { cout <<"const A& a"<< endl; }
	A(A&& a) :v(std::move(a.v)) { cout << "A(A&&)" << endl; }
};
int main()
{
	vector<A> v;
	cout << "push_back" << endl;
	v.push_back(1);
	cout << "emplace_back" << endl;
	v.emplace_back(2);

	return 0;
}

/*
push_back
A(int)
A(A&&)
emplace_back
A(int)
const A& a
*/

