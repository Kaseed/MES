#pragma once

#include "Element4_2D.h"
#include "Grid.h"
#include "Element.h"

void testElement4_2D(Element4_2D element);

void test_grid_nodes(Grid grid);

void test_grid_element(Grid grid);

void test_grid_H_matrix(Grid grid);

void test_grid_P_matrix(Grid grid, double* P_matrix);

void test_grid_C_matrix(Grid grid);