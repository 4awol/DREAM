#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring path, Vector2 maxFrame)
    : Quad()
    , _maxFrame(maxFrame)
{
    _srv = ADD_SRV(path);
    _size = _srv->GetImageSize();
    _size.x /= _maxFrame.x;
    _size.y /= _maxFrame.y;

    CreateVertices();
    CreateData(path);

    _actionBuffer = make_shared<ActionBuffer>();
    _actionBuffer->_data.imageSize = _srv->GetImageSize();
    _actionBuffer->_data.size = _size;
}
Sprite::Sprite(wstring path, Vector2 maxFrame, Vector2 size)
: Quad()
, _maxFrame(maxFrame)
{
    _srv = ADD_SRV(path);
    _size = size;

    CreateVertices();
    CreateData(path);

    _actionBuffer = make_shared<ActionBuffer>();
    _actionBuffer->_data.imageSize = _srv->GetImageSize();
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
    _actionBuffer->Update_Resource();
	Quad::Update();
}

void Sprite::Render()
{
    _actionBuffer->SetPS_Buffer(0);
	Quad::Render();
}

void Sprite::CreateVertices()
{
    Vertex_Texture v;

    Vector2 halfSize = _size * 0.5f;

    v.pos = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
    v.color = { 1.0f, 0.0f, 0.0f, 1.0f };
    v.uv = { 0.0f, 0.0f };
    _vertices.push_back(v);

    v.pos = { halfSize.x, halfSize.y, 0.0f }; // 오른쪽 위
    v.color = { 0.0f, 1.0f, 0.0f, 1.0f };
    v.uv = { 1.0f, 0.0f };
    _vertices.push_back(v);

    v.pos = { halfSize.x, -halfSize.y, 0.0f }; // 오른쪽 아래
    v.color = { 0.0f, 0.0f, 1.0f, 1.0f };
    v.uv = { 1.0, 1.0f };
    _vertices.push_back(v);

    v.pos = { -halfSize.x, -halfSize.y, 0.0f }; // 왼쪽 아래
    v.color = { 0.0f, 0.0f, 0.0f, 1.0f };
    v.uv = { 0.0f, 1.0f };
    _vertices.push_back(v);

    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);

    _indices.push_back(0);
    _indices.push_back(2);
    _indices.push_back(3);
}

void Sprite::CreateData(wstring path)
{
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Texture), _vertices.size());
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
    _vs = make_shared<VertexShader>(L"Shader/TextureVS.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/ActionPS.hlsl");
}

void Sprite::SetCurClip(Vector2 frame)
{
    Vector2 size = _actionBuffer->_data.size;
    _actionBuffer->_data.startPos.x = (frame.x * size.x);
    _actionBuffer->_data.startPos.y = (frame.y * size.y) ;
}

void Sprite::SetCurClip(Action::Clip clip)
{
    _actionBuffer->_data.size = clip.size;
    _actionBuffer->_data.startPos = clip.startPos;
}
