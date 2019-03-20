#include <algorithm>
#include <iostream>
using namespace std;
int QuickSelect(int*const cl, int*const cr, size_t kth)
{
    auto size=cr-cl+1;
    if(size<kth+1) throw;
    if(size<=5)
    {
        for(auto ptr=cl;ptr!=cr;++ptr)
        {
            for(auto p=ptr;p<=cr;++p)
            {
                if(*ptr>*p)
                {
                    *p ^= *ptr;
                    *ptr ^= *p;
                    *p ^= *ptr;
                }
            }
        }
        return cl[kth];
    }
    size_t times=(size+4)/5;
    
    for(int i=0;i<times-1;++i)
    {
        auto tmp=QuickSelect(cl+i*5,cl+i*5+4,2);
        cl[i*5+2]=cl[i];
        cl[i]=tmp;
    }

	// 处理最后一组
    auto tmp=QuickSelect(cl+(times-1)*5,cr,(size-(times-1)*5-1)/2);
    *(cl+(times-1)*5+(cr-(cl+(times-1)*5))/2)=cl[times-1];
    cl[times-1]=tmp;
    
	// 求所有中位数的中位数
    auto mid=QuickSelect(cl,cl+times-1,(times-1)/2);
    int ltcnt=0,eqcnt=0;
    
    for(auto ptr=cl;ptr<=cr;++ptr)
    {
        if(*ptr==mid)++eqcnt;
        else if(*ptr<mid)++ltcnt;
    }

    if(ltcnt==kth || ((ltcnt<kth)&&(ltcnt+eqcnt)>kth) )
    {
        return mid;
    }

	

    auto l=cl,r=cr;
    int cnt=0;
    if(ltcnt+1>kth)
    {
        for(cnt=0;l<=r;)
        {
			if (*l >= mid)
			{
				++cnt;
				swap(*l, *r);
				--r;
			}
			else ++l;
			
        }
    }
    else
    {
		for (cnt = 0; l <= r;)
		{
			if (*l <= mid)
			{
				++cnt;
				swap(*l, *r);
				--r;
			}
			else l++;
		}
		kth -= cnt;
    }
	return QuickSelect(cl, cr - cnt, kth);

} 

int main()
{
	int x[10] = { 2,9,0,7,3,1,6,4,5,8 };
	for (int i = 0; i < 10; ++i)
	{
		int j = QuickSelect(x, x + 9, i);
		cout << j << endl;
	}

	int y[20] = { 14, 9, 12, 6, 11, 13, 18, 5, 1, 17, 2, 4, 8, 19, 0, 10, 3, 16, 7, 15 };
	for (int i = 0; i < 20; ++i)
	{
		int j = QuickSelect(y, y + 19, i);
		cout << j << endl;
	}

	int z[100] = { 13, 47, 43, 16, 94, 46, 56, 62, 9, 7, 12, 81, 21, 39, 99, 29, 17, 37, 79, 49, 2, 26, 40, 0, 59, 98, 82, 31, 22, 33, 10, 89, 63, 93, 4, 28, 86, 75, 6, 66, 92, 25, 45, 68, 34, 11, 41, 36, 67, 95, 76, 72, 57, 80, 73, 51, 74, 19, 14, 24, 38, 58, 27, 96, 20, 50, 3, 48, 18, 64, 52, 91, 30, 5, 85, 97, 71, 69, 55, 23, 88, 61, 8, 15, 1, 83, 60, 65, 90, 77, 87, 42, 84, 70, 44, 32, 78, 53, 54, 35 };
	for (int i = 0; i < 100; ++i)
	{
		int j = QuickSelect(z, z + 99, i);
		cout << j << endl;
	}
	
    return 0;
}