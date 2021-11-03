#include <iostream>

#include "Element4_2D.h"

#include "gaussIntegral.h"

Element4_2D::Element4_2D(int amountOfNodes)
{
	amountOfNodes = 2*2;

	eta = new double* [amountOfNodes];
	ksi = new double* [amountOfNodes];

	double* points = nodePoints(2);

	double points2[4][2] = { {points[0], points[0]},{points[1], points[0]},{points[1], points[1]},{points[0], points[1]} };

	for (int i = 0; i < amountOfNodes; i++)
	{
		eta[i] = new double[amountOfNodes];
		ksi[i] = new double[amountOfNodes];
	}

	for (int i = 0; i < amountOfNodes; i++)
	{
		//std::cout << points2[i][0] << std::endl;

		ksi[i][0] = -0.25 * (1 - points2[i][1]);
		ksi[i][1] = 0.25 * (1 - points2[i][1]);
		ksi[i][2] = 0.25 * (1 + points2[i][1]);
		ksi[i][3] = -0.25 * (1 + points2[i][1]);

		eta[i][0] = -0.25 * (1 - points2[i][0]);
		eta[i][1] = -0.25 * (1 + points2[i][0]);
		eta[i][2] = 0.25 * (1 + points2[i][0]);
		eta[i][3] = 0.25 * (1 - points2[i][0]);
	}

	/*std::cout << "dKsi" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << ksi[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout <<"--------------------" << std::endl;

	std::cout << "dEta" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << eta[i][j] << " ";
		}
		std::cout << std::endl;
	}*/

}

Element4_2D::Element4_2D(Element4_2D& element)
{
	eta = new double* [4];
	ksi = new double* [4];

	for (int i = 0; i < 4; i++)
	{
		eta[i] = new double[4];
		ksi[i] = new double[4];
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			eta[i][j] = element.eta[i][j];
			ksi[i][j] = element.ksi[i][j];
		}
	}
}

