/* LATTICE PATHS
===================
Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?

Date : 5 Oct 2016
Duration: 1.5 hours
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> getPrimeFactors(int num)
{
	if (num < 2)
		return {};

	vector<int> primeFactors;
	vector<int> primeNumbers; // to be filled with prime numbers in increasing order
	primeNumbers.push_back(2);	// first prime number
	
	// first, find all prime numbers up to num
	for (int i = 3; i <= num; i++)
	{
		for (int j = 2; j < i; j++)
		{
			if (i%j == 0)	// i is not prime number
				break;
			else if (j == i - 1)	// end of iterations, so i is a prime number
				primeNumbers.push_back(i);
		}
	}

	// next, select prime numbers which are smallest prime factors of num
	int tempNum = num;
	for (int i = 0; i < primeNumbers.size(); i++)
	{
		while (tempNum % primeNumbers[i] == 0)
		{
			primeFactors.push_back(primeNumbers[i]);
			tempNum /= primeNumbers[i];
		}
	}

	return primeFactors;
}

int main()
{
	// Answer to the solution is (20+20)C(20), a combination calculation. 
	// The integer and long long number containers will probably be capacity-wise insufficient to perform the large nominator multiplication; 
	// hence the need to cancel as many as possible with the denominators first. In this case, it's (40*39*38*...*21)/20! = (
	const int gridWidth = 20, gridHeight = 20;
	unsigned long long numRoutes=1;
	vector<int> numerators, denominators, numeratorPrimeFactors, denominatorPrimeFactors;
	for (int i = gridWidth + gridHeight; i > gridHeight+1; i--)
	{
		numerators.push_back(i);
		denominators.push_back(i - gridWidth);
	}
	numerators.push_back(gridHeight + 1);

	cout << "Numerators = {";
	for (int i = 0; i < numerators.size()-1; i++)
	{
		cout << numerators[i] << ", ";
	}
	cout << numerators[numerators.size() - 1] << "}" << endl;
	cout << "Denominators = {";
	for (int i = 0; i < denominators.size() - 1; i++)
	{
		cout << denominators[i] << ", ";
	}
	cout << denominators[denominators.size() - 1] << "}" << endl;

	// decompose the numerators and denominators into their prime factors for canceling each other
	for (int i = 0; i < numerators.size(); i++)	// numerators.size() = denominators.size()
	{
		vector<int> tempNum = getPrimeFactors(numerators[i]);
		numeratorPrimeFactors.insert(numeratorPrimeFactors.end(), tempNum.begin(), tempNum.end());

		vector<int> tempDen = getPrimeFactors(denominators[i]);
		denominatorPrimeFactors.insert(denominatorPrimeFactors.end(), tempDen.begin(), tempDen.end());
	}

	// cancel out common prime factors between the numerators and denominators
	for (int i = 0; i < numeratorPrimeFactors.size(); i++)
	{
		for (int j = 0; j < denominatorPrimeFactors.size(); j++)
		{
			if (numeratorPrimeFactors[i] == denominatorPrimeFactors[j])	// remove this factor from both lists by marking its value to 0
			{
				numeratorPrimeFactors[i] = denominatorPrimeFactors[j] = 0;
				break;
			}
		}
	}

	// perform clean multiplication and division
	for (int i = 0; i < numeratorPrimeFactors.size(); i++)
	{
		if (numeratorPrimeFactors[i] != 0)
			numRoutes *= numeratorPrimeFactors[i];
	}
	for (int i = 0; i < denominatorPrimeFactors.size(); i++)
	{
		if (denominatorPrimeFactors[i] != 0)
			numRoutes /= denominatorPrimeFactors[i];
	}

	cout << "The number of routes through a " << gridWidth << "x" << gridHeight << " grid is " << numRoutes << endl;
	return 0;
}