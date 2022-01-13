#include <iostream>

#include "Element4_2D.h"

//#include "gaussIntegral.h"

Element4_2D::Element4_2D(int amountOfNodes)
{
	amountOfNodes = 2 * 2;

	eta = new double* [amountOfNodes];
	ksi = new double* [amountOfNodes];

	//double* points = { -1 / sqrt(3), 1 / sqrt(3) }; //nodePoints(2);
	double points[2] = { -1 / sqrt(3), 1 / sqrt(3) };

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

	//Side WEST

	for (int i = 0; i < 2; i++)
	{
		int ksiWest = -1;
		sideWest[i][0] = 0.25 * (1.0 - ksiWest) * (1.0 - points[i]);
		sideWest[i][1] = 0.25 * (1.0 + ksiWest) * (1.0 - points[i]);
		sideWest[i][2] = 0.25 * (1.0 + ksiWest) * (1.0 + points[i]);
		sideWest[i][3] = 0.25 * (1.0 - ksiWest) * (1.0 + points[i]);
	}

	//Side SOUTH

	for (int i = 0; i < 2; i++)
	{
		int etaSouth = -1;
		sideSouth[i][0] = 0.25 * (1.0 - points[i]) * (1.0 - etaSouth);
		sideSouth[i][1] = 0.25 * (1.0 + points[i]) * (1.0 - etaSouth);
		sideSouth[i][2] = 0.25 * (1.0 + points[i]) * (1.0 + etaSouth);
		sideSouth[i][3] = 0.25 * (1.0 - points[i]) * (1.0 + etaSouth);
	}

	// Side EAST

	for (int i = 0; i < 2; i++)
	{
		int ksiEast = 1;
		sideEast[i][0] = 0.25 * (1.0 - ksiEast) * (1.0 - points[i]);
		sideEast[i][1] = 0.25 * (1.0 + ksiEast) * (1.0 - points[i]);
		sideEast[i][2] = 0.25 * (1.0 + ksiEast) * (1.0 + points[i]);
		sideEast[i][3] = 0.25 * (1.0 - ksiEast) * (1.0 + points[i]);
	}

	// Side NORTH

	for (int i = 0; i < 2; i++)
	{
		int etaNorth = 1;
		sideNorth[i][0] = 0.25 * (1.0 - points[i]) * (1.0 - etaNorth);
		sideNorth[i][1] = 0.25 * (1.0 + points[i]) * (1.0 - etaNorth);
		sideNorth[i][2] = 0.25 * (1.0 + points[i]) * (1.0 + etaNorth);
		sideNorth[i][3] = 0.25 * (1.0 - points[i]) * (1.0 + etaNorth);
	}

	for (int i = 0; i < 4; i++)
	{
		N[i][0] = 0.25 * (1.0 - points2[i][0]) * (1.0 - points2[i][1]);
		N[i][1] = 0.25 * (1.0 + points2[i][0]) * (1.0 - points2[i][1]);
		N[i][2] = 0.25 * (1.0 + points2[i][0]) * (1.0 + points2[i][1]);
		N[i][3] = 0.25 * (1.0 - points2[i][0]) * (1.0 + points2[i][1]);
	}

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
			N[i][j] = element.N[i][j];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sideWest[i][j] = element.sideWest[i][j];
			sideSouth[i][j] = element.sideSouth[i][j];
			sideEast[i][j] = element.sideEast[i][j];
			sideNorth[i][j] = element.sideNorth[i][j];
		}
	}
}
