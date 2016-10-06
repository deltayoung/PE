/* POWER DIGIT SUM
=====================
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000 ?

Date : 6 Oct 2016
Duration : 30 min
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// Strategy: to add num with itself at each increment of power and store the result in an expanding vector firstNum (least significant digit at the front, most significant digit at the back)
	const int maxPower = 1000;	// assume maxPower is integer > 0
	int carry, sum = 0; 
	vector<int> num;
	num.push_back(1);	// 2^0 = 1
	
	for (int i = 1; i <= maxPower; i++)
	{
		carry = 0;
		for (int j = 0; j < num.size(); j++)
		{
			num[j] += carry + num[j]; // for addition, num[j] will never reach 3 digits and carry will always be 1 digit
			carry = num[j] / 10;
			num[j] = num[j] % 10;
		}
		if (carry > 0)
			num.push_back(carry);
	}

	cout << "Digits: ";
	for (int i = 0; i < num.size(); i++)
	{
		cout << num[i] << " ";
		sum += num[i];
	}
	cout << endl;

	cout << "The sum of the digits of the number 2^1000 is " << sum << endl;
	return 0;
}