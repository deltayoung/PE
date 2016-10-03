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
Duration: 
*/

#include <iostream>
using namespace std;

int main()
{
	// Observation: Each number has a fixed Collatz sequence length, hence it can be recursively calculated
	// Strategy: Once a number has been counted for its Collatz sequence length, record it in a lookup table for future reference so it doesn't need to be recalculated
	const int numLimit = 999999;
	int startNum = numLimit, curNum = startNum, longestChainStartNum, chainLength=1, maxChainLength=chainLength;
	
	calculateCollatzSequenceLength(startNum);
	while (curNum != 1)
	{
		if (curNum % 2 == 0)	// even number
		{
			curNum /= 2;
		}
		else	// odd number
		{
			curNum = 3 * curNum + 1;
		}
		chainLength++;
	}
	if (chainLength > maxChainLength)

	cout << "The starting number, under one million, which produces the longest chain is " << startNum << endl;
	return 0;
}