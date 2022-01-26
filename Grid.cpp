#include "Grid.h"

#include <iostream>

Grid::Grid(float h, float w, int nH, int nW)
	:height(h), width(w), nHeight(nH), nWidth(nW)
{
	nNodes = nHeight * nWidth;
	nElements = (nHeight - 1) * (nWidth - 1);

	nodes = new Node[nNodes];
	elements = new Element[nElements];

	for (int i = 0; i < nNodes; i++)
	{
		short bc = 0;
		float x = (i / nHeight) * ((float)width / (float)(nWidth - 1));
		float y = (i % nHeight) * ((float)height / (float)(nHeight - 1));
		/*Pierwszy cz³on s³u¿y do obliczania poziomu wysokoœci na której znajduje siê
	dany punkt na siatce tak aby po powrocie na dó³ siatki uzyskaæ wartoœæ zerow¹ (i%nHeight)
	Drugi cz³on wyliczenie przyrostu pojedyñczego mno¿enia
	Pomno¿enie poziomu razy przyrost daje dok³adnie wspó³rz¹dn¹ y
	*/
		if (x == 0.0 || y == 0.0 || fabs(x- width) < 0.00001 || fabs(y - height) < 0.00001)
		{
			bc = 1;
		}

		nodes[i].set_x(x); //= { x, y, bc };
		nodes[i].set_y(y); //= { x, y, bc };
		nodes[i].set_bc(bc); //= { x, y, bc };

		elements[0].set_id(1, nHeight + 1, nHeight + 2 ,2);

		for (int i = 1; i < nElements; i++)
		{
			int id1 = elements[i - 1].get_id1() + 1;
			if (id1 % nHeight == 0)
				id1++;
			int id2 = id1 + nHeight;
			int id3 = id2 + 1;
			int id4 = id1 + 1;

			elements[i].set_id(id1, id2, id3, id4);
		}
	}
}

Grid::Grid(Grid& grid)
	:height(grid.height), width(grid.width), nHeight(grid.nHeight), nWidth(grid.nWidth), nNodes(grid.nNodes), nElements(grid.nElements)
{
	nodes = new Node[nNodes];
	elements = new Element[nElements];

	for (int i = 0; i < nNodes; i++)
	{
		nodes[i] = grid.nodes[i];
	}

	for (int i = 0; i < nElements; i++)
	{
		elements[i].copy_element(grid.elements[i]);
	}
}

Grid::~Grid()
{
		delete[] nodes;
		delete[] elements;
}

void Grid::show_nodes()
{
	for (int i = 0; i < nNodes; i++)
	{
		std::cout << this->nodes[i].get_x() << ", " << this->nodes[i].get_y() << " - " << this->nodes[i].get_bc() << std::endl;
	}
}

void Grid::show_elements()
{
	for (int i = 0; i < nElements; i++)
	{
		std::cout << this->elements[i].get_id1() << " - ";
		std::cout << this->elements[i].get_id2() << " - ";
		std::cout << this->elements[i].get_id3() << " - ";
		std::cout << this->elements[i].get_id4() << std::endl;
	}
}

int Grid::get_amount_nodes()
{
	return nNodes;
}

int Grid::get_amount_elements()
{
	return nElements;
}

float Grid::get_width()
{
	return width;
}

float Grid::get_height()
{
	return height;
}

int Grid::get_n_height()
{
	return nHeight;
}

int Grid::get_n_width()
{
	return nWidth;
}

double** Grid::get_H_matrix()
{
	return nullptr;
}

void Grid::get_H_matrix(int number)
{
	//return elements[number].get_H_matrix();
	elements[number].show_H_matrix();
}

void Grid::get_C_matrix(int number)
{
	elements[number].show_C_matrix();
}

double Grid::get_H_matrix_at(int element, int row, int column)
{
	return elements[element].H[row][column];
}

double Grid::get_P_matrix_at(int element, int row)
{
	return elements[element].P[row];
}

double Grid::get_C_matrix_at(int element, int row, int column)
{
	return elements[element].C[row][column];
}

Node Grid::get_node(int number)
{
	return nodes[number];
}

Element Grid::get_element(int number)
{
	return elements[number];
}

void Grid::save_H_Matrix(double H[4][4], int element)
{
	this->elements[element].set_H_matrix(H);
	//for(int i = 0; i < 4; i++)
	//	for(int j = 0; j < 4; j++)
	//		elements[element].H[i][j] = H[i][j];
}

void Grid::add_boundary_Condition(int element, double Hbc[4][4], double P[4])
{
	for (int k = 0; k < 4; k++)
	{
		this->elements[element].P[k] += P[k];
		for (int l = 0; l < 4; l++)
		{
			this->elements[element].Hbc[k][l] += Hbc[k][l];
		}
	}
}

void Grid::sum_boundary_Condition()
{
	for (int i = 0; i < nElements; i++)
	{
		this->elements[i].add_boundary_condition();
	}
}

void Grid::save_C_matrix(double H[4][4], int element)
{
	this->elements[element].set_C_matrix(H);
}
