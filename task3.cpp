#include <iostream>
using namespace std;

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Check if 'num' is valid in the given row
bool isRowSafe(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return false;
    return true;
}

// Check if 'num' is valid in the given column
bool isColSafe(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return false;
    return true;
}

// Check if 'num' is valid in the 3x3 box
bool isBoxSafe(int grid[N][N], int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + startRow][col + startCol] == num)
                return false;
    return true;
}

// Check if it's safe to place 'num' at grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    return isRowSafe(grid, row, num) &&
           isColSafe(grid, col, num) &&
           isBoxSafe(grid, row - row % 3, col - col % 3, num);
}

// Find the next empty cell (returns true if found)
bool findEmptyLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

// Backtracking Sudoku solver
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If no empty cell remains, puzzle is solved
    if (!findEmptyLocation(grid, row, col))
        return true;

    // Try numbers 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;  // Place number

            // Recursive call
            if (solveSudoku(grid))
                return true;

            grid[row][col] = 0; // Undo and backtrack
        }
    }

    return false; // Trigger backtracking
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku Solved Successfully!\n\n";
        printGrid(grid);
    } else {
        cout << "No solution exists\n";
    }

    return 0;
}

