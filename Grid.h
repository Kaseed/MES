#pragma once
//#include "structures.h"
#include "Element4_2D.h"
#include "Node.h"
#include "Element.h"

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

	Grid(float h, float w, int nH, int nW);

	Grid(Grid& grid);

	//~Grid();

	void show_nodes();

	void show_elements();

	int get_amount_nodes();

	int get_amount_elements();

	float get_width();

	float get_height();

	int get_n_height();

	int get_n_width();

	void get_H_matrix(int number);

	double get_H_matrix_at(int element, int row, int column);

	double get_P_matrix_at(int element, int row);

	Node get_node(int number);

	Element get_element(int number);

	void save_H_Matrix(double H[4][4], int element);

	void add_boundary_Condition(int element, double Hbc[4][4], double P[4]);

};


