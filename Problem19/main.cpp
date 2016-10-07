/* COUNTING SUNDAYS
==========================
You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?

Date : 7 Oct 2016
Duration : 30 min
*/

#include <iostream>
using namespace std;

int main()
{
	int sunCount = 0;
	int nonLeapMonthlyDayCount[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int leapMonthlyDayCount[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	enum days { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
	int firstDay;	// day of 1 Jan 1901
	int firstSundayDate;	// the first Sunday in Jan 1901

	// find out the day on 1 Jan 1901 first
	// year 1900 is not a leap year since it's on a century undivisible by 400
	int totalDayInOneYear=0;
	for (int i = 0; i < 12; i++)
		totalDayInOneYear += nonLeapMonthlyDayCount[i];
	firstDay = totalDayInOneYear % 7;	// firstDay 0 is a Monday
	firstSundayDate = 7 - firstDay;

	for (int year = 1901; year <= 2000; year++)
	{
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))	// leap year
		{
			for (int month = 0; month < 12; month++)
			{
				if (firstSundayDate == 1)
					sunCount++;
				firstDay = (firstDay + leapMonthlyDayCount[month]) % 7; // 1st of next month
				firstSundayDate = 7 - firstDay;
			}
		}
		else // non-leap year
		{
			for (int month = 0; month < 12; month++)
			{
				if (firstSundayDate == 1)
					sunCount++;
				firstDay = (firstDay + nonLeapMonthlyDayCount[month]) % 7; // 1st of next month
				firstSundayDate = 7 - firstDay;
			}
		}
	}

	cout << "There are " << sunCount << " Sundays fell on the first of the month during the 20th century (1 Jan 1901 - 31 Dec 2000)" << endl;
	return 0;
}