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
    const int testResult = Validator::ValidateStringView (validStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateStringViewFail)
{
    // Arange.
    std::string invalidStringView {"0+-"};
    int etalonResult {0};
    // Act.
    int testResult = Validator::ValidateStringView (invalidStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidStringView = "+a-";
    etalonResult = 1;
    // Act.
    testResult = Validator::ValidateStringView (invalidStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidStringView = "+- ";
    etalonResult = 2;
    // Act.
    testResult = Validator::ValidateStringView (invalidStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexViewSuccess)
{
    // Arange.
    std::string validHexView {"0"};
    // Act.
    int result = Validator::ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);

    // Arange.
    validHexView = "01";
    // Act.
    result = Validator::ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);

    // Arange.
    validHexView = "0f";
    // Act.
    result = Validator::ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);

    // Arange.
    validHexView = "0F";
    // Act.
    result = Validator::ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);
}



TEST_F (ValidatorTest, ValidateHexViewFail)
{
    // Arange.
    std::string invalidHexView {"+0"};
    int etalonResult {0};
    // Act.
    int testResult = Validator::ValidateHexView (invalidHexView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidHexView = "0j1";
    etalonResult = 1;
    // Act.
    testResult = Validator::ValidateHexView (invalidHexView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidHexView = "00 ";
    etalonResult = 2;
    // Act.
    testResult = Validator::ValidateHexView (invalidHexView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}