#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

int main()
{
    ifstream ifcin(R"(D:\code\plainCode\text\top.py)");
    ofstream ofcout(R"(D:\code\plainCode\text\top)");
    string sss;
    vector<string> vsss;
    while(ifcin>>sss)
    {
        vsss.push_back(sss);
    }
    sort(vsss.begin(),vsss.end(),[](string a, string b){return a<b;});
    vsss.erase( std::unique( vsss.begin(), vsss.end() ), vsss.end() );
    for(auto i: vsss)
    {
        ofcout<<i<<endl;
    }
    return 0;
}
