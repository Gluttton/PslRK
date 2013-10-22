#include "Calculator.h"
#include <gtest/gtest.h>



using Pslrk::Core::Calculator;



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



TEST_F (CalculatorTest, CalculateMsl_10111_Success)
{
    // Arange.
    const std::string code {"+-+++"};
    constexpr int etalonMsl {1};
    // Act.
    const int testMsl {Calculator::CalculateMsl (code)};
    // Assert.
    EXPECT_EQ (etalonMsl, testMsl);
}



TEST_F (CalculatorTest, CalculateMsl_00011010_Success)
{
    // Arange.
    const std::string code {"---++-+-"};
    constexpr int etalonMsl {2};
    // Act.
    const int testMsl {Calculator::CalculateMsl (code)};
    // Assert.
    EXPECT_EQ (etalonMsl, testMsl);
}