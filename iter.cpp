#include "common.h"

using namespace std;


/*
��ν stream _iterator �ṩ�� = ���㣬�������
��ʼ��ʱ������һ�� delimiter
*�����++ -- ������ʱû��
��� std::copy ����ʵ������IO
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