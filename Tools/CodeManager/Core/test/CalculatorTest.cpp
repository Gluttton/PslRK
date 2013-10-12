#include "CalculatorInterface.h"
#include <gtest/gtest.h>
#include <string>



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



TEST_F (CalculatorTest, CalculateAcfSuccess)
{
    // Arange.
    ICalculator * c;
    const std::string code {"+-+++"};
    const std::vector <int> etalonAcf {1, 0, 1, 0, 5, 0, 1, 0, 1};
    // Act.
    const std::vector <int> testAcf = c->CalculateAcf (code);
    // Assert.
    EXPECT_EQ (etalonAcf, testAcf);
}



TEST_F (CalculatorTest, CalculateMslSuccess)
{
    // Arange.
    ICalculator * c;
    const std::string code {"+-+++"};
    constexpr int etalonMsl {1};
    // Act.
    const int testMsl = c->CalculateMsl (code);
    // Assert.
    EXPECT_EQ (etalonMsl, testMsl);
}
