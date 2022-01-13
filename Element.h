#pragma once

#include <iostream>
class Element
{
public:
	int ID[4];
	double H[4][4];
	double Hbc[4][4];
	double P[4];
	double C[4][4];


	Element();
	Element(Element& element);
	Element(int* array);
	Element(int id1, int id2, int id3, int id4);
	Element(int* array, double H1[4][4]);
	Element(int id1, int id2, int id3, int id4, double H1[4][4]);

	void copy_element(Element& element);

	void set_id(int id1, int id2, int id3, int id4);
	void set_H_matrix(double H1[4][4]);

	double** get_H_matrix();
	int get_id1();
	int get_id2();
	int get_id3();
	int get_id4();
	int get_id_parameter(int number);

	void show_H_matrix();
	void show_C_matrix();

	void set_Hbc_matrix(double H1[4][4]);
	void set_C_matrix(double C[4][4]);

	void add_boundary_condition();
};

