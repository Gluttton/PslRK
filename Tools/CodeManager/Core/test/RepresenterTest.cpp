#include "Representer.h"
#include "Exception.h"
#include <gtest/gtest.h>



using Pslrk::Core::Representer;
using Pslrk::Core::codeFamilySize;
using Pslrk::Core::ExceptionInvalidStringView;
using Pslrk::Core::ExceptionInvalidHexView;



class RepresenterTest : public ::testing::Test
{
    protected:
        virtual void SetUp    () override;
        virtual void TearDown () override;
};



void RepresenterTest::SetUp ()
{
}



void RepresenterTest::TearDown ()
{
}



TEST_F (RepresenterTest, HexViewToStringViewInvalidViewThrow)
{
    // Arange.
    const std::string hexView {"1j35"};
    // Act, Assert.
    EXPECT_THROW (Representer::HexViewToStringView (hexView), ExceptionInvalidHexView);
}



TEST_F (RepresenterTest, HexViewToStringViewSuccess)
{
    // Arange.
    const std::string hexView {"1f35"};
    const std::string etalonStringView {"+++++--++-+-+"};
    // Act.
    const std::string testStringView {Representer::HexViewToStringView (hexView)};
    // Assert.
    EXPECT_EQ (etalonStringView, testStringView);
}



TEST_F (RepresenterTest, HexViewToStringViewLeadingZeroInvalidViewThrow)
{
    // Arange.
    const std::string hexView {"1j35"};
    constexpr size_t codeLength {13};
    // Act, Assert.
    EXPECT_THROW (Representer::HexViewToStringView (hexView, codeLength), ExceptionInvalidHexView);
}



TEST_F (RepresenterTest, HexViewToStringLeadingZeroViewSuccess)
{
    // Arange.
    const std::string hexView {"00ca"};
    const std::string etalonStringView {"-----++--+-+-"};
    constexpr size_t codeLength {13};
    // Act.
    const std::string testStringView {Representer::HexViewToStringView (hexView, codeLength)};
    // Assert.
    EXPECT_EQ (etalonStringView, testStringView);
}



TEST_F (RepresenterTest, StringViewToHexViewInvalidViewThrow)
{
    // Arange.
    const std::string stringView {"+++++--1+-+-+"};
    // Act, Assert.
    EXPECT_THROW (Representer::StringViewToHexView (stringView), ExceptionInvalidStringView);
}



TEST_F (RepresenterTest, StringViewToHexViewSuccess)
{
    // Arange.
    const std::string stringView {"+++++--++-+-+"};
    const std::string etalonHexView {"1f35"};
    // Act.
    const std::string testHexView {Representer::StringViewToHexView (stringView)};
    // Assert.
    EXPECT_EQ (etalonHexView, testHexView);
}



TEST_F (RepresenterTest, ReverseCodeInvalidViewThrow)
{
    // Arange.
    const std::string stringView {"+++++--1+-+-+"};
    // Act, Assert.
    EXPECT_THROW (Representer::ReverseCode (stringView), ExceptionInvalidStringView);
}



TEST_F (RepresenterTest, ReverseCodeSuccess)
{
    // Arange.
    const std::string stringView {"+++++--++-+-+"};
    const std::string etalonReversedCode {"+-+-++--+++++"};
    // Act.
    const std::string testReversedCode {Representer::ReverseCode (stringView)};
    // Assert.
    EXPECT_EQ (etalonReversedCode, testReversedCode);
}



TEST_F (RepresenterTest, InverseCodeInvalidViewThrow)
{
    // Arange.
    const std::string stringView {"+++++--1+-+-+"};
    // Act, Assert.
    EXPECT_THROW (Representer::InverseCode (stringView), ExceptionInvalidStringView);
}



TEST_F (RepresenterTest, InverseCode)
{
    // Arange.
    const std::string stringView {"+++++--++-+-+"};
    const std::string etalonInversedCode {"-----++--+-+-"};
    // Act.
    const std::string testInversedCode {Representer::InverseCode (stringView)};
    // Assert.
    EXPECT_EQ (etalonInversedCode, testInversedCode);
}



TEST_F (RepresenterTest, GenerateCodeFamilyInvalidViewThrow)
{
    // Arange.
    const std::string stringView {"+++++--1+-+-+"};
    // Act, Assert.
    EXPECT_THROW (Representer::GenerateCodeFamily (stringView), ExceptionInvalidStringView);
}



TEST_F (RepresenterTest, GenerateCodeFamilySuccess)
{
    // Arange.
    const std::string stringView {"+++++--++-+-+"};
    const std::array <std::string, codeFamilySize> etalonCodeFamily {
        "+++++--++-+-+",
        "+-+-++--+++++",
        "-----++--+-+-",
        "-+-+--++-----"
    };
    // Act.
    const std::array <std::string, codeFamilySize> testCodeFamily = Representer::GenerateCodeFamily (stringView);
    // Assert.
    EXPECT_EQ (etalonCodeFamily, testCodeFamily);
}



TEST_F (RepresenterTest, DetectCodeIdInvalidViewThrow)
{
    // Arange.
    const std::string stringView {"+++++--1+-+-+"};
    // Act, Assert.
    EXPECT_THROW (Representer::DetectCodeId (stringView), ExceptionInvalidStringView);
}



TEST_F (RepresenterTest, DetectCodeId_13_Success)
{
    // Arange.
    const std::string stringView {"+++++--++-+-+"};
    const std::string etalonCodeId {"1f35"};
    // Act.
    const std::string testCodeId {Representer::DetectCodeId (stringView)};
    // Assert.
    EXPECT_EQ (etalonCodeId, testCodeId);
}



TEST_F (RepresenterTest, DetectCodeId_51_Success)
{
    // Arange.
    const std::string stringView {"16dab767701c7"};
    const std::string etalonCodeId {"71c077376adb4"};

    // Act.
    const std::string testCodeId {Representer::DetectCodeId (Representer::HexViewToStringView (stringView, 51) )};
    // Assert.
    EXPECT_EQ (etalonCodeId, testCodeId);
}