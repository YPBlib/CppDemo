#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int pack(vector<int> value, vector<int> item,int V)
{
	int dp[20][20] = { 0 };
	for (int i = 0; i < item.size(); ++i)
	{
		for (int j = item[i]; j <= V; ++j)
		{
			int a = dp[i][j];
			int b = dp[i][j - item[i]] + value[i];
			dp[i+1][j] = max(a, b);
		}
	}
	return dp[item.size()][V];
}

int main()
{
	vector<int> values;
	vector<int> items;
	int v;

	items = { 7,8,9,10,11,12 };
	v = 15;
	values = { 100,110,120,130,140,150 };

	cout << pack(values, items, v) << endl;
	
    return 0;
}