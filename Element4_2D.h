#pragma once
class Element4_2D
{
public:
	int schemat;

	double** eta;
	double** ksi;
	double* weight;

	double** sideWest;
	double** sideNorth;
	double** sideEast;
	double** sideSouth;

	double** N;

	Element4_2D(int amountOfNodes);

	Element4_2D(Element4_2D& element);

	~Element4_2D();
};