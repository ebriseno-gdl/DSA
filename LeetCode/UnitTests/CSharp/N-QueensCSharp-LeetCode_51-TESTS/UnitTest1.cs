using NUnit.Framework;
using NUnit.Framework.Legacy;
using Project;

/*
 * Unit tests for `SolveNQueens*` methods in `N-QueensCSharp-LeetCode_51\Program.cs`.
 *
 */
namespace N_QueensCSharp_LeetCode_51_TESTS
{
    public class Tests
    {
        private static readonly object[] _cases =
        {
            new object[] { new int[] { 1 }, new List<string> { "Q" } },
            new object[] { new int[] { 2 }, new List<string> { } },
            new object[] { new int[] { 3 }, new List<string> { } },
            new object[] { new int[] { 4 }, new List<string> { ".Q..,...Q,Q...,..Q.", "..Q.,Q...,...Q,.Q.." } },
            new object[] { new int[] { 5 }, new List<string> { "Q....,..Q..,....Q,.Q...,...Q.", "Q....,...Q.,.Q...,....Q,..Q..", ".Q...,...Q.,Q....,..Q..,....Q", ".Q...,....Q,..Q..,Q....,...Q.", "..Q..,Q....,...Q.,.Q...,....Q", "..Q..,....Q,.Q...,...Q.,Q....", "...Q.,Q....,..Q..,....Q,.Q...", "...Q.,.Q...,....Q,..Q..,Q....", "....Q,.Q...,...Q.,Q....,..Q..", "....Q,..Q..,Q....,...Q.,.Q..." } },
            new object[] { new int[] { 6 }, new List<string> { ".Q....,...Q..,.....Q,Q.....,..Q...,....Q.", "..Q...,.....Q,.Q....,....Q.,Q.....,...Q..", "...Q..,Q.....,....Q.,.Q....,.....Q,..Q...", "....Q.,..Q...,Q.....,.....Q,...Q..,.Q...." } }
        };

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_SolveNQueens1_JaggedHash(int[]  Narr, List<string> expectedValues)
        {
            var N = Narr[0];
            var result = Project.Program.SolveNQueens1_JaggedHash(N);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_SolveNQueens2_Array2D(int[] Narr, List<string> expectedValues)
        {
            var N = Narr[0];
            var result = Project.Program.SolveNQueens2_Array2D(N);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_SolveNQueens3_BoolArr(int[] Narr, List<string> expectedValues)
        {
            var N = Narr[0];
            var result = Project.Program.SolveNQueens3_BoolArr(N);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_SolveNQueens4_BitMask(int[] Narr, List<string> expectedValues)
        {
            var N = Narr[0];
            var result = Project.Program.SolveNQueens4_BitMask(N);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_SolveNQueens5_JaggedBM(int[] Narr, List<string> expectedValues)
        {
            var N = Narr[0];
            var result = Project.Program.SolveNQueens5_JaggedBM(N);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }

        [Test]
        [TestCaseSource(nameof(_cases))]
        public void Test_SolveNQueens6_Compact(int[] Narr, List<string> expectedValues)
        {
            var N = Narr[0];
            var result = Project.Program.SolveNQueens6_Compact(N);
            var asStrings = result.Select(group => string.Join(",", group)).ToList();
            CollectionAssert.AreEqual(expectedValues, asStrings);
        }
    }
}

