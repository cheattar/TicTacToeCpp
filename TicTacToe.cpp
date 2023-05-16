// TicTacToe.cpp: definiuje punkt wejścia dla aplikacji.
//

// TODO: Fix bug, when inputing an blank input the 'game' frezzes.

#include "TicTacToe.h"

using namespace std;

/* False, 0: Naught
   True,  1: Cross
   2: Empty
   3: Error
*/

int playerToInt(bool b) {
    switch (b) { 
    case false:
        return 0;
    case true:
        return 1;
    default:
        return 3;
    }    
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

int main() {
    vector<vector<int>> board{ {2,2,2},
                               {2,2,2},
                               {2,2,2} 
                                       };
    bool player = false; // false == naught
                         // true  == cross
    int turns = 0;
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
            case 'A':
                if (board[0][extractInt(input)] == 2) { board[0][extractInt(input)] = playerToInt(player); break; }
                else { cout << "This row is already filled out!\n"; goto start; }
            case 'B':
                if (board[1][extractInt(input)] == 2) { board[1][extractInt(input)] = playerToInt(player); break; }
                else { cout << "This row is already filled out!\n"; goto start; }
            case 'C':
                if (board[2][extractInt(input)] == 2) { board[2][extractInt(input)] = playerToInt(player); break; }
                else { cout << "This row is already filled out!\n"; goto start; }
            default:
                cout << "Please enter a correct row or columb input!\n"; goto start;
            }
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
