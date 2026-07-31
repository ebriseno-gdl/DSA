using Microsoft.VisualStudio.TestPlatform.TestHost;
using NUnit.Framework;
using NUnit.Framework.Legacy;
using Project;

/*
 * Unit tests for `Permute` method in `PermutationsCSharp-LeetCode_46\Program.cs`.
 *
 */

namespace PermutationsCSharp_LeetCode_46_TESTS
{
    public class Tests
    {
        private static readonly object[] _cases =
        {
            new object[] { new int[] { 1, 2, 3 }, new List<string> { "1,2,3", "1,3,2", "2,1,3", "2,3,1", "3,1,2", "3,2,1" } },
            new object[] { new int[] { 0, 1 },    new List<string> { "0,1", "1,0" } },
            new object[] { new int[] { 1 },       new List<string> { "1" } }
        };

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_Permute(int[] nums, List<string> expectedValues)
        {
            var result = Project.Program.Permute(nums);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }
    }
}
