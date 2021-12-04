#pragma once

#include <iostream>

#include "Element4_2D.h"
#include "Grid.h"
#include "Element.h"
#include "Node.h"

void jakobian(int i, int j, double I[2][2], double Iinv[2][2], Element4_2D element, Grid& grid);

void solve_H_matrix(Grid& grid, Element4_2D element);

void add_boundary_condition(Grid& grid, Element4_2D uniwersalElement);

double** aggregation_H(Grid& grid);

double* aggregation_P(Grid& grid);
