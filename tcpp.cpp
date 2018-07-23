#include<cstdio>
#include<iostream>
#include<ios>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<typeinfo>
#include<iterator>
#include<cstddef>
#include<stdexcept>
#include<vector>
#include<deque>
#include<list>
#include<forward_list>
#include<array>
#include<string>
#include<memory>
#include<new>
#include<utility>
#include<functional>
#include<future>
#include<thread>
#include<chrono>
#include<random>
#include<exception>
#include"tcpp.h"
//#include<mpi.h>
using namespace::std;



template <typename T>
class hasStaticMember
{
public:
	int count() { return ctr; }
	void add(void)
	{
		++ctr;
	}
private:
	static int ctr;
	int tri = 0;
};

template <typename T>
int hasStaticMember<T>::ctr;

template <typename X=unsigned>
X clacX(const X& a, const X& b)
{
	X tmp = a*b;
	return tmp;
};
class TestBoolInitialization
{
public:
	int z;
	bool xb;
	bool xb2;
	bool xb3;
	bool xb4;
	bool xb5;
	TestBoolInitialization()
	{
		xb = true;
	}
};

void Const_Auto_Ref_Ptr_TCPP()
{
	
	//	const auto & and other keywords
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
}


// init
void Initialization_TCPP()
{
	// There are 6 kinds of init, as far as I know,
	// default direct value copy list move

	// default init CppPrimer $2.2.1 P43
	string initializers1;
	int x;

	// !! one should not tell by whether using = or () to tell copy-ctor or direct-ctor
	// for now, i think the difference between the two is that,
	// copy-ctor uses an already-existing object to init another
	// direct-ctor uses some args to init the object !!

	//direct init CppPrimer $3.2.1 P84
	string initializers2("fghijklmn");
	string initializers5(100, 'a');
	int initializera3{ 0 };
	int initializera4(0);

	// copy init CppPrimer $3.2.1 P84
	string initializers6(initializers2);
	string initializers3 = initializers1;
	int initializera1 = 0;
	int initializera2 = { 0 };
	// implicit copy ctor
	string initializers4 = "123465";
	
	
	// value init CppPrimer $3.3.1 P98
	vector<int> init_vec1(10, 5);
	vector<string> init_str(10, "abcde");

	// list init
	vector<int> init_vec2{ 1,2,3,4,5 };
	vector<bool> init_vec3{ true,false,true,true,false };

	//I don't like this kind...it's wierd
	vector<string> vec_str1{ 10 };
	vector<string> vec_str2{ 10,"abc" };

}

class init_class1
{
	// for class member, you can use assign `=`,curly `{}` to init them , 
	// but not `()`
	int x = 1;
	int y{ 2 };
	//int z(3); //wrong
};

class init_class2
{
public:
	int i;

	init_class2() = default;
	// set copy construct to be explicit may cause trouble
	explicit init_class2(const init_class2& b)
	{
		i = b.i;
	}
	init_class2& operator=(const init_class2& b)
	{
		i = b.i;
		return *this;
	}

	/*
	int main(void)
{
	init_class2 x1;
	init_class2 x2 = x1; // error, because of `explicit`
	return 0;
}
	*/
};

// constructor

class Constructor_Class
{
	int i;
};

/*
class Constructor_Class2
{
public:
	Constructor_Class2(int a):a(a) // init must be put here!
	{
		// here is assign ,not init
		b = a;  // error
		c = a;  // erroe
	}
private:
	int a;
	const int b;
	int& c;
};
*/




void String_TCPP()
{
	string ssr{ "erty" };
	//	"132465".size();		//wrong!!! string literals are not STL strings;
	const string sss = "   " + ssr;
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
}
	
void iterator_TCPP()
{
	//	 iterator
	string s{ "123456789" };

	string::iterator sit;
	sit = s.begin();
	
	string::size_type sst;
	vector<int>::iterator ivecit;
	vector<int>::size_type ivecst;
	vector<int>::const_iterator iveccoit;
}

int doSomething(char c)
{
	std::default_random_engine der(c);
	std::uniform_int_distribution<int> id(10, 1000);
	for (int i = 0; i < 10; ++i)
	{
		this_thread::sleep_for(std::chrono::milliseconds(id(der)));
		std::cout.put(c).flush();
	}
	return c;
}

int func1()
{
	return doSomething('.');
}

int func2()
{
	return doSomething('+');
}


void try_thread()
{
	std::cout << "starting fun1 in background, func2 in foreground" << std::endl;

	std::future<int> result1(std::async(func1));

	int result2 = func2();

	auto result = result1.get() + result2;

	std::cout << "\n func1()+funbc2() = " << result << std::endl;


	

}

int main(void)
{
	try_thread();
	return 0;
}
	
	
	
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

	/*
	//		Array
	int arr[]={1,2,3};
	int a[3];
	a=arr;          //Wrong


	int a[5] = { 1,2,3,4,5 };
	vector<int> ivec10(begin(a), end(a));



	int mula[5][5][5] = { 0, };
	for (auto& level1 : mula)
	for (auto& level2 : level1)
	for (auto level3 : level2)
	{
	cout << level3 << endl;
	}
	*/

	/*
	//Expressions
	//	cout << -100 % 3 << -100 % -3 << 100 % -3 << endl; // m%n has the same sigh as m
	*/

	/*
	int i = 5;
	if (i)
	cout << "i!=1 but is true" << endl;
	if (i == true)
	cout << "i !=1 but == true" << endl;
	*/

	/*
	vector<int> veci{ 1,2,3,4,5 };
	cout << sizeof(vector<vector<string> >) << sizeof(vector<string>) << sizeof(string) << endl;
	int* iptr1 = 0;			//That works.
	void* vptr1 = iptr1;		// ok
	*/

	/*
	//		cast
	int i = 1, j = 1;
	double slope = static_cast<double>(j) / i;
	//			const_cast
	const int& cfun(int a);
	void cfunc(int& a);
	cfunc( const_cast<int&>( cfun(10) ) );
	//			reinterpret_cast
	void* va=nullptr;
	int i4 = reinterpret_cast<int>(va);
	*/

	/*
	//		Container

	forward_list<double> fld1(10, 10);
	forward_list<int> fli1{ 1,2,3,4,5 };
	list<double> lstd2(10, 10);
	forward_list<double>::iterator flit1=fld1.begin();
	list<double>::iterator lstit2 = lstd2.begin();
	forward_list<double>::const_iterator flcit3=fld1.cbegin();
	deque<int>::size_type dqst1;
	vector<int>::difference_type vctidt;
	forward_list<double>& fldr=fld1;
	const forward_list<double>& fldr2 = fld1;

	//	-- flit1;		//Wrong, forward_list::iterator
	//	--lstit2;			//Wrong, list::iterator

	auto lstdit = lstd2.rbegin();		//reverse
	auto lstdit2 = lstd2.crend();
	std::array<int, 5> arr5i1{2, };

	list<string> lststr1 = {"aaa","bbb","ccc"};
	vector<const char*> vcch1 = { "a","an","the" };
	list<string> lststr2(lststr1);
	//	vector<string> vstr1(vcch1);		//Wrong type
	vector<string> vstr2(vcch1.begin(), vcch1.end());
	deque<string> dqstr2(vcch1.begin(), vcch1.end());		//both OK
	deque<string> dqstr3{ "a","1","3" };
	dqstr3[1];
	*/

	/*
	array<int, 10> arrin1{ 1,2,3,4 };
	array<int, 10> arrin2 = arrin1;		//OK
	array<int, 5> arrin3 = { 1,2 };
	array<int, 5> arrin4 = { 2,34 };

	//	arrin2 = arrin3;		//	error, type
	arrin3 = arrin4;
	arrin3 = { 2,0xf4,0x04 ,07,002};
	swap(arrin3, arrin4);
	arrin3.swap(arrin3);
	swap(arrin1, arrin1);
	*/

	/*
	vector<int> vin1;
	vector<int> vin2;
	vin1.assign(10, 0xff);
	cout << vin1.cend()-vin1.cbegin() << endl;
	vin2.assign({2,4,5,6,6,5});
	cout << vin2.cend() - vin2.cbegin() << endl;
	vin2.assign(20, 0x565);
	vin2.assign(vin2.cbegin(), vin2.cend());
	int i8 = 10, i9 = 010;
	vin1.assign(10, 2);
	vin2.assign(5, 1);
	vector<int>::const_iterator vinit1 = vin1.cbegin(), vinit2 = vin1.cend(), vinit3 = vin2.cbegin(),
	vinit4 = vin2.cend();
	cout << vinit2 - vinit1 << endl;
	cout << vinit4 - vinit3 << endl;
	swap(vin1, vin2);
	cout << vinit2 - vinit1 << endl;
	cout << vinit4 - vinit3 << endl;
	cout << vin1.size() << endl;
	cout << vin2.max_size() << endl;
	*/

	/*
	list<int> lstin1(2, 1);
	list<int> lstin2{ 3,4,5 };
	int in1 = 3;
	lstin1.push_back(in1);
	lstin1.emplace_back(in1);
	lstin1.push_front(0);
	lstin1.emplace_front(0);
	lstin1.insert(lstin1.cend(), 10);
	lstin1.insert(lstin1.cend(), 2, in1);
	lstin1.insert(lstin1.cend(), lstin2.cbegin(), lstin2.cend());
	list<int>::iterator lstinit1 = lstin1.insert(lstin1.cend(), { 11,12,13 });

	if(! lstin1.empty())
	{
	auto in2 = lstin1.back() + lstin1.front();
	}
	lstin1.emplace(lstin1.cend(), in1);
	*/

	/*
	deque<int> dqin1{ 1,2,3 };
	auto& in3 = dqin1[0];		//may cause UB
	auto& in4 = dqin1.at(5);	//may cause exception
	*/

	/*
	list<int> lstin3(10, 0);
	lstin3.pop_front();
	lstin3.pop_back();
	lstin3.erase(lstin3.cbegin());
	lstin3.erase(lstin3.cbegin(), lstin3.cend());
	lstin3.clear();
	*/

	/*
	array<int, 4> arr4in1{ 5,6,7,8 };
	forward_list<int> flstin1(0xf, 0);
	flstin1.before_begin();
	flstin1.cbefore_begin();
	flstin1.insert_after(flstin1.cbegin(), 1);
	flstin1.insert_after(flstin1.before_begin(), 010, 010);
	flstin1.insert_after(flstin1.cbefore_begin(), arr4in1.cbegin(), arr4in1.cend());
	flstin1.insert_after(flstin1.cbegin(), { 0xa,0xb,0xc,0xd,0xe,0xf });
	flstin1.emplace_after(flstin1.before_begin(), 1);
	flstin1.erase_after(++flstin1.begin());
	flstin1.erase_after(flstin1.before_begin(), flstin1.cend());

	flstin1.resize(0x10);
	flstin1.resize(0x20,0xff);
	*/

	/*
	vector<int> vin4(3, 3);
	vin4.reserve(60);
	cout << vin4.capacity() << endl;
	//	vin4.shrink_to_fit();
	vin4.push_back(4);
	cout << vin4.capacity() << endl;
	cout << vin4.size() << endl;
	vin4.insert(vin4.cbegin(), 3355, 3355);
	cout << vin4.capacity() << endl;
	cout << vin4.size() << endl;
	*/

	/*
	//			IOstream

	cin.eof();
	cin.fail();
	cin.bad();
	cin.good();
	cin.clear();
	auto originST = cin.rdstate();
	cin.clear();
	cin.setstate(originST);

	cin.clear(cin.rdstate()& ~cin.failbit & ~cin.badbit);
	string ostring{ "test io" };
	cout << nounitbuf;

	cout << ostring;		//???? what causes the buffer to be flushed ???
	cout << endl;
	ifstream inn("Draft\\Draft\\whichwhere.txt");
	ofstream onn("Draft\\Draft\\wherewhich.txt");
	data eg1;
	if (readit(inn, eg1))
	{
	data trans;
	while (readit(inn, trans))
	{
	if (eg1.fetchd() == trans.fetchd())
	{
	eg1.merge(trans);
	}
	else
	{
	putit(onn, eg1);
	eg1 = trans;
	}
	}
	putit(onn, eg1);
	}
	else
	{
	std::cerr << "No data" << endl;
	}
	std::shared_ptr<string> sdps1;
	*/

	/*
	//			classes
	class globalscope
	{
	public:
	int v{3};
	int testscope(void){ return ::v; }
	};
	globalscope a;
	cout << a.testscope() << a.v << endl;
	*/

	/*
	//		dynamic memory
	int *newp1 = new (std::nothrow) int();
	int *newp2 = new int[10];
	int *newp3 = new int[10]();
	int *newp4 = new int[10]{ 1,2,3,4 };
	std::shared_ptr<int> sp2(new int(1024));
	std::shared_ptr<int> sp3 = static_cast<std::shared_ptr<int>>(newp1);
	std::shared_ptr<int> sp4 = std::make_shared<int>(24);
	int* ptoint6 = sp4.get();
	sp3 = sp4 = sp2 = nullptr;
	int mySpDeleter(std::shared_ptr<int> sp0);		// using our own deletion code
	auto x = std::make_shared<int>(20);
	mySpDeleter(x);
	cout << *x << endl;
	//unique_ptr
	std::unique_ptr<int> up1(new int(3));
	std::unique_ptr<int> up2(up1.release());
	//weak_ptr
	std::weak_ptr<int> wp1(sp3);
	auto sp1 = wp1.lock();
	wp1.use_count(), wp1.expired();
	wp1.reset();

	delete[] newp1, newp2, newp3, newp4;
	std::unique_ptr<int[]> up3(new int[10]{ 0,1,2 });
	allocator<string> alocs1;
	auto const alocps1 = alocs1.allocate(5);
	alocs1.destroy(alocps1);
	*/

	/*
	// Dynamic Memory
	std::unique_ptr<string[]> ptrl(new string[10]);
	ptrl.release();
	std::allocator<string> alloc;
	auto z = alloc.allocate(10);
	alloc.construct(z," ");
	alloc.destroy(z);
	alloc.deallocate(z, 10);
	*/

	/*
	// CopyControl
	// CopyConstructor CopyAssignment Destructor
	// rvalue
	int i3 = 5;
	int&& rr = std::move(i3);
	*/

	


