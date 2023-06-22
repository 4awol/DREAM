#pragma once
class Player
{
public:
	struct Vertex
	{
		Vector2 pos;
		int g; // Dijkstra ... cost
		int h;
		int f;

		bool operator<(const Vertex& other) const
		{
			return f < other.f;
		}

		bool operator>(const Vertex& other) const
		{
			return f > other.f;
		}
	};

	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();
	void BFS();
	void Astar();

	bool Cango(Vector2 pos);

private:
	Vector2 _startPos = {1,1};
	Vector2 _endPos = {1,1};

	float _time = 0.0f;

	int _pathIndex = 0;
	vector<Vector2> _path;

	weak_ptr<Maze> _maze;

	vector<vector<bool>> _discovered;
	vector<vector<Vector2>> _parent;
	vector<vector<int>> _best;
};

