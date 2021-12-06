#pragma once

#ifndef LAB_NO_H
#define LAB_NO_H

#define DEBUG 1

#endif


#include "matrixFEM.h"

void jakobian(int i, int j, double I[2][2], double Iinv[2][2], Element4_2D element, Grid& grid)
{
	double points[4][2] = { {0,0}, {0,0}, {0, 0}, {0,0} };

	points[0][0] = grid.get_node(grid.get_element(i).get_id1() - 1).get_x();
	points[0][1] = grid.get_node(grid.get_element(i).get_id1() - 1).get_y();

	points[1][0] = grid.get_node(grid.get_element(i).get_id2() - 1).get_x();
	points[1][1] = grid.get_node(grid.get_element(i).get_id2() - 1).get_y();

	points[2][0] = grid.get_node(grid.get_element(i).get_id3() - 1).get_x();
	points[2][1] = grid.get_node(grid.get_element(i).get_id3() - 1).get_y();

	points[3][0] = grid.get_node(grid.get_element(i).get_id4() - 1).get_x();
	points[3][1] = grid.get_node(grid.get_element(i).get_id4() - 1).get_y();

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

void solve_H_matrix(Grid& grid, Element4_2D element)
{
	// Wspó³czynnik przewodzenia
	double countivity = 25.0;


	//Przechodzenie po ka¿dym elemencie
	for (int i = 0; i < grid.get_amount_elements(); i++)
	{
		double H[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
#if DEBUG==1
		std::cout << "Element " << i + 1 << std::endl;
#endif

		//Przechodzenie po ka¿dym wierzcho³ku
		for (int j = 0; j < 4; j++)
		{
#if DEBUG==1
			std::cout << "Point " << j + 1 << std::endl;
#endif

			double I[2][2] = { {0,0},{0,0} };
			double Iinv[2][2] = { {0,0},{0,0} };

			jakobian(i, j, I, Iinv, element, grid);

#if DEBUG==1
			for (int l = 0; l < 2; l++)
			{
				for (int m = 0; m < 2; m++)
					std::cout << I[l][m] << " ";
				std::cout << std::endl;
			}
			std::cout << std::endl;
#endif
			double dNdx[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
			double dNdy[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };

			//Liczenie macierzy powierzchni po punktach ca³kowania
			for (int l = 0; l < 4; l++)
				for (int m = 0; m < 4; m++)
				{
					dNdx[l][m] = Iinv[0][0] * element.ksi[l][m] + Iinv[0][1] * element.eta[l][m];
					dNdy[l][m] = Iinv[1][0] * element.ksi[l][m] + Iinv[1][1] * element.eta[l][m];
				}

			double Hx[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
			double Hy[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
			double H1[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };

			for (int k = 0; k < 4; k++)
			{
				for (int m = 0; m < 4; m++)
				{
					Hx[k][m] = dNdx[j][k] * dNdx[j][m];
					Hy[k][m] = dNdy[j][k] * dNdy[j][m];
					double detI = I[0][0] * I[1][1] - I[1][0] * I[0][1];

					H1[k][m] = countivity * (Hx[k][m] + Hy[k][m]) * detI;

					H[k][m] += H1[k][m];
#if DEBUG==1
					std::cout << H1[k][m] << " ";
#endif
				}
#if DEBUG==1
				std::cout << std::endl;
#endif

			}
#if DEBUG==1
			std::cout << std::endl;
#endif


		}

		for (int l = 0; l < 4; l++)
		{
			for (int m = 0; m < 4; m++)
				std::cout << H[l][m] << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;

		grid.save_H_Matrix(H, i);

	}
}

void add_boundary_condition(Grid& grid, Element4_2D uniwersalElement)
{
	//TO DO
	//Zmieniæ detJ z oblicznia z d³ugoœci na obliczanie ze wspó³rzêdnych punktów
	//Zamieniæ 300 na alfa
	//Zamieniæ 1200 na temperature

	for (int i = 0; i < grid.get_amount_elements(); i++)
	{
		std::cout << "Element " << i + 1 << std::endl;
		if (grid.get_node(grid.get_element(i).get_id1() - 1).get_bc() == 1)
		{
			if (grid.get_node(grid.get_element(i).get_id2() - 1).get_bc() == 1)
			{
				double Hbc[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
				double P[4] = { 0,0,0,0 };

				for (int k = 0; k < 4; k++)
				{
					double det = (grid.get_width() / (grid.get_n_width() - 1)) / 2;
					P[k] = 300 * (uniwersalElement.sideSouth[0][k] * 1200 + uniwersalElement.sideSouth[1][k] * 1200) * det;
					for (int l = 0; l < 4; l++)
					{
						//std::cout << "\t----------------" << det;
						Hbc[k][l] =300 * (uniwersalElement.sideSouth[0][k] * uniwersalElement.sideSouth[0][l] + uniwersalElement.sideSouth[1][k] * uniwersalElement.sideSouth[1][l]) * det;
					}
				}
				grid.add_boundary_Condition(i, Hbc, P);
				for (int z = 0; z < 4; z++)
				{
					for (int v = 0; v < 4; v++)
						std::cout << Hbc[z][v] << " ";
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}

			if (grid.get_node(grid.get_element(i).get_id4() - 1).get_bc() == 1)
			{
				double Hbc[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
				double P[4] = { 0,0,0,0 };
				for (int k = 0; k < 4; k++)
				{
					double det = (grid.get_height() / (grid.get_n_height() - 1)) / 2;
					P[k] = 300 * (uniwersalElement.sideWest[0][k] * 1200 + uniwersalElement.sideWest[1][k] * 1200) * det;
					for (int l = 0; l < 4; l++)
					{
						Hbc[k][l] = 300 * (uniwersalElement.sideWest[0][k] * uniwersalElement.sideWest[0][l] + uniwersalElement.sideWest[1][k] * uniwersalElement.sideWest[1][l]) * det;
					}
				}

				grid.add_boundary_Condition(i, Hbc, P);
				for (int z = 0; z < 4; z++)
				{
					for (int v = 0; v < 4; v++)
						std::cout << Hbc[z][v] << " ";
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
		}

		if (grid.get_node(grid.get_element(i).get_id3() - 1).get_bc() == 1)
		{
			if (grid.get_node(grid.get_element(i).get_id2() - 1).get_bc() == 1)
			{
				double Hbc[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
				double P[4] = { 0,0,0,0 };
				for (int k = 0; k < 4; k++)
				{
					double det = (grid.get_height() / (grid.get_n_height() - 1)) / 2;
					P[k] = 300 * (uniwersalElement.sideEast[0][k] * 1200 + uniwersalElement.sideEast[1][k] * 1200) * det;
					for (int l = 0; l < 4; l++)
					{
						Hbc[k][l] = 300 * (uniwersalElement.sideEast[0][k] * uniwersalElement.sideEast[0][l] + uniwersalElement.sideEast[1][k] * uniwersalElement.sideEast[1][l]) * det;
					}
				}
				grid.add_boundary_Condition(i, Hbc, P);
				for (int z = 0; z < 4; z++)
				{
					for (int v = 0; v < 4; v++)
						std::cout << Hbc[z][v] << " ";
					std::cout << std::endl;
				}
				std::cout << std::endl;

			}

			if (grid.get_node(grid.get_element(i).get_id4() - 1).get_bc() == 1)
			{
				double Hbc[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
				double P[4] = { 0,0,0,0 };
				for (int k = 0; k < 4; k++)
				{
					double det = (grid.get_width() / (grid.get_n_width() - 1)) / 2;
					P[k] = 300 * (uniwersalElement.sideNorth[0][k] * 1200 + uniwersalElement.sideNorth[1][k] * 1200) * det;
					for (int l = 0; l < 4; l++)
					{
						Hbc[k][l] = 300 * (uniwersalElement.sideNorth[0][k] * uniwersalElement.sideNorth[0][l] + uniwersalElement.sideNorth[1][k] * uniwersalElement.sideNorth[1][l]) * det;
					}
				}

				grid.add_boundary_Condition(i, Hbc, P);
				for (int z = 0; z < 4; z++)
				{
					for (int v = 0; v < 4; v++)
						std::cout << Hbc[z][v] << " ";
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
		}
	}
}

double** aggregation_H(Grid& grid)
{
	//return nullptr;
	double** aggregation_matrix = new double* [grid.get_amount_nodes()];
	for (int i = 0; i < grid.get_amount_nodes(); i++)
	{
		aggregation_matrix[i] = new double[grid.get_amount_nodes()];
		for (int j = 0; j < grid.get_amount_nodes(); j++)
		{
			aggregation_matrix[i][j] = 0.0;
		}
	}

	//Przejscie po ka¿dym elemencie
	for (int i = 0; i < grid.get_amount_elements(); i++)
	{
		for(int l = 0 ; l < 4; l++)
			for (int k = 0; k < 4; k++)
			{
				aggregation_matrix[grid.get_element(i).get_id_parameter(l) - 1][grid.get_element(i).get_id_parameter(k) - 1] +=  grid.get_H_matrix_at(i, l, k);
			}
	}

	for (int i = 0; i < grid.get_amount_nodes(); i++)
	{
		for (int j = 0; j < grid.get_amount_nodes(); j++)
		{
			std::cout << aggregation_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	return aggregation_matrix;

}

double* aggregation_P(Grid& grid)
{
	double* aggregation_matrix = new double [grid.get_amount_nodes()];
	for (int j = 0; j < grid.get_amount_nodes(); j++)
	{
		aggregation_matrix[j] = 0.0;
	}

	//Przejscie po ka¿dym elemencie
	for (int i = 0; i < grid.get_amount_elements(); i++)
	{
		for (int l = 0; l < 4; l++)
		{
			aggregation_matrix[grid.get_element(i).get_id_parameter(l) - 1] += grid.get_P_matrix_at(i, l);
		}
	}

	//std::cout << "\n\n\n";

	//for (int i = 0; i < grid.get_amount_nodes(); i++)
	//{
	//	std::cout << aggregation_matrix[i] << " ";
	//}
	//std::cout << "\n";

	return aggregation_matrix;

}
