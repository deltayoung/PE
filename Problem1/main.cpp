/* MULTIPLES OF 3 AND 5
==========================
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. 
The sum of these multiples is 23. Find the sum of all the multiples of 3 or 5 below 1000.

Date : 27 Aug 2016
*/

#include <iostream>
using namespace std;

int main()
{
	const int c1 = 3, c2 = 5, limit = 999;
	int c1c2 = c1*c2,
		multiplierC1 = limit / c1,
		multiplierC2 = limit / c2,
		multiplierC1C2 = limit / c1c2,
		maxC1 = multiplierC1 * c1,
		maxC2 = multiplierC2 * c2,
		maxC1C2 = multiplierC1C2 * c1c2,
		sumC1, sumC2, sumC1C2;
	sumC1 = multiplierC1*(c1+maxC1)/2;	// watch out: the divider should be put at the end to prevent premature roundoff
	sumC2 = multiplierC2*(c2+maxC2)/2;
	sumC1C2 = multiplierC1C2*(c1c2+maxC1C2)/2;

	std::cout << "c1c2=" << c1c2 << ", multiplierC1=" << multiplierC1 << ", multiplierC2=" << multiplierC2 << ", multiplierC1C2=" << multiplierC1C2 << 
		", maxC1=" << maxC1 << ", maxC2=" << maxC2 << ", maxC1C2=" << maxC1C2 << ", sumC1=" << sumC1 << ", sumC2=" << sumC2 << ", sumC1C2=" << sumC1C2 << std::endl;
	
	std::cout << "The sum of all multiples of 3 or 5 below 1000 is " << sumC1+sumC2-sumC1C2 << std::endl;

	return 0;
}
