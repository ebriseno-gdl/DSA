#include <gtest/gtest.h>
#include <vector>
#include "../../../Cpp/CombinationSumIICpp-LeetCode_40/Solution.h"

using namespace std;

/*
 * Google Unit tests for `combinationSum2` method in `CombinationSumIICpp-LeetCode_40`.
 *
 */

TEST(CombinationSumII, Example1) 
{
    Solution solver;

    vector<int> input{ 10, 1, 2, 7, 6, 1, 5 };
	int target = 8;
    vector<vector<int>> expected{
        {1, 1, 6},
        {1, 2, 5},
		{1, 7},
		{2, 6}
    };
    auto output = solver.combinationSum2(input, target);
    EXPECT_EQ(output, expected);
}

TEST(CombinationSumII, Example2)
{
    Solution solver;

    vector<int> input{ 2, 5, 2, 1, 2 };
    int target = 5;
    vector<vector<int>> expected{
        {1, 2, 2},
        {5}
    };
    auto output = solver.combinationSum2(input, target);
    EXPECT_EQ(output, expected);
}

TEST(CombinationSumII, Example3)
{
    Solution solver;

    vector<int> input{ 1, 1, 2, 2, 3 };
    int target = 4;
    vector<vector<int>> expected{
        {1, 1, 2},
        {1, 3},
        {2, 2}
    };
    auto output = solver.combinationSum2(input, target);
    EXPECT_EQ(output, expected);
}

TEST(CombinationSumII, Example4)
{
    Solution solver;

    vector<int> input{ 1, 1, 3 };
    int target = 7;
    vector<vector<int>> expected{};
    auto output = solver.combinationSum2(input, target);
    EXPECT_EQ(output, expected);
}

TEST(CombinationSumII, Example5)
{
    Solution solver;

    vector<int> input{ 0, 0, 0 };
    int target = 0;
    vector<vector<int>> expected{
        {}
    };
    auto output = solver.combinationSum2(input, target);
    EXPECT_EQ(output, expected);
}