#pragma once

struct Node
{
	Node() {}
	Node(int key) : key(key) {}

	int key = -1;
	int data = 0;

	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
};

class BST
{
public:
	BST();
	~BST();

	void Insert(int key);
	void PrintTree(Node* node);

	Node* Search(Node* node, int key);
	Node* Min(Node* node);
	Node* Max(Node* node);

	Node* Previous(Node* node);
	Node* Next(Node* node);
	void Delete(Node* node);

private:
	void Replace(Node* node1, Node* node2);
public:
	Node* _root = nullptr;
};

