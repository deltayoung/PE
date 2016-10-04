/* LONGEST COLLATZ SEQUENCE
=============================
The following iterative sequence is defined for the set of positive integers:
n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. 
Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?
NOTE: Once the chain starts the terms are allowed to go above one million.

Date : 3 Oct 2016
Duration: 1.5 hrs
Note: The main trap of this problem is that the Collatz sequence numbers can exceed the integer range, so it's necessary to cater the tested numbers to long long range
*/

#include <iostream>
using namespace std;

const int numLimit = 999999;
int skipList[numLimit];

long long calculateCollatzSequenceLength(long long num)
{
	if (num > 1)
	{
		if (num <= numLimit)
			skipList[num] = 1;	//skip
		if (num % 2 == 0)
			return 1 + calculateCollatzSequenceLength(num / 2);
		else // num % 2 == 1
			return 1 + calculateCollatzSequenceLength(3 * num + 1);
	}
	else if (num == 1)
		return 1;
	else
		return 0;
	
}

int main()
{
	// Observation: Each number has a fixed Collatz sequence length, hence it can be recursively calculated
	// Strategy: Once a number has been visited in calculating one Collatz sequence length, record it in a lookup table for future reference so it can be skipped because it definitely has shorter Collatz sequence length

	int i, curNum, longestChainStartNum=-1, chainLength, maxChainLength=0;
	skipList[1] = 1;
	if (numLimit >= 1)
	{
		maxChainLength = 1;
		longestChainStartNum = 1;
	}
	
	for (i = 2; i <= numLimit; i *= 2)	// all numbers from the power of 2 are precalculated
	{
		skipList[i] = 1;
		maxChainLength++;
	}
	if (numLimit > 1)
		longestChainStartNum = i / 2;
	cout << "Initial longestChainStartNum=" << longestChainStartNum << " with chain length of " << maxChainLength << endl;

	/*cout << endl;
	for (int j = 1; j <= numLimit; j++)
	{
		if (skipList[j] == 1)
			cout << "X";
		else
			cout << "=";
	}
	cout << endl;*/

	for (i=numLimit; i>2; i--)
	{
		if (skipList[i] != 1)
		{
			chainLength = calculateCollatzSequenceLength(i);

			if (chainLength > maxChainLength)
			{
				maxChainLength = chainLength;
				longestChainStartNum = i;
			}
		}
	}

	/*cout << endl;
	for (int j = 1; j <= numLimit; j++)
	{
		if (skipList[j] == 1)
			cout << "X";
		else
			cout << "=";
	}
	cout << endl;*/

	cout << "The starting number, under one million, which produces the longest chain is " << longestChainStartNum << " with chain length of " << maxChainLength << endl;
	return 0;
}