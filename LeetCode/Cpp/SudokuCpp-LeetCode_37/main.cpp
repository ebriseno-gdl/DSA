#include "Solution.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Helper function to print the board
static void printBoard(string prompt, const vector<vector<char>>& board)
{
    cout << prompt << " (" << board.size() << " rows) : \n";
    for (const auto& r : board) {
        for (char ch : r) cout << ch << ' ';
        cout << '\n';
    }
}

// Main function to run the Sudoku solver
int main()
{
	cout << "--- Sudoku Solver Problem - LeetCode 37 - Backtracking (C++) ---\n";

	// CRITICAL HACKERRANK C++ OPTIMIZATION: Deactivate standard I/O synchronization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    // Prompt for input n
    cout << "Enter the board (single line or multiple lines) and then send EOF (or press Enter to use default examples): \n";
    cout << "Note: On Windows console: press Ctrl+Z then Enter to send EOF \n";
    string inputLine;

	Solution solver;

    if (!getline(cin, inputLine)) return 0;

    if (!inputLine.empty() && inputLine.find_first_not_of(" \t\r\n") != string::npos)
    {
        // Paste the board (single line or multiple lines) and then send EOF.
        // On Windows console: press Ctrl+Z then Enter to send EOF.
        string input;
        input += inputLine;
        while (getline(cin, inputLine)) {
            if (!input.empty()) input.push_back('\n');
            input += inputLine;
        }

        vector<vector<char>> board;
        vector<char> row;
        int depth = 0;

        for (size_t i = 0; i < input.size(); ++i) {
            char c = input[i];
            if (c == '[') {
                ++depth;
            }
            else if (c == ']') {
                --depth;
                // when we close an inner array (depth goes from 2 -> 1), push collected row
                if (depth == 1 && !row.empty()) {
                    board.push_back(row);
                    row.clear();
                }
            }
            else if (c == '"') {
                size_t j = input.find('"', i + 1);
                if (j == string::npos) break;
                string token = input.substr(i + 1, j - (i + 1));
                // token for Sudoku input should be single char like "5" or "."
                if (!token.empty()) row.push_back(token[0]);
                else row.push_back(' ');
                i = j;
            }
        }

        if (board.empty()) {
            cerr << "Failed to parse board. Make sure the pasted text matches the format.\n";
            return 1;
        }

        // Print Input board
		printBoard("Input board", board);

		auto board1 = board; // copy board (separate instance)
		solver.solveSudoku1(board1);
        printBoard("Solved 1 board", board1);

		auto board2 = board; // copy board (separate instance)
        solver.solveSudoku2(board2);
        printBoard("Solved 2 board", board2);

        auto board3 = board; // copy board (separate instance)
        solver.solveSudoku3(board3);
        printBoard("Solved 3 board", board3);

        auto board4 = board; // copy board (separate instance)
        solver.solveSudoku4(board4);
        printBoard("Solved 4 board", board4);
        
        auto board5 = board; // copy board (separate instance)
        solver.solveSudoku5(board5);
        printBoard("Solved 5 board", board5);

        auto board6 = board; // copy board (separate instance)
        solver.solveSudoku6(board6);
        printBoard("Solved 6 board", board6);

        auto board7 = board; // copy board (separate instance)
        solver.solveSudoku7(board7);
        printBoard("Solved 7 board", board7);

        auto board8 = board; // copy board (separate instance)
        solver.solveSudoku8(board8);
        printBoard("Solved 8 board", board8);
    }
    else
    {
		// Default Examples
        
		// Example 1
		vector<vector<char>> boardA = {
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
        };
		printBoard("Input board A", boardA);

		auto boardA1 = boardA; // copy board (separate instance)
		solver.solveSudoku1(boardA1);
		printBoard("Solved 1 board A", boardA1);

		auto boardA2 = boardA; // copy board (separate instance)
        solver.solveSudoku2(boardA2);
        printBoard("Solved 2 board A", boardA2);

		auto boardA3 = boardA; // copy board (separate instance)
		solver.solveSudoku3(boardA3);
		printBoard("Solved 3 board A", boardA3);

        auto boardA4 = boardA; // copy board (separate instance)
        solver.solveSudoku4(boardA4);
        printBoard("Solved 4 board A", boardA4);

        auto boardA5 = boardA; // copy board (separate instance)
        solver.solveSudoku5(boardA5);
        printBoard("Solved 5 board A", boardA5);

        auto boardA6 = boardA; // copy board (separate instance)
        solver.solveSudoku6(boardA6);
        printBoard("Solved 6 board A", boardA6);

        auto boardA7 = boardA; // copy board (separate instance)
        solver.solveSudoku7(boardA7);
        printBoard("Solved 7 board A", boardA7);

        auto boardA8 = boardA; // copy board (separate instance)
        solver.solveSudoku8(boardA8);
        printBoard("Solved 8 board A", boardA8);
    }
    return 0;
}