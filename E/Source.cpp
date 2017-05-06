#include <iostream>
#include <ctime>
#include <algorithm>
#include <climits>

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

#define BOMB_THE_PLANE 0x3f3f3f3f
int fitness(int solution[], int N)
{
	int value = 0;
	for (int i = 0; i < N; i++)
	{
		if (solution[i] < LT[i][0])
		{
			return BOMB_THE_PLANE;
		}
		else if (solution[i] > LT[i][2])
		{
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

		if (i > 0)
		{
			int x = i - 1;
			int y = i;
			
			if (abs(solution[y] - solution[x]) < ST[x][y])
			{
				return BOMB_THE_PLANE;
			}
		}
	}

	return value;
}

#define POPULATION_SIZE 100

int population[POPULATION_SIZE][3];

int solve(
	int generations_count,
	int generation_size,
	double xover_prob,
	double mutat_prob
)
{
	int best_fitness = INT_MAX;

	for (int genId = 0; genId < generations_count; genId++)
	{
		int fit = fitness(population[genId], N);

		if (fit < best_fitness)
		{
			best_fitness = fit;
		}
	}

	return best_fitness;
}

#define INITIAL_POPULATION_SOLUTION_RANGE 10

int main()
{
	srand(time(NULL));

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			population[i][j] = LT[j][1] + (
				(rand() % (2 * INITIAL_POPULATION_SOLUTION_RANGE)) -
				INITIAL_POPULATION_SOLUTION_RANGE);
		}
	}

	cout << solve(100, POPULATION_SIZE, 0.2, 0.4);
}