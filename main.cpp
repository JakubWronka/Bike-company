#include <stdio.h>
#include "Queue.h"
#define INF 999999


bool BFS(Queue** tab, int people, int bikes, int* pair_U, int* pair_V, int* dist)
{
	Queue queue(people * 2);
	for (int i = 1; i <= people; i++)
	{
		if (pair_U[i] == 0)
		{
			dist[i] = 0;
			queue.push(i);
		}
		else dist[i] = INF;
	}
	dist[0] = INF;

	int u;

	while (!queue.isEmpty())
	{
		u = queue.pop();
		if (dist[u] < dist[0])
		{
			Queue* temp = tab[u];
			int* sasiedzi = temp->sasiad();
			for (int i = 0; i<temp->getSize(); i++)
			{
				if (dist[pair_V[sasiedzi[i]]] == INF)
				{
					dist[pair_V[sasiedzi[i]]] = dist[u] + 1;
					queue.push(pair_V[sasiedzi[i]]);
				}

			}
		}
	}

	
	return dist[0] != INF;

}

bool DFS(Queue** tab, int u, int* pair_U, int* pair_V, int* dist, int bikes)
{
	if (u != 0)
	{
		Queue* temp = tab[u];
		int* sasiedzi = temp->sasiad();
		for (int i = 0; i<temp->getSize(); i++)
		{
			if (dist[pair_V[sasiedzi[i]]] == dist[u] + 1)
			{
				if (DFS(tab, pair_V[sasiedzi[i]], pair_U, pair_V, dist, bikes))
				{
					pair_V[sasiedzi[i]] = u;
					pair_U[u] = sasiedzi[i];
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}

int Hopcroft_Karp(Queue** tab, int* pair_U, int* pair_V, int* dist, int people, int bikes)
{
	int matching = 0;
	while (BFS(tab, people, bikes, pair_U, pair_V, dist))
	{
		for (int i = 1; i <= people; i++)
		{
			if (pair_U[i] == 0)
			{
				if (DFS(tab, i, pair_U, pair_V, dist, bikes))
					matching++;
			}
		}

	}

	return matching;
}



int main()
{
	//printf("%d", sizeof(Element));
	int people = 0;
	int bikes = 0;

	scanf("%d %d", &people, &bikes);

	int size = people + bikes + 1;

	Queue **tab = new Queue*[people + 1];
	for (int i = 0; i <people + 1; i++)
	{
		tab[i] = NULL;
	}

	//1-bikes - rowery w tablicy, bikes+1 - size - ludzie
	for (int i = 1; i <= people; i++)
	{
		int connection_number = 0;
		scanf("%d", &connection_number);
		tab[i] = new Queue(connection_number);
		for (int j = 1; j <= connection_number; j++)
		{
			int bike_index = 0;
			scanf("%d", &bike_index);
			tab[i]->push(bike_index);
		}
	}

	int* pair_V = new int[bikes + 1];
	int* pair_U = new int[people + 1];
	int *dist = new int[people + 1];

	for (int i = 0; i <= people; i++)
	{
		pair_U[i] = 0;
		dist[i] = 0;
	}

	for (int i = 0; i <= bikes; i++)
	{
		pair_V[i] = 0;

	}


	printf("%d", Hopcroft_Karp(tab, pair_U, pair_V, dist, people, bikes));


	//deleteTab(tab, size);

	for (int i = 1; i <= people; i++)
	{
		delete tab[i];
	}
	delete[]tab;

	delete[]pair_U;
	delete[]pair_V;
	delete[]dist;


	return 0;
}