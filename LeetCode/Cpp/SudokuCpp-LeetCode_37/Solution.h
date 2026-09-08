#pragma once

#include <vector>

using namespace std;

class Solution {
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
};
