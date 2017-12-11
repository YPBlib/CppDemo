#include<cstdio>
#include<iostream>
#include<ios>
#include<fstream>
#include<sstream>
#include<cctype>
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
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<regex>
#include"try.h"
//using namespace::std;
using std::vector;
using std::deque;
using std::list;
using std::forward_list;
using std::array;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::begin;
using std::end;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;
using std::nounitbuf;
using std::allocator;
using std::runtime_error;
using std::regex;
using std::smatch;
using std::regex_search;
using std::regex_match;
using std::regex_replace;
using std::sregex_iterator;
using std::ssub_match;
int c11regex(void);
void c11stl(void)
{
	c11regex();
	
	return;
}

int c11regex(void)
{
	string pattern("[^c]ei");
	pattern = "[[:alpha:]]" + pattern + "[[:alpha:]]*";
	regex r(pattern,regex::icase);
	smatch results;
	string re_test1 = "receipt freind theif receive";
	if (regex_search(re_test1, results, r))
		cout << results.str() << endl;
	
	return 0;
}