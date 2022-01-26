#include <iostream>

#include "Element4_2D.h"

//#include "gaussIntegral.h"

Element4_2D::Element4_2D(int amountOfNodes)
{
	schemat = amountOfNodes;

	if (schemat == 2)
	{
		amountOfNodes = 2 * 2;

		eta = new double* [amountOfNodes];
		ksi = new double* [amountOfNodes];
		N = new double* [amountOfNodes];

		//double* points = { -1 / sqrt(3), 1 / sqrt(3) }; //nodePoints(2);
		double points[2] = { -1 / sqrt(3), 1 / sqrt(3) };

		double points2[4][2] = { {points[0], points[0]},{points[1], points[0]},{points[1], points[1]},{points[0], points[1]} };

		weight = new double[2];

		weight[0] = 1.0;
		weight[1] = 1.0;

		for (int i = 0; i < amountOfNodes; i++)
		{
			eta[i] = new double[amountOfNodes];
			ksi[i] = new double[amountOfNodes];
			N[i] = new double[amountOfNodes];
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

		sideEast = new double* [2];
		sideNorth = new double* [2];
		sideSouth = new double* [2];
		sideWest = new double* [2];

		for (int i = 0; i < 2; i++)
		{
			sideEast[i] = new double[4];
			sideNorth[i] = new double[4];
			sideSouth[i] = new double[4];
			sideWest[i] = new double[4];
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

	if (schemat == 3)
	{
		amountOfNodes = 3 * 3;

		eta = new double* [amountOfNodes];
		ksi = new double* [amountOfNodes];
		N = new double* [amountOfNodes];

		weight = new double[3];

		weight[0] = 5.0 / 9.0;
		weight[1] = 8.0 / 9.0;
		weight[2] = 5.0 / 9.0;

		double points[3] = { - sqrt(3.0/5.0), 0 ,sqrt(3.0 / 5.0) };

		double points2[9][2] = { {points[0], points[0]},{points[0], points[1]},{points[0], points[2]}, {points[1], points[0]},{points[1], points[1]},{points[1], points[2]}, {points[2], points[0]},{points[2], points[1]},{points[2], points[2]} };

		for (int i = 0; i < amountOfNodes; i++)
		{
			eta[i] = new double[4];
			ksi[i] = new double[4];
			N[i] = new double[4];
		}

		for (int i = 0; i < amountOfNodes; i++)
		{
			ksi[i][0] = -0.25 * (1 - points2[i][1]);
			ksi[i][1] = 0.25 * (1 - points2[i][1]);
			ksi[i][2] = 0.25 * (1 + points2[i][1]);
			ksi[i][3] = -0.25 * (1 + points2[i][1]);

			eta[i][0] = -0.25 * (1 - points2[i][0]);
			eta[i][1] = -0.25 * (1 + points2[i][0]);
			eta[i][2] = 0.25 * (1 + points2[i][0]);
			eta[i][3] = 0.25 * (1 - points2[i][0]);
		}

		/*for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				std::cout << ksi[i][j] << " ";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl << std::endl;

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				std::cout << eta[i][j] << " ";
			}
			std::cout << std::endl;
		}*/

		sideEast = new double* [3];
		sideNorth = new double* [3];
		sideSouth = new double* [3];
		sideWest = new double* [3];

		for (int i = 0; i < 3; i++)
		{
			sideEast[i] = new double[4];
			sideNorth[i] = new double[4];
			sideSouth[i] = new double[4];
			sideWest[i] = new double[4];
		}

		//Side WEST

		for (int i = 0; i < 3; i++)
		{
			int ksiWest = -1;
			sideWest[i][0] = 0.25 * (1.0 - ksiWest) * (1.0 - points[i]);
			sideWest[i][1] = 0.25 * (1.0 + ksiWest) * (1.0 - points[i]);
			sideWest[i][2] = 0.25 * (1.0 + ksiWest) * (1.0 + points[i]);
			sideWest[i][3] = 0.25 * (1.0 - ksiWest) * (1.0 + points[i]);
		}

		//Side SOUTH

		for (int i = 0; i < 3; i++)
		{
			int etaSouth = -1;
			sideSouth[i][0] = 0.25 * (1.0 - points[i]) * (1.0 - etaSouth);
			sideSouth[i][1] = 0.25 * (1.0 + points[i]) * (1.0 - etaSouth);
			sideSouth[i][2] = 0.25 * (1.0 + points[i]) * (1.0 + etaSouth);
			sideSouth[i][3] = 0.25 * (1.0 - points[i]) * (1.0 + etaSouth);
		}

		// Side EAST

		for (int i = 0; i < 3; i++)
		{
			int ksiEast = 1;
			sideEast[i][0] = 0.25 * (1.0 - ksiEast) * (1.0 - points[i]);
			sideEast[i][1] = 0.25 * (1.0 + ksiEast) * (1.0 - points[i]);
			sideEast[i][2] = 0.25 * (1.0 + ksiEast) * (1.0 + points[i]);
			sideEast[i][3] = 0.25 * (1.0 - ksiEast) * (1.0 + points[i]);
		}

		// Side NORTH

		for (int i = 0; i < 3; i++)
		{
			int etaNorth = 1;
			sideNorth[i][0] = 0.25 * (1.0 - points[i]) * (1.0 - etaNorth);
			sideNorth[i][1] = 0.25 * (1.0 + points[i]) * (1.0 - etaNorth);
			sideNorth[i][2] = 0.25 * (1.0 + points[i]) * (1.0 + etaNorth);
			sideNorth[i][3] = 0.25 * (1.0 - points[i]) * (1.0 + etaNorth);
		}

		for (int i = 0; i < amountOfNodes; i++)
		{
			N[i][0] = 0.25 * (1.0 - points2[i][0]) * (1.0 - points2[i][1]);
			N[i][1] = 0.25 * (1.0 + points2[i][0]) * (1.0 - points2[i][1]);
			N[i][2] = 0.25 * (1.0 + points2[i][0]) * (1.0 + points2[i][1]);
			N[i][3] = 0.25 * (1.0 - points2[i][0]) * (1.0 + points2[i][1]);
		}
	}

}

Element4_2D::Element4_2D(Element4_2D& element)
{
	this->schemat = element.schemat;

	eta = new double* [schemat * schemat];
	ksi = new double* [schemat * schemat];
	N = new double* [schemat * schemat];

	weight = new double[element.schemat];

	for (int i = 0; i < schemat; i++)
	{
		weight[i] = element.weight[i];
	}

	for (int i = 0; i < schemat * schemat; i++)
	{
		eta[i] = new double[4];
		ksi[i] = new double[4];
		N[i] = new double[4];
	}

	for (int i = 0; i < schemat * schemat; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			eta[i][j] = element.eta[i][j];
			ksi[i][j] = element.ksi[i][j];
			N[i][j] = element.N[i][j];
		}
	}

	sideEast = new double* [schemat];
	sideNorth = new double* [schemat];
	sideSouth = new double* [schemat];
	sideWest = new double* [schemat];

	for (int i = 0; i < schemat; i++)
	{
		sideEast[i] = new double[4];
		sideNorth[i] = new double[4];
		sideSouth[i] = new double[4];
		sideWest[i] = new double[4];
	}

	for (int i = 0; i < schemat; i++)
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

Element4_2D::~Element4_2D()
{
	for (int i = 0; i < schemat * schemat; i++)
	{
		delete[] eta[i];
		delete[] ksi[i];
		delete[] N[i];
	}

	for (int i = 0; i < schemat; i++)
	{
		delete[] sideEast[i];
		delete[] sideNorth[i];
		delete[] sideSouth[i];
		delete[] sideWest[i];
	}

	delete[] weight;
	delete[] eta;
	delete[] ksi;
	delete[] N;
	delete[] sideEast;
	delete[] sideNorth;
	delete[] sideSouth;
	delete[] sideWest;
}
