/* NON-ABUNDANT SUMS
=======================
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. 
For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.
As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. 
By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. 
However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

Date : 19 Oct 2016
Duration : 
*/

#include <iostream>
using namespace std;

int main()
{
	const int limit = 28123, smallestSummableNumber = 24;
	int summableList[limit+1] = { 0 };	// 0 - not summable, 1 - summable
	unsigned long long sum = 0;
	for (int i = 1; i < smallestSummableNumber; i++)
		sum += i;
	summableList[smallestSummableNumber] = 1;

	// check for summability
	for (int i = smallestSummableNumber+1; i <= limit; i++)
	{
		if (isSummable(i))
		{
			summableList[i] = 1;
			for (int j = smallestSummableNumber; j < i; j++)
			{
				if (summableList[j] == 1)

			}
		}
	}

	// sum up the non-summable numbers
	for (int i = smallestSummableNumber+1; i <= limit; i++)
	{
		if (summableList[i] == 0)
			sum += i;
	}

	cout << "The sum of all the positive integers which cannot be written as the sum of two abundant numbers is " << sum << endl;
	return 0;
}