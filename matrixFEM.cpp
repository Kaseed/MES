#pragma once

#ifndef LAB_NO_H
#define LAB_NO_H

#define DEBUG 0

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
	// Współczynnik przewodzenia
	double countivity = 25.0;


	//Przechodzenie po każdym elemencie
	for (int i = 0; i < grid.get_amount_elements(); i++)
	{
		double H[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
#if DEBUG==1
		std::cout << "Element " << i + 1 << std::endl;
#endif

		//Przechodzenie po każdym wierzchołku
		for (int j = 0; j < element.schemat * element.schemat; j++) //Dodac więcej punktów
		{
#if DEBUG==1
			std::cout << "Point " << j + 1 << std::endl;
#endif

			double I[2][2] = { {0,0},{0,0} };
			double Iinv[2][2] = { {0,0},{0,0} };

			jakobian(i, j, I, Iinv, element, grid);

#if DEBUG==1
			/*for (int l = 0; l < 2; l++)
			{
				for (int m = 0; m < 2; m++)
					std::cout << I[l][m] << " ";
				std::cout << std::endl;
			}
			std::cout << std::endl;*/
#endif
			if(element.schemat == 2)
			{
				double dNdx[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
				double dNdy[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };

				//Liczenie macierzy powierzchni po punktach całkowania
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
			else if (element.schemat == 3)
			{
				double dNdx[9][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
				double dNdy[9][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
			
				for (int l = 0; l < 9; l++)
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

						H1[k][m] = countivity * (Hx[k][m] + Hy[k][m]) * detI * element.weight[j/3] * element.weight[j%3];

						H[k][m] += H1[k][m];

						//std::cout << H1[k][m] << " ";

					}

					//std::cout << std::endl;


				}
				//std::cout << std::endl;
			
			}


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
	//Zmienić detJ z oblicznia z długości na obliczanie ze współrzędnych punktów
	//Zamienić 300 na alfa
	//Zamienić 1200 na temperature

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
					//std::cout << "det\n" << det;
					if(uniwersalElement.schemat == 2)
					{ 
						
						for (int l = 0; l < 4; l++)
						{
							P[k] += 300 * (uniwersalElement.sideSouth[0][k] * 1200 + uniwersalElement.sideSouth[1][k] * 1200) * det;
							Hbc[k][l] =300 * (uniwersalElement.sideSouth[0][k] * uniwersalElement.sideSouth[0][l] + uniwersalElement.sideSouth[1][k] * uniwersalElement.sideSouth[1][l]) * det;
						}
					}
					else if (uniwersalElement.schemat == 3) 
					{
						P[k] += 300 * (uniwersalElement.weight[0] * uniwersalElement.sideSouth[0][k] * 1200 + uniwersalElement.weight[1] * uniwersalElement.sideSouth[1][k] * 1200 + uniwersalElement.weight[2] * uniwersalElement.sideSouth[2][k] * 1200) * det;
						
						for (int l = 0; l < 4; l++)
						{
							Hbc[k][l] = 300 * (uniwersalElement.sideSouth[0][k] * uniwersalElement.sideSouth[0][l] * uniwersalElement.weight[0] + uniwersalElement.sideSouth[1][k] * uniwersalElement.sideSouth[1][l] * uniwersalElement.weight[1] + uniwersalElement.sideSouth[2][k] * uniwersalElement.sideSouth[2][l] * uniwersalElement.weight[2]) * det;
						}
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
					
					if (uniwersalElement.schemat == 2)
					{
						P[k] += 300 * (uniwersalElement.sideWest[0][k] * 1200 + uniwersalElement.sideWest[1][k] * 1200) * det;
						for (int l = 0; l < 4; l++)
						{
							Hbc[k][l] = 300 * (uniwersalElement.sideWest[0][k] * uniwersalElement.sideWest[0][l] + uniwersalElement.sideWest[1][k] * uniwersalElement.sideWest[1][l]) * det;
						}
					}
					else if (uniwersalElement.schemat == 3)
					{
						P[k] += 300 * (uniwersalElement.weight[0] * uniwersalElement.sideWest[0][k] * 1200 + uniwersalElement.weight[1] * uniwersalElement.sideWest[1][k] * 1200 + uniwersalElement.weight[2] * uniwersalElement.sideWest[2][k] * 1200) * det;
						for (int l = 0; l < 4; l++)
						{
							Hbc[k][l] = 300 * (uniwersalElement.sideWest[0][k] * uniwersalElement.sideWest[0][l] * uniwersalElement.weight[0] + uniwersalElement.sideWest[1][k] * uniwersalElement.sideWest[1][l] * uniwersalElement.weight[1] + uniwersalElement.sideWest[2][k] * uniwersalElement.sideWest[2][l] * uniwersalElement.weight[2]) * det;
						}
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
					if (uniwersalElement.schemat == 2)
					{
						P[k] += 300 * (uniwersalElement.sideEast[0][k] * 1200 + uniwersalElement.sideEast[1][k] * 1200) * det;
						for (int l = 0; l < 4; l++)
						{
							Hbc[k][l] = 300 * (uniwersalElement.sideEast[0][k] * uniwersalElement.sideEast[0][l] + uniwersalElement.sideEast[1][k] * uniwersalElement.sideEast[1][l]) * det;
						}
					} 
					else if (uniwersalElement.schemat == 3)
					{
						P[k] += 300 * (uniwersalElement.weight[0] * uniwersalElement.sideEast[0][k] * 1200 + uniwersalElement.weight[1] * uniwersalElement.sideEast[1][k] * 1200 + uniwersalElement.weight[2] * uniwersalElement.sideEast[2][k] * 1200) * det;
						for (int l = 0; l < 4; l++)
						{
							Hbc[k][l] = 300 * (uniwersalElement.sideEast[0][k] * uniwersalElement.sideEast[0][l] * uniwersalElement.weight[0] + uniwersalElement.sideEast[1][k] * uniwersalElement.sideEast[1][l] * uniwersalElement.weight[1] + uniwersalElement.sideEast[2][k] * uniwersalElement.sideEast[2][l] * uniwersalElement.weight[2]) * det;
						}
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
					
					if (uniwersalElement.schemat == 2)
					{
						P[k] += 300 * (uniwersalElement.sideNorth[0][k] * 1200 + uniwersalElement.sideNorth[1][k] * 1200) * det;
						for (int l = 0; l < 4; l++)
						{
							Hbc[k][l] = 300 * (uniwersalElement.sideNorth[0][k] * uniwersalElement.sideNorth[0][l] + uniwersalElement.sideNorth[1][k] * uniwersalElement.sideNorth[1][l]) * det;
						}
					}
					else if (uniwersalElement.schemat == 3)
					{
						P[k] += 300 * (uniwersalElement.weight[0] * uniwersalElement.sideNorth[0][k] * 1200 + uniwersalElement.weight[1] * uniwersalElement.sideNorth[1][k] * 1200 + uniwersalElement.weight[2] * uniwersalElement.sideNorth[2][k] * 1200) * det;
						for (int l = 0; l < 4; l++)
						{
							Hbc[k][l] = 300 * (uniwersalElement.sideNorth[0][k] * uniwersalElement.sideNorth[0][l] * uniwersalElement.weight[0] + uniwersalElement.sideNorth[1][k] * uniwersalElement.sideNorth[1][l] * uniwersalElement.weight[1] + uniwersalElement.sideNorth[2][k] * uniwersalElement.sideNorth[2][l] * uniwersalElement.weight[2]) * det;
						}
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

void solve_C_matrix(Grid& grid, Element4_2D element)
{
	double c = 700.0, ro = 7800.0;
	for (int i = 0; i < grid.get_amount_elements(); i++)
	{
		double C[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
		for (int j = 0; j < element.schemat * element.schemat; j++) //schemat całkowania
		{
			double I[2][2] = { {0,0},{0,0} };
			double Iinv[2][2] = { {0,0},{0,0} };

			jakobian(i, j, I, Iinv, element, grid);
			double detI = I[0][0] * I[1][1] - I[1][0] * I[0][1];

			for (int k = 0; k < 4; k++)
			{
				for (int m = 0; m < 4; m++)
				{
					double data;
					if (element.schemat == 2)
					{
						data = c * ro * (element.N[j][k] * element.N[j][m]) * detI;
					}
					else if (element.schemat == 3)
					{
						data = c * ro * (element.N[j][k] * element.N[j][m]) * detI * element.weight[j / 3] * element.weight[j % 3];
					}
					C[k][m] += data;
				}
			}

		}
		grid.save_C_matrix(C, i);

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

	//Przejscie po każdym elemencie
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

	//Przejscie po każdym elemencie
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

double** aggregation_C(Grid& grid)
{
	double** aggregation_matrix = new double* [grid.get_amount_nodes()];
	for (int i = 0; i < grid.get_amount_nodes(); i++)
	{
		aggregation_matrix[i] = new double[grid.get_amount_nodes()];
		for (int j = 0; j < grid.get_amount_nodes(); j++)
		{
			aggregation_matrix[i][j] = 0.0;
		}
	}

	for (int i = 0; i < grid.get_amount_elements(); i++)
	{
		for (int l = 0; l < 4; l++)
			for (int k = 0; k < 4; k++)
			{
				aggregation_matrix[grid.get_element(i).get_id_parameter(l) - 1][grid.get_element(i).get_id_parameter(k) - 1] += grid.get_C_matrix_at(i, l, k);
			}
	}

	std::cout << "C matrix\n";

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

bool GaussElimination(int n, double* X, double** H, double* P)
{
	//n - liczba elementów wektora P oraz jednego wymiaru macierzy H
	//X - tablica zawierajaca wynik operacji
	//eps - dokladnosc obliczen

	const double eps = 1e-12;

	//Tworzenie tablicy n x n + 1 na której wykonywane beda operacje
	double** N = new double* [n];
	for (int i = 0; i < n; i++)
	{
		N[i] = new double[n + 1];
		for (int j = 0; j < n; j++)
		{
			N[i][j] = H[i][j];
		}
		N[i][n] = P[i];
	}

	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < n + 1; j++)
	//	{
	//		std::cout << N[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}

	//Wlasciwa eliminacja Gaussa
	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = i; j < n + 1; j++)
	//	{
	//		if (fabs(N[i][i]) < eps)
	//			return false;		//jesli warunek spelniony na przekatnej jest 0 czyli brak rozwiazania
	//		double divisor = -N[j][i] / N[i][i];
	//		for (int k = i + 1; k <= n + 1; k++)
	//		{
	//			N[j][k] += divisor * N[i][k];
	//		}
	//	}
	//}

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (fabs(N[i][i]) < eps) return false;
			double m = -N[j][i] / N[i][i];
			for (int k = i + 1; k <= n; k++)
				N[j][k] += m * N[i][k];
		}
	}

	if (X == nullptr) 
	{
		X = new double[n];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		double s = N[i][n];
		for (int j = n - 1; j >= i + 1; j--)
			s -= N[i][j] * X[j];
		if (fabs(N[i][i]) < eps) return false;
		X[i] = s / N[i][i];
	}
	
	std::cout << "Wynik dzialania" << std::endl;
	for (int i = 0; i < n; i++)
		std::cout << X[i] << std::endl;
	
	return true;

	/*
	for (int i = n - 1; i >= 0; i--)
	{
		double s = N[i][n];
		for (int j = n - 1; j >= i + 1; j--)
		{
			s -= N[i][j] * X[j];
		}
		if (fabs(N[i][i]) < eps) 
			return false;
		X[i] = s / N[i][i];
	}

	for (int i = 0; i < n; i++)
	{
		delete[] N[i];
	}
	delete[] N;
	return true;*/
}

double* Gauss_elimination(double** AB, int N) {
	const double accuracy = 1e-15;
	double* result = new double[N];
	int* vector = new int[N + 1];

	for (int i = 0; i < N + 1; i++)
		vector[i] = i;

	for (int i = 0; i < N - 1; i++) {
		bool hasChanged = false;
		int largest = i;

		for (int j = i + 1; j < N; j++)
			if (fabs(AB[i][vector[largest]]) < fabs(AB[i][vector[j]])) {
				hasChanged = true;
				largest = j;
			}

		if (hasChanged) {
			int pom = vector[i];
			vector[i] = vector[largest];
			vector[largest] = pom;
		}

		for (int j = i + 1; j < N; j++) {
			if (fabs(AB[i][vector[i]]) < accuracy)
				return NULL;

			double divisor = AB[j][vector[i]] / AB[i][vector[i]];

			for (int k = i + 1; k < N + 1; k++)
				AB[j][vector[k]] -= (AB[i][vector[k]] * divisor);
		}
	}

	for (int i = N - 1; i >= 0; i--) {
		if (fabs(AB[i][vector[i]]) < accuracy)
			return NULL;

		for (int j = N - 1; j > i; j--)
			AB[i][N] -= AB[i][vector[j]] * result[vector[j]];

		result[vector[i]] = AB[i][N] / AB[i][vector[i]];
	}

	return result;
}

/**
 * Algorytm eliminacji Gauss'a do rozwi¹zywania uk³adów liniowych.
 *
 * @param A - macierz niewiadomych
 * @param B - wektor rozwi¹zañ
 * @param N - liczba uk³adów równañ
 */
double* Gauss_elimination(double** A, double* B, int n) {
	//double** temp = merge(A, B, N);
	//return Gauss_elimination(temp, N);

	double** temp = new double* [n];
	for (int i = 0; i < n; i++)
	{
		temp[i] = new double[n + 1];
		for (int j = 0; j < n; j++)
		{
			temp[i][j] = A[i][j];
		}
		temp[i][n] = B[i];
	}

	return Gauss_elimination(temp, n);
}

double** sum_matrix(double** matrix1, double** matrix2, int size)
{
	double** temp = new double* [size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = new double[size];
	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			temp[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	return temp;
}

double* multiplication_matrix_by_vector(double** matrix1, double* vector1, int size)
{
	double* temp = new double[size];
	for (int i = 0; i < size; i++)
		temp[i] = 0.0;


	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			temp[i] += matrix1[i][j] * vector1[j];

		}
	return temp;
}

double** devide_matrix_by_number(double** matrix1, double number1, int size)
{
	double** temp = new double* [size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = new double[size];
	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			temp[i][j] = matrix1[i][j] / number1;
		}
	return temp;
}

double* sum_vector(double* vector1, double* vector2, int size)
{
	double* temp = new double[size];

	for (int i = 0; i < size; i++)
		temp[i] = vector1[i] + vector2[i];
	return temp;
}

void print_temperature(double** H, double** C, double* P, double* t_start, int time, int step, int n)
{
	//std::cout << "Step 1\n";
	//for (int i = 0; i < n; i++)
	//	std::cout << t_start[i] << " ";
	//std::cout << std::endl;
	std::cout << "Time[s]\tMinTemp[s]\tMaxTemp[s]\n";
	for (int i = 0; i < time/step; i++)
	{
		double* temperature = calculate_temperature(H, C, P, t_start, step, n);
		delete[] t_start;
		/*std::cout << "Step " << i + 1 << "\n";
		for (int i = 0; i < n; i++)
			std::cout << temperature[i] << " ";*/
		/*std::cout << std::endl;*/
		double min = min_temperature(temperature, n);
		double max = max_temperature(temperature, n);
		std::cout << (time / (time/step)) * (i + 1) << "\t" << min << "\t\t" << max << "\n";
		t_start = temperature;
	}
}

double* calculate_temperature(double** H, double** C, double* P, double* t_start, int step, int n)
{
	double** newC = devide_matrix_by_number(C, step, n);
	double** newMatrixHC = sum_matrix(H, newC, n);
	for (int i = 0; i < n; i++)
		delete[] newC[i];
	delete[] newC;

	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//	{
	//		std::cout << newMatrixHC[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;

	newC = devide_matrix_by_number(C, step, n);
	double* newVector = multiplication_matrix_by_vector(newC, t_start, n);
	for (int i = 0; i < n; i++)
		delete[] newC[i];
	delete[] newC;

	//for (int i = 0; i < n; i++)
	//{
	//	std::cout << P[i] << " ";
	//}
	//std::cout << std::endl;

	double* newVector2 = sum_vector(newVector, P, n);

	//for (int i = 0; i < n; i++)
	//{
	//	std::cout << newVector2[i] << " ";
	//}
	//std::cout << std::endl;

	double* new_temperature = Gauss_elimination(newMatrixHC, newVector2, n);

	for (int i = 0; i < n; i++)
		delete[] newMatrixHC[i];
	delete[] newMatrixHC;

	delete[] newVector;
	delete[] newVector2;

	return new_temperature;
}

double max_temperature(double* temperature, int n)
{
	double max = temperature[0];

	for (int i = 1; i < n; i++)
	{
		if (max < temperature[i])
		{
			max = temperature[i];
		}
	}

	return max;
}

double min_temperature(double* temperature, int n)
{
	double min = temperature[0];

	for (int i = 1; i < n; i++)
	{
		if (min > temperature[i])
		{
			min = temperature[i];
		}
	}

	return min;
}
