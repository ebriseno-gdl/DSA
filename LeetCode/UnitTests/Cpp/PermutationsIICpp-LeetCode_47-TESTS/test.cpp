#include <gtest/gtest.h>
#include <vector>
#include "../../../Cpp/PermutationsIICpp-LeetCode_47/Solution.h"

/*
 * Google Unit tests for `permuteUnique` method in `PermutationsIICpp-LeetCode_47`.
 *
 */

TEST(Permutations, Example1)
{
    Solution solver;

    vector<int> input{ 1, 1, 2 };
    vector<vector<int>> expected{
        {1, 1, 2},
        {1, 2, 1},
        {2, 1, 1}
    };
    auto output = solver.permuteUnique(input);
    EXPECT_EQ(output, expected);
}

TEST(Permutations, Example2)
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
    auto output = solver.permuteUnique(input);
    EXPECT_EQ(output, expected);
}

TEST(Permutations, Example3)
{
    Solution solver;

    vector<int> input{ 0, 0, 0 };
    vector<vector<int>> expected{
        {0,0,0}
    };
    auto output = solver.permuteUnique(input);
    EXPECT_EQ(output, expected);
}

TEST(Permutations, Example4)
{
    Solution solver;

    vector<int> input{ 1, 2, 2 };
    vector<vector<int>> expected{
        {1, 2, 2},
        {2, 1, 2},
        {2, 2, 1}
    };
    auto output = solver.permuteUnique(input);
    EXPECT_EQ(output, expected);
}

TEST(Permutations, Example5)
{
    Solution solver;

    vector<int> input{ 1, 1, 1, 2 };
    vector<vector<int>> expected{
        {1, 1, 1, 2},
        {1, 1, 2, 1},
        {1, 2, 1, 1},
        {2, 1, 1, 1}
    };
    auto output = solver.permuteUnique(input);
    EXPECT_EQ(output, expected);
}