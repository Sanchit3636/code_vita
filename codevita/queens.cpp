#include<bits/stdc++.h>
using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col){
    int N = board.size();

    // Check this column on the upper side
    for (int i = 0; i < row; i++) {
        if (board[i][col]) return false;
    }

    // Check the upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }

    // Check the upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) return false;
    }

    return true;
}

// Function to solve the N-Queens problem using backtracking
void solveNQueensUtil(vector<vector<int>>& board, int row){
    int N = board.size();

    // Base case: If all queens are placed
    if (row >= N) {
        // Print the board configuration when all queens are placed
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << (board[i][j] ? "Q " : ". ");
            }
            cout << endl;
        }
        cout << endl;
        return;
    }

    // Try placing a queen in each column of the current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;  // Place the queen
            solveNQueensUtil(board, row + 1);  // Recur to place the next queen
            board[row][col] = 0;  // Backtrack and remove the queen
        }
    }
}

int main(){
    int N;
    cin >> N;  // Input the size of the chessboard (N)

    vector<vector<int>> board(N, vector<int>(N, 0));  // Initialize the board with 0 (no queens)

    solveNQueensUtil(board, 0);  // Start solving from the first row

    return 0;
}
