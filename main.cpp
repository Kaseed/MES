#include <iostream>

#include "grid.h"
#include "gaussIntegral.h"

using namespace std;

int main()
{
	//Grid grid(0.2, 0.1, 6, 5);

	////Grid grid(1, 1, 7, 4);

	////Grid grid(0.5, 0.5, 3, 6);

	//grid.show_nodes();
	//grid.show_elements();

	cout << gaussIntegrall2D(2) << endl;

	cout << gaussIntegrall2D(3) << endl;

	return 0;
}