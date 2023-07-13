/* Program Name: Bowling
 * Student Name: Parker Haney
 * Net ID: phaney
 * Student ID: 000542681
 * Program Description: This program allows the user enter in players names
 * and theyre scores for each frame/roll for a bowling game. Once all the 
 * players have been entered, the program will calculate each players total score,
 * print it out, end list the worst and best player as well.
 * */

#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector <string> playerNames;
	vector <int> playerScores;

	//This is the while loop that executes the bowling score collection while players are still being entered
	while(true) {

		//This first block creates some vectors that we use to calculate each score.
		//This block also prompts for player names and breaks once "done" is enetered. 
		int rollInput;
		const int totalRolls = 21;
		vector <int> rolls(totalRolls, 0);
		string name;
		int rollIndex;
		cout << "Enter player's name (done for no more players): ";
		cin >> name;
		if (name == "done") {
			cout << endl;
			break;
		}

		// This is else statement is what executes when a name is enetered.
		// It goes through and prompts the user for their individual score for each
		// frame/roll, which depends on the socre of the current roll/rolls.
		else {
			playerNames.push_back(name);
			
			// This inner/outer for loop prompts for the first 20 rolls, with a condition checking for strikes to skip rolls.
			for (int i = 0; i < 10; i++) { 
				for (int o = 0; o < 2; o++) {
					cout << "Enter score for frame " << (i + 1) << ", roll " << (o + 1) << ": ";
					cin >> rollInput;
					rollIndex = (i * 2) + o;
					rolls[rollIndex] = rollInput;
					if (rollInput == 10 && o == 0) {
						if (i != 9) {
							rolls.push_back(0);
							o++;
						}
					}
				}	
			} 

			// This if/else statement prompts for the 3rd roll of the 10th frame, if it is required.
			if (rolls[18] == 10) {
				cout << "Enter score for frame 10, roll 3: ";
				cin >> rollInput;
				rolls[20] = rollInput;
			}
			else { 
				if (rolls[18] + rolls[19] == 10) {
					cout << "Enter score for frame 10, roll 3: ";
					cin >> rollInput;
					rolls[20] = rollInput;
				}
			}
		}
			
			// This segment below declares numerous variables that refer to rolls, frames, next rolls and next frames 
			// that are used in the process of counting the score, giving them names saves space and time when typing. 
			int roundScore = 0;
			for (int f = 0; f < 10; f++) {
				const int currentf = f * 2;
				const int nextf = currentf + 2;
				const int nextnextf = nextf + 2;

				int roll1 = rolls[currentf];
				int roll2 = rolls[currentf + 1];
				int nroll1 = rolls[nextf];
				int nroll2 = rolls[nextf + 1];
				int nnroll1 = rolls[nextf + 2];
				
				// These outer if/else statements are each for specific cases of scoring.
				// This first if statement tests for a double strike, and then inside that it tests
				// to see if it is an edge case or not.
				if (roll1 == 10 && rolls[currentf + 2] == 10) {
					if (f < 8) {
						roundScore += roll1 + nroll1 + nnroll1;
					}
					else if (f == 8) {
						roundScore += roll1 + nroll1 + nroll2;
					}
					else if (f == 9) {
						roundScore += roll1 + roll2 + rolls[currentf + 2]; 
					}
				}
				
				// This else if statement tests for a regular strike and adds itself and the next two rolls to the score
				// This has an imbedded if/else statement to make calculation of the strike easier depending 
				// on if its the last frame or not.
				else if (roll1 == 10 && nroll1 != 10) {
					if (f != 9) {
						roundScore += roll1 + nroll1 + nroll2;
					}
					else {
						roundScore += roll1 + roll2 + rolls[currentf + 2];
					}
				}

				// This else if statement tests for a spare, and adds the calculation to the score.
				// A spare is independent from the frame number, which is why we dont need an imbedded if statement.
				else if (roll1 + roll2 == 10) {
						roundScore += roll1 + roll2 + rolls[currentf + 2];
				}

				// The lest else in this string of statements is for just a regular frame of bowling,
				// no strikes, double strikes, or spares.
				// This is also independent of frame number.
				else {
					roundScore += roll1 + roll2;
				}
			}

			playerScores.push_back(roundScore); //This is the vector where the scores are saved, the scores and names have the same index for organization.
	}

	// Quits the program if no players are entered.
	if (playerNames.size() == 0) {
		cout << "No players were entered." << endl;
		return 0;
	}

	// This prints out each players name and their score before showing the best and worst scores.
	for (int i = 0; i < playerNames.size(); i++) {
		cout << playerNames[i] << " scored " << playerScores[i] << "." << endl;
	}
		
	int worstScore = playerScores[0];
	int bestScore = playerScores[0];
	string worstPlayer = playerNames[0];
	string bestPlayer = playerNames[0];
			
	// This for loop will cycle through the playerScores and playerNames vectors, and will compare each score
	// to the previous one using "greater than" or "less than" to find the lowest and highest number 
	// stored in the playerScores vector.
	for (int i = 1; i < playerNames.size(); i++) {
		if (playerScores[i] > bestScore) {
			bestScore = playerScores[i];
			bestPlayer = playerNames[i];
		}
		if (playerScores[i] < worstScore) {
			worstScore = playerScores[i];
			worstPlayer = playerNames[i];
		}
	}

	// This uses the variables created above and prints out the worst and best players and their scores.
	cout << worstPlayer << " did the worst by scoring " << worstScore << "." << endl;
	cout << bestPlayer << " won the game by scoring " << bestScore << "." << endl;
}

