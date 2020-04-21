//
//  main.cpp
//  MATH 214 Capstone
//

#include <algorithm>
#include <iostream>

using namespace std;
  
struct Move {
    int row, col;
};

//Here, X is a maximizer and O is a minimizer
char player1 = 'X', player2 = 'O';

bool whoseMove;

/* This function returns true if there are moves
remaining on the board */
bool movesRemain(char board[3][3]) {
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_')
                return true;
    return false;
}
  
//Function that checks who is winning based on the board
//High value returned if maximizer's turn, else low value for minimizer
int evaluate(char board[3][3]) {
    // checking for rows for X or O victory.
    for (int row = 0; row<3; row++) {
        if (board[row][0]==board[row][1] &&
            board[row][1]==board[row][2]) {
            if (board[row][0]==player1)
                return +10;
            else if (board[row][0]==player2)
                return -10;
        }
    }
  
    // checking for columns for X or O victory.
    for (int col = 0; col<3; col++) {
        if (board[0][col]==board[1][col] &&
            board[1][col]==board[2][col]) {
            if (board[0][col]==player1)
                return +10;
  
            else if (board[0][col]==player2)
                return -10;
        }
    }
  
    // checking for diagonals for X or O victory.
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2]) {
        if (board[0][0]==player1)
            return +10;
        else if (board[0][0]==player2)
            return -10;
    }
  
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0]) {
        if (board[0][2]==player1)
            return +10;
        else if (board[0][2]==player2)
            return -10;
    }
  
    // else if none of them have won then return 0
    return 0;
}
  
/* This minimax function considers all the
   possible ways the game can go and returns
   the value of the board */
int minimax(int depth, char board[3][3], bool isMax) {
    int score = evaluate(board);
    // If maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;
  
    // If minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;
  
    // If there are no more moves and no winner then
    // it is a tie
    if (movesRemain(board)==false)
        return 0;
  
    // If this maximizer's move
    if (isMax) {
        int best = -1000;
        // Traverse all cells
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                // Check if cell is empty
                if (board[i][j]=='_') {
                    // Make the move
                    board[i][j] = player1;
  
                    // Call minimax recursively and choose the maximum value
                    // This recursive call applies the minimax algorithm for best move to make
                    best = max(best,
                        minimax(depth + 1, board, !isMax));
  
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
  
    // if this minimizer's move
    else {
        int best = 1000;
        // traverse all cells
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                // Check if cell is empty
                if (board[i][j]=='_') {
                    // Make the move
                    board[i][j] = player2;
  
                    // Call minimax recursively and choose
                    // the minimum value
                    best = min(best,
                           minimax(depth + 1, board, !isMax));
  
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}
  
// This will return the best possible move for the player
Move findBestMove(char board[3][3]) {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
  
    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i<3; i++) {
        for (int j = 0; j<3; j++) {
            // Check if cell is empty
            if (board[i][j]=='_') {
                // Make the move
                board[i][j] = player1;
  
                // compute evaluation function for this
                // move.
                int moveVal = minimax(0, board, false);
  
                // Undo the move
                board[i][j] = '_';
  
                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal) {
                    bestMove.row = i + 1;
                    bestMove.col = j + 1;
                    bestVal = moveVal;
                }
            }
        }
    }
  
    printf("The value of the best Move is : %d\n\n",
            bestVal);
  
    return bestMove;
}
  
// Driver code
int main() {
    char board[3][3] =
    {
        { 'X', 'X', '_' },
        { 'O', 'O', 'X' },
        { '_', 'O', '_' }
    };
  
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j != 2) {
                cout << "|";
            }
            else {
                cout << "\n";
            }
        }
        if (i != 2) {
            cout << "-+-+-\n";
        }
    }
    cout << endl << "The character '_' signifies moves that can still\nbe made on the board" <<
    endl << endl;
    Move bestMove = findBestMove(board);
    cout << "The optimal move is:\n";
    cout << "ROW: " << bestMove.row << " COL: " << bestMove.col << '\n';
    return 0;
}
