/* FACTORIAL DIGIT SUM
==========================
n! means n × (n − 1) × ... × 3 × 2 × 1
For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800, and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!

Date : 7 Oct 2016
Duration : (in progress) 1.5 hrs
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	const int num = 100;
	int sum = 0, curNum = num, curDigit, carry;
	vector<int> factorial;	// stores the digit of factorial of num, starting from least significant digit to most significant digit

	// push num digits to factorial first
	while (curNum >= 10)
	{
		factorial.push_back(curNum % 10);
		curNum /= 10;
	}
	factorial.push_back(curNum);

	for (int i = num-1; i > 0; i--)
	{
		vector<int> curFactorial(factorial);
		factorial.clear();	// empty the factorial container
		curNum = i;
		carry = 0;
		int offset = 0;
		while (curNum > 0)
		{
			curDigit = curNum % 10;

			// multiply current factorial digits with curDigit
			for (int j = 0; j < curFactorial.size(); j++)
			{
				if (j + offset == factorial.size())
					factorial.push_back(0);		// a placeholder
				factorial[j+offset] += curFactorial[j]*curDigit + carry;	// the multiplication result is up to 2 digits
				carry = factorial[j+offset] / 10;	// 1 digit
				factorial[j+offset] = factorial[j+offset] % 10;
			}
			if (carry > 0)
					factorial.push_back(carry);

			curNum /= 10;
			offset++;	// tracking the current digit of curNum being processed 
		}
	}
	
	for (int i = 0; i < factorial.size(); i++)
		sum += factorial[i];

	cout << "The sum of the digits in the number 100! is " << sum << endl;
	
	return 0;
}