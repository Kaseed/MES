#include <iostream>
#include "grid.h"


Grid::Grid(float h, float w, int nH, int nW)
	:height(h), width(w), nHeight(nH), nWidth(nW)
{
	nNodes = nHeight * nWidth;
	nElements = (nHeight - 1) * (nWidth - 1);

	nodes = new Node[nNodes];
	elements = new Element[nElements];

	for (int i = 0; i < nNodes; i++)
	{
		float x = (i / nHeight) * ((float)width / (float)(nWidth - 1));
		float y = (i % nHeight) * ((float)height / (float)(nHeight - 1));
		/*Pierwszy cz³on s³u¿y do obliczania poziomu wysokoœci na której znajduje siê
		dany punkt na siatce tak aby po powrocie na dó³ siatki uzyskaæ wartoœæ zerow¹ (i%nHeight)
		Drugi cz³on wyliczenie przyrostu pojedyñczego mno¿enia
		Pomno¿enie poziomu razy przyrost daje dok³adnie wspó³rz¹dn¹ y
		*/
		nodes[i] = { x, y };
	}

	/*for (int i = 0; i < nElements; i++)
	{
		int id1 = (i / nHeight) + i;
		int id2 = id1 + nHeight;
		int id3 = id2 + 1;
		int id4 = id1 + 1;

		elements[i] = { id1, id2, id3, id4 };
	}*/

	elements[0] = {1, nHeight + 1, nHeight + 2 ,2};

	for (int i = 1; i < nElements; i++)
	{
		int id1 = elements[i - 1].ID[0] + 1;
		if (id1 % nHeight == 0)
			id1++;
		int id2 = id1 + nHeight;
		int id3 = id2 + 1;
		int id4 = id1 + 1;

		elements[i] = { id1, id2, id3, id4 };
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
		std::cout << nodes[i].x << ", " << nodes[i].y << std::endl;
	}
}

void Grid::show_elements()
{
	for (int i = 0; i < nElements; i++)
	{
		std::cout << elements[i].ID[0] << " - ";
		std::cout << elements[i].ID[1] << " - ";
		std::cout << elements[i].ID[2] << " - ";
		std::cout << elements[i].ID[3] << std::endl;
	}
}


