#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

vector<vector<int>> adjacent_list;
vector<vector<bool>> adjacent;

// 인접행렬
void CreateGraph()
{
	//	  0  1  2  3  4  5  6
	// 0  1  1  1  0  0  0  0
	// 1  1  1  0  0  0  0  1
	// 2  1  0  1  1  0  1  0
	// 3  0  0  1  1  0  0  0
	// 4  1  0  0  0  1  0  0
	// 5  0  0  1  0  0  1  0
	// 6  0  1  0  0  0  0  1

	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));

	adjacent[0][0] = true;
	adjacent[0][1] = true;
	adjacent[0][2] = true;
	adjacent[0][4] = true;

	adjacent[1][0] = true;
	adjacent[1][1] = true;
	adjacent[1][6] = true;

	adjacent[2][0] = true;
	adjacent[2][2] = true;
	adjacent[2][3] = true;
	adjacent[2][5] = true;

	adjacent[3][3] = true;
	adjacent[3][2] = true;

	adjacent[4][0] = true;
	adjacent[4][4] = true;

	adjacent[5][2] = true;
	adjacent[5][5] = true;

	adjacent[6][1] = true;
	adjacent[6][6] = true;
}

// 인접리스트
void CreateGraphByList()
{
	adjacent_list.resize(7);

	adjacent_list[0].push_back(0);
	adjacent_list[0].push_back(1);
	adjacent_list[0].push_back(2);
	adjacent_list[0].push_back(4);

	adjacent_list[1].push_back(1);
	adjacent_list[1].push_back(0);
	adjacent_list[1].push_back(6);

	adjacent_list[2].push_back(2);
	adjacent_list[2].push_back(0);
	adjacent_list[2].push_back(5);
	adjacent_list[2].push_back(3);

	adjacent_list[3].push_back(3);
	adjacent_list[3].push_back(2);

	adjacent_list[4].push_back(4);
	adjacent_list[4].push_back(0);

	adjacent_list[5].push_back(5);
	adjacent_list[5].push_back(2);

	adjacent_list[6].push_back(6);
	adjacent_list[6].push_back(1);
}

int main()
{
	CreateGraphByList();

	// 0과 1이 인접해있습니까?

	auto iter = std::find(adjacent_list[0].begin(), adjacent_list[0].end(), 1);
	if (iter != adjacent_list[0].end())
	{
		cout << *iter << "이 0과 인접해있습니다." << endl;
	}

	CreateGraph(); // 인접행렬

	// 5와 2가 인접해있습니까?
	if (adjacent[5][2])
	{
		cout << "5와 2가 인접해있습니다."<<endl;
	}

	return 0;
}