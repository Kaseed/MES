#include <iostream>

#include "grid.h"
#include "Element4_2D.h"
#include "Tests.h"
#include "matrixFEM.h"
#include "Data.h"

using namespace std;

int main() {

	Element4_2D element(2);

	Element4_2D element3ptk(3);

	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << element.sideEast[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << endl;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << element.sideWest[i][j] << " ";
		}
		cout << endl;
	}*/

	//testElement4_2D(element);

	//Grid grid(0.5, 0.1, 5, 4);

	//test_grid_element(grid);

	//test_grid_nodes(grid);

	//solve_H_matrix(grid, element);

	//test_grid_H_matrix(grid);

	//add_boundary_condition(grid, element);

	//test_grid_H_matrix(grid);

	//aggregation(grid);
	Data data;

	data.SimulationTime = 500;
	data.SimulationStepTime = 50;
	data.Conductivity = 25;
	data.Alfa = 300;
	data.Tot = 1200;
	data.InitialTemp = 100;
	data.Density = 7800;
	data.SpecificHeat = 700;
	

	Grid grid1(0.1, 0.1, 4, 4);

	solve_H_matrix(grid1, element, data);

	add_boundary_condition(grid1, element, data);

	test_grid_H_matrix(grid1);

	aggregation_H(grid1);

	double* P = aggregation_P(grid1);

	//test_grid_P_matrix(grid1, P);

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

	solve_C_matrix(grid1, element, data);


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


	return 0;
}