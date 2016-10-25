/* NON-ABUNDANT SUMS
=======================
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. 
For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.
As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. 
By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. 
However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

Date : 19-25 Oct 2016
Duration : 2 hours
Note: A tad long runtime (~20 seconds) without optimisation. After optimisation by reducing the search space by avoiding repeated summations of all abundant numbers for each input, the running time is less than 1 second (instantaneous).
*/

#include <iostream>
#include <vector>
using namespace std;

const int limit = 28123, smallestAbundantNumber = 12;
int smallestSummableNumber = smallestAbundantNumber + smallestAbundantNumber;
vector<int> abundantNumberList;

/*void findDivisors(int num, vector<int> &properDivisors)
{
	properDivisors.clear();

	if (num < 1)
		return;
	else
		properDivisors.push_back(1);

	for (int i = 2; i < num; i++)
	{
		if (num % i == 0)
			properDivisors.push_back(i);
	}
}*/

bool isAbundantNumber(int num)
{
	unsigned long long sum = 1;

	/*vector<int> properDivisors;
	findDivisors(num, properDivisors);

	for (int i = 0; i < properDivisors.size(); i++)
	{
		sum += properDivisors[i];
	}*/

	if (num < 1)
		return false;
	int mid = (int)floor(sqrt(num)), otherFactor;
	for (int i = 2; i <= mid; i++)
	{
		if (num%i == 0)
		{
			sum += i;
			otherFactor = num / i;
			if (otherFactor != i)
				sum += otherFactor;
		}
	}

	if (sum > num)
		return true;
	else
		return false;
}

/*bool isSummable(int num)
{
	for (int i = 0; i < abundantNumberList.size(); i++)
	{
		for (int j = 0; j < abundantNumberList.size(); j++)
		{
			if (abundantNumberList[i] + abundantNumberList[j] == num)
				return true;
		}
	}

	return false;
}*/

int main()
{
	//vector<int> summableList;
	int summableList[2 * limit + 1] = { 0 };	// 0 - non-summable, 1 - summable
	unsigned long long sum = 0;

	abundantNumberList.push_back(smallestAbundantNumber);

	for (int i = 1; i < smallestSummableNumber; i++)
		sum += i;
	//summableList.push_back(smallestSummableNumber);
	summableList[smallestSummableNumber] = 1;

	for (int i = smallestAbundantNumber + 1; i <= smallestSummableNumber; i++)
	{
		if (isAbundantNumber(i))
			abundantNumberList.push_back(i);
	}

	// check for summability
	for (int i = smallestSummableNumber+1; i <= limit; i++)
	{
		if (isAbundantNumber(i))
			abundantNumberList.push_back(i);
		/*if (isSummable(i))
		{
			summableList.push_back(i);
		}
		else
			sum += i;*/
		/*if (!isSummable(i))
			sum += i;*/
	}
	for (int i = 0; i < abundantNumberList.size(); i++)
	{
		for (int j = i; j < abundantNumberList.size(); j++)
			summableList[abundantNumberList[i] + abundantNumberList[j]] = 1;
	}

	for (int i = smallestSummableNumber+1; i <= limit; i++)
		if (summableList[i] == 0)
			sum += i;
	/*cout << "List of abundant numbers: ";
	for (int i = 0; i < 1000; i++)
	//for (int i = 0; i < abundantNumberList.size(); i++)
	{
		cout << abundantNumberList[i] << " ";
	}
	cout << endl;*/

	//cout << "There are " << limit - summableList.size() << " non-summable numbers" << endl;

	cout << "The sum of all the positive integers which cannot be written as the sum of two abundant numbers is " << sum << endl;
	return 0;
}