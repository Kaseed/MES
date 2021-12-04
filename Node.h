#pragma once
class Node
{
	float x;
	float y;
	short bc;
public:
	Node();
	Node(float x, float y, short bc);

	void set_x(float x);

	void set_y(float y);

	void set_bc(short bc);


	float get_x();

	float get_y();

	short get_bc();
};

