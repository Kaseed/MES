#include <iostream>

#include "grid.h"
#include "gaussIntegral.h"
#include "Element4_2D.h"

using namespace std;

void jakobian(int i, int j, double I[2][2], double Iinv[2][2], Element4_2D element, Grid grid)
{
	//TEST dla stalej tablicy
	/*double points[4][2] = { {0,0}, {0.025,0}, {0.025, 0.025}, {0,0.025} };

	for (int k = 0; k < 4; k++)
	{
		I[1][1] += element.eta[j][k] * points[k][1];
		I[0][0] += element.ksi[j][k] * points[k][0];
		I[0][1] += element.ksi[j][k] * points[k][1];
		I[1][0] += element.eta[j][k] * points[k][0];
	}*/

	double points[4][2] = { {0,0}, {0,0}, {0, 0}, {0,0} };

	points[0][0] = grid.get_node(grid.get_element(i).ID[0] - 1).x;
	points[0][1] = grid.get_node(grid.get_element(i).ID[0] - 1).y;

	points[1][0] = grid.get_node(grid.get_element(i).ID[1] - 1).x;
	points[1][1] = grid.get_node(grid.get_element(i).ID[1] - 1).y;

	points[2][0] = grid.get_node(grid.get_element(i).ID[2] - 1).x;
	points[2][1] = grid.get_node(grid.get_element(i).ID[2] - 1).y;

	points[3][0] = grid.get_node(grid.get_element(i).ID[3] - 1).x;
	points[3][1] = grid.get_node(grid.get_element(i).ID[3] - 1).y;

	for (int k = 0; k < 4; k++)
	{
		I[0][0] += element.ksi[j][k] * points[k][0];
		I[1][1] += element.eta[j][k] * points[k][1];
		I[0][1] += element.ksi[j][k] * points[k][1];
		I[1][0] += element.eta[j][k] * points[k][0];
	}


	double detI = I[0][0] * I[1][1] - I[1][0] * I[0][1];

	Iinv[1][1] = (1.0 / detI) * I[0][0];
	Iinv[0][0] = (1.0 / detI) * I[1][1];
	Iinv[0][1] = (1.0 / detI) * -I[0][1];
	Iinv[1][0] = (1.0 / detI) * -I[1][0];
}



int main()
{
	Grid grid(0.5, 0.1, 5, 4);

	////Grid grid(1, 1, 7, 4);

	////Grid grid(0.5, 0.5, 3, 6);

	//grid.show_nodes();
	//grid.show_elements();

	//cout << gaussIntegrall1D(2) << endl;

	//cout << gaussIntegrall1D(2, polinomial_fx) << endl;

	//cout << gaussIntegrall1D(3) << endl;

	//cout << gaussIntegrall1D(3, polinomial_fx) << endl;



	//cout << gaussIntegrall2D(2) << endl;

	//cout << gaussIntegrall2D(3) << endl;

	//cout << gaussIntegrall2D(2, polinomial_fxy) << endl;

	//cout << gaussIntegrall2D(3, polinomial_fxy) << endl;

	Element4_2D element(2);

	std::cout << "dKsi" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << element.ksi[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "--------------------" << std::endl;

	std::cout << "dEta" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << element.eta[i][j] << " ";
		}
		std::cout << std::endl;
	}







	double I[2][2] = { {0,0},{0,0} };
	double Iinv[2][2] = { {0,0},{0,0} };
	double points[4][2] = { {0,0}, {0.025,0}, {0.025, 0.025}, {0,0.025} };


	for (int i = 0; i < grid.get_amount_elements(); i++)
	{
		std::cout << "Element " << i + 1 << std::endl;

		for (int j = 0; j < 4; j++)
		{
			std::cout << "Point " << j + 1 << std::endl;

			I[1][1] = 0;
			I[0][0] = 0;
			I[0][1] = 0;
			I[1][0] = 0;

			Iinv[1][1] = 0;
			Iinv[0][0] = 0;
			Iinv[0][1] = 0;
			Iinv[0][1] = 0;

			jakobian(i,j,I,Iinv,element, grid);

			for (int l = 0; l < 2; l++)
			{
				for (int m = 0; m < 2; m++)
				{
					std::cout << I[l][m] << " ";
				}
				std::cout << std::endl;
			}

			for (int l = 0; l < 2; l++)
			{
				for (int m = 0; m < 2; m++)
				{
					std::cout << Iinv[l][m] << " ";
				}
				std::cout << std::endl;
			}

			std::cout << "--------------------" << std::endl;
		}
	}

	return 0;
}
