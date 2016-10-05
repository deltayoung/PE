/* LATTICE PATHS
===================
Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?

Date : 5 Oct 2016
Duration:
*/

#include <iostream>
using namespace std;

int main()
{
	const int gridWidth = 20, gridHeight = 20;
	int numRoutes;

	cout << "The number of routes through a " << gridWidth << "x" << gridHeight << " grid is " << numRoutes << endl;
	return 0;
}