using NUnit.Framework;
using NUnit.Framework.Legacy;
using Project;

/*
 * Unit tests for `CombinationSum2` method in `CombinationSumIICpp-LeetCode_40\Program.cs`.
 *
 */

namespace CombinationSumIICSharp_LeetCode_40_TESTS
{
    public class Tests
    {
        private static readonly object[] _cases =
        {
            new object[] { new int[] { 10, 1, 2, 7, 6, 1, 5 }, new int[] { 8 }, new List<string> { "1,1,6", "1,2,5", "1,7", "2,6" } },
            new object[] { new int[] { 2, 5, 2, 1, 2 }, new int[] { 5 }, new List<string> { "1,2,2", "5" } },
            new object[] { new int[] { 1, 1, 2, 2, 3 }, new int[] { 4 }, new List<string> { "1,1,2", "1,3", "2,2" } },
            new object[] { new int[] { 1, 1, 3 }, new int[] { 7 }, new List<string> { } },
            new object[] { new int[] { 0, 0, 0 }, new int[] { 0 }, new List<string> { "" } }
        };

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_CombinationSum2(int[] nums, int[] targetArr, List<string> expectedValues)
        {
            var target = targetArr[0];
            var result = Project.Program.CombinationSum2(nums, target);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }
    }
}
