
#include <gtest/gtest.h>
#include <vector>
#include "../../../Cpp/PermutationsCpp-LeetCode_46/Solution.h"

using namespace std;

/*
 * Google Unit tests for `permute` and `permute1` methods in `PermutationsCpp-LeetCode_46`.
 *
 */

TEST(Permutations, Example1)
{
    Solution solver;

    vector<int> input{ 1, 2, 3 };
    vector<vector<int>> expected{
        {1,2,3},
        {1,3,2},
        {2,1,3},
        {2,3,1},
        {3,1,2},
        {3,2,1}
    };
    auto output1 = solver.permute(input);
    EXPECT_EQ(output1, expected);
    auto output2 = solver.permute1(input);
    EXPECT_EQ(output2, expected);
}

TEST(Permutations, Example2)
{
    Solution solver;

    vector<int> input = { 0, 1 };
    vector<vector<int>> expected{
        {0,1},
        {1,0}
    };
    auto output1 = solver.permute(input);
    EXPECT_EQ(output1, expected);
    auto output2 = solver.permute(input);
    EXPECT_EQ(output2, expected);
}

TEST(Permutations, Example3)
{
    Solution solver;

    vector<int> input = { 1 };
    vector<vector<int>> expected{
        {1}
    };
    auto output1 = solver.permute(input);
    EXPECT_EQ(output1, expected);
    auto output2 = solver.permute(input);
    EXPECT_EQ(output2, expected);
}