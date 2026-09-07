#include <gtest/gtest.h>
#include <vector>
#include "../../../Cpp/SudokuCpp-LeetCode_37/Solution.h"

/*
 * Google Unit tests for `solveSudoku` method in `SudokuCpp-LeetCode_37`.
 *
 */

class SudokuTest : public ::testing::Test {
protected:
    std::vector<std::vector<char>> initial;
    std::vector<std::vector<char>> expected;

    void SetUp() override {
        initial = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        };
        expected = {
            {'5','3','4','6','7','8','9','1','2'},
            {'6','7','2','1','9','5','3','4','8'},
            {'1','9','8','3','4','2','5','6','7'},
            {'8','5','9','7','6','1','4','2','3'},
            {'4','2','6','8','5','3','7','9','1'},
            {'7','1','3','9','2','4','8','5','6'},
            {'9','6','1','5','3','7','2','8','4'},
            {'2','8','7','4','1','9','6','3','5'},
            {'3','4','5','2','8','6','1','7','9'}
        };
    }
};

TEST_F(SudokuTest, SolveSudoku1) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku1(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, SolveSudoku2) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku2(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, SolveSudoku3) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku3(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, SolveSudoku4) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku4(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, SolveSudoku5) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku5(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, SolveSudoku6) {
	Solution solver;
	// copy board (separate instance)
	auto board = initial;                 // copy so each test starts fresh
	solver.solveSudoku6(board);
	EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, SolveSudoku7) {
	Solution solver;
	// copy board (separate instance)
	auto board = initial;                 // copy so each test starts fresh
	solver.solveSudoku7(board);
	EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, SolveSudoku8) {
	Solution solver;
	// copy board (separate instance)
	auto board = initial;                 // copy so each test starts fresh
	solver.solveSudoku8(board);
	EXPECT_EQ(board, expected);
}