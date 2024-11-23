#include <iostream>
#include <vector>

using namespace std;

void printSolution(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
    // Check the current row on the left side
    for (int i = 0; i < col; i++) {
        if (board[row][i] == 1)
            return false;
    }

    // Check the upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1)
            return false;
    }

    // Check the lower diagonal on the left side
    for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

bool solveNQueensUtil(vector<vector<int>>& board, int col, int N) {

    if (col >= N) {
        return true;
    }

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            // Place this queen in board[i][col]
            board[i][col] = 1;

            // Recur to place rest of the queens
            if (solveNQueensUtil(board, col + 1, N)) {
                return true;
            }

            // If placing the queen in board[i][col] doesn't lead to a solution,
            // then backtrack and remove the queen from board[i][col]
            board[i][col] = 0;
        }
    }

    return false;
}

bool solveNQueens(int N) {
    vector<vector<int>> board(N, vector<int>(N, 0)); // Initialize the board with all 0s

    if (!solveNQueensUtil(board, 0, N)) {
        cout << "Solution does not exist." << endl;
        return false;
    }

    printSolution(board, N);
    return true;
}

int main() {
    int N;
    cout << "Enter the size of the chessboard (N): ";
    cin >> N;

    solveNQueens(N);

    return 0;
}

