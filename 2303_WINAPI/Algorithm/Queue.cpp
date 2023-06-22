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

class Queue
{
public:
	void push(const int& value)
	{
		dq.push_back(value);
	}

	void pop()
	{
		dq.pop_front();
	}

	const int& front()
	{
		return dq.front();
	}

	bool empty()
	{
		return dq.size() == 0;
	}

private:
	deque<int> dq;
};

int main()
{
	Queue q;

	q.push(5);
	q.push(3);
	q.push(2);
	q.push(10);
	q.push(11);

	while (true)
	{
		if(q.empty())
			break;

		cout << q.front() << endl;

		q.pop();
	}


	return 0;
}