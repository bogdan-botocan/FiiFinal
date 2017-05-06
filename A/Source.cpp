#include <iostream>
#include <vector>

#define MAX 100
using namespace std;

int studs[MAX];
bool selected[MAX];

int main()
{
	int N; cin >> N;

	for (int i = 0; i < N; i++)
	{
		int x; cin >> x;
		studs[i] = x;

		int best = -1;
		int index = -1;
		for (int j = 0; j < i; j++)
		{
			if(studs[j] >= x || selected[j])
			{
				continue;
			}

			if (studs[j] > best)
			{
				best = studs[j];
				index = j;
			}
		}

		if (best == -1)
		{
			continue;
		}

		selected[index] = true;
		selected[i] = true;
		cout << best << " " << x << '\n';
	}

	return 0;
}