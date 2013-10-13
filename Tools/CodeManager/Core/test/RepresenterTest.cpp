#include "Representer.h"
#include <gtest/gtest.h>



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
    IRepresenter * r = new Representer ();
    const std::string hexView {"1f35"};
    const std::string etalonStringView {"+++++--++-+-+"};
    // Act.
    const std::string testStringView = r->HexViewToStringView (hexView);
    // Assert.
    EXPECT_EQ (etalonStringView, testStringView);

    // Clearing.
    delete r;
}



TEST_F (RepresenterTest, HexViewToStringLeadingZeroViewSuccess)
{
    // Arange.
    IRepresenter * r = new Representer ();
    const std::string hexView {"00ca"};
    const std::string etalonStringView {"-----++--+-+-"};
    constexpr size_t codeLength {13};
    // Act.
    const std::string testStringView = r->HexViewToStringView (hexView, codeLength);
    // Assert.
    EXPECT_EQ (etalonStringView, testStringView);

    // Clearing.
    delete r;
}



TEST_F (RepresenterTest, StringViewToHexViewSuccess)
{
    // Arange.
    IRepresenter * r = new Representer ();
    const std::string stringView {"+++++--++-+-+"};
    const std::string etalonHexView {"1f35"};
    // Act.
    const std::string testHexView = r->StringViewToHexView (stringView);
    // Assert.
    EXPECT_EQ (etalonHexView, testHexView);

    // Clearing.
    delete r;
}



TEST_F (RepresenterTest, ReverseCodeSuccess)
{
    // Arange.
    IRepresenter * r = new Representer ();
    const std::string code {"+++++--++-+-+"};
    const std::string etalonReversedCode {"+-+-++--+++++"};
    // Act.
    const std::string testReversedCode = r->ReverseCode (code);
    // Assert.
    EXPECT_EQ (etalonReversedCode, testReversedCode);

    // Clearing.
    delete r;
}



TEST_F (RepresenterTest, InverseCode)
{
    // Arange.
    IRepresenter * r = new Representer ();
    const std::string code {"+++++--++-+-+"};
    const std::string etalonInversedCode {"-----++--+-+-"};
    // Act.
    const std::string testInversedCode = r->InverseCode (code);
    // Assert.
    EXPECT_EQ (etalonInversedCode, testInversedCode);

    // Clearing.
    delete r;
}



TEST_F (RepresenterTest, GenerateCodeFamilySuccess)
{
    // Arange.
    IRepresenter * r = new Representer ();
    const std::string code {"+++++--++-+-+"};
    const std::array <std::string, 4> etalonCodeFamily {
        "+++++--++-+-+",
        "+-+-++--+++++",
        "-----++--+-+-",
        "-+-+--++-----"
    };
    // Act.
    const std::array <std::string, 4> testCodeFamily = r->GenerateCodeFamily (code);
    // Assert.
    EXPECT_EQ (etalonCodeFamily, testCodeFamily);

    // Clearing.
    delete r;
}



TEST_F (RepresenterTest, DetectCodeId_13_Success)
{
    // Arange.
    IRepresenter * r = new Representer ();
    const std::string code {"+++++--++-+-+"};
    const std::string etalonCodeId {"1f35"};
    // Act.
    const std::string testCodeId = r->DetectCodeId (code);
    // Assert.
    EXPECT_EQ (etalonCodeId, testCodeId);

    // Clearing.
    delete r;
}



TEST_F (RepresenterTest, DetectCodeId_51_Success)
{
    // Arange.
    IRepresenter * r = new Representer ();
    const std::string code {"16dab767701c7"};
    const std::string etalonCodeId {"71c077376adb4"};

    // Act.
    const std::string testCodeId = r->DetectCodeId (r->HexViewToStringView (code, 51) );
    // Assert.
    EXPECT_EQ (etalonCodeId, testCodeId);

    // Clearing.
    delete r;
}
