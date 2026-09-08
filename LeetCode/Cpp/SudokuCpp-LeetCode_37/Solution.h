#pragma once

#include <vector>

using namespace std;

class Solution {
private:
	// Class private members and methods for solveSudoku9_Bitmask_MRV_PrivateHelpers public method.
	// solveSudoku9_Bitmask_MRV_PrivateHelpers method is same than solveSudoku8_Bitmask_MRV_Popcount but with private helper functions instead of lambdas for better readability, maintainability and performance.
	
	// Class private members `rows`, `columns`, `boxes`, and `sudoku_solved` are used to maintain state across recursive calls.
	// Flat arrays of bitmasks for rows, columns, and 3x3 boxes.
	// Each array index contains a 9-bit bitmask representing digits 1-9.
	int rows[9] = { 0 };
	int columns[9] = { 0 };
	int boxes[9] = { 0 };
	// `sudoku_solved` is used to indicate when a solution has been found, allowing early termination of the backtracking process
	bool sudoku_solved = false;

	// 9x9 lookup table for instantaneous O(1) box index retrieval
	inline static const int BOX_INDEX[9][9] = {
		{0,0,0, 1,1,1, 2,2,2},
		{0,0,0, 1,1,1, 2,2,2},
		{0,0,0, 1,1,1, 2,2,2},
		{3,3,3, 4,4,4, 5,5,5},
		{3,3,3, 4,4,4, 5,5,5},
		{3,3,3, 4,4,4, 5,5,5},
		{6,6,6, 7,7,7, 8,8,8},
		{6,6,6, 7,7,7, 8,8,8},
		{6,6,6, 7,7,7, 8,8,8}
	};

	// Class private member `get_valid_choices`, `place_number`, `remove_number`, and `backtrack` are used by solveSudoku9_Bitmask_MRV_PrivateHelpers public method
	// These corresond to the lambda functions used in solveSudoku8_Bitmask_MRV_Popcount
	int get_valid_choices(int row, int col, int idx);
	void place_number(int d, int row, int col, int idx, vector<vector<char>>& board);
	void remove_number(int d, int row, int col, int idx, vector<vector<char>>& board);
	void backtrack(vector<vector<char>>& board);

public:
	// Backtracking using dynamically allocated `int**` trackers for rows/cols/boxes; mutates board in-place.
	void solveSudoku1_JaggedNew(vector<vector<char>>& board);

	// Backtracking with explicit box-index parameter and dynamic trackers; choose/explore/unchoose flow.
	void solveSudoku2_IdxParam_JaggedNew(vector<vector<char>>& board);

	// RAII-friendly variant using `vector` trackers to avoid manual memory management.
	void solveSudoku3_VectorRAII(vector<vector<char>>& board);

	// Manual trackers with centralized cleanup lambda for exception-safe manual memory release.
	void solveSudoku4_ManualCleanup(vector<vector<char>>& board);

	// Vector-based trackers with a precomputed box-index table for faster box lookup.
	void solveSudoku5_PrecomputedBox_Vector(vector<vector<char>>& board);

	// Bitmask-based solver using candidate bitsets and popcount-assisted pruning.
	void solveSudoku6_Bitmask_Candidates(vector<vector<char>>& board);

	// Flat bitmask arrays + static `BOX_INDEX` for O(1) checks and minimal footprint.
	void solveSudoku7_Bitmask_Flat(vector<vector<char>>& board);

	// Bitmask + MRV heuristic (minimum-remaining-values) using popcount for aggressive pruning.
	void solveSudoku8_Bitmask_MRV_Popcount(vector<vector<char>>& board);

	// Bitmask + MRV (popcount) solver; same than solveSudoku8_Bitmask_MRV_Popcount but with private helper functions instead of lambdas.
	void solveSudoku9_Bitmask_MRV_PrivateHelpers(vector<vector<char>>& board);

};
