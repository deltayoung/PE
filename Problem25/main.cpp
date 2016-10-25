/* 1000-DIGIT FIBONACCI NUMBER
=================================
The Fibonacci sequence is defined by the recurrence relation:
F(n) = F(n−1) + F(n−2), where F(1) = 1 and F(2) = 1.
Hence the first 12 terms will be:
F(1) = 1
F(2) = 1
F(3) = 2
F(4) = 3
F(5) = 5
F(6) = 8
F(7) = 13
F(8) = 21
F(9) = 34
F(10) = 55
F(11) = 89
F(12) = 144
The 12th term, F(12), is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to contain 1000 digits?

Date : 25 Oct 2016
Duration : 20 min
Strategy: Work from the least significant digit using expandable vector container to store the latest Fibonacci number digits
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	const int firstNum = 1, secondNum = 1, totalDigits = 1000;
	int index = 3, carry, temp;
	vector<int> latestFiboNum, secondLatestFiboNum;
	latestFiboNum.push_back(firstNum + secondNum);	// as long as firstNum+secondNum doesn't exceed 1 digit, this is safe as a start
	secondLatestFiboNum.push_back(secondNum);

	while (latestFiboNum.size() < totalDigits)
	{
		index++;
		carry = 0;
		for (int i = 0; i < secondLatestFiboNum.size(); i++)
		{
			temp = latestFiboNum[i];
			latestFiboNum[i] += carry + secondLatestFiboNum[i];
			carry = latestFiboNum[i] / 10;
			if (carry > 0)
			{
				latestFiboNum[i] = latestFiboNum[i] % 10;
			}
			secondLatestFiboNum[i] = temp;
		}
		for (int i = secondLatestFiboNum.size(); i < latestFiboNum.size(); i++)
		{
			temp = latestFiboNum[i];
			latestFiboNum[i] += carry;
			carry = latestFiboNum[i] / 10;
			if (carry > 0)
				latestFiboNum[i] = latestFiboNum[i] % 10;
			secondLatestFiboNum.push_back(temp);
		}
		if (carry > 0)
			latestFiboNum.push_back(carry);
	}

	cout << "The index of the first term in the Fibonacci sequence to contain " << totalDigits << " digits is " << index << endl;

	return 0;
}

