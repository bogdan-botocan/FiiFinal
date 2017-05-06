#include <iostream>
#include <ctime>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// number of planes
int N = 3;
// Times per plane:
// {earliest landing time, target landing time, latest landing time}
int LT[3][3] = {
	{129, 155, 559},
	{195, 258, 744},
	{89, 98, 510}
};
// penalty cost penalty cost per unit of time per plane:
// {for landing before target, after target}
int PC[3][2] =
{
	{10, 10},
	{10, 10}, 
	{30, 30}
};

// Separation time required after i lands before j can land
int ST[3][3] =
{
	{99999, 80, 15},
	{3, 99999, 15},
	{100, 15, 99999}
}; 

#define HIJACK_THE_PLANE 0x3f
#define BOMB_THE_PLANE 0x3f3f3f3f
#define MAX_N 10

pair<int, int> temp[MAX_N];
int fitness(int solution[], int N, bool* valid)
{
	*valid = true;

	int value = 0;
	for (int i = 0; i < N; i++)
	{
		if (solution[i] < LT[i][0])
		{
			*valid = false;
			return BOMB_THE_PLANE;
		}
		else if (solution[i] > LT[i][2])
		{
			*valid = false;
			return BOMB_THE_PLANE;
		}

		if (solution[i] < LT[i][1])
		{
			value += (LT[i][1] - solution[i]) * PC[i][0];
		}
		else if (solution[i] > LT[i][1])
		{
			value += (solution[i] - LT[i][1]) * PC[i][1];
		}
	}

	for (int i = 0; i < N; i++)
	{
		temp[i] = make_pair(solution[i], i);
	}

	sort(temp, temp + N);

	for (int i = 1; i < N; i++)
	{
		if (abs(temp[i].first - temp[i - 1].first) <
			ST[temp[i - 1].second][temp[i].second])
		{
			int diff = ST[temp[i - 1].first][temp[i].second] -
				abs(temp[i].first - temp[i - 1].first);
			*valid = false;
			value += diff * HIJACK_THE_PLANE;
		}
	}

	return value;
}

#define GENERATION_SIZE 1000

vector<pair<int, int*>> population;
vector<pair<int, int*>> new_population;

#define INITIAL_POPULATION_SOLUTION_RANGE 100
#define POPULATION_SOLUTION_RANGE 10

int solve(
	int generations_count,
	int generation_size,
	int xover_prob,
	int mutat_prob
)
{
	int best_fitness = INT_MAX;

	for (int genId = 0; genId < generations_count; genId++)
	{
		sort(population.begin(), population.end());

		for (int id = 0; id < generation_size / 4; id++)
		{
			new_population.push_back(population[id]);
		}

		population = new_population;

		for (int id = 0; id < generation_size - generation_size / 4; id++)
		{
			int x = rand() % generation_size / 4;
			int y = rand() % generation_size / 4;

			if (rand() % 100 < xover_prob)
			{
				int point = rand() % N;

				for (int i = 0; i < point; i++)
				{
					int t = population[x].second[i];
					population[x].second[i] = population[x].second[i + 1];
					population[x].second[i + 1] = t;
				}
			}

			if (rand() % 100 < mutat_prob)
			{
				int point = rand() % N;
				
				population[x].second[point] +=
					(rand() % (2 * POPULATION_SOLUTION_RANGE) -
						POPULATION_SOLUTION_RANGE);
			}
		}

		std::cout << "Genid: " << genId << ": " << best_fitness << '\n';
	}

	return best_fitness;
}

bool dummy = false;
int main()
{
	srand(time(NULL));

	for (int i = 0; i < GENERATION_SIZE; i++)
	{
		int *x = new int[N];
		for (int j = 0; j < 3; j++)
		{
			x[j] = LT[j][1] + (
				(rand() % (2 * INITIAL_POPULATION_SOLUTION_RANGE)) -
				INITIAL_POPULATION_SOLUTION_RANGE);
			population.push_back(make_pair(fitness(x, N, &dummy), x));
		}
	}

	std::cout << solve(1000, GENERATION_SIZE, 100, 100) << '\n';
}