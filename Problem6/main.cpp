/* SUM SQUARE DIFFERENCE
==========================

The sum of the squares of the first ten natural numbers is 1^2 + 2^2 + ... + 10^2 = 385
The square of the sum of the first ten natural numbers is (1 + 2 + ... + 10)^2 = 55^2 = 3025
Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

Date : 29 Sep 2016
Duration: 15 minutes
*/

#include <iostream>
using namespace std;

int main()
{
	const int natNumCount = 100;
	int sumSqr=0, sqrSum=0;

	for (int i=1; i<=natNumCount; i++)
	{
		sumSqr += i*i;
		sqrSum += i;
	}
	sqrSum *= sqrSum;

	cout << "The difference between the sum of the squares of the first one hundred natural numbers and the square of the sum is " << sumSqr-sqrSum << endl;

	return 0;
}