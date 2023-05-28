#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

/* False, 0: Naught
   True,  1: Cross
   2: Empty
   3: Error
*/

// Copied from: https://stackoverflow.com/questions/6486289/how-can-i-clear-console/52895729#52895729
void clear() {
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

// Change boolean player to integer player. Pretty self-explanatory.
int playerToInt(bool b) {
    if (b == true) { return 1; }
    else { return 0; }
}

// Used to extract row position, from the input the player entered.
int extractInt(string str) {
    int i = str[1] - '0';
    if (i <= 0) { return 3; }
    if (i >= 4) { return 3; }
    else { return i - 1; }
}

// Print the board. This function is cursed and I don't wanna touch it.
void printBoard(vector<vector<int>> board) {
    cout << "+--1-2-3+ \n";
    vector<string> alfa = {"|A|","|B|","|C|"};
    vector<string> playerChar = {"O","X","-","?"};
    for (int i = 0; i < board.size(); i++)
    {
        cout << alfa[i];
        for (int j = 0; j < board[i].size(); j++)
        {
            cout << playerChar[board[i][j]] << "|";
            
        }
        cout << " ";
        cout << endl;
    }
    cout << "+-------+" << endl;
}

// Check if one of the players won. Returns the player number which won.
int checkIfWon(vector<vector<int>> board) {
    // Horizontal
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 2) {
            return board[i][0];
        } 
    }
    // Vertical
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 2) {
            return board[0][i];
        } 
    }

    // Diagonals
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 2) {
			return board[0][0];
		}
    if (board[2][0] == board[1][1] && board[1][1] ==  board[0][2] && board[2][0] != 2) {
			return board[2][0];
		}

    else {
        return 2;
    }
}

// Check if the game is tied.
bool checkIfTie(vector<vector<int>> board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 2) {
                    return false;
            }
        }
    }
    return true;
}

int main() {
    clear();
    vector<vector<int>> board{ {2,2,2},
                               {2,2,2},
                               {2,2,2} 
                                       };
    bool player = false; // false == naught
                         // true  == cross
    int turns = 0; // Actually this counter was only meant to change the player, but also when we finish we can also show in how many turns the game was completed.
    cout << "Tic Tac Toe!\nInput your your position using A to C for columns, and 1 to 3 for rows.\n";
    while (true) {
        start: // Goto's aren't the best idea when developing stuff in C++, 
               // but in this instance I couldn't be arsed to debug the switch statement below...
               // I mean it works ¯\_(ツ)_/¯
        printBoard(board);

        string input, playerInpStr;
        
        if (player == false) { playerInpStr = " Naught "; }
        else { playerInpStr = " Cross "; }

        cout << "Please enter your move." << playerInpStr << "is playing.\n? "; cin >> input;
        
        // If the row number the player inputted isn't in range (1 to 3), then we ask them a input a correct one.
        if (extractInt(input) == 3) {
            clear(); cout << "Please enter a correct row number!\n";
        }
        else {
            switch (input[0]) {
            case 'a':
            case 'A':
                if (board[0][extractInt(input)] == 2) { board[0][extractInt(input)] = playerToInt(player); break; }
                else { clear();  cout << "This row is already filled out!\n"; goto start; }
            case 'b':
            case 'B':
                if (board[1][extractInt(input)] == 2) { board[1][extractInt(input)] = playerToInt(player); break; }
                else { clear(); cout << "This row is already filled out!\n"; goto start; }
            case 'c':
            case 'C':
                if (board[2][extractInt(input)] == 2) { board[2][extractInt(input)] = playerToInt(player); break; }
                else { clear(); cout << "This row is already filled out!\n"; goto start; }
            default:
                clear(); cout << "Please enter a correct row and column input! Ex. A3, b1, etc...\n"; goto start;
            }
            
            // Check if we tied. This if statement used to be an switch, and for some reason it didn't work.
            // This seriously was a real PITA to debug lol
            if (checkIfTie(board) == true) {
                clear(); printBoard(board);
                cout << "The game was tied in " << turns << " turns.\n"; return 0;
            }
            
            // Check if we won, if not change player.
            switch (checkIfWon(board)) {
            case 0:
                clear(); printBoard(board);
                cout << "Naught won the game in " << turns << " turns.\n"; return 0;
            case 1:
                clear(); printBoard(board);
                cout << "Cross won the game in " << turns << " turns.\n"; return 0;
            case 2:
                goto addTurn;
            }
            
            addTurn:
            // Change player. Cross on an even turn, circle uneven. After that increment the turns counter.
            if (turns % 2 == 0) {
                player = true;
            }
            else {
                player = false;
            }
            turns++;
            clear();
        }
    }	
	return 0;
}
