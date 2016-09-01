/* LARGEST PRIME NUMBER
==========================
The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143 ?

Date : 27 Aug 2016
Duration: 1.5 hours
*/

#include <iostream>
#include <math.h>
using namespace std;

bool isPrimeNumber(long long theNumber)
{
	bool isPrime = true;
	int sqrtOfNumber = (int)floor(sqrt((double)theNumber))+1;
	for (int i=2; i<sqrtOfNumber; i++)
	{
		if (theNumber % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}

bool isPrimeNumber(int theNumber)
{
	bool isPrime = true;
	int sqrtOfNumber = (int)floor(sqrt((double)theNumber))+1;
	for (int i=2; i<sqrtOfNumber; i++)
	{
		if (theNumber % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}

int main()
{
	// The largest prime factor can be found more quickly by starting to divide the number with the smallest divider going up until sqrt(number)
	// to yield a large factor which is potentially a prime number - if it's not prime, then move on to the next smaller large factor of the number
	// and so on until the prime is found

	const long long theNumber = 600851475143;
	long long aFactor;
	int sqrtOfNumber = (int)floor(sqrt((double)theNumber))+1;
	int largestPrimeFactor = 1;
	bool primeFound = false;
	
	for (int i=2; i<sqrtOfNumber; i++)
	{
		if (theNumber % i == 0)
		{
			aFactor = theNumber/i;
			if (isPrimeNumber(aFactor))
			{
				largestPrimeFactor = aFactor;
				primeFound = true;
				break;
			}
			else if (isPrimeNumber(i))
			{
				largestPrimeFactor = i;
				primeFound = true;
			}
		}
	}
	if (!primeFound)
		largestPrimeFactor = theNumber;

	std::cout << std::endl << "The largest prime factor of " << theNumber << " is " << largestPrimeFactor << std::endl;

	return 0;
}
