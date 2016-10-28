/* SU DOKU
========================
Su Doku (Japanese meaning number place) is the name given to a popular puzzle concept. 
Its origin is unclear, but credit must be attributed to Leonhard Euler who invented a similar, and much more difficult, puzzle idea called Latin Squares. 
The objective of Su Doku puzzles, however, is to replace the blanks (or zeros) in a 9 by 9 grid in such that each row, column, and 3 by 3 box contains 
each of the digits 1 to 9. 

A well constructed Su Doku puzzle has a unique solution and can be solved by logic, although it may be necessary to employ "guess and test" methods 
in order to eliminate options (there is much contested opinion over this). The complexity of the search determines the difficulty of the puzzle; 
the example above is considered easy because it can be solved by straight forward direct deduction.

The 6K text file, sudoku.txt (right click and 'Save Link/Target As...'), contains fifty different Su Doku puzzles ranging in difficulty, 
but all with unique solutions (the first puzzle in the file is the example above).

By solving all fifty puzzles find the sum of the 3-digit numbers found in the top left corner of each solution grid; 
for example, 483 is the 3-digit number found in the top left corner of the solution grid above.

Date : 27,28 Oct 2016
Duration: 5 hrs
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int gridSize = 9, regionDim = sqrt(gridSize);
vector<vector<vector<int>>> puzzles;

bool readInput(string inputFile)
{
	bool success = false;
	string aLine;
	fstream fileStream(inputFile, ios::in);

	if (fileStream.is_open())
	{
		while (getline(fileStream, aLine))
		{
			// ignore first line "Grid #x"
			vector<int> aRow;
			vector<vector<int>> aGrid;
			for (int i = 0; i < gridSize; i++)
			{
				getline(fileStream, aLine);
				aRow.clear();
				for (int j = 0; j < gridSize; j++)
					aRow.push_back(aLine.at(j) - '0');
				aGrid.push_back(aRow);
			}
			puzzles.push_back(aGrid);
		}
		fileStream.close();

		// printout of read input
		cout << "Puzzles:" << endl;
		for (int i = 0; i < puzzles.size(); i++)
		{
			cout << "Grid " << i + 1 << endl;
			for (int j = 0; j < gridSize; j++)
			{
				for (int k = 0; k < gridSize; k++)
					cout << puzzles[i][j][k];
				cout << endl;
			}
		}

		success = true;
	}
	else
		cout << "Invalid input file" << endl;

	return success;
}

void solvePuzzle(const int index)
{
	vector<vector<int>> inRow, inColumn, inRegion;	// to mark inRow[num-1][x]/inColumn[num-1][x]/inRegion[num-1][x] if a number exists in particular row/column/region x: 0=non-existent, 1=exist 
													// for inRegion, the regions are numbered 1 till gridSize horizontally from left to right, moving downwards
	vector<pair<int, int>> priorityQ;	// the order of processing each number; a number has higher priority if it's been completed in more regions (but not fully completed at all regions yet); pair<num, counter>
	for (int i = 1; i <= gridSize; i++)
		priorityQ.push_back(make_pair(i, 0));

	for (int i = 0; i < gridSize; i++)	// pre-allocating space for vectors
	{
		vector<int> aCluster(gridSize);
		inRow.push_back(aCluster);
		inColumn.push_back(aCluster);
		inRegion.push_back(aCluster);
	}

	// fill up inRow, inColumn, inRegion initial information
	for (int i = 0; i < gridSize; i++)	// row i
	{
		for (int j = 0; j < gridSize; j++)	// column j
		{
			if (puzzles[index][i][j] != 0)
			{
				inRow[puzzles[index][i][j] - 1][i] = 1;
				inColumn[puzzles[index][i][j] - 1][j] = 1;
				inRegion[puzzles[index][i][j] - 1][i / 3 * regionDim + j / 3] = 1;
			}
		}
	}

	// determine initial priority queue
	for (int i = 0; i < gridSize; i++)
		for (int j = 0; j < gridSize; j++)
			if (puzzles[index][i][j] != 0)
				priorityQ[puzzles[index][i][j] - 1].second++;
	for (int i = priorityQ.size()-1; i >= 0; i--)
	{
		if (priorityQ[i].second == gridSize)	// fully solved for the number i
			priorityQ.pop_back();
	}
	// sort priorityQ based on counter
	struct {
		bool operator()(pair<int, int> a, pair<int, int> b)
		{
			return a.second > b.second;
		}
	} myCompare;
	sort(priorityQ.begin(), priorityQ.end(), myCompare);

	while (puzzles[index][0][0] == 0 || puzzles[index][0][1] == 0 || puzzles[index][0][2] == 0)	// only need to solve the first 3 top left numbers for each puzzle
	{
		for (int i = 0; i < priorityQ.size(); i++)	// check for answers systematically using some rules for filling in numbers 1 to 9 according to the priority queue
		{
			while (priorityQ[i].second < gridSize)
			{
				for (int j = 0; j < inRegion[priorityQ[i].first - 1].size(); j++)	// check each region
				{
					if (inRegion[priorityQ[i].first - 1][j] == 0)	// to attempt to solve for number i by checking its inRegion horizontally and vertically - if all its corresponding horizontal(left&right)/vertical(up&down) neighboring regions have been solved but one region, then it can be deduced  
					{
						if (inRegion[priorityQ[i].first - 1][j%regionDim == 0 ? j - 1 + regionDim : j - 1] == 1 && inRegion[priorityQ[i].first - 1][(j + 1) % regionDim == 0 ? j + 1 - regionDim : j + 1] == 1 && inRegion[priorityQ[i].first - 1][j < regionDim ? gridSize + j - regionDim : j - regionDim] == 1 && inRegion[priorityQ[i].first - 1][j + regionDim >= gridSize ? j%regionDim : j + regionDim] == 1)
						{
							// solvable

						}
						
					}
				}
				// when new input is found, break from the while loop
				if ()
					break;
			}

		}
	}
	
}

int main()
{
	int answer = 0;
	
	if (readInput("../../p096_sudoku.txt") == false)
		return -1;

	// sum answers from each puzzle
	for (int i = 0; i < puzzles.size(); i++)
	{
		solvePuzzle(i);
		answer += puzzles[i][0][0] * 100 + puzzles[i][0][1] * 10 + puzzles[i][0][2];
	}
	
	cout << "The sum of the 3-digit numbers found in the top left corner of each of 50 solution grids is " << answer << std::endl;

	return 0;
}