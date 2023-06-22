#pragma once
class MazeBlock
{
public:
	enum class BlockType
	{
		ABLE,
		DISABLE,
		PLAYER,
		END,
		FOOTPRINT,
		VISITED,
		NONE
	};

	MazeBlock();
	~MazeBlock();

	void Update();
	void Render(HDC hdc);

	void SetPostion(Vector2 pos) { _rect->SetCenter(pos); }
	void SetType(MazeBlock::BlockType type) { _type = type; }
	MazeBlock::BlockType GetType() { return _type; }

private:
	BlockType _type = BlockType::NONE;
	vector<HBRUSH> _brushes;

	shared_ptr<RectCollider> _rect;
};

