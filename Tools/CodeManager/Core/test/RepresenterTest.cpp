#include "Representer.h"
#include <gtest/gtest.h>



using Pslrk::Core::Representer;



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



TEST_F (RepresenterTest, HexViewToStringViewSuccess)
{
    // Arange.
    const std::string hexView {"1f35"};
    const std::string etalonStringView {"+++++--++-+-+"};
    // Act.
    const std::string testStringView = Representer::HexViewToStringView (hexView);
    // Assert.
    EXPECT_EQ (etalonStringView, testStringView);
}



TEST_F (RepresenterTest, HexViewToStringLeadingZeroViewSuccess)
{
    // Arange.
    const std::string hexView {"00ca"};
    const std::string etalonStringView {"-----++--+-+-"};
    constexpr size_t codeLength {13};
    // Act.
    const std::string testStringView = Representer::HexViewToStringView (hexView, codeLength);
    // Assert.
    EXPECT_EQ (etalonStringView, testStringView);
}



TEST_F (RepresenterTest, StringViewToHexViewSuccess)
{
    // Arange.
    const std::string stringView {"+++++--++-+-+"};
    const std::string etalonHexView {"1f35"};
    // Act.
    const std::string testHexView = Representer::StringViewToHexView (stringView);
    // Assert.
    EXPECT_EQ (etalonHexView, testHexView);
}



TEST_F (RepresenterTest, ReverseCodeSuccess)
{
    // Arange.
    const std::string code {"+++++--++-+-+"};
    const std::string etalonReversedCode {"+-+-++--+++++"};
    // Act.
    const std::string testReversedCode = Representer::ReverseCode (code);
    // Assert.
    EXPECT_EQ (etalonReversedCode, testReversedCode);
}



TEST_F (RepresenterTest, InverseCode)
{
    // Arange.
    const std::string code {"+++++--++-+-+"};
    const std::string etalonInversedCode {"-----++--+-+-"};
    // Act.
    const std::string testInversedCode = Representer::InverseCode (code);
    // Assert.
    EXPECT_EQ (etalonInversedCode, testInversedCode);
}



TEST_F (RepresenterTest, GenerateCodeFamilySuccess)
{
    // Arange.
    const std::string code {"+++++--++-+-+"};
    const std::array <std::string, 4> etalonCodeFamily {
        "+++++--++-+-+",
        "+-+-++--+++++",
        "-----++--+-+-",
        "-+-+--++-----"
    };
    // Act.
    const std::array <std::string, 4> testCodeFamily = Representer::GenerateCodeFamily (code);
    // Assert.
    EXPECT_EQ (etalonCodeFamily, testCodeFamily);
}



TEST_F (RepresenterTest, DetectCodeId_13_Success)
{
    // Arange.
    const std::string code {"+++++--++-+-+"};
    const std::string etalonCodeId {"1f35"};
    // Act.
    const std::string testCodeId = Representer::DetectCodeId (code);
    // Assert.
    EXPECT_EQ (etalonCodeId, testCodeId);
}



TEST_F (RepresenterTest, DetectCodeId_51_Success)
{
    // Arange.
    const std::string code {"16dab767701c7"};
    const std::string etalonCodeId {"71c077376adb4"};

    // Act.
    const std::string testCodeId = Representer::DetectCodeId (Representer::HexViewToStringView (code, 51) );
    // Assert.
    EXPECT_EQ (etalonCodeId, testCodeId);
}