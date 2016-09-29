/* SPECIAL PHYTAGOREAN TRIPLET
===============================
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which a^2 + b^2 = c^2.
For example, 32 + 42 = 9 + 16 = 25 = 52.

There exists exactly one Pythagorean triplet for which a + b + c = 1000. Find the product abc.

Date : 29 Sep 2016
Duration: 30 min
*/

#include <iostream>
using namespace std;

int main()
{
	int product = 1, sum = 1000, 
		a=0, b=0, c=0, 
		minA=1, maxA=sum/3-1, minB, maxB;
		//minB=2, maxB=(sum-1)%2==0?(sum-1)/2-1:(sum-1)/2, 
		//minC=3, maxC=sum-minA-minB;

	// reduce the search space by using range of possible a, for each possible value of a, reduce the search space of possible b
	for (int i=minA; i<=maxA; i++)
	{
		minB = i+1;
		maxB = (sum-i)%2==0?(sum-i)/2-1:(sum-i)/2;
		for (int j=minB; j<=maxB; j++)
		{
			c = sum - i - j;
			if (i*i+j*j == c*c)
			{
				a = i; 
				b = j;
				break;
			}
		}
		if (a != 0)
			break;
	}

	cout << "The product of a Pythagorean triplet that sums to 1000 is " << a*b*c << endl;
	return 0;
}