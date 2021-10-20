#pragma once

double gaussIntegrall1D(int amountOfPoints);

double gaussIntegrall1D(int amountOfPoints, double(*f)(double x));

double polinomial_fx(double x);

double gaussIntegrall2D(int amountOfPoints);

double gaussIntegrall2D(int amountOfPoints, double(*f)(double x, double y));

double polinomial_fxy(double x, double y);

double* nodePoints(int nodes);

double* nodeWeight(int nodes);
