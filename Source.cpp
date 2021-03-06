#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Sudoku.h"
#include "SudokuSolver.h"

/*
 * Enter sudoku need to solve to input.txt
 * results -> output.txt file
 */
void solve(Sudoku& sudoku)
{
    ofstream outputFile("output.txt", fstream::out);
    SudokuSolver::solve(sudoku, 2000);
    cout.rdbuf(outputFile.rdbuf());
    cout << sudoku;
}

void minify(Sudoku& sudoku)
{
    //ofstream outputFile("output.txt", fstream::out);
    int count = SudokuSolver::solve(sudoku, 2);
    if (count == 0)
    {
        throw runtime_error("Can't solve this sudoku board");
    }
    if (count != 1)
    {
        sudoku.saveResult();
    }
    int size = Sudoku::SQUARE_LENGTH * Sudoku::SQUARE_LENGTH;

    int positions[Sudoku::SQUARE_LENGTH * Sudoku::SQUARE_LENGTH];
    for (auto i = size - 1; i >= 0; --i)
    {
        positions[i] = i;
    }

    // mixed position in array
    for (auto i = size - 1; i >= 0; --i)
    {
        int j = rand() % size;
        int tmp = positions[i];
        positions[i] = positions[j];
        positions[j] = tmp;
    }

    // remove a position if new board have 1 result
    for (auto i = size - 1; i >= 0; --i)
    {
        int j = positions[i];
        int val = sudoku.at(j);
        if (val == 0)
        {
            continue;
        }
        sudoku.at(j) = 0;
        if (SudokuSolver::solve(sudoku, 2) > 1)
        {
            sudoku.at(j) = val;
        }
    }
    SudokuSolver::solve(sudoku);
    cout << sudoku;
}

int main()
{
    srand(time(NULL));
    ifstream inputFile("input.txt", fstream::in);
    Sudoku sudoku(&inputFile);
    //solve(sudoku);
    minify(sudoku);
    system("pause");
    return 0;
}
