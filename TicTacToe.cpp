// TicTacToe.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "TicTacToe.h"

using namespace std;

/* False, 0: Naught
   True,  1: Cross
   2: Empty
   3: Error
*/

int playerToInt(bool b) {
    if (b == true) { return 1; }
    else { return 0; }
}

int extractInt(string str) {
    int i = str[1] - '0';
    if (i <= 0) { return 3; }
    if (i >= 4) { return 3; }
    else { return i - 1; }
}

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
	if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 2) {
			return board[0][0];
		}
    if(board[2][0] == board[1][1] && board[1][1] ==  board[0][2] && board[2][0] != 2) {
			return board[2][0];
		}

    else {
        return 2;
    }
}

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
    vector<vector<int>> board{ {2,2,2},
                               {2,2,2},
                               {2,2,2} 
                                       };
    bool player = false; // false == naught
                         // true  == cross
    int turns = 0;
    cout << "Tic Tac Toe!\nInput your your position using A to C for columns, and 1 to 3 for rows.\n";
    while (true) {
        start:
        printBoard(board);

        string input, playerInpStr;
        
        if (player == false) { playerInpStr = " Naught "; }
        else { playerInpStr = " Cross "; }

        cout << "Please enter your move." << playerInpStr << "is playing.\n? "; cin >> input;
        
        if (extractInt(input) == 3) {
            cout << "Please enter a correct row number!\n";
        }
        else {
            switch (input[0]) {
            case 'a':
            case 'A':
                if (board[0][extractInt(input)] == 2) { board[0][extractInt(input)] = playerToInt(player); break; }
                else { cout << "This row is already filled out!\n"; goto start; }
            case 'b':
            case 'B':
                if (board[1][extractInt(input)] == 2) { board[1][extractInt(input)] = playerToInt(player); break; }
                else { cout << "This row is already filled out!\n"; goto start; }
            case 'c':
            case 'C':
                if (board[2][extractInt(input)] == 2) { board[2][extractInt(input)] = playerToInt(player); break; }
                else { cout << "This row is already filled out!\n"; goto start; }
            default:
                cout << "Please enter a correct row or columb input!\n"; goto start;
            }

            switch (checkIfWon(board)) {
            case 0:
                cout << "Naught won the game in " << turns << " turns.\n"; return 0;

            case 1:
                cout << "Cross won the game in " << turns << " turns.\n"; return 0;
            case 2:
                goto addTurn;
            /*default:
                continue;*/ 
            }
            switch (checkIfTie(board)) {
            case true:
                cout << "The game was tied in " << turns << " turns.\n"; return 0;
            case false:
                goto addTurn;
            }
            addTurn:
            if (turns % 2 == 0) {
                player = true;
            }
            else {
                player = false;
            }
            turns++;
        }
    }	
	return 0;
}
