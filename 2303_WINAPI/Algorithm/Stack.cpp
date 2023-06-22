#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <stack>
#include <deque>

using namespace std;

// Stack
template <typename T, typename Container = vector<T>>
class Stack
{
public:
	void push(const T& value)
	{
		container.push_back(value);
	}

	void pop()
	{
		container.pop_back();
	}

	const T& top()
	{
		return container.back();
	}

	bool empty()
	{
		return container.empty();
	}

private:
	Container container;
};

int main()
{
	Stack<int,deque<int>> s;

	s.push(4);
	s.push(2);
	s.push(1);
	s.push(3);
	s.push(10);

	while (true)
	{
		if(s.empty())
			break;

		cout << s.top() << endl;
		s.pop();
	}

	return 0;
}