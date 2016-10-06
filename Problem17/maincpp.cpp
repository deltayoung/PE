/* NUMBER LETTER COUNT
==========================
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
The use of "and" when writing out numbers is in compliance with British usage.

Date : 6 Oct 2016
Duration : 2 hours
Note : The formulation of dictionary and the many categories with various boundaries are treacherous and time-consuming. Most time spent on debugging them.
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int letterCount = 0, subTo, subFrom;
	const int from = 1, to = 1000;	// the value of "to" can only be up to 1000

	// spell out standard words - actually, the dict pairs are not complex enough to be searched/indexed randomly by the first element; this program only access the unitLength vector in order
	pair<int, string> dictArray[] = { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"},
		{11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"}, {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"}, {20, "twenty"},
		{30, "thirty"}, {40, "forty"}, {50, "fifty"}, {60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"}, {100, "hundred"}, {1000, "thousand"} };
	vector<pair<int, string>> dict(dictArray, dictArray + sizeof(dictArray) / sizeof(pair<int, string>));
	vector<int> unitLength;	// corresponding lengths of dict second elements

	for (int i = 0; i < dict.size(); i++)
	{
		unitLength.push_back(dict[i].second.length());
	}

	// count letters from 1 to 20 - still ordered without skipping any number
	subTo = to >= 20 ? 20 : to;
	for (int i = from; i <= subTo; i++)
	{
		letterCount += unitLength[i - 1];
	}
	cout << "Checkpoint 1 = " << letterCount << endl;

	if (to > subTo)
	{
		// from 21 to 99 (2 digits)
		subFrom = from > subTo ? from : subTo + 1;
		subTo = to > 99 ? 99 : to;
		for (int i = subFrom; i <= subTo; i++)
		{
			letterCount += unitLength[17 + i/10];	// accessing the tens (i/10 range from 2 to 9)
			int leastDigit = i % 10;	// accessing the least significant digit (range from 0 to 9)
			if (leastDigit > 0)
				letterCount += unitLength[leastDigit-1];	
		}
		cout << "Checkpoint 2 = " << letterCount << endl;

		// from 100 to 999 (3 digits)
		subFrom = subTo + 1;	
		subTo = to > 999 ? 999 : to;
		for (int i = subFrom; i <= subTo; i++)
		{
			letterCount += unitLength[i/100-1] + unitLength[27];	// accessing the hundreds (i/100 range from 1 to 9)
			int tens = i % 100;	// accessing the tens (i%100 range from 0 to 99)
			if (tens > 20)	// 21 to 99
			{ 
				letterCount += unitLength[17 + tens / 10] + 3;  // accessing the tens (tens/10 range from 2 to 9), +3 for "and"
				int leastDigit = tens % 10;		// accessing the least significant digit (range from 0 to 9)
				if (leastDigit > 0)
					letterCount += unitLength[leastDigit - 1];
			}
			else if (tens > 0)	// 1 to 20
			{
				letterCount += unitLength[tens - 1] + 3;	// +3 for "and"
			}
		}
		cout << "Checkpoint 3 = " << letterCount << endl;

		// for 1000
		if (to == 1000)
			letterCount += unitLength[0] + unitLength[28];

	}

	cout << "The number of letter used in writing all the numbers from 1 to 1000 in words is " << letterCount << endl;
	return 0;
}
