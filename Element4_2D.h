#pragma once
class Element4_2D
{
public:
	double** eta;
	double** ksi;

	double sideWest[2][4];
	double sideNorth[2][4];
	double sideEast[2][4];
	double sideSouth[2][4];

	Element4_2D(int amountOfNodes);

	Element4_2D(Element4_2D& element);
};