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

// Tree
// - root
// - leaf
// - depth

// 1. 계층적 구조를 나타내기에 가장 적합한 구조.
// 2. 서브트리가 존재하며, 트리는 재귀적 속성을 갖는다.

struct Node
{
	Node() {}
	Node(const string& data) : _data(data) {}
	
	vector<Node*> _children;
	string _data;
};

Node* CreateTree()
{
	Node* root = new Node("개발팀");
	{
		Node* children_1 = new Node("프로그래밍팀");
		root->_children.push_back(children_1);

		{
			Node* children_2 = new Node("클라이언트");
			children_1->_children.push_back(children_2);
		}

		{
			Node* children_2 = new Node("서버");
			children_1->_children.push_back(children_2);
		}

		{
			Node* children_2 = new Node("엔진");
			children_1->_children.push_back(children_2);
		}
	}

	{
		Node* children_1 = new Node("기획");
		root->_children.push_back(children_1);

		{
			Node* children_2 = new Node("스토리");
			children_1->_children.push_back(children_2);
		}

		{
			Node* children_2 = new Node("레벨디자인");
			children_1->_children.push_back(children_2);
		}

		{
			Node* children_2 = new Node("밸런스");
			children_1->_children.push_back(children_2);
		}
	}

	{
		Node* children_1 = new Node("아트");
		root->_children.push_back(children_1);

		{
			Node* children_2 = new Node("배경");
			children_1->_children.push_back(children_2);
		}

		{
			Node* children_2 = new Node("원화");
			children_1->_children.push_back(children_2);
		}

		{
			Node* children_2 = new Node("모델링");
			children_1->_children.push_back(children_2);
		}
	}

	return root;
}

void PrintTree(Node* root, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout<< "-";
	}


	cout << root->_data << endl;
	for (auto node : root->_children)
	{
		PrintTree(node, depth + 1);
	}
}

int main()
{
	Node* root = CreateTree();

	PrintTree(root,0);

	return 0;
}