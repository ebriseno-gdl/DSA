using NUnit.Framework;
using NUnit.Framework.Legacy;
using Project;

/*
 * Unit tests for `PermuteUnique` method in `PermutationsIICSharp-LeetCode_47\Program.cs`.
 *
 */

namespace PermutationsIICSharp_LeetCode_47_TESTS
{
    public class Tests
    {
        private static readonly object[] _cases =
        {
            new object[] { new int[] { 1, 1, 2 }, new List<string> { "1,1,2", "1,2,1", "2,1,1" } },
            new object[] { new int[] { 1, 2, 3 }, new List<string> { "1,2,3", "1,3,2", "2,1,3", "2,3,1", "3,1,2", "3,2,1" } },
            new object[] { new int[] { 0, 0, 0 }, new List<string> { "0,0,0" } },
            new object[] { new int[] { 1, 2, 2 }, new List<string> { "1,2,2", "2,1,2", "2,2,1" } },
            new object[] { new int[] { 1, 1, 1, 2 }, new List<string> { "1,1,1,2", "1,1,2,1", "1,2,1,1", "2,1,1,1" } }
        };

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_Permute(int[] nums, List<string> expectedValues)
        {
            var result = Project.Solution.PermuteUnique(nums);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }
    }
}
