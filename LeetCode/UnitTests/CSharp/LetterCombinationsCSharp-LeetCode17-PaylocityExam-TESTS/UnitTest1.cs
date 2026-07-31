using NUnit.Framework;
using NUnit.Framework.Legacy;
using Project;

/*
 * Unit tests for `LetterCombinations` method in `LetterCombinationsCSharp-LeetCode17-PaylocityExam\Program.cs`.
 *
 */

namespace LetterCombinationsCSharp_LeetCode17_PaylocityExam_TESTS
{
    public class UnitTests
    {
        private static readonly object[] _sourceLists =
        {
            new object[] {"32", new List<string>{"da","db","dc","ea","eb","ec","fa","fb","fc"}},
            new object[] {"662", new List<string>{"mma","mmb","mmc","mna","mnb","mnc","moa","mob","moc","nma","nmb","nmc","nna","nnb","nnc","noa","nob","noc","oma","omb","omc","ona","onb","onc","ooa","oob","ooc"}},
            new object[] {"5", new List<string> {"j","k","l"}},
            new object[] {"", new List<string> {}}
        };

        [Test]
        [TestCaseSource(nameof(_sourceLists))]
        public void Test_LetterCombinations(string digits, List<string> expectedValues)
        {
            var result = Project.MainClass.LetterCombinations(digits);
            CollectionAssert.AreEqual(expectedValues, result);
        }
    }
}
