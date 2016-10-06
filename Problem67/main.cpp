/* MAXIMUM PATH SUM II
==========================
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
		3
	   7 4
      2 4 6
     8 5 9 3
That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom in triangle.txt, a 15K text file containing a triangle with one-hundred rows.

NOTE: This is a much more difficult version of Problem 18. It is not possible to try every route to solve this problem, as there are 299 altogether! 
If you could check one trillion (1012) routes every second it would take over twenty billion years to check them all. There is an efficient algorithm to solve it. ;o)

Date : 6 Oct 2016
Duration : 5 min
*/


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	// Strategy: Bottom up approach. At each node, find its maximum value (best path below it), accumulating upwards till the top. 
	// Data structure choice: 2D vector (sparse, half-filled)

	vector<vector<int>> data;	// read from "triangle.txt" file
	string filename = "../../triangle.txt";
	fstream fileStream(filename, ios::in);

	// read input data
	if (fileStream.is_open())
	{
		string aLine, aNum;
		stringstream ss;
		while (getline(fileStream, aLine))
		{
			vector<int> lineInput;
			ss.clear();
			ss.str(aLine);

			while (getline(ss, aNum, ' '))
			{
				lineInput.push_back(stoi(aNum));
			}
			data.push_back(lineInput);
		}
		fileStream.close();
	}
	else
	{
		cout << "Error: Can't open input file" << endl;
		return -1;
	}
	cout << "Input data : " << endl;
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
			cout << data[i][j] << " ";
		cout << endl;
	}

	for (int j = data.size() - 2; j >= 0; j--)
		for (int i = 0; i < data[j].size(); i++)	// updating the maximum sum bottom up
		{
			data[j][i] += data[j + 1][i] > data[j + 1][i + 1] ? data[j + 1][i] : data[j + 1][i + 1];
		}

	cout << "Output : " << endl;
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
			cout << data[i][j] << " ";
		cout << endl;
	}

	cout << "The maximum total from top to bottom of the triangle is " << data[0][0] << endl;
	return 0;
}