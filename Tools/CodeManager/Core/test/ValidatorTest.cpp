#include "ValidatorInterface.h"
#include <gtest/gtest.h>
#include <string>



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
    IValidator * v;
    const std::string validStringView {"+-"};
    constexpr int etalonResult {-1};
    // Act.
    const int testResult = v->ValidateStringView (validStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateStringViewFail)
{
    // Arange.
    IValidator * v;
    std::string invalidStringView {"0+-"};
    int etalonResult {0};
    // Act.
    int testResult = v->ValidateStringView (invalidStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidStringView = "+a-";
    etalonResult = 1;
    // Act.
    testResult = v->ValidateStringView (invalidStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidStringView = "+- ";
    etalonResult = 2;
    // Act.
    testResult = v->ValidateStringView (invalidStringView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}



TEST_F (ValidatorTest, ValidateHexViewSuccess)
{
    // Arange.
    IValidator * v;
    std::string validHexView {"0"};
    // Act.
    int result = v->ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);

    // Arange.
    validHexView = "01";
    // Act.
    result = v->ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);

    // Arange.
    validHexView = "0f";
    // Act.
    result = v->ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);

    // Arange.
    validHexView = "0F";
    // Act.
    result = v->ValidateHexView (validHexView);
    // Assert.
    EXPECT_EQ (-1, result);
}



TEST_F (ValidatorTest, ValidateHexViewFail)
{
    // Arange.
    IValidator * v;
    std::string invalidHexView {"+0"};
    int etalonResult {0};
    // Act.
    int testResult = v->ValidateHexView (invalidHexView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidHexView = "0a1";
    etalonResult = 1;
    // Act.
    testResult = v->ValidateHexView (invalidHexView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);


    // Arange.
    invalidHexView = "00 ";
    etalonResult = 2;
    // Act.
    testResult = v->ValidateHexView (invalidHexView);
    // Assert.
    EXPECT_EQ (etalonResult, testResult);
}
