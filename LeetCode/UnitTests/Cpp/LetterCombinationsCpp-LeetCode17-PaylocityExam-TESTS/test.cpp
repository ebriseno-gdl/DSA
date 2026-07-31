#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../../../Cpp/LetterCombinationsCpp-LeetCode17-PaylocityExam/Solution.h"

using namespace std;

/*
 * Google Unit tests for `letterCombinations` method in `LetterCombinationsCpp-LeetCode17-PaylocityExam`.
 *
 */
TEST(LetterCombinations, Example1)
{
	Solution solver;
	string input = "23";
	vector<string> expected{
		"ad", "ae", "af",
		"bd", "be", "bf",
		"cd", "ce", "cf"
	};
	auto output = solver.letterCombinations(input);
	EXPECT_EQ(output, expected);
}

TEST(LetterCombinations, Example2)
{
	Solution solver;
	string input = "32";
	vector<string> expected{
		"da", "db", "dc",
		"ea", "eb", "ec",
		"fa", "fb", "fc"
	};
	auto output = solver.letterCombinations(input);
	EXPECT_EQ(output, expected);
}

TEST(LetterCombinations, Example3)
{
	Solution solver;
	string input = "662";
	vector<string> expected{
		"mma", "mmb", "mmc",
		"mna", "mnb", "mnc",
		"moa", "mob", "moc",
		"nma", "nmb", "nmc",
		"nna", "nnb", "nnc",
		"noa", "nob", "noc",
		"oma", "omb", "omc",
		"ona", "onb", "onc",
		"ooa", "oob", "ooc"
	};
	auto output = solver.letterCombinations(input);
	EXPECT_EQ(output, expected);
}

TEST(LetterCombinations, Example4)
{
	Solution solver;
	string input = "";
	vector<string> expected{};
	auto output = solver.letterCombinations(input);
	EXPECT_EQ(output, expected);
}

TEST(LetterCombinations, Example5)
{
	Solution solver;
	string input = "5";
	vector<string> expected{
		"j", "k", "l"
	};
	auto output = solver.letterCombinations(input);
	EXPECT_EQ(output, expected);
}
