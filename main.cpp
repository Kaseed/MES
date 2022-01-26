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



	//data.SimulationTime = 500;
	//data.SimulationStepTime = 50;
	//data.Conductivity = 25;
	//data.Alfa = 300;
	//data.Tot = 1200;
	//data.InitialTemp = 100;
	//data.Density = 7800;
	//data.SpecificHeat = 700;

	Grid grid1(0.1, 0.1, 4, 4);

	Grid gridtemp;

	Data data("data/data4.txt", gridtemp);

	solve_H_matrix(gridtemp, element, data);

	add_boundary_condition(gridtemp, element, data);

	aggregation_H(gridtemp);

	double* P = aggregation_P(gridtemp);

	double* t = new double[gridtemp.get_amount_nodes()];

	for (int i = 0; i < gridtemp.get_amount_nodes(); i++)
		t[i] = data.InitialTemp;

	gridtemp.sum_boundary_Condition();

	double** H = aggregation_H(gridtemp);

	solve_C_matrix(gridtemp, element, data);


	double** C = aggregation_C(gridtemp);

	print_temperature(H, C, P, t, data.SimulationTime, data.SimulationStepTime, gridtemp.get_amount_nodes());


	return 0;
}