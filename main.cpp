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

	test_grid_H_matrix(grid1);

	aggregation_H(grid1);

	aggregation_P(grid1);

	return 0;
}