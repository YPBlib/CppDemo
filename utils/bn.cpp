#include<cstdio>
#include<iostream>
#include<ios>
#include<fstream>
#include<sstream>
#include<cctype>
#include<cstdlib>
#include<cmath>
#include<math.h>
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
#include<regex>
#include<cwchar>
#define Pi 3.14159265358979
using std::vector;;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::begin;
using std::end;
using std::ifstream;
using std::ofstream;
using std::sin;
using std::cos;
using std::ceil;
using std::regex;
struct complex;
vector<complex> DFT(vector<complex>& a, const int flag);
vector<complex> vecplxplus(const vector<complex>&a, const vector<complex>&b);
vector<complex> vecplxsub(const vector<complex>&a, const vector<complex>&b);
vector<complex> vecplxmult(const vector<complex>&a, const vector<complex>&b);
vector<complex> vecplxdiv(const vector<complex>&a, const vector<complex>& b);
vector<complex> vecplxremain(const vector<complex>& a, const vector<complex>& b);
vector<complex> plx_init(const string& x);
string plx_output(const vector<complex>& a);
vector<complex> super_pow(const vector<complex>&base, const vector<complex>& top, const vector<complex>& module);
vector<complex> half(const vector<complex>& a);
inline int intceil(const int& a)
{
	return (a % 2) ? ((a + 1) / 2) : a / 2;
}
struct complex
{
	double real;
	double imaginary;
	complex() :real(0.0), imaginary(0.0) {}
	complex(double r, double i) :real(r), imaginary(i) {}
	complex operator=(const complex& a)
	{
		real = a.real;
		imaginary = a.imaginary;
		return *this;
	}
	bool operator==(const complex& b)const
	{
		return real == b.real&&imaginary == b.imaginary;
	}
	bool operator>(const complex& b)const
	{
		return real > b.real;
	}
	complex operator+(const complex& b)const
	{
		complex result;
		result.imaginary = imaginary + b.imaginary;
		result.real = real + b.real;
		return result;
	}
	complex operator-(const complex& b)const
	{
		complex result;
		result.imaginary = imaginary - b.imaginary;
		result.real = real - b.real;
		return result;
	}
	complex operator*(const complex& b)const
	{
		complex result;
		result.real = real*b.real - imaginary*b.imaginary;
		result.imaginary = real*b.imaginary + imaginary*b.real;
		return result;
	}
	complex operator/(const complex& b)const
	{
		complex result;
		result.real = (real*b.real + imaginary*b.imaginary) / (b.real*b.real + b.imaginary*b.imaginary);
		result.imaginary = (imaginary*b.real - real*b.imaginary) / (b.real*b.real + b.imaginary*b.imaginary);
		return result;
	}
};
bool diffbyone(const string& up, const string& down)
{
	auto  b = plx_init(down);
	complex ij(1., 0.);
	vector<complex> one{ ij };
	b = plx_init(plx_output(vecplxplus(one, b)));
	return up == plx_output(b);
}
vector<complex> plx_init(const string& x)
{
	vector<complex> item;
	int ctz = 0;
	auto xi = x;
	// 抹掉高位的0，[0][1][2]
	for (auto i = x.begin(); i != x.end(); ++i)
	{
		if (*i == '0')
			++ctz;
		else break;
	}
	xi.erase(xi.begin() , xi.begin()+ctz);
	if (xi.empty() || xi == "0")
	{
		complex z(0., 0.);
		item.push_back(z);
		return item;
	}
	regex numstr("([0-9]|[1-9][0-9]*)");
	if (std::regex_match(xi.begin(), xi.end(), numstr))
	{
		auto c = xi.begin();
		while (c != xi.end())
		{
			complex temp(static_cast<double>(*c - '0'), 0.);
			// item[0] is low bit
			item.insert(item.begin(), 1, temp);
			c++;
		}
	}
	else
	{
		throw xi;
	}
	return item;
}
vector<complex> half(const vector<complex>& a)
{
	auto ai = a;
	auto lena = ai.size();
	if (lena < 6)
	{
		string cs = plx_output(ai);
		int css = atoi(cs.c_str());
		css /= 2;
		std::stringstream ssr;
		ssr << css;
		ssr >> cs;
		ai = plx_init(cs);
		return plx_init(plx_output(ai));
	}
	else
	{
		vector<complex> bi(ai.begin() + 6, ai.end());
		int carry1 = 0, carry2 = 0;
		for (auto i = bi.rbegin(); i != bi.rend(); ++i)
		{
			carry2 = static_cast<int>(i->real) % 2;
			i->real = static_cast<double>(( carry1*10+static_cast<int>(i->real)) / 2 );
			carry1 = carry2;
		}
		vector<complex> ci(ai.begin(), ai.begin()+6);
		string cs = plx_output(ci);
		int css = atoi(cs.c_str());
		css /= 2;
		std::stringstream ssr;
		ssr << css;
		ssr >> cs;
		ci = plx_init(cs);
		bi.insert(bi.end(), ci.begin(), ci.end());
		return bi;
	}
}
string plx_output(const vector<complex>& a)
{
	string s;
	auto ai = a;
	int carry = 0;
	int count_z = 0;
	for (auto i = ai.rbegin(); i != ai.rend(); ++i)
	{
		if (std::abs(i->real) < 0.0625)
			count_z++;
		else break;
	}
	if (a.size() == 0 || count_z == a.size())
		return "0";
	ai.erase(ai.end() - count_z, ai.end());
	//flatten
	for (auto& i : ai)
		i.imaginary = 0.;
	for (auto i = ai.cbegin(); i != ai.cend(); ++i)
	{
		int carry_t = 0;
		auto f = i->real;
		auto in = static_cast<int>(ceil(f-0.5));
		in += carry;
		if (in < 0)
		{
			int in_t = -in;
			while (in_t)
			{
				in_t /= 10;
				carry_t--;
			}
			int t = 1;
			for (int j = 0; j > carry_t; --j)
				t *= 10;
			in += t;	
		}
		s.insert(s.begin(),1,static_cast<char>(in % 10 + '0'));
		carry = in / 10;
		carry += carry_t;
	}
	if (carry < 0)
		return "-";
	while (carry)
	{
		char c = static_cast<char>(carry % 10 + '0');
		string cs;
		cs.push_back(c);
		s = cs + s;
		carry /= 10;
	}
	return s;
}
bool plx_GT(const vector<complex>& a, const vector<complex>& b)
{
	if (a.size()>b.size())
		return true;
	if (b.size()>a.size())
		return false;
	for (int i = a.size()-1; i >=0; --i)
	{
		if (a[i].real>b[i].real)
			return true;
		if (a[i].real<b[i].real)
			return false;
	}
	return false;
}
bool isodd(const vector<complex>& a)
{
	return static_cast<int>(a[0].real) % 2;
}
vector<complex> super_pow(const vector<complex>&base, const vector<complex>& top, const vector<complex>& modu)
{
	complex gg(1.0, 0.);
	complex hh(2.0, 0.);
	vector<complex> one{ gg };
	vector<complex> two{ hh };
	if (plx_output(top) == "1")
		return vecplxremain(base,modu);
	auto ti = one;
	if (isodd(top))
	{
		auto e = plx_init(plx_output(vecplxsub(top, one)));
		e = half(e);
		e = super_pow(base, e, modu);
		e = vecplxmult(e, e);
		e=vecplxmult(base, e);
		e = plx_init(plx_output(e));
		for (auto& i : e)
			i.imaginary = 0.;
		return vecplxremain(e, modu);
	}
	else
	{
		auto e = half(top);
		e=super_pow(base, e, modu);
		e=vecplxmult(e, e);
		e = plx_init(plx_output(e));
		for (auto& i : e)
			i.imaginary = 0.;
		return vecplxremain(e, modu);
	}
}
int main(void)
{
	vector<complex> x, ai, bi;
	ifstream fa("a.txt"), fb("b.txt");
	ofstream fc("c.txt");
	string opa, opb;
	fa >> opa;
	fb >> opb;
	try
	{
		ai = plx_init(opa);
		bi = plx_init(opb);
	}
	catch (string x)
	{
		cout << x << " is not valid input " << endl;
	}
	auto ci_plus = vecplxplus(ai, bi);
	auto ci_sub = vecplxsub(ai, bi);
	auto ci_mult = vecplxmult(ai, bi);
	fc << "a+b= " << plx_output(ci_plus) << endl;
	fc << "a-b= " << plx_output(ci_sub) << endl;
	fc << "a*b= " << plx_output(ci_mult) << endl;
	auto ci_div = vecplxdiv(ai, bi);
	fc << "a/b= " << plx_output(ci_div) << endl;
	auto ci_mod = vecplxremain(ai, bi);
	fc << "a%b= " << plx_output(ci_mod) << endl;
	//try
	//{
	//auto ci_div = vecplxdiv(ai, bi);
	//}
	/*catch (complex zero)
	{
	cout << "can't devide 0" << endl;
	}*/
	//auto ci_remain = vecplxremain(ai, bi);

	// BELOW is the D-H exchange procedure
	ifstream root("r.txt"), prime("prime.txt"), Alice("Alice.txt"), Bob("Bob.txt");
	ofstream privacy("privacy.txt");
	string A, B, R, P;
	Alice >> A;
	Bob >> B;
	root >> R;
	prime >> P;
	vector<complex> XA = plx_init(A);
	vector<complex> XB = plx_init(B);
	vector<complex> ROOT = plx_init(R);
	vector<complex> PRIME = plx_init(P);
	vector<complex> YA, KEY;
	
	YA=super_pow(ROOT, XA, PRIME);
	YA = plx_init(plx_output(YA));
	KEY = super_pow(YA, XB, PRIME);
	string p_key = plx_output(KEY);
	privacy << p_key << endl;
	return 0;
}
vector<complex> DFT(vector<complex>& a, const int flag)
{
	// coe <-> point
	int len = a.size();
	double n = static_cast<double>(len);
	if (len == 1)
		return a;
	vector<complex> a0(len / 2);
	vector<complex> a1(len / 2);
	for (int i = 0; i < len / 2; ++i)
	{
		a0[i] = a[i * 2];
		a1[i] = a[i * 2 + 1];
	}
	complex w = complex(1, 0);
	complex wn = complex(cos(2.*Pi / n), flag*sin(2.*Pi / n));
	DFT(a0, flag);
	DFT(a1, flag);
	
	for (int i = 0; i < len / 2; ++i)
	{
		// A(x) = A0(x^2) + x A1(x^2)
		a[i] = a0[i] + w* a1[i];
		a[i + len / 2] = a0[i] - w*a1[i];
		w = w *  wn;
	}
	return a;
}
vector<complex> vecplxmid(const vector<complex>&a, const vector<complex>&b)
{
	vector<complex> di;
	auto ai = a, bi = b;
	auto ci = vecplxplus(ai, bi);
	string cs = plx_output(ci);
	ci = plx_init(cs);
	if (cs.size() <= 6)
	{
		int x = atoi(cs.c_str());
		x /= 2;
		std::stringstream ss;
		ss << x;
		ss >> cs;
	}
	else
	{
		cs = "";
		int carry = 0;
		for (auto i = ci.rbegin(); i != ci.rend(); ++i)
		{
			int ij = carry + static_cast<int>(i->real) / 2;
			carry= static_cast<int>(i->real) % 2;
			cs.insert(cs.begin(), 1, static_cast<char>('0' + ij));
		}
	}
	di = plx_init(cs);
	return di;
}
vector<complex> vecplxplus(const vector<complex>&a, const vector<complex>&b)
{

	auto lena = a.size();
	auto lenb = b.size();
	auto min_iter = lena <= lenb ? lena : lenb;
	auto result = lena > lenb ? a : b;
	auto aux = lena > lenb ? b : a;
	for (auto i = 0; i < min_iter; ++i)
	{
		result[i] = result[i] + aux[i];
	}
	return result;
}
vector<complex> vecplxsub(const vector<complex>&a, const vector<complex>&b)
{
	auto ai = plx_init(plx_output(a)), bi = plx_init(plx_output(b));
	auto lena = ai.size();
	auto lenb = bi.size();
	auto max_iter = lena + lenb;
	complex z(0., 0.);
	vector<complex> result = ai, aux = bi;
	result.insert(result.end(), lenb, z);
	aux.insert(aux.end(), lena, z);
	
	for (auto i = 0; i < max_iter; ++i)
	{
		result[i] = result[i] - aux[i];
	}
	return result;
}
vector<complex> vecplxmult(const vector<complex>&a, const vector<complex>&b)
{

	vector<complex>ai = a, bi = b;


	int lena = ai.size(), lenb = bi.size();
	int max_len = lena + lenb;
	// enlarge size to 2^n
	int scale = 1;
	while (scale < max_len)
	{
		scale <<= 1;
	}
	ai.insert(ai.end(), scale - lena, complex(0, 0));
	bi.insert(bi.end(), scale - lenb, complex(0, 0));
	DFT(ai, 1);
	
	DFT(bi, 1);

	
	vector<complex> ci;
	for (int i = 0; i != scale; ++i)
	{
		ci.push_back(ai[i] * bi[i]);
	}
	DFT(ci, -1);
	double dl = static_cast<double>(scale);
	for (auto i=ci.begin();i!=ci.end();++i)
		i->real /= dl;
	return ci;
}

vector<complex> vecplxdiv(const vector<complex>&a, const vector<complex>& b)
{
	complex jc(2.0, 0), ic(1.0, 0), kc(0.0, 0.);
	const vector<complex> zero{ kc };
	const vector<complex> one{ ic };
	const vector<complex> two{ jc };
	if (plx_GT(b, a))
	{
		return zero;
	}
	vector<complex> up = a, down = one;
	auto memory_result = down, attempt_result = down;
	while (1)
	{
		string diff_u = plx_output(up);
		string diff_d = plx_output(down);
		
		if (diffbyone(diff_u, diff_d))
		{
			return down;
		}
		
		auto zz = vecplxmult(b, attempt_result);
		zz = plx_init(plx_output(zz));
		if(!plx_GT(zz,a))
		//if (plx_output(vecplxsub(a, vecplxmult(b, attempt_result))) != "-")
		{
			memory_result=down = plx_init(plx_output(attempt_result));
			attempt_result = plx_init(plx_output(vecplxmid(up, down)));	
		}
		else
		{
			up = plx_init(plx_output(attempt_result));
			attempt_result = plx_init(plx_output(vecplxmid(up, down)));
		}
		
	}
	
}
vector<complex> vecplxremain(const vector<complex>& a, const vector<complex>& b)
{
	auto qi = vecplxdiv(a, b);
	return vecplxsub(a, vecplxmult(qi, b));
}
