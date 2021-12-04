#pragma once

#include <iostream>
#include "Tests.h"

void testElement4_2D(Element4_2D element)
{
	std::cout << "ETA\n";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << element.eta[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "KSI\n";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << element.ksi[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "WEST\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << element.sideWest[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "SOUTH\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << element.sideSouth[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "EAST\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << element.sideEast[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "NORTH\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << element.sideNorth[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void test_grid_nodes(Grid grid)
{
	grid.show_nodes();
}

void test_grid_element(Grid grid)
{
	grid.show_elements();
}

void test_grid_H_matrix(Grid grid)
{
	for (int i = 0; i < grid.get_amount_elements(); i++)
	{
		std::cout << "Element " << i + 1 << std::endl;
		grid.get_H_matrix(i);
	}
}


