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



TEST_F (CalculatorTest, AcfInvalidViewThrow)
{
    // Arange.
    const std::string code {"+0+++"};
    // Act, Assert.
    EXPECT_THROW (Calculator::Acf (code), ExceptionInvalidStringView);
}



TEST_F (CalculatorTest, AcfEmptyViewSuccess)
{
    // Arange.
    const std::string code {""};
    const std::vector <int> etalonAcf {};
    std::vector <int> testAcf {};
    // Act.
    EXPECT_NO_THROW (
        testAcf = Calculator::Acf (code)
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
TEST_F (CalculatorTest, Acf_10111_Success)
{
    // Arange.
    const std::string code {"+-+++"};
    const std::vector <int> etalonAcf {1, 0, 1, 0, 5, 0, 1, 0, 1};
    // Act.
    const std::vector <int> testAcf = Calculator::Acf (code);
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
TEST_F (CalculatorTest, Acf_00011010_Success)
{
    // Arange.
    const std::string code {"---++-+-"};
    const std::vector <int> etalonAcf {1, 0, 1, -2, -1, 0, -1, 8, -1, 0, -1, -2, 1, 0, 1};
    // Act.
    const std::vector <int> testAcf {Calculator::Acf (code)};
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
TEST_F (CalculatorTest, Ccf_10111_and_10111_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"+-+++"};
    const std::vector <int> etalonCcf {1, 0, 1, 0, 5, 0, 1, 0, 1};
    // Act.
    const std::vector <int> testCcf = Calculator::Ccf (codeOne, codeTwo);
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
TEST_F (CalculatorTest, Ccf_10111_and_11011_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"++-++"};
    const std::vector <int> etalonCcf {1, 0, -1, 4, 1, 0, 1, 2, 1};
    // Act.
    const std::vector <int> testCcf = Calculator::Ccf (codeOne, codeTwo);
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
TEST_F (CalculatorTest, Ccf_10111_and_11011010_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"++-++-+-"};
    const std::vector <int> etalonCcf {-1, 2, -3, 2, -1, -1, 3, 1, 0, 1, 2, 1};
    // Act.
    const std::vector <int> testCcf {Calculator::Ccf (codeOne, codeTwo)};
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
TEST_F (CalculatorTest, Ccf_1110110_and_11101_Success)
{
    // Arange.
    const std::string codeOne {"+++-++-"};
    const std::string codeTwo {"+++-+"};
    const std::vector <int> etalonCcf {1, 0, 1, 0, 5, 1, -1, 2, 1, 0, -1};
    // Act.
    const std::vector <int> testCcf {Calculator::Ccf (codeOne, codeTwo)};
    // Assert.
    EXPECT_EQ (etalonCcf, testCcf);
}



TEST_F (CalculatorTest, MlInvalidViewThrow)
{
    // Arange.
    const std::string code {"+0+++"};
    // Act, Assert.
    EXPECT_THROW (Calculator::Ml (code), ExceptionInvalidStringView);
}



TEST_F (CalculatorTest, MlEmptyViewSuccess)
{
    // Arange.
    const std::string code {""};
    constexpr int etalonMl {0};
    int testMl;
    // Act.
    EXPECT_NO_THROW (
        testMl = Calculator::Ml (code);
    );
    // Assert.
    EXPECT_EQ (etalonMl, testMl);
}



TEST_F (CalculatorTest, Ml_10111_Success)
{
    // Arange.
    const std::string code {"+-+++"};
    constexpr int etalonMl {5};
    // Act.
    const int testMl {Calculator::Ml (code)};
    // Assert.
    EXPECT_EQ (etalonMl, testMl);
}



TEST_F (CalculatorTest, Ml_10111_10111_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"+-+++"};
    constexpr int etalonMl {5};
    // Act.
    const int testMl {Calculator::Ml (codeOne, codeTwo)};
    // Assert.
    EXPECT_EQ (etalonMl, testMl);
}



TEST_F (CalculatorTest, Ml_10111_100_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"+--"};
    constexpr int etalonMl {3};
    // Act.
    const int testMl {Calculator::Ml (codeOne, codeTwo)};
    // Assert.
    EXPECT_EQ (etalonMl, testMl);
}



TEST_F (CalculatorTest, PslInvalidViewThrow)
{
    // Arange.
    const std::string code {"+0+++"};
    // Act, Assert.
    EXPECT_THROW (Calculator::Psl (code), ExceptionInvalidStringView);
}



TEST_F (CalculatorTest, PslEmptyViewSuccess)
{
    // Arange.
    const std::string code {""};
    constexpr int etalonPsl {0};
    int testPsl;
    // Act.
    EXPECT_NO_THROW (
        testPsl = Calculator::Psl (code);
    );
    // Assert.
    EXPECT_EQ (etalonPsl, testPsl);
}



TEST_F (CalculatorTest, Psl_10111_Success)
{
    // Arange.
    const std::string code {"+-+++"};
    constexpr int etalonPsl {1};
    // Act.
    const int testPsl {Calculator::Psl (code)};
    // Assert.
    EXPECT_EQ (etalonPsl, testPsl);
}



TEST_F (CalculatorTest, Psl_00011010_Success)
{
    // Arange.
    const std::string code {"---++-+-"};
    constexpr int etalonPsl {2};
    // Act.
    const int testPsl {Calculator::Psl (code)};
    // Assert.
    EXPECT_EQ (etalonPsl, testPsl);
}



TEST_F (CalculatorTest, Psl_10111_100_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"+--"};
    constexpr int etalonPsl {1};
    // Act.
    const int testPsl {Calculator::Psl (codeOne, codeTwo)};
    // Assert.
    EXPECT_EQ (etalonPsl, testPsl);
}



TEST_F (CalculatorTest, E_1010110011111_Success)
{
    // Arange.
    const std::string code {"+-+-++--+++++"};
    constexpr unsigned int etalonE  {2u * 6u};
    // Act.
    const unsigned int testE {Calculator::E (code)};
    // Assert.
    EXPECT_EQ (etalonE, testE);
}



TEST_F (CalculatorTest, E_10111_100_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"+--"};
    constexpr int etalonE {4u};
    // Act.
    const unsigned int testE {Calculator::E (codeOne, codeTwo)};
    // Assert.
    EXPECT_EQ (etalonE, testE);
}



TEST_F (CalculatorTest, Isl_1010110011111_Success)
{
    // Arange.
    const std::string code {"+-+-++--+++++"};
    constexpr float etalonIsl  {-11.487f};
    constexpr float epsilonIsl {0.001f};
    // Act.
    const float testIsl {Calculator::Isl (code)};
    // Assert.
    EXPECT_NEAR (etalonIsl, testIsl, epsilonIsl);
}



TEST_F (CalculatorTest, Isl_10111_100_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"+--"};
    constexpr float etalonIsl  {-6.021f};
    constexpr float epsilonIsl {0.001f};
    // Act.
    const float testIsl {Calculator::Isl (codeOne, codeTwo)};
    // Assert.
    EXPECT_NEAR (etalonIsl, testIsl, epsilonIsl);
}



TEST_F (CalculatorTest, Mf_10110111000_Success)
{
    // Arange.
    const std::string code {"+-++-+++---"};
    constexpr float etalonMf  {(11.0f * 11.0f) / (2 * 5)};
    constexpr float epsilonMf {0.001f};
    // Act.
    const float testMf {Calculator::Mf (code)};
    // Assert.
    EXPECT_NEAR (etalonMf, testMf, epsilonMf);
}



TEST_F (CalculatorTest, Mf_1010110011111_Success)
{
    // Arange.
    const std::string code {"+-+-++--+++++"};
    constexpr float etalonMf  {(13.0f * 13.0f) / (2 * 6)};
    constexpr float epsilonMf {0.001f};
    // Act.
    const float testMf {Calculator::Mf (code)};
    // Assert.
    EXPECT_NEAR (etalonMf, testMf, epsilonMf);
}



TEST_F (CalculatorTest, Mf_10111_100_Success)
{
    // Arange.
    const std::string codeOne {"+-+++"};
    const std::string codeTwo {"+--"};
    constexpr float etalonMf  {4.000f};
    constexpr float epsilonMf {0.001f};
    // Act.
    const float testMf {Calculator::Mf (codeOne, codeTwo)};
    // Assert.
    EXPECT_NEAR (etalonMf, testMf, epsilonMf);
}



TEST_F (CalculatorTest, Db_1_to_5_Success)
{
    // Arange.
    constexpr int ml  {5};
    constexpr int psl {1};
    constexpr long double etalonDb {-13.979f};
    constexpr long double epsilonDb {0.001f};
    // Act.
    const long double testDb {Calculator::Db (ml, psl)};
    // Assert.
    EXPECT_NEAR (etalonDb, testDb, epsilonDb);
}



TEST_F (CalculatorTest, Db_1_to_13_Success)
{
    // Arange.
    constexpr int ml  {13};
    constexpr int psl {1};
    constexpr long double etalonDb {-22.279f};
    constexpr long double epsilonDb {0.001f};
    // Act.
    const long double testDb {Calculator::Db (ml, psl)};
    // Assert.
    EXPECT_NEAR (etalonDb, testDb, epsilonDb);
}
