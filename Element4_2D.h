#pragma once
class Element4_2D
{
public:
	double** eta;
	double** ksi;

	Element4_2D(int amountOfNodes);

	Element4_2D(Element4_2D& element);
};

