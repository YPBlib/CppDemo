#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  vector<int> primers{2, 3, 5, 7, 11, 13};
  int low=14;
  int high=2147483647;
  for(int i=low;i<high;++i)
  {
    for(auto p:primers)
    {
      if(p>(int)(sqrt(i))+1)
      {
        primers.push_back(i);
        break;
      }
      if(i%p==0)break;
    }
  }
  cout<<primers.size()<<endl;
  return 0;

}
