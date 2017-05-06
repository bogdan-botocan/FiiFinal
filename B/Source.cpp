#include <iostream>

using namespace std;

int main()
{
	int long long N, K;
	cin >> N >> K;

	int long long previous = 0;
	int long long count = 0;
	int long long current_length = 0;
	for (int i = 0; i < N; i++)
	{
		int long long x; cin >> x;
		if (x == previous + 1)
		{
			current_length += 1;
		}	
		else
		{
			count += current_length / K;
			current_length = 1;
		}

		previous = x;
	}

	count += current_length / K;

	cout << count;
}