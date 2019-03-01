#include "Queue.h"
Queue::Queue(int size)
{
	this->size = size;
	tab = new int[size];
	first = 0;
	last = 0;
	for (int i = 0; i < size; i++)
	{
		tab[i] = NULL;
	}
}

void Queue::push(int vertex)
{
	if (last == 0)
	{
		tab[first] = vertex;
		last++;
	}
	else if (last == size)
	{
		printf("%s\n", "Kolejka pelna");
	}
	else
	{
		tab[last] = vertex;
		last++;
	}
}

int Queue::pop()
{
	if (last == 0)
	{
		printf("%s\n", "Kojejka pusta");
		return -1;
	}
	else
	{
		last--;
		return tab[last];
		
	}
}

bool Queue::isEmpty()
{
	if (last == 0)
		return true;
	else return false;
}

int* Queue::sasiad()
{
	return tab;
}

int Queue::getSize()
{
	return size;
}


Queue::~Queue()
{
	delete[]tab;
}