#pragma once

#include <vector>
#include <string>

using namespace std;

class Solution {
	public:
    vector<vector<string>> SolveNQueens1_JaggedHash(int n);
	vector<vector<string>> solveNQueens2_StringBoard_Hash(int n);
	vector<vector<string>> solveNQueens3_BoolArr(int n);
	vector<vector<string>> solveNQueens4_BitMask(int n);
	vector<vector<string>> solveNQueens5_IndexBoard_BitMask(int n);
};