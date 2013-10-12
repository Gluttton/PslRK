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
