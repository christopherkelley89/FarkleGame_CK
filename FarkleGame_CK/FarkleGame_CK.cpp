/*
*Christopher Kelley
*7-1 Final Project Submission: Dice Game
^ IT 312 
* Southern New Hampshire University
*/
// FarkleCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.


//#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

// The Dice Class for each player
// This class rolls the 6 dice at a time
class Dice
{
private:
	int diceValue[6];
	bool rerollDiceValue[6];
	int rollDieCount;
	int countForReRoll;
public:

	// The dice constructor!!
	Dice()
	{
		for (int i = 0; i < 6; i++)
		{
			diceValue[i] = 0;
			rerollDiceValue[i] = false;
		}
		countForReRoll = 0;
		rollDieCount = 0;
	}

	//RollThe Dice rolls the 6 dice using a random number generator 
	void rollTheDice()
	{
		for (int i = 0; i < 6; i++)
		{
			diceValue[i] = (rand() % 6 + 1);
			if (diceValue[i] != 1 && diceValue[i] != 5)
			{
				rerollDiceValue[i] = true;
			}
		}
	}

	//Re-rolls the non-point dice if the player wants to re-roll them
	void reRollTheDice()
	{
		for (int i = 0; i < 6; i++)
		{
			if (rerollDiceValue[i] == true)
				diceValue[i] = (rand() % 6 + 1);
		}
	}

	// to reset the rerollDiceValues to false
	void resetReRoll()
	{
		for (int i = 0; i < 6; i++)
		{
			rerollDiceValue[i] = false;
		}
	}

	// GetRoundScore gets the scores of the 6 dice and scores according to the farkle game rules 
	int getRoundScore()
	{
		int one_Count = 0, two_Count = 0, three_Count = 0, four_Count = 0, five_Count = 0, six_Count = 0;
		int score = 0;

		rollDieCount = 0;
		for (int i = 0; i < 6; i++)
		{
			switch (diceValue[i])
			{
			case 1:
				score += 100;
				one_Count++;
				break;
			case 2:
				two_Count++;
				rollDieCount++;

				break;
			case 3:
				three_Count++;
				rollDieCount++;

				break;
			case 4:
				four_Count++;
				rollDieCount++;

				break;
			case 5:
				score += 50;
				five_Count++;
				break;
			case 6:
				six_Count++;
				rollDieCount++;

				break;
			}
		}
		if (rollDieCount == 6)
		{
			cout << "Farkle!";
			score = 0;
		}
		else
		{
			if (one_Count >= 3)
			{
				score = (score - 300) + 1000;
			}
			else if (two_Count >= 3)
			{
				score += 200;
				for (int i = 0; i < 6; i++)
				{
					if (diceValue[i] == 2)
					{
						rerollDiceValue[i] = false;
					}
				}
				rollDieCount -= 3;
			}
			else if (three_Count >= 3)
			{
				score += 300;
				for (int i = 0; i < 6; i++)
				{
					if (diceValue[i] == 3)
					{
						rerollDiceValue[i] = false;
					}
				}
				rollDieCount -= 3;
			}
			else if (four_Count >= 3)
			{
				score += 400;
				for (int i = 0; i < 6; i++)
				{
					if (diceValue[i] == 4)
					{
						rerollDiceValue[i] = false;
					}
				}
				rollDieCount -= 3;
			}
			else if (five_Count >= 3)
			{
				score = (score - 150) + 500;
			}
			else if (six_Count >= 3)
			{
				score += 600;
				for (int i = 0; i < 6; i++)
				{
					if (diceValue[i] == 6)
					{
						rerollDiceValue[i] = false;
					}
				}
				rollDieCount -= 3;
			}
		}
		return score;
	}

	//displays the 6 dice rolls/values
	void displayDice()
	{
		for (int i = 0; i < 6; i++)
		{
			cout << diceValue[i] << " ";
		}
	}

	// Gets the rollDieCount
	int getRollDieCount()
	{
		return rollDieCount;
	}

	//sets the rollDieCount
	void setRollDieCount(int value)
	{
		rollDieCount = value;
	}
};

// Player class to hold the each round score and over
// all score
class Player
{
private:
	string name;
	int score;
	int totalScore;
public:

	// Player constructor
	Player()
	{
		name = "XXXXXX";
		score = 0;
		totalScore = 0;
	}

	// parameterized constructor
	// it accepts a specific number of parameters

	// Testing Below 
	/*
	Player(string name, int score, int totalScore)
	 {
		this->name = name;
		this->score = score;
		this->totalScore = totalScore;
	}
	*/

	Player(string name)
	{
		this->name = name;
		score = 0;
		totalScore = 0;
	}

	// Sets the Player Name
	void setName(string name)
	{
		this->name = name;
	}

	//Get Name from Player
	string getName()
	{
		return this->name;
	}

	// Adds score to the total roundscore
	void addScore(int roundscore)
	{
		score = roundscore;
		totalScore += roundscore;
	}

	// to set the score
	void setScore(int score)
	{
		this->score = score;
	}

	// Grabs total score 
	int getTotalScore()
	{
		return totalScore;
	}

	// Get's score after completion of each round
	int getScore()
	{
		return score;
	}
};


// FarkleGame class which holds all the player names
// Initializes the game, declares a winner and gets round status 
class FarkleGame
{
private:

	Player* players;
	int countPlayers;
	Dice dice;
public:

	// parameterized constructor
	FarkleGame(int numPlayers)
	{
		players = new Player[numPlayers];
		countPlayers = numPlayers;
	}

	//Reads the names of the players
	void readNamesOfPlayers()
	{
		string name;
		for (int i = 0; i < countPlayers; i++)
		{
			cout << "Enter the name of player " << (i + 1) << ": ";
			cin >> name;
			players[i].setName(name);
		}
	}

	// Rolls the dice for each player until the player scores 1000 or more points
	void playersToEnterGame()
	{
		int score = 0;
		for (int i = 0; i < countPlayers; i++)
		{
			score = 0;
			while (score < 1000)
			{
				dice.rollTheDice();
				dice.displayDice();
				score = dice.getRoundScore();
				cout << "\t Points Scored: " << score << endl;
			}
			players[i].addScore(score);
			cout << players[i].getName() << " enters the game!" << endl << endl;
		}
		dice.setRollDieCount(0);
		cout << "All players entered the game. Let's begin the game!" << endl << endl;
	}


	//This will check whether any player has reached 10000 or more points and Gets the index of the winner and declares winner
	bool winsTheGame(int* index)
	{
		for (int i = 0; i < countPlayers; i++)
		{
			if (players[i].getTotalScore() >= 10000)
			{
				*index = i;
				return true;
			}
		}
		return false;
	}


	//Plays each round for Farkle Players
	void eachPlayerGame(int i)
	{
		char wouldLikeToReRoll;
		int score = 0;
		cout << players[i].getName() << " roll's the dice: " << endl;
		dice.rollTheDice();
		dice.displayDice();
		score = dice.getRoundScore();
		cout << "\t Points Scored: " << score << endl;
		players[i].setScore(score);
		if (dice.getRollDieCount() == 0)
		{
			cout << "Point-dice scoring! You have got a chance to play one more round again!" << endl;
			players[i].addScore(score);
			dice.reRollTheDice();
			dice.displayDice();
			score += dice.getRoundScore();
			cout << "\t Points Scored: " << score << endl << endl;
			players[i].setScore(score);
		}
		else if (dice.getRollDieCount() != 6)
		{
			cout << endl << "Would you like to reroll the " << dice.getRollDieCount()
				<< " non-point dice? (Y/N): ";
			cin >> wouldLikeToReRoll;
			cout << endl;
			if (wouldLikeToReRoll == 'y' || wouldLikeToReRoll == 'Y')
			{
				dice.reRollTheDice();
				dice.displayDice();
				score = dice.getRoundScore();
				cout << "\t Points Scored: " << score << endl << endl;
				if (players[i].getScore() > score)
					score = players[i].getScore();
				players[i].setScore(score);
			}
			else if (wouldLikeToReRoll == 'n' || wouldLikeToReRoll == 'N')
			{
				cout << players[i].getName() << " turn is over..." << endl << endl;
				dice.setRollDieCount(0);
			}
		}

		dice.resetReRoll();
		cout << players[i].getName() << " your score from that round: " << players[i].getScore() << endl;
		players[i].addScore(score);

		cout << "Your total score after the round: " << players[i].getTotalScore() << endl << endl;
		cout << endl << "============================================"
			<< "============================" << endl << endl;
	}

	// to play the game for multiple players
	void playEachRound(int index)
	{
		for (int i = index; i < countPlayers; i++)
		{
			eachPlayerGame(i);
		}
	}

	// to begin the game and display the winner strategy
	void playTheGame()
	{
		int index = 0;
		while (!winsTheGame(&index))
		{
			playEachRound(0);
		}
		int i = 0;
		int count = 0;

		for (i = index + 1; i < countPlayers; i++)
		{
			eachPlayerGame(i);
			count++;
		}
		if (count != countPlayers - 1)
		{
			for (i = 0; i < index; i++)
				eachPlayerGame(i);
		}

		int max = 0;

		// logic to check for the winner
		for (int i = 0; i < countPlayers; i++)
		{
			if (players[i].getTotalScore() > max)
			{
				max = players[i].getTotalScore();
				index = i;
			}
		}

		// displays the winner
		cout << endl << "Winner Winner... Chicken Dinner!!!" << endl;
		cout << endl << "The winner is " << players[index].getName() << " with " << players[index].getTotalScore() << " points!" << endl;

	}
};

// to display the rules from the text file
void displayRules()
{
	string lineInFile;
	ifstream inputfile;
	inputfile.open("Farkle_Rules.txt");
	while (getline(inputfile, lineInFile))
	{
		cout << lineInFile << '\n';
	}
	inputfile.close();
}

// main function
int main(string* players[])
{
	srand(time(0));
	int numPlayers;

	// display the rules
	displayRules();
	cout << endl << "*************************************************" << "******************************" << endl << endl;
	cout << endl << "\t\t=====  Let the game Begin!!! =====" << endl << endl;

	// prompt the user for number of players are participating in the game
	cout << endl << endl << "Number of players would like to play the game? ";
	cin >> numPlayers;
	while (numPlayers < 2)
	{
		cin.clear();
		cin.ignore();
		cout << "Please enter a number" << endl;
		cin >> numPlayers;
	}

	// create an object for FarkleGame class
	FarkleGame fg(numPlayers);

	// call the method readNamesOfPlayers() to read names of the players
	fg.readNamesOfPlayers();

	// call the method playersToEnterGame() to make the each player score 1000 points
	fg.playersToEnterGame();

	// call the method playTheGame() to start the game
	fg.playTheGame();
	system("PAUSE");
	return 0;
}