/* 10001ST PRIIME
==========================
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
What is the 10 001st prime number?

Date : 29 Sep 2016
Duration: 15 minutes
*/

#include <iostream>
using namespace std;

bool isPrimeNumber(int num)
{
	bool isPrime = true;
	if (num < 2)
		return false;
	else if (num == 2)
		return true;
	else
	{
		for (int i=2; i<num; i++)
		{
			if (num%i == 0)
			{
				isPrime = false;
				break;
			}
		}
	}

	return isPrime;
}

int main()
{
	int primeCount=0, curNum=1;
	const int finalCount = 10001;

	if (finalCount < 1)
		return -1;	// invalid request

	while (primeCount != finalCount)
	{
		if (isPrimeNumber(++curNum))
			primeCount++;
	}
		
	cout << "The 10001st prime number is " << curNum << endl;

	return 0;
}