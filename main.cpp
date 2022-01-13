#include <iostream>

#include "grid.h"
//#include "gaussIntegral.h"
#include "Element4_2D.h"
#include "Tests.h"
#include "matrixFEM.h"

using namespace std;

int main() {

	Element4_2D element(2);

	//testElement4_2D(element);

	//Grid grid(0.5, 0.1, 5, 4);

	//test_grid_element(grid);

	//test_grid_nodes(grid);

	//solve_H_matrix(grid, element);

	//test_grid_H_matrix(grid);

	//add_boundary_condition(grid, element);

	//test_grid_H_matrix(grid);

	//aggregation(grid);

	Grid grid1(0.1, 0.1, 4, 4);

	solve_H_matrix(grid1, element);

	add_boundary_condition(grid1, element);

	//test_grid_H_matrix(grid1);

	aggregation_H(grid1);

	double* P = aggregation_P(grid1);

	test_grid_P_matrix(grid1, P);

	double* t = new double[grid1.get_amount_nodes()];

	for (int i = 0; i < grid1.get_amount_nodes(); i++)
		t[i] = 100.0;

	grid1.sum_boundary_Condition();

	double** H = aggregation_H(grid1);

	for (int i = 0; i < grid1.get_amount_nodes(); i++)
	{
		for (int j = 0; j < grid1.get_amount_nodes(); j++)
		{
			cout << H[i][j] << " ";
		}
		cout << endl;
	}

	solve_C_matrix(grid1, element);

	//test_grid_C_matrix(grid1);

	double** C = aggregation_C(grid1);

	for (int i = 0; i < grid1.get_amount_nodes(); i++)
	{
		for (int j = 0; j < grid1.get_amount_nodes(); j++)
		{
			cout << C[i][j] << " ";
		}
		cout << endl;
	}

	print_temperature(H, C, P, t, 500, 50, grid1.get_amount_nodes());

	//EliminujX(grid1.get_amount_elements(), t, H, P);

	//std::cout << std::endl;

	//for (int i = 0; i < grid1.get_amount_elements(); i++)
	//{
	//	std::cout << t[i];
	//}

	//std::cout << std::endl;

	/*int n = 4;

	double** N = new double* [n];
	for (int i = 0; i < n; i++)
	{
		N[i] = new double[n + 1];
	}
	N[0][0] = 4.;
	N[0][1] = -2.;
	N[0][2] = 4.;
	N[0][3] = -2.;

	N[1][0] = 3.;
	N[1][1] = 1.;
	N[1][2] = 4.;
	N[1][3] = 2.;
	
	N[2][0] = 2.;
	N[2][1] = 4.;
	N[2][2] = 2.;
	N[2][3] = 1.;
	
	N[3][0] = 2.;
	N[3][1] = -2.;
	N[3][2] = 4.;
	N[3][3] = 2.;

	double T[4] = { 8., 7., 10., 2. };

	double* value = nullptr;

	GaussElimination(4, value, N, T);

	for (int i = 0; i < n; i++)
	{
		cout << value << " ";
	}*/

	//double* X = nullptr;

	//cout << GaussElimination(grid1.get_amount_nodes(), X, H, P);

	//delete[] P;



	return 0;
}