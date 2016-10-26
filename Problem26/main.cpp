/* RECIPROCAL CYCLES
=================================
A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:
1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.

Date : 26 Oct 2016
Duration : 1 hour
Strategy: Do the division operation manually to keep track of the remainders of the divisions; once the same remainder comes up again, that's when a pattern finished running and would restart.
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	const int maxDenominator = 1000;
	vector<int> remainderList,	// list of remainders that have occurred - as soon as one of the remainders re-occurs, it indicates a pattern is going to repeat 
				patternBookmark; // list of bookmarked patternCounts at which a corresponding remainder happened for the first time - the length of the pattern is the difference of current patternCounter value with the bookmarked value 
	int curRemainder, patternCounter, maxPatternLength=0, maxPatternLengthDenominator;
	bool breakCycle;
	for (int i = 2; i < maxDenominator; i++)
	{
		breakCycle = false;
		patternCounter = 0;
		remainderList.clear();
		patternBookmark.clear();
		curRemainder = 1;
		remainderList.push_back(curRemainder);
		patternBookmark.push_back(patternCounter);

		while (!breakCycle)
		{
			if (curRemainder / i == 0)
				curRemainder *= 10;	// no increment for patternCounter for the first multiplication

			while (curRemainder / i == 0)
			{
				curRemainder *= 10;
				patternCounter++;
			}

			// here, curRemainder/i will range from 1 to 9 (1 digit)
			patternCounter++;

			curRemainder = curRemainder % i;
			if (curRemainder == 0)
			{
				break;	//from while (!breakCycle) loop
			}
			for (int j = 0; j < remainderList.size(); j++)
			{
				if (curRemainder == remainderList[j])	// a pattern will repeat
				{
					if (patternCounter-patternBookmark[j] > maxPatternLength)
					{
						maxPatternLengthDenominator = i;
						maxPatternLength = patternCounter - patternBookmark[j];
					}
					breakCycle = true;
					break;
				}
			}
			if (!breakCycle)
			{
				remainderList.push_back(curRemainder);
				patternBookmark.push_back(patternCounter);
			}
			
			//patternCounter++;

		}
	}

	cout << "The value of d < " << maxDenominator << " for which 1/d contains the longest recurring cycle in its decimal fraction part is " << maxPatternLengthDenominator << endl;

	return 0;
}