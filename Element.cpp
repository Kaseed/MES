#include "Element.h"

Element::Element()
{
	for (int i = 0; i < 4; i++)
	{
		ID[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		P[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			H[i][j] = 0;
			Hbc[i][j] = 0;
		}
	}
}

Element::Element(Element& element)
{
	for (int i = 0; i < 4; i++)
	{
		this->ID[i] = element.ID[i];
	}

	for (int i = 0; i < 4; i++)
	{
		P[i] = element.P[i];
		for (int j = 0; j < 4; j++)
		{
			this->H[i][j] = element.H[i][j];
			Hbc[i][j] = element.Hbc[i][j];
		}
	}
}


Element::Element(int* array)
{
	for (int i = 0; i < 4; i++)
	{
		ID[i] = array[i];
	}

	for (int i = 0; i < 4; i++)
	{
		P[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			H[i][j] = 0;
			Hbc[i][j] = 0;
		}
	}
}

Element::Element(int id1, int id2, int id3, int id4)
{
	ID[0] = id1;
	ID[1] = id2;
	ID[2] = id3;
	ID[3] = id4;

	for (int i = 0; i < 4; i++)
	{
		P[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			H[i][j] = 0;
			Hbc[i][j] = 0;
		}
	}
}

Element::Element(int* array, double H1[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		ID[i] = array[i];
	}

	for (int i = 0; i < 4; i++)
	{
		P[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			H[i][j] = H1[i][j];
			Hbc[i][j] = 0;
		}
	}
}

Element::Element(int id1, int id2, int id3, int id4, double H1[4][4])
{
	ID[0] = id1;
	ID[1] = id2;
	ID[2] = id3;
	ID[3] = id4;

	for (int i = 0; i < 4; i++)
	{
		P[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			H[i][j] = H1[i][j];
			Hbc[i][j] = 0;
		}
	}
}

void Element::copy_element(Element& element)
{
	for (int i = 0; i < 4; i++)
	{
		this->ID[i] = element.ID[i];
	}

	for (int i = 0; i < 4; i++)
	{
		P[i] = element.P[i];
		for (int j = 0; j < 4; j++)
		{
			this->H[i][j] = element.H[i][j];
			this->Hbc[i][j] = element.Hbc[i][j];
		}
	}
}

void Element::set_id(int id1, int id2, int id3, int id4)
{
	ID[0] = id1;
	ID[1] = id2;
	ID[2] = id3;
	ID[3] = id4;
}

void Element::set_H_matrix(double H1[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			double temp = H1[i][j];
			this->H[i][j] = temp;
		}
}

double** Element::get_H_matrix()
{

	double** array = new double* [4];
	for (int i = 0; i < 4; i++)
	{
		array[i] = new double[4];
		for (int j = 0; j < 4; j++)
			array[i][j] = H[i][j];
	}
	return array;
}


int Element::get_id1()
{
	return ID[0];
}

int Element::get_id2()
{
	return ID[1];
}

int Element::get_id3()
{
	return ID[2];
}

int Element::get_id4()
{
	return ID[3];
}

int Element::get_id_parameter(int number)
{
	return ID[number];
}

void Element::show_H_matrix()
{
	for (int l = 0; l < 4; l++)
	{
		for (int m = 0; m < 4; m++)
			std::cout << H[l][m] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Element::set_Hbc_matrix(double H1[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			this->Hbc[i][j] = H1[i][j];
		}
}
