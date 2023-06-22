#include <iostream>
#include <vector>

using namespace std;

int n = 50;
vector<bool> IsPrime = vector<bool>(51, true);

bool IsPrime_(int number)
{
	if(number == 0 || number == 1)
		return false;
	if(number == 2 || number == 3 || number == 5)
		return true;

	int sqrtN = sqrt(number);

	for (int i = 2; i < sqrtN; i++)
	{
		if(number % i == 0)
			return false;
	}

	return true;
}

void Eratosthenes()
{
	IsPrime[0] = false;
	IsPrime[1] = false;
	int sqrtN = sqrt(n);

	for (int i = 2; i <= sqrtN; i++)
	{
		if (IsPrime[i])
		{
			// i * i의 미만인 수는 이미 체크가 되어있을 것.
			for (int j = i * i; j <= n; j += i)
			{
				IsPrime[j] = false;
			}
		}
	}
}

int main()
{
	Eratosthenes();

	cout << IsPrime[50] << endl;
	cout << IsPrime_(50) << endl;

	return 0;
}