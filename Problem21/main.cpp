/* AMICABLE NUMBERS
==========================
Let d(n) be defined as the sum of proper divisors of n(numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.
For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
Evaluate the sum of all the amicable numbers under 10000.

Date : 10 Oct 2016
Duration : 1-2 hrs
Fixed : The program can't progress till the end consistently due to memory problem on out of bound array index issue, despite producing the correct answer. 
*/

#include <iostream>
//#include <math.h>
using namespace std;

int findD(const int num)
{
	int dn = 1, sqrtNum = (int)floor(sqrt(num));

	if (num < 2)
		return 0;

	for (int i = 2; i <= sqrtNum; i++)
	{
		if (num % i == 0)
		{
			dn += i + num / i;
		}
	}

	return dn;
}

int main()
{
	// Strategy: Start with a lowest number a which has not been checked so far. 
	// Check d(a)=b, d(b)==a?found:d(b)=c,... in chain fashion until an amicable pair is found, while marking off all the numbers as checked. 
	const int limit = 10000;
	int sum = 0, lowestNum = 2, curNum = lowestNum, curD, nextD;
	int checked[limit];
	checked[0] = checked[1] = checked[2] = 1;	// skip checking for numbers 0, 1, and 2

	while (lowestNum < limit)
	{
		curNum = lowestNum;
		checked[curNum] = 1;

		while (true)
		{
			curD = findD(curNum);
			//if (curNum >= 4319)
			//	cout << "Checkpoint0" << endl;
			if (curD >= limit || checked[curD] == 1)
				break;
			//if (curNum >= 4319)
			//	cout << "Checkpoint1" << endl;
			nextD = findD(curD);
			checked[curD] = 1;
			if (curNum == nextD)	// curNum and curD are amicable numbers
			{
				sum += curNum + curD;
				//cout << "Sum = " << sum << endl;
				//cout << "lowestNum = " << lowestNum << endl;
				//cout << "d(" << curNum << ")=" << curD << ", d(" << curD << ")=" << nextD << endl;
			
				/*if (curNum == 2620)
				{
					cout << "Checked: ";
					for (int i = lowestNum; i < limit; i++)
						if (checked[i] == 1)
							cout << i << " ";
					cout << endl;
				}*/
				
				break;
			}
			else
			{
				curNum = curD;
				if (checked[curNum] == 1)
					break;
				else
					checked[curNum] = 1;
			}
			//if (curNum >= 4319)
			//	cout << "Checkpoint2" << endl;
		}
		//if (curNum >= 4319)
		//	cout << "Checkpoint A: curNum=" << curNum << ", lowestNum=" << lowestNum << endl;

		for (int i = lowestNum+1; i < limit; i++) // find the next unchecked lowest number
		{
			if (checked[i] == 0)
			{
				lowestNum = i;
				break;
			}
		}
		if (checked[lowestNum] == 1)	// to mark termination for next round
			lowestNum = limit;
			
		//if (curNum >= 4319)
		//	cout << "Checkpoint B: curNum=" << curNum << ", lowestNum=" << lowestNum << endl;

		//if (lowestNum == limit)
		//	cout << "Reached end" << endl;
	}
	
	cout << "The sum of all the amicable numbers under 10000 is " << sum << endl;
	return 0;
}