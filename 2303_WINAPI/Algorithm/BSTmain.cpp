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

#include "BST.h"

// BST (Binary Search Tree) => 이진 탐색 트리


int main()
{
	BST bst;
	bst.Insert(3);
	bst.Insert(7);
	bst.Insert(10);
	bst.Insert(15);
	bst.Insert(25);
	bst.Insert(30);
	
	bst.PrintTree(bst._root);

	Node* newRoot = bst.Search(bst._root, 7);

	Node* findNode = bst.Next(newRoot);

	return 0;
}