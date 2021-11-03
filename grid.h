#pragma once
#include "structures.h"

class Grid
{
	double height;
	double width;

	int nHeight;
	int nWidth;

	int nNodes;
	int nElements;

	Node* nodes;// [nNodes] ;
	Element* elements;//[nElements];

public:

	Grid(double height, double width, int nH, int nW);

	Grid(Grid & grid);

	~Grid();

	void show_nodes();

	void show_elements();

	int get_amount_nodes();

	int get_amount_elements();

	Node get_node(int number);

	Element get_element(int number);
};
