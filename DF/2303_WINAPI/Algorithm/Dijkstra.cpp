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
vector<vector<int>> adjacent;
vector<bool> discovered;
vector<int> parent;
vector<int> best;

struct Vertex
{
	int vertexNum;
	int cost;

	bool operator<(const Vertex& other) const
	{
		return cost < other.cost;
	}

	bool operator>(const Vertex& other) const
	{
		return cost > other.cost;
	}
};


void CreateGraph()
{
	adjacent = vector<vector<int>>(7, vector<int>(7, -1));

	adjacent[0][0] = 0;
	adjacent[0][1] = 4;
	adjacent[0][2] = 1;
	adjacent[0][4] = 8;

	adjacent[1][0] = 4;
	adjacent[1][1] = 0;
	adjacent[1][6] = 7;
	adjacent[1][2] = 2;

	adjacent[2][0] = 1;
	adjacent[2][1] = 2;
	adjacent[2][2] = 0;
	adjacent[2][3] = 4;
	adjacent[2][5] = 5;

	adjacent[3][3] = 0;
	adjacent[3][2] = 4;

	adjacent[4][0] = 8;
	adjacent[4][4] = 0;

	adjacent[5][2] = 5;
	adjacent[5][5] = 0;
	adjacent[5][6] = 80;

	adjacent[6][1] = 7;
	adjacent[6][5] = 80;
	adjacent[6][6] = 0;
}

void Dijkstra(int startIndex)
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	best = vector<int>(adjacent.size(), INT_MAX);
	discovered = vector<bool>(adjacent.size(), false);
	parent = vector<int>(adjacent.size(), -1);

	Vertex start;
	start.vertexNum = startIndex;
	start.cost = 0;

	pq.push(start);
	best[start.vertexNum] = start.cost;
	discovered[start.vertexNum] = true;
	parent[start.vertexNum] = start.vertexNum;

	while (true)
	{
		if(pq.empty())
			break;

		int cost = pq.top().cost;
		int here = pq.top().vertexNum;

		pq.pop();

		// 먼저 찾은게 현재 추가할려는 Vertex의 가중치보다 작은 경우
		if (best[here] < cost)
		{
			cout<< here << endl;
			cout << cost << endl;
			cout << best[here] << endl;
			continue;
		}

		// BFS와 동일하게 인접한 Vertex 확인
		for (int there = 0; there < adjacent.size(); there++)
		{
			// 현재 pq에 추가할 위치가 동일하면 continue;
			if(here == there)
				continue;

			// 인접확인
			if(adjacent[here][there] == -1)
				continue;

			int nextCost = best[here] + adjacent[here][there];

			// 뒤늦게 찾은 Vertex의 best가
			// 기존에 찾은 Vertex의 best보다 더 크면 다음 꺼 확인
			if (nextCost >= best[there])
			{
				cout << here << "에서 " << there <<"까지" << endl;
				cout << "이미 더 좋은 best값이 있어서 무시하겠습니다." <<endl;
				continue;
			}

			Vertex v;
			v.vertexNum = there;
			v.cost = nextCost;
			pq.push(v);
			best[there] = nextCost;
			discovered[there] = true;
			parent[there] = here;
		}
	}

	for (int i = 0; i < adjacent.size(); i++)
	{
		cout << i << "의 부모 : " << parent[i] << endl;
		cout << i << "의 시작점부터의 최소거리 : " << best[i] << endl;
	}
}

int main()
{
	CreateGraph(); // 인접행렬
	Dijkstra(0);

	return 0;
}