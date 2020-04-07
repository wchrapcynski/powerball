#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes
int randomNumber(int);
void checkAutoUserWhiteDup(int array[][9], int rows);
void checkAutoWinningWhiteDup(int array[]);
bool checkUserWhiteDup(int array[][9], int rows);
int powerplay();
void sortUserWhite(int array[][9], int rows);
void sortWinningWhite(int array[6]);
void FindWinningtickets(int array[][9], int rows);
void calculateWinnings(int array[][9], int rows, float &winnings, int powerPlay);
void showTickets(int array[][9], int rows);

// main program
int main() {
	unsigned short int seed = time(0);
	srand(seed);
	
	// Set to 1 for debugging mode. Winning number is set to 1 2 3 4 5 6 and the end of the program outputs tickets with winning tally count.
	int debuggingMode = 0;
	
	// Show welcome message and rules
	cout << "Welcome to the Powerball Lottery Game!\n";
	cout << "Please read the rules before playing:\n";
	cout << "1. Select your game mode: auto-pick or self-pick\n";
	cout << "2. Choose how many tickets that you'd like to buy\n";
	cout << "3. Randomize/input 5 while ball numbers (1-69)\n";
	cout << "4. Randomize/input 1 red ball number (1-26)\n";
	cout << "5. See if any of your tickets match the winning numbers!\n\n";
	cout << "Get ready to see if you have hit the jackpot of $999 Million Dollars!\n\n";

	cout << "Choose A or B:\n";
	cout << "A: Let Auto-Pick choose your numbers\n";
	cout << "B: Pick your own numbers\n";
	
	// Checks to see if user input a correct menu choice
	char selfOrAuto;
	bool badInput = false;
	do {		
		selfOrAuto = cin.get();
		if (selfOrAuto == 'a' || selfOrAuto == 'A' || selfOrAuto == 'b' || selfOrAuto == 'B') {
			cin.ignore();
			badInput = false;
		} else {
			cin.ignore();
			cout << "You must choose A or B\n";
			badInput = true;
		}
	} while (badInput == true);	
	
	int tickets;
	int multiplier;
	int userNumbers[100][9];
	
	// Program area where ticket numbers are chosen
	switch(selfOrAuto) {
		case 'a':
		case 'A':
			
			// Asks user how many tickets they're going to purchase
			do {
				cout << "How many tickets do you want to purchase? (Maximum is 100): ";
				cin >> tickets;
				if (tickets > 100 || tickets <=0) {
					cout << "You must choose between 1 and 100 tickets.\n";
					cin.clear();
					cin.ignore(); 
				}		
			} while (tickets > 100 || tickets <=0);
			
			// Asks if user wants Powerplay
			multiplier = powerplay();
			
			/* Generates five random numbers between 1-60 and puts them in the first set of elements (white balls) in a row userNumbers 
			with tickets being the maximum number of rows. */
			for (int h = 0; h < tickets; h++) {
				for (int i = 0; i < 5; i++) {
					userNumbers[h][i] = randomNumber(60);		
				}		
			}
			/* Generates one random number betwen 1-26 and puts it in the 6th column (red ball) of userNumbers
			with tickets being the maximum number of rows. */
			for (int h = 0; h < tickets; h++) {
				userNumbers[h][5] = randomNumber(26);
			}
			
			// Checks for duplicates
			checkAutoUserWhiteDup(userNumbers, tickets);
			
			// Sorts white balls for the users tickets
			sortUserWhite(userNumbers, tickets);
			
			// Sets [][6], [][7], [][8] to 0;
			for (int i = 0; i < tickets; i++) {
				userNumbers[i][6] = 0;
				userNumbers[i][7] = 0;
				userNumbers[i][8] = 0;
			}
			
			// Checks to see if the user wants to see their tickets before the drawing.
			showTickets(userNumbers, tickets);
			
			break;
		
		case 'b':

		case 'B':
			
				// Asks user how many tickets they're going to purchase
			do {
				cout << "How many tickets do you want to purchase? (Maximum is 100): ";
				cin >> tickets;
				if (tickets > 100 || tickets <=0) {
					cout << "You must choose between 1 and 100 tickets.\n";
					cin.clear();
					cin.ignore();
				}
			} while (tickets > 100 || tickets <=0);
			
			// Asks if user wants Powerplay
			multiplier = powerplay();
						
			// The user picks the numbers for their ticket(s)
			for (int i = 0; i < tickets; i++) {
				cout << "You will now choose your first five numbers (white balls) for ticket #" << i + 1 << " " << endl <<
				"Please pick five unique numbers from 1-60:\n";
				
				bool duplicates;
				do {
					for (int j = 0; j < 5; j++) {
						duplicates = false;
						bool badInput;
						do {
							cout << "Please select your number for White #" << j + 1 << " " << endl;
							cin >> userNumbers[i][j];
							if (userNumbers[i][j] < 1 || userNumbers[i][j] > 60) {
								badInput = true;
								cout << "You can only use numbers between 1 and 60.\n";
								cin.clear();
								cin.ignore();
							} else {
								badInput = false;
							}
						} while (badInput == true);
					}
					// Checks to see if there are any duplicates for the white balls ont the current ticket being filled out
					duplicates = checkUserWhiteDup(userNumbers, i);
				} while (duplicates == true);
			
				cout << "You will now pick the number for the red ball for ticket #" << i + 1 << " " << endl <<
				"Please pick a number bertween 1-26:\n";
				do {
					cin >> userNumbers[i][5];
					if (userNumbers[i][5] < 1 || userNumbers[i][5] > 26) {
						badInput = true;
						cout << "You can only use numbers between 1 and 26.\n";
						cin.clear();
						cin.ignore();
					} else {
						badInput = false;
					}
				} while (badInput == true);
			}
			
			// Sorts white balls for the users tickets
			sortUserWhite(userNumbers, tickets);
			
			// Sets [][6], [][7], [][8] to 0;
			for (int i = 0; i < tickets; i++) {
				userNumbers[i][6] = 0;
				userNumbers[i][7] = 0;
				userNumbers[i][8] = 0;
			}
			
			// Checks to see if the user wants to see their tickets before the drawing.
			showTickets(userNumbers, tickets);
			
			break;
		
		default:
			cout << "Invalid Input";
			break;
	}	
	
	// Draw white ball winning numbers
	int winningNumber[6];
	for (int i = 0; i < 5; i++) {
		winningNumber[i] = randomNumber(60);	
	}
	// Check to see if any of the whine balls picked are duplicates
	checkAutoWinningWhiteDup(winningNumber);
	// Draw red ball winning number
	winningNumber[5] = randomNumber(26);
	// Sort winning (white balls) numbers
	sortWinningWhite(winningNumber);
	
	// This manually sets the winning number to 1 2 3 4 5 6. This is for debugging various parts of the code. 
	// Debugging Mode needs to be set to 1 at the top of the main section.
		if (debuggingMode == 1) {
		for (int i = 0; i < 6; i++) {
			winningNumber[i] = i + 1;
		}
	}
	
	// Compare and tally numbers to determine winning tickets.
	// Number of white balls matches stored in userNumbers[][6] and red ball matches go in userNumbers[][7].
	// Compare white balls and tally matches
	for (int i = 0; i < tickets; i++) {
		for (int j = 0; j < 5 ; j++) {
			for (int k = 0; k < 5; k++) {
				if (userNumbers[i][j] == winningNumber[k]) {
					userNumbers[i][6] += 1;
				}
			}
		}
	}
	//Compare red balls and tally matches
	for (int i = 0; i < tickets; i++) {
		if (userNumbers[i][5] == winningNumber[5]) {
			userNumbers[i][7] += 1;
		}
	}
	
	// Print out winning number
	cout << "\nThe winning number is:\n";
	for (int i = 0; i < 6; i++) {
		cout << winningNumber[i] << " ";
	}
	cout << endl << endl;
	
	// Calculates what is a winning ticket and outputs them to the terminal and a file.
	FindWinningtickets(userNumbers, tickets);	
	
	// Calculates how much money the user has won
	float totalWinnings = 0;
	calculateWinnings(userNumbers, tickets, totalWinnings, multiplier);
	if (totalWinnings < 1000000) {
		cout << "\nYou have won a total of $" << fixed << setprecision(0) << totalWinnings << " dollar(s)!" << endl;
	} else {
		cout << "\nYou have won a total of " << showpoint << fixed << setprecision(1) << totalWinnings / 1000000 << " million dollars!" << endl;
	}
	
	cout << "\nThank you for playing!\n";

	// This is for printing out all of userNumbers after calculations to manually check for bugs.
	// Debugging Mode needs to be set to 1 at the top of the main section.
	if (debuggingMode == 1) {	
		for (int j = 0; j < tickets; j++) {
			cout << "Ticket #" << j + 1<< " - "; 
			for (int i = 0; i < 9; i++) {
			cout << userNumbers[j][i] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}

// Creates a random number between 1 and the max number passed in
int randomNumber(int maxNumber) {
	int number;
	number = rand() % maxNumber + 1;
	return number;
}

/* Checks to see if one of the randomly generated numbers (for the white balls) in a particular row are duplicates. 
If it is, another random number replaces it. */
void checkAutoUserWhiteDup(int array[][9], int rows) { 
	bool duplicates;
	for (int h = 0; h < rows; h++) {
		do {
			duplicates = false;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < i; j++) {
					if (array[h][i] == array[h][j]) {
						duplicates = true;
						array[h][i] = randomNumber(60);
					}
				}
			}
		} while (duplicates == true);
	}
}

/* Checks to see if one of the randomly generated numbers (for the white balls) for the winning numbers are duplicates. 
If it is, another random number replaces it. */
void checkAutoWinningWhiteDup(int array[]) { 
	bool duplicates = false;
	do {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < j; k++) {
				if (array[j] == array[k]) {
					duplicates = true;
					array[j] = randomNumber(60);
				} else {
					duplicates = false;
				}
			}
		}
	} while (duplicates == true);
}

// Checks the numbers the user picked to see if there are duplicates for the white balls
bool checkUserWhiteDup(int array[][9], int rows) {
	for (int h = 0; h < 5; h++) {
		for (int j = 0; j < h; j++) {
			if (array[rows][h] == array[rows][j]) {
				cout << "You have a duplicate number on this ticket. Please repick your numbers.\n";
				return true;
			}
		}
	}
	return false;
}

// Sorts the first five numbers (white balls) in each row for users tickets
void sortUserWhite(int array[][9], int rows) {
	for (int k = 0; k < rows; k++) {
		int temp;
		int minElement;
		for(int i = 0; i < 5 - 1; i++) {	
			minElement = i;
			for(int j = i + 1; j < 5; j++)
			{
				if(array[k][j] < array[k][minElement]) {
					minElement = j; 
				}
			}
			if (minElement != i) {
				temp = array[k][i];
				array[k][i] = array[k][minElement];
				array[k][minElement] = temp;
			}	
		}
	}
}

// Sorts the first five (white balls) for the winning numbers
void sortWinningWhite(int array[6]) {
	int temp;
	for(int i = 0; i < 5 - 1; i++) {		
		for(int j = i + 1; j < 5; j++) {
			if(array[i] > array[j]) {
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

/* This checks to see if any of the tickets have one and marks which of the 9 ways it has won. Also outputs winning numbers to a file.
0 - 0 matches and it's not a winning number.
1 - 0 white 1 red
2 - 1 white 1 red
3 - 2 white 1 red
4 - 3 white 0 red
5 - 3 white 1 red
6 - 4 white 0 red
7 - 4 white 1 red
8 - 5 white 0 red
9 - 5 white 1 red
*/
void FindWinningtickets(int array[][9], int rows){
	ofstream dataOutput;
	dataOutput.open("winning_numbers.txt");
	if (!dataOutput) {
		cout << "The output file can not be opened! No data will be recorded to file.\n\n";
	}
	for (int i = 0; i < rows; i++) {
		if (array[i][6] == 0 && array[i][7] == 1) {
			array[i][8] = 1;
		} else if (array[i][6] == 1 && array[i][7] == 1) {
			array[i][8] = 2;
		} else if (array[i][6] == 2 && array[i][7] == 1) {
			array[i][8] = 3;
		} else if (array[i][6] == 3 && array[i][7] == 0) {
			array[i][8] = 4;
		} else if (array[i][6] == 3 && array[i][7] == 1) {
			array[i][8] = 5;	
		} else if (array[i][6] == 4 && array[i][7] == 0) {
			array[i][8] = 6;	
		} else if (array[i][6] == 4 && array[i][7] == 1) {
			array[i][8] = 7;	
		} else if (array[i][6] == 5 && array[i][7] == 0) {
			array[i][8] = 8;	
		} else if (array[i][6] == 5 && array[i][7] == 1) {
			array[i][8] = 9;	
		} else {
			array[i][8] = 0;
		}
	}
	dataOutput << "These are your winning ticket numbers (if any):\n";
	cout << "These are your winning ticket numbers (if any):\n";
	for (int i = 0; i < rows; i++) {
		if (array[i][8] > 0) {
			for(int j = 0; j < 6; j++) {
				dataOutput << array[i][j] << " ";
				cout << array[i][j] << " ";
			}
			dataOutput << endl;
			cout << endl;
		}
	}
	dataOutput.close();
}

/* This calculates how much money the user has won based on userNumbers[][8]
1 - 2: $4
3 - 4: $7
5 - 6: $100
7: $50000
8: $1000000
9: Jackpot: $999000000
*/
void calculateWinnings(int array[][9], int rows, float &winnings, int powerPlay) {
	for (int i = 0; i < rows; i++) {
		if (array[i][8] == 1 || array[i][8] == 2) {
			winnings += 4 * powerPlay;
		} else if (array[i][8] == 3 || array[i][8] == 4) {
			winnings += 7 * powerPlay;
		} else if (array[i][8] == 5 || array[i][8] == 6) {
			winnings += 100 * powerPlay;
		} else if (array[i][8] == 7) {
			winnings += 50000 * powerPlay;
		} else if (array[i][8] == 8) {
			if (powerPlay == 10 || (powerPlay > 1 && powerPlay < 6)) {
				winnings += 2000000;
			} else {
				winnings += 1000000;
			}
		} else if (array[i][8] == 9) {
			winnings += 999000000;
		} 
	}
}

// Shows the users tickets
void showTickets(int array[][9], int rows) {
	cout << "\nWould you like to see your tickets before the winning number is drawn? Y or N: ";
	bool badInput = false;
	char showTickets;
	do {		
		cin >> showTickets;
		if (showTickets == 'y' || showTickets == 'Y') {
			cin.ignore();
			badInput = false;
			for (int j = 0; j < rows; j++) {
				cout << "Ticket #" << j + 1<< " - "; 
				for (int i = 0; i < 6; i++) {
				cout << array[j][i] << " ";
				}
			cout << endl;
			}
		} else if (showTickets == 'n' || showTickets == 'N') {
			badInput = false;
			break;
		} else {
			cin.ignore();
			cout << "You must choose Y for Yes or N for No.\n";
			badInput = true;
		}
	} while (badInput == true);	
}

// Asks if the user wants a multiple for their tickets
int powerplay() {
	bool badInput;
	int powerplayMulti;
	cout << "Choose the Powerplay multiplier you would like.\nThis can multiple how much money you can win!\nChoose 1(no multiplier), 2, 3, 4, 5 or 10: ";
	do {
		cin >> powerplayMulti;
		if (powerplayMulti < 1 || (powerplayMulti > 5 && powerplayMulti < 10) || powerplayMulti > 10 )  {
			badInput = true;
			cout << "You can only choose 1, 2, 3, 4, 5 or 10: ";
			cin.clear();
			cin.ignore();
		} else {
			badInput = false;
		}
	} while (badInput == true);
	return powerplayMulti;
}
