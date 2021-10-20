#include <math.h>

#include "gaussIntegral.h"


double gaussIntegrall1D(int amountOfPoints)
{
    double* points = nodePoints(amountOfPoints);
    double* weight = nodeWeight(amountOfPoints);

    double value = 0;

    for (int i = 0; i < amountOfPoints; i++)
    {
        value += weight[i] * (5 * points[i] * points[i] + 3 * points[i] + 6);
    }

    delete[] points;
    delete[] weight;

    return value;
}

double gaussIntegrall1D(int amountOfPoints, double(*f)(double))
{
    double* points = nodePoints(amountOfPoints);
    double* weight = nodeWeight(amountOfPoints);

    double value = 0;

    for (int i = 0; i < amountOfPoints; i++)
    {
        value += weight[i] * f(points[i]);
    }

    delete[] points;
    delete[] weight;

    return value;
}

double polinomial_fx(double x)
{
    // 5x^2 + 3x + 6
    return (5 * x * x + 3 * x + 6);
}

double gaussIntegrall2D(int amountOfPoints)
{
    double* points = nodePoints(amountOfPoints);
    double* weight = nodeWeight(amountOfPoints);

    double value = 0;

    for (int i = 0; i < amountOfPoints; i++)
    {
        for (int j = 0; j < amountOfPoints; j++)
        {
            value += weight[i] * weight[j] * (5 * points[i] * points[i] * points[j] * points[j] + 3 * points[i] * points[j] + 6);
        }
    }

    delete[] points;
    delete[] weight;

    return value;
}

double gaussIntegrall2D(int amountOfPoints, double(*f)(double x, double y))
{
    double* points = nodePoints(amountOfPoints);
    double* weight = nodeWeight(amountOfPoints);

    double value = 0;

    for (int i = 0; i < amountOfPoints; i++)
    {
        for (int j = 0; j < amountOfPoints; j++)
        {
            value += weight[i] * weight[j] * f(points[i], points[j]);
        }
    }

    delete[] points;
    delete[] weight;

    return value;
}

double polinomial_fxy(double x, double y)
{
    // 5x^2y^2 + 3xy + 6
    return (5 * x * x * y * y + 3 * x * y + 6);
}

double* nodeWeight(int nodes)
{
    double* ptr = nullptr;
	switch(nodes)
    {
    case 2:
        ptr = new double[2]{1.0, 1.0};
        return ptr;
        break;

    case 3:
        ptr = new double[3]{ 5.0/9, 8.0/9, 5.0/9 };
        return ptr;
        break;

    default:
        return nullptr;
    }
}

double* nodePoints(int nodes)
{
    double* ptr = nullptr;
    switch (nodes)
    {
    case 2:
        ptr = new double[2]{ -1.0 / sqrt(3), 1.0 / sqrt(3) };
        return ptr;
        break;

    case 3:
        ptr = new double[3]{ -sqrt(3.0 / 5.0), 0, sqrt(3.0 / 5.0) };
        return ptr;
        break;

    default:
        return nullptr;
    }
}
