#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 완전 탐색
// => 재귀 호출, 반복문

string babbling[4] = {"aya", "ye", "woo", "ma"};
vector<string> result;
vector<bool> visited;

void DFS(int start, string word)
{
	if(word.size() >= 10)
		return;

	string makeWord = word + babbling[start];
	result.push_back(makeWord);
	visited[start] = true;

	for (int i = 0; i < 4; i++)
	{
		if(start == i)
			continue;
		if(visited[i] == true)
			continue;

		DFS(i, makeWord);
	}

	visited[start] = false;
}

int main()
{

	for (int i = 0; i < 4; i++)
	{
		visited = vector<bool>(4, false);
		DFS(i, "");
	}

	return 0;
}