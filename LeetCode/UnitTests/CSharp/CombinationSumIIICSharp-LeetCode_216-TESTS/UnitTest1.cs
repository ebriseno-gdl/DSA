using NUnit.Framework;
using NUnit.Framework.Legacy;
using Project;

/*
 * Unit tests for `CombinationSum3` method in `CombinationSumIIICpp-LeetCode_216\Program.cs`.
 *
 */


namespace CombinationSumIIICSharp_LeetCode_216_TESTS
{
    public class Tests
    {
        private static readonly object[] _cases =
        {
            new object[] { new int[] { 3 }, new int[] { 7 }, new List<string> { "1,2,4" } },
            new object[] { new int[] { 3 }, new int[] { 9 }, new List<string> { "1,2,6", "1,3,5", "2,3,4" } },
            new object[] { new int[] { 4 }, new int[] { 1 }, new List<string> { } }
        };

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_CombinationSum3(int[] kArr, int[] nArr, List<string> expectedValues)
        {
            var k = kArr[0];
            var n = nArr[0];
            var result = Project.Program.CombinationSum3(k, n);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }
    }
}
            