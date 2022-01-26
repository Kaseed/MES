#include "Data.h"

Data::Data()
{
	SimulationTime = 0;
	SimulationStepTime = 0;
	Conductivity = 0;
	Alfa = 0;
	Tot = 0;
	InitialTemp = 0;
	Density = 0;
	SpecificHeat = 0;
}

Data::Data(string path, Grid &grid)
{
	fstream plik;
	plik.open(path);
	if (plik.good())
	{
		string line;
		string name, value;
		int amount_of_nodes = 0;
		int amount_of_element = 0;
		int loads = 0;
		while (getline(plik, line))
		{
			if (line[0] == '*')
			{
				loads++;
				getline(plik, line);
			}
			if (loads == 0)
			{
				stringstream load(line);
				load >> name;
				load >> value;
				if (name == "SimulationTime")
					SimulationTime = stod(value);
				else if (name == "SimulationStepTime")
					SimulationStepTime = stod(value);
				else if (name == "Conductivity")
					Conductivity = stod(value);
				else if (name == "Alfa")
					Alfa = stod(value);
				else if (name == "Tot")
					Tot = stod(value);
				else if (name == "InitialTemp")
					InitialTemp = stod(value);
				else if (name == "Density")
					Density = stod(value);
				else if (name == "SpecificHeat")
					SpecificHeat = stod(value);
				else if (name == "Nodes_number")
				{
					amount_of_nodes = stoi(value);
					grid.setnNodes(amount_of_nodes);
				}
				else if (name == "Elements_number")
				{
					amount_of_element = stoi(value);
					grid.setnElements(amount_of_element);
				}
				else
					cout << "B³êdne dane" << name << " " << value << endl;
			}
			if (loads == 1)
			{
				string node;
				string x, y;
				stringstream load(line);
				load >> node;
				load >> x;
				load >> y;
				node.pop_back();
				x.pop_back();
				Node* handle = grid.get_orginal_node(stoi(node) - 1);
				handle->set_x(stod(x));
				handle->set_y(stod(y));
				handle->set_bc(0);
			}
			if (loads == 2)
			{
				string element;
				string nod1, nod2, nod3, nod4;
				stringstream load(line);
				load >> element;
				load >> nod1;
				load >> nod2;
				load >> nod3;
				load >> nod4;
				element.pop_back();
				nod1.pop_back();
				nod2.pop_back();
				nod3.pop_back();

				Element* handle = grid.get_orginal_element(stoi(element) - 1);
				handle->set_id(stoi(nod1), stoi(nod2), stoi(nod3), stoi(nod4));
			}
			if (loads == 3)
			{
				string border;
				stringstream load(line);
				while (true)
				{
					load >> border;
					if (border[border.size() - 1] == ',')
					{
						border.pop_back();
						Node* handle = grid.get_orginal_node(stoi(border) - 1);
						handle->set_bc(1);
					}
					else
					{
						Node* handle = grid.get_orginal_node(stoi(border) - 1);
						handle->set_bc(1);
						break;
					}
				}
			}
		}
	}
	else
		cout << "Input ERROR\n";
}
