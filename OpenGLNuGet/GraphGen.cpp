#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "DataType.h"

class origin {
	node *thisNode = new node;
	
	public: origin() {
		node *childs = new node[];

		thisNode->parent = NULL;
		thisNode->left = NULL;
		thisNode->right = NULL;
		thisNode->position[0] = 0;
		thisNode->position[1] = 0;
		thisNode->position[2] = 0;

		srand(time(NULL));
		int rnd = rand() % rand() + 3;
	
		for (int i = 0; i < rnd; i++)
		{
			childs[i].parent = thisNode;
		}
	}
};