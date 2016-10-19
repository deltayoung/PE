/* NAMES SCORES
=================
Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.
For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.
What is the total of all the name scores in the file?

Date : 10-19 Oct 2016
Duration : 5 hours
Note: Quicksort is too slow for large list (over 5 minutes and still running, O(n^2)). Try merge sort or heapsort with much better time performance (O(n log n)). 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int partition(vector<string> &list, int start, int end)
{
	int pivot = start;
	string temp, pivotValue = list[end];

	for (int i = start; i < end; i++)
	{
		// comparison
		if (list[i].compare(pivotValue) > 0)
		{
			// swap
			temp = list[i];
			list[i] = list[pivot];
			list[pivot] = temp;
		}
		else
		{
			pivot++;
		}
	}
	// swap
	list[end] = list[pivot];
	list[pivot] = pivotValue;

	return pivot;
}

void quicksort(vector<string> &list, int start, int end)
{
	if (start >= end)
		return;

	int pivot = partition(list, start, end);
	quicksort(list, 0, pivot - 1);
	quicksort(list, pivot + 1, end); 
}

void merge(vector<string> &list, int start, int mid, int end)
{
	vector<string> tempList;
	int i = start, j = mid;
	while (i < mid && j < end)
	{
		if (list[i] <= list[j])
		{
			tempList.push_back(list[i++]);
		}
		else
		{
			tempList.push_back(list[j++]);
		}
	}
	int tempStart = (i == mid) ? j : i, tempEnd = (i == mid) ? end : mid;
	for (int k = tempStart; k < tempEnd; k++)
		tempList.push_back(list[k]);

	// copy result to the list
	for (int k = 0; k < tempList.size(); k++)
	{
		list[start++] = tempList[k];
	}
}

void mergesort(vector<string> &list, int start, int end)
{
	if (end-start < 2)
		return;

	int mid = (start + end) / 2;
	mergesort(list, start, mid);
	mergesort(list, mid, end);

	merge(list, start, mid, end);
}

int score(string aName)
{
	int score = 0;
	for (int i = 0; i < aName.length(); i++)
	{
		score += aName[i] - 'A' + 1;
	}

	return score;
}

int main()
{
	string filename = "../../names.txt", aName;
	vector<string> nameList;
	fstream fileStream(filename, ios::in);
	if (fileStream.is_open())
	{
		while (getline(fileStream, aName, ','))
		{
			aName.erase(0, 1); // remove the double quote signs
			aName.pop_back();	
			nameList.push_back(aName);
		}

		fileStream.close();
	}
	else
	{
		cout << "Error in opening input file" << endl;
	}

	//quicksort(nameList, 0, nameList.size() - 1);
	mergesort(nameList, 0, nameList.size());

	for (int i = 0; i < nameList.size(); i++)
		cout << nameList[i] << endl;

	unsigned long long sum = 0;
	for (int i = 0; i < nameList.size(); i++)
	{
		sum += score(nameList[i]) * (i+1);
	}

	cout << "The total of all the name scores in the file is " << sum << endl;

	return 0;
}