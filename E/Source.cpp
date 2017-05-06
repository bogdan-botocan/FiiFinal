#include <iostream>

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

#define POPULATION_SIZE 100

int population[POPULATION_SIZE][3];

int solve(
	int generations_count,
	int generation_size,
	double xover_prob,
	double mutat_prob
)
{
	for (int genId = 0; genId < generations_count; genId++)
	{

	}
}

int main()
{
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			population[i][j] = 
		}
	}

	
}