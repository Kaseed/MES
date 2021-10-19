#pragma once
#include "structures.h"

class Grid
{
	float height;
	float width;

	int nHeight;
	int nWidth;

	int nNodes;
	int nElements;

	Node* nodes;// [nNodes] ;
	Element* elements;//[nElements];

public:
	Grid(float height, float width, int nH, int nW);

	~Grid();

	void show_nodes();

	void show_elements();
};

