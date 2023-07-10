#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// n개의 공을 갖고있다.
// 순서 상관없이 m개의 공을 꺼낼 때 나올 수 있는 경우의 수를 모두 구하시오.
// n >= 1
// m >= 0

vector<vector<int>> cache = vector<vector<int>>(101, vector<int>(101, -1));

int Combine(int n, int m)
{
	// 기저사항
	if(n == 1 || m == 0 || n == m)
		return 1;

	// 메모이제이션
	if(cache[n][m] != -1)
		return cache[n][m];

	// 구하기
	return cache[n][m] = Combine(n-1, m) + Combine(n-1, m -1);
}

int main()
{
	cout << Combine(99,15) << endl;
	// 5! = 120
	// 2! * (5-2)! = 2 * 6

	vector<int> v = {1,2,3,4};

	while (true)
	{
		if (std::next_permutation(v.begin(), v.end()))
		{
			for (auto value : v)
			{
				cout << value << ",";
			}

			cout << endl;
		}
		else
			break;
	}

	return 0;
}