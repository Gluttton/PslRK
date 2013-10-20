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
    Validator validator;
    const std::string validStringView {"+-"};
    constexpr int etalonResult {-1};
    // Act.
    const int testResult = validator.ValidateStringView (validStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateStringViewFail)
{
    // Arange.
    Validator validator;
    std::string invalidStringView {"0+-"};
    int etalonResult {0};
    // Act.
    int testResult = validator.ValidateStringView (invalidStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidStringView = "+a-";
    etalonResult = 1;
    // Act.
    testResult = validator.ValidateStringView (invalidStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidStringView = "+- ";
    etalonResult = 2;
    // Act.
    testResult = validator.ValidateStringView (invalidStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexViewSuccess)
{
    // Arange.
    Validator validator;
    std::string validHexView {"0"};
    // Act.
    int result = validator.ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);

    // Arange.
    validHexView = "01";
    // Act.
    result = validator.ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);

    // Arange.
    validHexView = "0f";
    // Act.
    result = validator.ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);

    // Arange.
    validHexView = "0F";
    // Act.
    result = validator.ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);
}



TEST_F (ValidatorTest, ValidateHexViewFail)
{
    // Arange.
    Validator validator;
    std::string invalidHexView {"+0"};
    int etalonResult {0};
    // Act.
    int testResult = validator.ValidateHexView (invalidHexView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidHexView = "0j1";
    etalonResult = 1;
    // Act.
    testResult = validator.ValidateHexView (invalidHexView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidHexView = "00 ";
    etalonResult = 2;
    // Act.
    testResult = validator.ValidateHexView (invalidHexView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}