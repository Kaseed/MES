#pragma once

#include <iostream>
#include <math.h>

#include "Element4_2D.h"
#include "Grid.h"
#include "Element.h"
#include "Node.h"

void jakobian(int i, int j, double I[2][2], double Iinv[2][2], Element4_2D element, Grid& grid);

void solve_H_matrix(Grid& grid, Element4_2D element);

void add_boundary_condition(Grid& grid, Element4_2D uniwersalElement);

void solve_C_matrix(Grid& grid, Element4_2D element);

double** aggregation_H(Grid& grid);

double* aggregation_P(Grid& grid);

double** aggregation_C(Grid& grid);

bool GaussElimination(int n, double* X, double** H, double* P);

double* Gauss_elimination(double** AB, int N);

double* Gauss_elimination(double** A, double* B, int N);

double** sum_matrix(double** matrix1, double** matrix2, int size);

double* multiplication_matrix_by_vector(double** matrix1, double* vector1, int size);

double** devide_matrix_by_number(double** matrix1, double number1, int size);

double* sum_vector(double* vector1, double* vector2, int size);

double* calculate_temperature(double** H, double**C, double* P, double* t_start, int step, int n);

void print_temperature(double** H, double** C, double* P, double* t_start, int time, int step, int n);

double max_temperature(double* temperature, int n);

double min_temperature(double* temperature, int n);
