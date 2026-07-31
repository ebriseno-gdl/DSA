#include <gtest/gtest.h>
#include <vector>
#include "../../../Cpp/CombinationSumIIICpp-LeetCode_216/Solution.h"

using namespace std;

/*
 * Google Unit tests for `combinationSum3` method in `CombinationSumIIICpp-LeetCode_216`.
 *
 */

TEST(CombinationSumIII, Example1)
{
    Solution solver;

    int k = 3;
    int n = 7;
    vector<vector<int>> expected{
        {1, 2, 4}
    };
    auto output = solver.combinationSum3(k, n);
    EXPECT_EQ(output, expected);
}

TEST(CombinationSumIII, Example2)
{
    Solution solver;

    int k = 3;
    int n = 9;
    vector<vector<int>> expected{
        {1, 2, 6}, 
        {1, 3, 5}, 
        {2, 3, 4}
    };
    auto output = solver.combinationSum3(k, n);
    EXPECT_EQ(output, expected);
}

TEST(CombinationSumIII, Example3)
{
    Solution solver;

    int k = 4;
    int n = 1; 
    vector<vector<int>> expected{};
    auto output = solver.combinationSum3(k, n);
    EXPECT_EQ(output, expected);
}