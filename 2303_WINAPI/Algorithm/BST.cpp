#include <iostream>

using namespace std;

#include "BST.h"

BST::BST()
{
}

BST::~BST()
{
}

void BST::Insert(int key)
{
    Node* newNode = new Node(key);

    // 트리의 첫 생성
    if (_root == nullptr)
    {
        _root = newNode;
        return;
    }

    Node* node = _root;
    Node* parent = nullptr;

    while (true)
    {
        if(node == nullptr)
            break;

        parent = node;
        if(key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    node = newNode;
    node->parent = parent;

    if(node->key < parent->key)
        parent->left = node;
    else
        parent->right = node;
}

void BST::PrintTree(Node* node)
{
    if(node == nullptr)
        return;

    // 전위 순회 : root가 제일 앞으로
    // 중위 순회 : root가 중간
    // 후위 순회 : root가 제일 뒤에

    PrintTree(node->left);
    cout << node->key << endl;
    PrintTree(node->right);
}

Node* BST::Search(Node* node, int key)
{
    if(node == nullptr)
        return nullptr;

    if (node->key == key)
    {
        return node;
    }

    if(node->key > key)
        return Search(node->left, key);
    else
        return Search(node->right,key);
}

Node* BST::Min(Node* node)
{
    if(node == nullptr)
        return nullptr;

    if(node->left != nullptr)
        return Min(node->left);

    return node;
}

Node* BST::Max(Node* node)
{
    if (node == nullptr)
        return nullptr;

    if (node->right != nullptr)
        return Min(node->right);

    return node;
}

Node* BST::Previous(Node* node)
{
    if(node == nullptr)
        return nullptr;

    if(node->left == nullptr)
        return nullptr;

    return Max(node->left);
}

Node* BST::Next(Node* node)
{
    if (node == nullptr)
        return nullptr;

    if (node->right == nullptr)
        return nullptr;

    return Min(node->right);
}

void BST::Delete(Node* node)
{
    if(node == nullptr)
        return;

    // 지울 노드의 왼쪽 자식이 없다
    if(node->left == nullptr)
        Replace(node, node->right);
    // 지울 노드의 오른쪽 자식이 없는 경우
    else if(node->right == nullptr)
        Replace(node, node->left);
    // 자식 둘다 있는 경우
    else
    {
        Node* prev = Previous(node);
        node->key = prev->key;
        node->data = prev->data;
        Delete(prev);
    }
}

void BST::Replace(Node* node1, Node* node2)
{
    // node1이 루트일 때
    if(node1->parent == nullptr)
        _root = node2;

    // node1이 부모쪽에서 왼쪽 자식 노드일 때
    else if (node1 == node1->parent->left)
    {
        node1->parent->left = node2;
    }
    // node1이 부모쪽에서 오른쪽 자식 노드일 때
    else if (node1 == node1->parent->right)
    {
        node1->parent->right = node2;
    }

    if(node2 != nullptr)
        node2->parent = node1->parent;

    delete node1;
}
