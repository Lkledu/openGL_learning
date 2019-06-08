#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifndef DATE_H
#define DATE_H

class node {
	public:
		float position[3];
		node* left ;
		node* right;
		node* parent;
};
#endif