#pragma once
#include <stdio.h>
class Queue
{
private:
	int size;
	int first, last;
	int* tab;

public:
	Queue(int size);

	void push(int vertex);
	int pop();


	int* sasiad();
	int getSize();

	bool isEmpty();


	~Queue();
};
