/* LEXICOGRAPHIC PERMUTATIONS
=================================
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. 
If all of the permutations are listed numerically or alphabetically, we call it lexicographic order.The lexicographic permutations of 0, 1 and 2 are:
012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9 ?

Date : 25 Oct 2016
Duration : 3 hours
Note: A trap of one off the goalIndex to determine the divisor - reason: the goalIndex should start from 0 instead of 1
*/

#include <iostream>
#include <vector>
using namespace std;


int main()
{
	const int numOfDigits = 10, initGoalIndex = 1000000; 
	int numOfPermutations = 1, goalIndex = initGoalIndex;
	vector<int> goalNumber;
	int permutations[numOfDigits + 1] = { 1 };	// store 1!, 2!, …, numOfDigits! - note that permutations[0] = 0! = 1
	int taken[numOfDigits] = { 0 }; // 0 = not taken, 1 = taken

	// pre-compute permutation numbers
	permutations[1] = 1;
	for (int i = 2; i <= numOfDigits; i++)
	{
		numOfPermutations *= i;
		permutations[i] = numOfPermutations;
	}

	cout << "Permutations[0.." << numOfDigits << "] = ";
	for (int i = 0; i <= numOfDigits; i++)
	{
		cout << permutations[i] << " ";
	}
	cout << endl;

	// check for out of bound input
	if (goalIndex > numOfPermutations)
	{
		cout << "There is no " << goalIndex << "th lexicographic permutation of the digits[0 - 9]" << endl;
		return -1;
	}


	for (int i = 1; i <= numOfDigits; i++)
	{
		int divisor = (goalIndex-1) / permutations[numOfDigits - i], // range [0,9]
			divisorOffset = 0;
		goalIndex -= divisor * permutations[numOfDigits - i];
		cout << divisor << " ";
		for (int j=0; j<=divisor+divisorOffset; j++)	// adjust divisor
		{
			if (taken[j] == 1)
				divisorOffset++;
		}
		divisor += divisorOffset;
		if (divisor > numOfDigits - 1)
		{
			cout << "Exception, program aborted." << endl;
			return -1;
		}
		goalNumber.push_back(divisor);
		taken[divisor] = 1;
	}

	cout << endl << "The " << initGoalIndex << "th lexicographic permutations of 0 - " << numOfDigits-1 << " is ";
	for (int i = 0; i<goalNumber.size(); i++)
	{
		cout << goalNumber[i];
	}
	cout << endl;

	return 0;
}

