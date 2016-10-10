/* NAMES SCORES
=================
Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.
For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.
What is the total of all the name scores in the file?

Date : 10 Oct 2016
Duration : 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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

	for (int i = 0; i < nameList.size(); i++)
	{
		cout << nameList[i] << endl;
	}



	return 0;
}