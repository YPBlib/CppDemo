#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>
#include<typeinfo>
#include"try.h"
#include<vector>
using namespace::std;
using std::string;
using std::cin;
using std::cout;
static int v = 0;
int foo(int i);
auto func(int a);


int main(void)
{


	// 	const int coni1 = 1;	int* p1 = &coni1;   普通指针不能指向const
	//	int const i1 = 1;	int & r1 = i1;	普通引用不能引用const
	int i2 = 11;		const int * const p2 = &i2;
	//	int & const conrr2 = i2;	const被忽略	,有时也被视为不合法的写法
	//	int* const pp2 = &i2; int ii2 = 6l; auto atpp2 = p2; atpp2 = &ii2; *atpp2 = 5; auto保留底层const，抛弃顶层const
	//	int i3 = 1;  decltype(p2) atp4 = &i3; *atp4 = 5;	//decltype 的顶层const底层const均被保留
	//	const int coni3 = 4, ii3 = 5, &rconi3 = coni3; rconi3 = 6;		//Wrong ii3和rconi3 也是const
	//	constexpr int  *p = &v; 	*p = 5;		p = &i2; //p是顶层const
	int i3 = 3;		int&r3 = i3;	int*pi3 = &i3;
	auto ati3 = i3;//不相关
	auto atii3 = r3;	//不相关
	auto atiii3 = *pi3;		//不相关
	auto &atri3 = i3;	//相关
	auto &atrii3 = r3;	//相关
	auto &atriii3 = *pi3;		//相关	
								//	decltype(i3) dpi3 ;		//相关
								//	typedef decltype(*(&i3)) dpi3;		dpi3 wtf = i3;  //相关
								//	decltype(i3=0) dpasri3 = i3;	//相关

	cout << i3 << endl;
	decltype(r3) dpii3 = r3;	//相关
	decltype(r3 + 0) dpiij3 = r3;	//不相关
	decltype(*pi3) dpiii3 = *pi3;	//相关
	decltype((((i3)))) dpri3 = i3;	//相关,括号中为int变量时返回引用

	decltype((2 % 0))l;  //有效
	const int const* * const* p = nullptr;  //const的位置有没有其它方法
	const int coni4 = 1;
	auto z = p;		//z保留了几层const？？？


	double price = 0.;
	//	std::cin >> data1.bookNo >> data1.units >> price;
	// initialization
	string initializers1;
	string initializers2(initializers1);	//direct
	string initializers3 = initializers1;	//copy
	string initializers4 = "123465";	//copy
	string initializers5(100, 'a');	//direct
	int initializera1 = 0;  //copy
	int initializera2 = { 0 };	//copy
	int initializera3{ 0 };	//direct
	int initializera4(0);	//direct
							//string
							//	cin >> initializers1;
							//	cout << initializers1 << endl;
							//	getline(cin,initializers1);
	cout << initializers1;
	initializers1.size();
	//	"132465".size();		//wrong!!! string literals are not STL strings;
	string sss = "   " + initializers5;










	return 0;
}

int foo(int i)
{
	printf("%d %d %d \n", i++ * ++i, i-- - i--, ++i);
	return ++i + i++;
}

auto func(int a)
{
	decltype(nullptr)l = nullptr;
	int*p = nullptr;
	return p;

}