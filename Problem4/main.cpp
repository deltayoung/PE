/* LARGEST PALINDROME PRODUCT
==============================
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
Find the largest palindrome made from the product of two 3-digit numbers.

Date : 27 Aug 2016
Duration: 1.5 hrs
*/

#include <iostream>
#include <sstream>
using namespace std;

bool isPalindromeNumber(int aNumber)
{
	bool isPalindrome = true;

	stringstream ss;
	ss << aNumber;
	string stringNumber = ss.str();
	int bound = stringNumber.length()/2;
	for (int i=0; i<bound; i++)
	{
		if (stringNumber[i] != stringNumber[stringNumber.length()-i-1])
		{
			isPalindrome = false;
			break;
		}
	}

	return isPalindrome;
}

int main()
{
	// Strategy: brute force from 999x999 until 999x101, 998x998 until 998x101, 997x997 until 997x101, and so on until 101x101, 
	// skipping all numbers ending with 0, because any multiplication with such number will never produce palindrome number

	const int start=999, end=101;
	int product=0, largestPalindrome = 1, iBound = end, jBound = end;

	for (int i=start; i>=iBound; i--)
	{
		for (int j=i; j>=jBound; j--)
		{
			product = i*j;
			if (product <= largestPalindrome)
				break;
			else if (isPalindromeNumber(product))
			{
				largestPalindrome = product;
				iBound = jBound = j+1;	// reduce the search space as the next product can only be bigger if the next i and j value is bounded to be lower than current i and higher than current j
				break;
			}
		}
	}

	std::cout << std::endl << "The largest palindrome number made from the product of two 3-digit numbers is " << largestPalindrome << std::endl;

	return 0;
}
