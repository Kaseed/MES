#include <iostream>

#include "grid.h"
#include "Element4_2D.h"
#include "Tests.h"
#include "matrixFEM.h"
#include "Data.h"

using namespace std;

int main() {

	//Element4_2D element(2);

	Element4_2D element3ptk(3);

	/*Data data;

	data.SimulationTime = 500;
	data.SimulationStepTime = 50;
	data.Conductivity = 25;
	data.Alfa = 300;
	data.Tot = 1200;
	data.InitialTemp = 100;
	data.Density = 7800;
	data.SpecificHeat = 700;

	Grid grid1(0.1, 0.1, 4, 4);*/

	Grid grid1;

	Data data("data/data4.txt", grid1);

	//test_grid_element(grid1);

	solve_H_matrix(grid1, element3ptk, data);

	add_boundary_condition(grid1, element3ptk, data);

	aggregation_H(grid1);

	double* P = aggregation_P(grid1);

	double* t = new double[grid1.get_amount_nodes()];

	for (int i = 0; i < grid1.get_amount_nodes(); i++)
		t[i] = data.InitialTemp;

	grid1.sum_boundary_Condition();

	double** H = aggregation_H(grid1);

	solve_C_matrix(grid1, element3ptk, data);


	double** C = aggregation_C(grid1);

	print_temperature(H, C, P, t, data.SimulationTime, data.SimulationStepTime, grid1.get_amount_nodes());


	return 0;
}