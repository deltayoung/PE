/* MONOPOLY ODDS
===================
In the game, Monopoly, the standard board is set up in the following way :
GO	A1	CC1	A2	T1	R1	B1	CH1	B2	B3	JAIL
H2	 									C1
T2	 									U1
H1	 									C2
CH3	 									C3
R4	 									R2
G3	 									D1
CC3	 									CC2
G2	 									D2
G1	 									D3
G2J	F3	U2	F2	F1	R3	E3	E2	CH2	E1	FP

A player starts on the GO square and adds the scores on two 6 - sided dice to determine the number of squares they advance in a clockwise direction.
Without any further rules we would expect to visit each square with equal probability : 2.5%. However, landing on G2J(Go To Jail), CC(community chest), and CH(chance) changes this distribution.

In addition to G2J, and one card from each of CC and CH, that orders the player to go directly to jail, if a player rolls three consecutive doubles, they do not advance the result of their 3rd roll.
Instead they proceed directly to jail.

At the beginning of the game, the CC and CH cards are shuffled.
When a player lands on CC or CH they take a card from the top of the respective pile and, after following the instructions, it is returned to the bottom of the pile.There are sixteen cards in each pile, 
but for the purpose of this problem we are only concerned with cards that order a movement; any instruction not concerned with movement will be ignored and the player will remain on the CC / CH square.

Community Chest(2 / 16 cards) :
	1. Advance to GO
	2. Go to JAIL
Chance(10 / 16 cards) :
	1. Advance to GO
	2. Go to JAIL
	3. Go to C1
	4. Go to E3
	5. Go to H2
	6. Go to R1
	7. Go to next R(railway company)
	8. Go to next R
	9. Go to next U(utility company)
	10. Go back 3 squares.
	
The heart of this problem concerns the likelihood of visiting a particular square. That is, the probability of finishing at that square after a roll.
For this reason it should be clear that, with the exception of G2J for which the probability of finishing on it is zero, the CH squares will have the lowest probabilities, 
as 5 / 8 request a movement to another square, and it is the final square that the player finishes at on each roll that we are interested in.
We shall make no distinction between "Just Visiting" and being sent to JAIL, and we shall also ignore the rule about requiring a double to "get out of jail", assuming that they pay to get out on their next turn.

By starting at GO and numbering the squares sequentially from 00 to 39 we can concatenate these two - digit numbers to produce strings that correspond with sets of squares.

Statistically it can be shown that the three most popular squares, in order, are JAIL(6.24%) = Square 10, E3(3.18%) = Square 24, and GO(3.09%) = Square 00. 
So these three most popular squares can be listed with the six - digit modal string : 102400.
If, instead of using two 6 - sided dice, two 4 - sided dice are used, find the six - digit modal string.

Date : 2 Nov 2016
Duration:
Strategy consideration: Markov Chain for 120 states (=40 squares * 3 consecutive rolls) is memory-less - can't account for probability distribution of orderly picked CC/CH cards from the shuffled decks. 
Alternatively, a full simulation of large number of dice rolls will produce a more accurate empirical probability distribution model, taking into consideration the order of CC/CH stacks.
Assumption: there is only 1 player in the simulation, so the CC/CH stack order will be preserved with respect to the movement among the squares.
Result: Inconsistent simulation result for 6-sided dies: 102400 / 102419 / 102425 even for 10^9 rolls. For 4-sided dies, it's more consistent, mostly 101524 (and very rarely 101516).
*/

#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main()
{
	srand(time(NULL));
	const int numSquares = 40, numRolls = 10000000, diceSides = 4, numDies = 2, stackSize = 16;

	int top1, top2, top3,	// answers
		diceRollSum, 
		doubleCount = 0,	// mark consecutive double rolls
		nextCCptr = 0,	// point to the topmost card in CC stack
		nextCHptr = 0,	// point to the topmost card in CH stack
		curPos = 0;	// start from 00 (GO)
	int CCstack[stackSize], CHstack[stackSize];
	vector<pair<int,int>> statistics;
	for (int i = 0; i < numSquares; i++)
		statistics.push_back(make_pair(i,0));
	for (int i = 0; i < stackSize; i++)
	{
		CCstack[i] = -1;  // non-movement card
		CHstack[i] = -1;  // non-movement card
	}

	cout << "Shuffling cards..." << endl;

	// shuffling CC stack
	int curCC, numCCmov = 0;
	while (true)
	{
		if (numCCmov == 2)	// there are only 2 movement cards in CC stack
			break;

		curCC = rand() % stackSize;
		if (CCstack[curCC] == -1)
		{
			if (numCCmov == 0)
				CCstack[curCC] = 0; // go to 00 (GO)
			else if (numCCmov == 1)
				CCstack[curCC] = 10; // go to 10 (JAIL)
			numCCmov++;
		}
	}

	// shuffling CH stack
	int curCH, numCHmov = 0;
	while (true)
	{
		if (numCHmov == 10)	// there are only 10 movement cards in CH stack
			break;

		curCH = rand() % stackSize;
		if (CHstack[curCH] == -1)
		{
			switch (numCHmov) {
			case 0:
				CHstack[curCH] = 0; // go to 00 (GO)
				break;
			case 1:
				CHstack[curCH] = 10; // go to 10 (JAIL)
				break;
			case 2:
				CHstack[curCH] = 11; // go to 11 (C1)
				break;
			case 3:
				CHstack[curCH] = 24; // go to 24 (E3)
				break;
			case 4:
				CHstack[curCH] = 39; // go to 39 (H2)
				break;
			case 5:
				CHstack[curCH] = 5; // go to 05 (R1)
				break;
			case 6:
				CHstack[curCH] = 35; // go to 05, 15, 25, or 35 (next R)
				break;
			case 7:
				CHstack[curCH] = 35; // go to 05, 15, 25, or 35 (next R)
				break;
			case 8:
				CHstack[curCH] = 12; // go to 12 or 28 (next U)
				break;
			case 9:
				CHstack[curCH] = -3; // go back 3 squares
				break;
			}
			numCHmov++;
		}
	}

	cout << "Dice rolling simulation..." << endl;

	// simulation
	int aDiceOutput;
	bool isDouble;
	for (int i = 0; i < numRolls; i++)
	{
		diceRollSum = 0;
		aDiceOutput = 0;
		int newDiceOutput = aDiceOutput = rand() % diceSides + 1;
		isDouble = true;
		for (int j = 0; j < numDies; j++)
		{
			if (aDiceOutput != newDiceOutput)
				isDouble = false;
			diceRollSum += newDiceOutput;
			newDiceOutput = rand() % diceSides + 1;
		}
		if (isDouble)
			doubleCount++;
		else
			doubleCount = 0;	// reset

		curPos = (curPos + diceRollSum) % numSquares;

		if (doubleCount == 3)
		{
			curPos = 10;	// go to jail upon 3 consecutive double dice rolls
			statistics[curPos].second++;
			doubleCount = 0;
		}
		else if (curPos == 30)
			curPos = 10;	// go to jail
		else if (curPos == 7 || curPos == 22 || curPos == 36)	// landed on CH1, CH2, or CH3
		{
			if (CHstack[nextCHptr] != -1)	// movement card is drawn from CH stack
			{
				if (CHstack[nextCHptr] == -3)	// go back 3 squares
					curPos -= 3;
				else if (CHstack[nextCHptr] == 12)	// go to next U
					curPos = (curPos == 22) ? 28 : 12;
				else if (CHstack[nextCHptr] == 35)	// go to next R
				{
					if (curPos == 7)
						curPos = 15;
					else if (curPos == 22)
						curPos = 25;
					else
						curPos = 5;
				}
				else // go to assigned square number
					curPos = CHstack[nextCHptr];	
			}

			nextCHptr = (nextCHptr + 1 == stackSize) ? 0 : nextCHptr + 1;
		}
		
		// this separate condition check is to accommodate the special case of going back 3 squares from CH3 to CC3
		if (curPos == 2 || curPos == 17 || curPos == 33)	// landed on CC1, CC2, or CC3
		{
			if (CCstack[nextCCptr] == 0)	// go to 00 (GO) movement card is drawn from CC stack
				curPos = 0;
			else if (CCstack[nextCCptr] == 10)	// go to 10 (JAIL) movement card is drawn from CC stack
				curPos = 10;

			nextCCptr = (nextCCptr + 1 == stackSize) ? 0 : nextCCptr + 1;	// put drawn CC card to the bottom of the stack
		}
		statistics[curPos].second++;
	}

	cout << "Processing statistics..." << endl;

	// processing statistics for top 3 most visited squares
	struct {
		bool operator()(pair<int, int> a, pair<int, int> b)
		{
			return a.second > b.second;
		}
	} myCompare;
	sort(statistics.begin(), statistics.end(), myCompare);
	top1 = statistics[0].first;
	top2 = statistics[1].first;
	top3 = statistics[2].first;

	cout << "When " << numDies << " " << diceSides << "-sided dies are used, the six-digit modal string is " << setfill('0') << setw(2) << top1 << setfill('0') << setw(2) << top2 << setfill('0') << setw(2) << top3 << endl;
	//cout << "When " << numDies << " " << diceSides << "-sided dies are used, the six-digit modal string is " << top1 << " " << top2 << " " << top3 << endl;

	return 0;
}