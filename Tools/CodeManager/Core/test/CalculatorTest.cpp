#include "Calculator.h"
#include "Exception.h"
#include <gtest/gtest.h>



using Pslrk::Core::Calculator;
using Pslrk::Core::ExceptionInvalidStringView;



class CalculatorTest : public ::testing::Test
{
    protected:
        virtual void SetUp    () override;
        virtual void TearDown () override;
};



void CalculatorTest::SetUp ()
{
}



void CalculatorTest::TearDown ()
{
}



TEST_F (CalculatorTest, CalculateAcfInvalidViewThrow)
{
    // Arange.
    const std::string code {"+0+++"};
    // Act, Assert.
    EXPECT_THROW (Calculator::CalculateAcf (code), ExceptionInvalidStringView);
}



TEST_F (CalculatorTest, CalculateAcfEmptyViewSuccess)
{
    // Arange.
    const std::string code {""};
    const std::vector <int> etalonAcf {};
    std::vector <int> testAcf {};
    // Act.
    EXPECT_NO_THROW (
        testAcf = Calculator::CalculateAcf (code)
    );
    // Assert.
    EXPECT_EQ (etalonAcf, testAcf);
}



//     |+-+++|
// +-++|+    |        1
//  +-+|++   |        0
//   +-|+++  |        1
//    +|-+++ |        0
//     |+-+++|        5
//     | +-++|+       0
//     |  +-+|++      1
//     |   +-|+++     0
//     |    +|-+++    1
TEST_F (CalculatorTest, CalculateAcf_10111_Success)
{
    // Arange.
    const std::string code {"+-+++"};
    const std::vector <int> etalonAcf {1, 0, 1, 0, 5, 0, 1, 0, 1};
    // Act.
    const std::vector <int> testAcf = Calculator::CalculateAcf (code);
    // Assert.
    EXPECT_EQ (etalonAcf, testAcf);
}



//        |---++-+-|
// ---++-+|-       |        1
//  ---++-|+-      |        0
//   ---++|-+-     |        1
//    ---+|+-+-    |       -2
//     ---|++-+-   |       -1
//      --|-++-+-  |        0
//       -|--++-+- |       -1
//        |---++-+-|        8
//        | ---++-+|-
//        |  ---++-|+-
//        |   ---++|-+-
//        |    ---+|+-+-
//        |     ---|++-+-
//        |      --|-++-+-
//        |       -|--++-+-
TEST_F (CalculatorTest, CalculateAcf_00011010_Success)
{
    // Arange.
    const std::string code {"---++-+-"};
    const std::vector <int> etalonAcf {1, 0, 1, -2, -1, 0, -1, 8, -1, 0, -1, -2, 1, 0, 1};
    // Act.
    const std::vector <int> testAcf {Calculator::CalculateAcf (code)};
    // Assert.
    EXPECT_EQ (etalonAcf, testAcf);
}



//     |+-+++|
// +-++|+    |        1
//  +-+|++   |        0
//   +-|+++  |        1
//    +|-+++ |        0
//     |+-+++|        5
//     | +-++|+       0
//     |  +-+|++      1
//     |   +-|+++     0
//     |    +|-+++    1
TEST_F (CalculatorTest, CalculateCcf_10111_and_10111_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"+-+++"};
    const std::vector <int> etalonCcf {1, 0, 1, 0, 5, 0, 1, 0, 1};
    // Act.
    const std::vector <int> testCcf = Calculator::CalculateCcf (codeOne, codeTwo);
    // Assert.
    EXPECT_EQ (etalonCcf, testCcf);
}



//     |+-+++|
// ++-+|+    |        1
//  ++-|++   |        0
//   ++|-++  |       -1
//    +|+-++ |        4
//     |++-++|        1
//     | ++-+|+       0
//     |  ++-|++      1
//     |   ++|-++     2
//     |    +|+-++    1
TEST_F (CalculatorTest, CalculateCcf_10111_and_11011_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"++-++"};
    const std::vector <int> etalonCcf {1, 0, -1, 4, 1, 0, 1, 2, 1};
    // Act.
    const std::vector <int> testCcf = Calculator::CalculateCcf (codeOne, codeTwo);
    // Assert.
    EXPECT_EQ (etalonCcf, testCcf);
}



//         |+-+++|
//  ++-++-+|-    |        -1
//   ++-++-|+-   |         2
//    ++-++|-+-  |        -3
//     ++-+|+-+- |         2
//      ++-|++-+-|        -1
//       ++|-++-+|-       -1
//        +|+-++-|+-       3
//         |++-++|-+-      1
//         | ++-+|+-+-     0
//         |  ++-|++-+-    1
//         |   ++|-++-+-   2
//         |    +|+-++-+-  1
TEST_F (CalculatorTest, CalculateCcf_10111_and_11011010_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"++-++-+-"};
    const std::vector <int> etalonCcf {-1, 2, -3, 2, -1, -1, 3, 1, 0, 1, 2, 1};
    // Act.
    const std::vector <int> testCcf {Calculator::CalculateCcf (codeOne, codeTwo)};
    // Assert.
    EXPECT_EQ (etalonCcf, testCcf);
}



//         |+++-++-|
//     +++-|+      |       1
//      +++|-+     |       0
//       ++|+-+    |       1
//        +|++-+   |       0
//         |+++-+  |       5
//         | +++-+ |       1
//         |  +++-+|      -1
//         |   +++-|+      2
//         |    +++|-+     1
//         |     ++|+-+    0
//         |      +|++-+  -1
TEST_F (CalculatorTest, CalculateCcf_1110110_and_11101_Success)
{
    // Arange.
    const std::string codeOne {"+++-++-"};
    const std::string codeTwo {"+++-+"};
    const std::vector <int> etalonCcf {1, 0, 1, 0, 5, 1, -1, 2, 1, 0, -1};
    // Act.
    const std::vector <int> testCcf {Calculator::CalculateCcf (codeOne, codeTwo)};
    // Assert.
    EXPECT_EQ (etalonCcf, testCcf);
}



TEST_F (CalculatorTest, CalculatePslInvalidViewThrow)
{
    // Arange.
    const std::string code {"+0+++"};
    // Act, Assert.
    EXPECT_THROW (Calculator::CalculatePsl (code), ExceptionInvalidStringView);
}



TEST_F (CalculatorTest, CalculatePslEmptyViewSuccess)
{
    // Arange.
    const std::string code {""};
    constexpr int etalonPsl {0};
    int testPsl;
    // Act.
    EXPECT_NO_THROW (
        testPsl = Calculator::CalculatePsl (code);
    );
    // Assert.
    EXPECT_EQ (etalonPsl, testPsl);
}



TEST_F (CalculatorTest, CalculatePsl_10111_Success)
{
    // Arange.
    const std::string code {"+-+++"};
    constexpr int etalonPsl {1};
    // Act.
    const int testPsl {Calculator::CalculatePsl (code)};
    // Assert.
    EXPECT_EQ (etalonPsl, testPsl);
}



TEST_F (CalculatorTest, CalculatePsl_00011010_Success)
{
    // Arange.
    const std::string code {"---++-+-"};
    constexpr int etalonPsl {2};
    // Act.
    const int testPsl {Calculator::CalculatePsl (code)};
    // Assert.
    EXPECT_EQ (etalonPsl, testPsl);
}



TEST_F (CalculatorTest, CalclulateDb_1_to_5_Success)
{
    // Arange.
    constexpr int ml  {5};
    constexpr int psl {1};
    constexpr long double etalonDb {-13.979f};
    constexpr long double epsilonDb {0.001f};

    // Act.
    const long double testDb {Calculator::CalculateDb (ml, psl)};

    // Assert.
    EXPECT_NEAR (etalonDb, testDb, epsilonDb);
}



TEST_F (CalculatorTest, CalclulateDb_1_to_13_Success)
{
    // Arange.
    constexpr int ml  {13};
    constexpr int psl {1};
    constexpr long double etalonDb {-22.279f};
    constexpr long double epsilonDb {0.001f};

    // Act.
    const long double testDb {Calculator::CalculateDb (ml, psl)};

    // Assert.
    EXPECT_NEAR (etalonDb, testDb, epsilonDb);
}