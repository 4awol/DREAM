#include "framework.h"
#include <map>
#include <queue>
#include "Maze.h"
#include "../../Math/DisJointSet.h"

Maze::Maze()
{
	Vector2 offset = Vector2(400,100);

	_blocks.resize(25);
	for (int y = 0; y < _poolCountY; y++)
	{
		_blocks[y].reserve(25);
		for (int x = 0; x < _poolCountX; x++)
		{
			shared_ptr<MazeBlock> block = make_shared<MazeBlock>();
			block->SetPostion(offset + Vector2(18 * x, 18 * y));
			block->SetType(MazeBlock::BlockType::DISABLE);

			_blocks[y].push_back(block);
		}
	}

	CreateMaze_Prim();
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blockArr : _blocks)
	{
		for(auto block : blockArr)
			block->Update();
	}
}

void Maze::Render(HDC hdc)
{
	for (auto blockArr : _blocks)
	{
		for (auto block : blockArr)
			block->Render(hdc);
	}
}

// Maze for Programmer
void Maze::CreateMaze()
{
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			_blocks[y][x]->SetType(MazeBlock::BlockType::DISABLE);
		}
	}

	// 노드 뚫기
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// 마지막 도착점 처리
			if(x == _poolCountX - 2 && y == _poolCountY - 2)
				continue;

			// 오른쪽 끝은 다 뚫려있게
			if (x == _poolCountX - 2)
			{
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}

			// 아래쪽 끝은 다 뚫려있게
			if (y == _poolCountY - 2)
			{
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}

			// 한개의 노드 기준 오른쪽 혹은 아래쪽 랜덤으로 길을 뚫는 작업
			const int randValue = rand() % 2;
			if(randValue == 0)
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
			else
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	_blocks[_poolCountY - 2][_poolCountX - 2]->SetType(MazeBlock::BlockType::END);
}

void Maze::CreateMaze_Kruskal()
{
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			_blocks[y][x]->SetType(MazeBlock::BlockType::DISABLE);
		}
	}

	// 노드 뚫기
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	// 모든 간선 담기
	// -> 오른쪽 혹은 아래쪽
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 오른쪽으로 향하는 간선 담기
			if (x < _poolCountX - 2)
			{
				const int randValue = rand() % 100;
				Edge_Kruskal edge;
				edge.u = Vector2(x,y);
				edge.v = Vector2 (x + 2, y);
				edge.cost = randValue;
				edges.push_back(edge);
			}

			// 아래쪽으로 향하는 간선 담기
			if (y < _poolCountY - 2)
			{
				const int randValue = rand() % 100;
				Edge_Kruskal edge;
				edge.u = Vector2(x,y);
				edge.v = Vector2(x, y + 2);
				edge.cost = randValue;
				edges.push_back(edge);
			}
		}
	}

	std::sort(edges.begin(), edges.end(), [](const Edge_Kruskal& a, const Edge_Kruskal& b)-> bool 
	{
		return (a.cost < b.cost);
	});

	DisJointSet sets(_poolCountX * _poolCountY);

	for (const auto& edge : edges)
	{
		int u = edge.u.y * _poolCountX + edge.u.x;
		int v = edge.v.y * _poolCountX + edge.v.x;
		if(sets.FindLeader(u) == sets.FindLeader(v))
			continue;

		sets.Merge(u,v);
		int yIndex = (edge.u.y + edge.v.y) / 2;
		int xIndex = (edge.u.x + edge.v.x) / 2;
		_blocks[yIndex][xIndex]->SetType(MazeBlock::BlockType::ABLE);
	}
}

void Maze::CreateMaze_Prim()
{
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			_blocks[y][x]->SetType(MazeBlock::BlockType::DISABLE);
		}
	}

	// 노드 뚫기
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	map<Vector2, vector<Edge>> edges;
	// edges[u]... u에 연결되어있는 모든 간선이 나온다.

	// 모든 간선의 후보를 담아두는 작업
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// 우측
			if (x < _poolCountX - 2)
			{
				const int randValue = rand() % 100;
				Vector2 u = {x,y};
				Vector2 v= {x + 2, y};
				edges[u].push_back({randValue, v});
				edges[v].push_back({randValue, u});
			}

			// 아래
			if (y < _poolCountY - 2)
			{
				const int randValue = rand() % 100;
				Vector2 u = {x,y};
				Vector2 v = {x, y + 2};
				edges[u].push_back({randValue, v});
				edges[v].push_back({randValue, u});
			}
		}
	}

	// 해당 정점이 집합에 포함이 되어있나?
	map<Vector2, bool> added;

	// 어떤 정점이 누구에 의해 연결되어있는지
	map<Vector2, Vector2> parent;

	// 만들고 있는 집합에 인접한 간선 중, 해당 정점에 닿는 최소 간선의 정보
	map<Vector2, int> best;

	// added, best 초기화
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			best[Vector2(x,y)] = INT_MAX;
			added[Vector2(x,y)] = false;
		}
	}

	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	Vector2 startPos = StartPos();
	pq.push({0,startPos});
	best[startPos] = 0;
	parent[startPos] = startPos;

	while (true)
	{
		if(pq.empty())
			break;

		Edge bestEdge = pq.top();
		pq.pop();

		// 새로 연결될 정점
		Vector2 vertex = bestEdge.v;

		if(added[vertex])
			continue;

		added[vertex] = true;

		// 맵에 적용
		{
			int x = (parent[vertex].x + vertex.x) / 2;
			int y = (parent[vertex].y + vertex.y) / 2;

			_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}

		for (Edge& edge : edges[vertex])
		{
			if(added[edge.v])
				continue;

			// 다른 경로로 더 좋은 후보가 발견이 되어있었으면 스킾
			if(edge.cost > best[edge.v])
				continue;

			best[edge.v] = edge.cost;
			parent[edge.v] = vertex;
			pq.push(edge);
		}
	}

	return;
}
