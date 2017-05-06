#include <iostream>

using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;

	int last_safe_place = 0;
	int previous_place = 0;
	int count = 0;
	int diff = 0;
	int x;
	for (int i = 0; i < N; i++)
	{
		cin >> x;

		if (x - 1 == previous_place && last_safe_place != previous_place)
		{
			previous_place = x;
			continue;
		}

		last_safe_place = x - 1;
		diff = x - last_safe_place;
		
		if (diff > K)
		{
			count += (diff / K);
			diff = 0;
		}

		previous_place = x;
		last_safe_place = previous_place - 1;
	}

	diff = x - last_safe_place;
	if (diff > K)
	{
		count += (diff / K);
		diff = 0;
	}

	cout << count;
}