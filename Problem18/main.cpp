/* MAXIMUM PATH SUM I
==========================
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
		 3
		7 4
	   2 4 6
	  8 5 9 3
That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:
												75
											  95 64
											17 47 82
										  18 35 87 10
										20 04 82 47 65
									  19 01 23 75 03 34
									88 02 77 73 07 63 67
								  99 65 04 28 06 16 70 92
								41 41 26 56 83 40 80 70 33
							  41 48 72 33 47 32 37 16 94 29
							53 71 44 65 25 43 91 52 97 51 14
						  70 11 33 28 77 73 17 78 39 68 17 57
						91 71 52 38 17 14 91 43 58 50 27 29 48
					  63 66 04 68 89 53 67 30 73 16 69 87 40 31
					04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. 
However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)

Date : 6 Oct 2016
Duration : 45 min
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

	vector<vector<int>> data;	// read from "input.txt" file
	string filename = "../../input.txt";
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

	for (int j=data.size()-2; j>=0; j--)
		for (int i = 0; i < data[j].size(); i++)	// updating the maximum sum bottom up
		{
			data[j][i] += data[j+1][i] > data[j+1][i+1] ? data[j+1][i] : data[j+1][i+1];
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