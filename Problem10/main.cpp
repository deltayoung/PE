/* SUMMATION OF PRIMES
===============================
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
Find the sum of all the primes below two million.

Date : 29 Sep 2016
Duration: 5 min (1.5 hours for the optimisation)
Comment: Runtime of this program is 5 minutes for ~2 million numbers to check using brute-force method. Use parallel computing for speedup - the tasks are highly parallel.
Forum recommended to avoid checking even numbers and multiples of smaller numbers; reducing the search space tremendously but didn't improve the execution time (5 minutes).
Another recommendation of maintaining prime number database (recursively) and to only check divisibility by prime numbers up to the square root of the number actually improve execution time to less than 1 second!
*/

#include <iostream>
//#include <math.h>
using namespace std;

const int checkLimit = 2000000;
int pool[checkLimit] = {0};
int primeNumbers[checkLimit] = {0};	// database of prime numbers; 
int primeCount = 1;
int lastCheckedNumber = 2;

bool isPrimeNumber(int num)	
{
	int mid;
	if (num < 2)
		return false;
	else if (num <= lastCheckedNumber)
	{
		for (int i=0; i<primeCount; i++)
			if (primeNumbers[i] == num)
				return true;
		
		return false;
	}
	else if (num == lastCheckedNumber+1)	// need to calculate and then update database
	{
		lastCheckedNumber = num;
		mid = sqrt((float)num);
		for (int i=0; i<primeCount; i++)
		{
			if (primeNumbers[i] > mid)
				return true;	// don't update prime count and database
			if (num % primeNumbers[i] == 0)
				return false;
		}
		primeNumbers[primeCount++] = num;
		return true;
	}
	else
	{
		isPrimeNumber(num-1);	// recursively update database for prime numbers up to the mid
		return isPrimeNumber(num);
	}

}

int main()
{
	primeNumbers[0] = 2;
	long long result = 2;
	int partition;

	if (checkLimit < 2)
		result = 0;
	else
	{
		for (int i=3; i<checkLimit; i+=2)
		{
			if (pool[i]==0)
			{
				partition = checkLimit/i;
				for (int j=i*2; j<checkLimit; j+=i)
				{
					pool[j] = 1;
				}
				if (isPrimeNumber(i))
					result += i;
			}
		}
	}


	std::cout << "The sum of all the primes below two million is " << result << endl;
	return 0;
}