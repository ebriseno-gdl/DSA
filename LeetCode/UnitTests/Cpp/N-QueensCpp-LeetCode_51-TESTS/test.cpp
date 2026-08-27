#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../../../Cpp/N-QueensCpp-LeetCode_51/Solution.h"

using namespace std;

/*
 * Google Unit tests for `solveNQueens*` methods in `N-QueensCpp-LeetCode_51`.
 *
 */
TEST(solveNQueens, Example1) 
{
	Solution solver;
	int n = 1;
	vector<vector<string>> expected{
		{"Q"}
	};
	auto solutions1 = solver.solveNQueens1(n);
	EXPECT_EQ(solutions1, expected);
	auto solutions2 = solver.solveNQueens2(n);
	EXPECT_EQ(solutions2, expected);
	auto solutions3 = solver.solveNQueens3(n);
	EXPECT_EQ(solutions3, expected);
	auto solutions4 = solver.solveNQueens4(n);
	EXPECT_EQ(solutions4, expected);
	auto solutions5 = solver.solveNQueens5(n);
	EXPECT_EQ(solutions5, expected);
}

TEST(solveNQueens, Example2)
{
	Solution solver;
	int n = 2;
	vector<vector<string>> expected{};
	auto solutions1 = solver.solveNQueens1(n);
	EXPECT_EQ(solutions1, expected);
	auto solutions2 = solver.solveNQueens2(n);
	EXPECT_EQ(solutions2, expected);
	auto solutions3 = solver.solveNQueens3(n);
	EXPECT_EQ(solutions3, expected);
	auto solutions4 = solver.solveNQueens4(n);
	EXPECT_EQ(solutions4, expected);
	auto solutions5 = solver.solveNQueens5(n);
	EXPECT_EQ(solutions5, expected);
}

TEST(solveNQueens, Example3)
{
	Solution solver;
	int n = 3;
	vector<vector<string>> expected{};
	auto solutions1 = solver.solveNQueens1(n);
	EXPECT_EQ(solutions1, expected);
	auto solutions2 = solver.solveNQueens2(n);
	EXPECT_EQ(solutions2, expected);
	auto solutions3 = solver.solveNQueens3(n);
	EXPECT_EQ(solutions3, expected);
	auto solutions4 = solver.solveNQueens4(n);
	EXPECT_EQ(solutions4, expected);
	auto solutions5 = solver.solveNQueens5(n);
	EXPECT_EQ(solutions5, expected);
}

TEST(solveNQueens, Example4)
{
	Solution solver;
	int n = 4;
	vector<vector<string>> expected{
		{".Q..", "...Q", "Q...", "..Q."},
		{"..Q.", "Q...", "...Q", ".Q.."}
	};
	auto solutions1 = solver.solveNQueens1(n);
	EXPECT_EQ(solutions1, expected);
	auto solutions2 = solver.solveNQueens2(n);
	EXPECT_EQ(solutions2, expected);
	auto solutions3 = solver.solveNQueens3(n);
	EXPECT_EQ(solutions3, expected);
	auto solutions4 = solver.solveNQueens4(n);
	EXPECT_EQ(solutions4, expected);
	auto solutions5 = solver.solveNQueens5(n);
	EXPECT_EQ(solutions5, expected);
}

TEST(solveNQueens, Example5)
{
	Solution solver;
	int n = 5;
	vector<vector<string>> expected{
		{"Q....","..Q..","....Q",".Q...","...Q."},
		{"Q....","...Q.",".Q...","....Q","..Q.."},
		{".Q...","...Q.","Q....","..Q..","....Q"},
		{".Q...","....Q","..Q..","Q....","...Q."},
		{"..Q..","Q....","...Q.",".Q...","....Q"},
		{"..Q..","....Q",".Q...","...Q.","Q...."},
		{"...Q.","Q....","..Q..","....Q",".Q..."},
		{"...Q.",".Q...","....Q","..Q..","Q...."},
		{"....Q",".Q...","...Q.","Q....","..Q.."},
		{"....Q","..Q..","Q....","...Q.",".Q..."}
	};
	auto solutions1 = solver.solveNQueens1(n);
	EXPECT_EQ(solutions1, expected);
	auto solutions2 = solver.solveNQueens2(n);
	EXPECT_EQ(solutions2, expected);
	auto solutions3 = solver.solveNQueens3(n);
	EXPECT_EQ(solutions3, expected);
	auto solutions4 = solver.solveNQueens4(n);
	EXPECT_EQ(solutions4, expected);
	auto solutions5 = solver.solveNQueens5(n);
	EXPECT_EQ(solutions5, expected);
}

TEST(solveNQueens, Example6)
{
	Solution solver;
	int n = 6;
	vector<vector<string>> expected{
		{".Q....","...Q..",".....Q","Q.....","..Q...","....Q."},
		{"..Q...",".....Q",".Q....","....Q.","Q.....","...Q.."},
		{"...Q..","Q.....","....Q.",".Q....",".....Q","..Q..."},
		{"....Q.","..Q...","Q.....",".....Q","...Q..",".Q...."}
	};
	auto solutions1 = solver.solveNQueens1(n);
	EXPECT_EQ(solutions1, expected);
	auto solutions2 = solver.solveNQueens2(n);
	EXPECT_EQ(solutions2, expected);
	auto solutions3 = solver.solveNQueens3(n);
	EXPECT_EQ(solutions3, expected);
	auto solutions4 = solver.solveNQueens4(n);
	EXPECT_EQ(solutions4, expected);
	auto solutions5 = solver.solveNQueens5(n);
	EXPECT_EQ(solutions5, expected);
}

