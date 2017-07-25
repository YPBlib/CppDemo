#include<cstdio>
#include<iostream>
#include<string>
#include<cctype>
#include<cstdlib>
#include<typeinfo>
#include<iterator>
#include<cstddef>
#include"try.h"
#include<vector>
#include<stdexcept>
//using namespace::std;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::begin;
using std::end;
using std::istream;
using std::runtime_error;

static int v = 0;
istream& readit(istream& is, data& it);



int main(void)
{
	cin.clear();
	/******************* const auto & and other keywords********************************/
	// 	const int coni1 = 1;	int* p1 = &coni1;   普通指针不能指向const
	//	int const i1 = 1;	int & r1 = i1;	普通引用不能引用const
	int i2 = 11;		const int * const p2 = &i2;
	//	int & const conrr2 = i2;	const被忽略	,有时也被视为不合法的写法
	//	int* const pp2 = &i2; int ii2 = 6l; auto atpp2 = p2; atpp2 = &ii2; *atpp2 = 5; auto保留底层const，抛弃顶层const
	//	int i3 = 1;  decltype(p2) atp4 = &i3; *atp4 = 5;	//decltype 的顶层const底层const均被保留
	//	const int coni3 = 4, ii3 = 5, &rconi3 = coni3; rconi3 = 6;		//Wrong ii3和rconi3 也是const
	//	constexpr int  *p = &v; 	*p = 5;		p = &i2; //p是顶层const
	int i3 = 3;		int& r3 = i3;	int* pi3 = &i3;
	auto ati3 = i3;//不相关
	auto atii3 = r3;	//不相关
	auto atiii3 = *pi3;		//不相关
	auto& atri3 = i3;	//相关
	auto& atrii3 = r3;	//相关
	auto& atriii3 = *pi3;		//相关

	using inttwelve = int[12];
	typedef inttwelve onefourfour[12];
	//	decltype(i3) dpi3 ;		//相关
	//	typedef decltype(*(&i3)) dpi3;		dpi3 wtf = i3;  //相关
	//	decltype(i3=0) dpasri3 = i3;	//相关

	cout << i3 << endl;
	decltype(r3) dpii3 = r3;	//相关
	decltype(r3 + 0) dpiij3 = r3;	//不相关
	decltype(*pi3) dpiii3 = *pi3;	//相关
	decltype((((i3)))) dpri3 = i3;	//相关,括号中为int变量时返回引用

	decltype((2 % 0))l;  //有效
						 //	const int const* * const* p = nullptr;  //const的位置有没有其它方法
	const int coni4 = 1;
	//	auto z = p;		//z保留了几层const？？？


	double price = 0.;
	//	std::cin >> data1.bookNo >> data1.units >> price;


	/******************************** initialization *******************************/
	string initializers1;
	string initializers2(initializers1);	//direct
	string initializers3 = initializers1;	//copy
	string initializers4 = "123465";	//copy
	string initializers5(100, 'a');	//direct
	int initializera1 = 0;  //copy
	int initializera2 = { 0 };	//copy
	int initializera3{ 0 };	//direct
	int initializera4(0);	//direct



							/************************** string ********************************************/
	initializers1.size();
	//	"132465".size();		//wrong!!! string literals are not STL strings;
	const string sss = "   " + initializers4;
	for (auto& c : sss)
	{
		cout << c << endl;
	}

	const string hexdigits = "0123456789ABCDEF";
	cout << "Enter digits<=15 ,seperated by ' ' , input 'q' when finished" << endl;
	string result = "";
	string::size_type n;
	while (cin >> n)
	{
		if (n < hexdigits.size())
			result += hexdigits[n];
	}
	cout << result << endl;
	/************************** vector ****************************************************/
	vector<int> ivec;				//default initialization: ivec has no elements
	ivec.push_back(2);
	//vector<int&> rivec;			//Wrong references are not objects
	vector<string> svec = { "a","an","the" };
	for (auto c : svec)
	{
		//svec.push_back(c);			//Wrong! body of range for must not change the size of the sequence over which it is itersting
	}
	vector<string> svec1{ "a","an","the" };
	//vector<string> svec12("a","an","the");		//wrong
	vector<string> svec2(svec);
	vector<string>svec3 = svec2;
	vector<string> svec4(10, "ha");
	vector<string>svec5{ 10,"ha" };
	vector<string> svec6{ 10 };
	vector<string> svec7(10);
	/***************************** iterator ********************************/


	/*
	string s{"123456789"};

	string::iterator sit;
	sit=s.begin();
	string__const_iterator csit=s.cbegin();
	string::size_type sst;
	vector<int>::iterator ivecit;
	vector<int>::size_type ivecst;
	vector<int>::const_iterator iveccoit;
	*/
	/*
	vector<string> svec{"abc","  ","def,","."," "};
	vector<string>::iterator svecit=svec.begin();
	++svecit;
	if(!svecit->empty())
	cout<<"svecit not  empty"<<endl;          //whitespace is not empty
	++svecit;
	cout<<*svecit<<endl;
	*/

	/*
	string::difference_type sdt=s.cbegin()-s.cend();
	*/

	/************************************* Array  *************************/
	/*
	int arr[]={1,2,3};
	int a[3];
	a=arr;          //Wrong
	*/

	int a[5] = { 1,2,3,4,5 };
	vector<int> ivec10(begin(a), end(a));
	/****		Multidimentional Array	***/
	int mula[5][5][5] = { 0, };
	for (auto& level1 : mula)
		for (auto& level2 : level1)
			for (auto level3 : level2)
			{
				cout << level3 << endl;
			}
	/********************	Expressions	********************/
	//	cout << -100 % 3 << -100 % -3 << 100 % -3 << endl; // m%n has the same sigh as m
	/*
	int i = 5;
	if (i)
	cout << "i!=1 but is true" << endl;
	if (i == true)
	cout << "i !=1 but == true" << endl;
	*/
	vector<int> veci{ 1,2,3,4,5 };
	cout << sizeof(vector<vector<string> >) << sizeof(vector<string>) << sizeof(string) << endl;
	int* iptr1 = 0;			//That works.
	void* vptr1 = iptr1;		// ok
			/*						cast					*/		
	//			static_cast
	int i = 1, j = 1;
	double slope = static_cast<double>(j) / i;		
	//			const_cast
	const int& cfun(int a);
	void cfunc(int& a);
	cfunc( const_cast<int&>( cfun(10) ) );
	//			reinterpret_cast
	void* va=nullptr;
	int i4 = reinterpret_cast<int>(va);
	/**************			try blocks and exception handling		******************/
	//	throw expression
	vector<float> fvec1{ 1.,2.,3. };
	vector<float> fvec2{ 0 };
	vector<float>::const_iterator fit1 = fvec1.cend();
	vector<float>::const_iterator fit2 = fvec2.cend();
/*
	if (1)
		throw runtime_error("Here is an exception");
*/
	
	data toal, tran;
	data& trans = tran;
	


	return 0;

}
data& data::merge(const data& dat)
{
	d += dat.d;
	a += dat.a;
	return *this;
}

istream& readit(istream& is, data& it)
{
	double p = 0;
	is >> it.str >> it.a >> p;
	it.d = p*it.a;
	return is;
}


data::data(std::istream&is)
{
	readit(is, *this);
}

const int& cfun(int a)
{
	return a;
}
void cfunc(int& a)
{
	a++;
}

