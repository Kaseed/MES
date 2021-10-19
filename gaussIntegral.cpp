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
