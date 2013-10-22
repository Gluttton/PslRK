#include "Validator.h"
#include <gtest/gtest.h>



using Pslrk::Core::Validator;



class ValidatorTest : public ::testing::Test
{
    protected:
        virtual void SetUp    () override;
        virtual void TearDown () override;
};



void ValidatorTest::SetUp ()
{
}



void ValidatorTest::TearDown ()
{
}



TEST_F (ValidatorTest, ValidateStringViewSuccess)
{
    // Arange.
    const std::string validStringView {"+-"};
    constexpr int etalonResult {-1};
    // Act.
    const int testResult {Validator::ValidateStringView (validStringView) };
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateStringViewWrongSymbolInFirstPositionFail)
{
    // Arange.
    const std::string invalidStringView {"0+-"};
    constexpr int etalonResult {0};
    // Act.
    const int testResult {Validator::ValidateStringView (invalidStringView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateStringViewWrongSymbolInMiddlePositionFail)
{
    // Arange.
    const std::string invalidStringView {"+a-"};
    constexpr int etalonResult {1};
    // Act.
    const int testResult {Validator::ValidateStringView (invalidStringView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateStringViewWrongSymbolInLastPositionFail)
{
    // Arange.
    const std::string invalidStringView {"+- "};
    constexpr int etalonResult {2};
    // Act.
    const int testResult {Validator::ValidateStringView (invalidStringView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexView_0_Success)
{
    // Arange.
    const std::string validHexView {"0"};
    constexpr int etalonResult {-1};
    // Act.
    const int testResult {Validator::ValidateHexView (validHexView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexView_01_Success)
{
    // Arange.
    const std::string validHexView {"01"};
    constexpr int etalonResult {-1};
    // Act.
    const int testResult {Validator::ValidateHexView (validHexView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexView_0f_Success)
{
    // Arange.
    const std::string validHexView {"0f"};
    constexpr int etalonResult {-1};
    // Act.
    const int testResult {Validator::ValidateHexView (validHexView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexView_0F_Success)
{
    // Arange.
    const std::string validHexView {"0F"};
    constexpr int etalonResult {-1};
    // Act.
    const int testResult {Validator::ValidateHexView (validHexView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexViewWrongSymbolInFirstPositionFail)
{
    // Arange.
    const std::string invalidHexView {"+0"};
    constexpr int etalonResult {0};
    // Act.
    const int testResult {Validator::ValidateHexView (invalidHexView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexViewWrongSymbolInMiddlePositionFail)
{
    // Arange.
    const std::string invalidHexView {"0j1"};
    constexpr int etalonResult {1};
    // Act.
    const int testResult {Validator::ValidateHexView (invalidHexView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexViewWrongSymbolInLastPositionFail)
{
    // Arange.
    const std::string invalidHexView {"00 "};
    constexpr int etalonResult {2};
    // Act.
    const int testResult {Validator::ValidateHexView (invalidHexView)};
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}