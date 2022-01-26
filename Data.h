#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Grid.h"

using namespace std;

class Data
{
public:
	int SimulationTime;
	int SimulationStepTime;
	int Conductivity;
	int Alfa;
	int Tot;
	int InitialTemp;
	int Density;
	int SpecificHeat;

	Data();

	Data(std::string path, Grid &grid);
};

