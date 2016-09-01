/* SMALLEST MULTIPLE
========================
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

Date : 27 Aug 2016
Duration: 45 minutes
*/

#include <iostream>
#include <vector>

bool isPrimeNumber(const int aNumber)
{
	bool isPrime = true;

	if (aNumber < 2)
		return false;
	else if (aNumber == 2)
		return isPrime;

	for (int i=2; i<aNumber; i++)
	{
		if (aNumber % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}

void findPrimeFactors(const int theNumber, std::vector<int> &primeFactors)
{
	primeFactors.clear();
	int tempNumber = theNumber;

	for (int i=2; i<=theNumber; i++)
	{
		if (tempNumber == 1)
			break;
		if (isPrimeNumber(i))
		{
			while (tempNumber % i == 0)
			{
				primeFactors.push_back(i);
				tempNumber /= i;
			}
		}
	}
}

int main()
{
	const int start=1, end=20;
	int answer=start, tempAnswer;
	std::vector<int> primeFactors;

	for (int i=start+1; i<=end; i++)
	{
		if (answer % i != 0)
		{
			tempAnswer = answer;
			findPrimeFactors(i, primeFactors);
			// update answer with additional prime factors of i so that the answer is divisible by i
			for (int j=0; j<primeFactors.size(); j++)
			{
				if (tempAnswer % primeFactors[j] == 0)
				{
					tempAnswer /= primeFactors[j];
				}
				else
					answer *= primeFactors[j];
			}
		}
	}

	std::cout << "The smallest positive number that is evenly divisible by all of the numbers from " << start << " to " << end << " is " << answer << std::endl;

	return 0;
}