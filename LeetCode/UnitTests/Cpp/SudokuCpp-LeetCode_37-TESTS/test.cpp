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

TEST_F(SudokuTest, solveSudoku1_JaggedNew) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku1_JaggedNew(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, solveSudoku2_IdxParam_JaggedNew) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku2_IdxParam_JaggedNew(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, solveSudoku3_VectorRAII) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku3_VectorRAII(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, solveSudoku4_ManualCleanup) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku4_ManualCleanup(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, solveSudoku5_PrecomputedBox_Vector) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku5_PrecomputedBox_Vector(board);
    EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, solveSudoku6_Bitmask_Candidates) {
	Solution solver;
	// copy board (separate instance)
	auto board = initial;                 // copy so each test starts fresh
	solver.solveSudoku6_Bitmask_Candidates(board);
	EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, solveSudoku7_Bitmask_Flat) {
	Solution solver;
	// copy board (separate instance)
	auto board = initial;                 // copy so each test starts fresh
	solver.solveSudoku7_Bitmask_Flat(board);
	EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, solveSudoku8_Bitmask_MRV_Popcount) {
	Solution solver;
	// copy board (separate instance)
	auto board = initial;                 // copy so each test starts fresh
	solver.solveSudoku8_Bitmask_MRV_Popcount(board);
	EXPECT_EQ(board, expected);
}

TEST_F(SudokuTest, veSudoku9_Bitmask_MRV_PrivateHelpers) {
    Solution solver;
    // copy board (separate instance)
    auto board = initial;                 // copy so each test starts fresh
    solver.solveSudoku9_Bitmask_MRV_PrivateHelpers(board);
    EXPECT_EQ(board, expected);
}