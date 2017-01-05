#include "generator.test.h"
#include <gtest/gtest.h>



class GeneratorTest : public ::testing::Test
{
    public:
        explicit GeneratorTest ();
        virtual ~GeneratorTest () = default;

    protected:
        Code code;

        void SetUp    () override;
        void TearDown () override;
};



GeneratorTest::GeneratorTest ()
            : code {0}
{
}



void GeneratorTest::SetUp ()
{
    memset (&code, 0x00u, sizeof (code) );
}



void GeneratorTest::TearDown ()
{
}



// Generator calls first time.
TEST_F (GeneratorTest, FirstCallGetNextCodeSuccess)
{
    // Arange.
    Generator generator     {13};
    bool result             {false};
    __s32 modifiedBits      {0};

    // Act.
    result = generator.GetNextCode (code, modifiedBits);

    // Assert.
    EXPECT_EQ (false, result);
    EXPECT_EQ (0,     modifiedBits);
    EXPECT_EQ (0x01,  code [0]);
}



// Generator calls second time.
TEST_F (GeneratorTest, SecondCallGetNextCodeSuccess)
{
    // Arange.
    Generator generator     {13};
    bool result             {false};
    __s32 modifiedBits      {0};

    // Act.
    for (auto i = 0; i < 2; ++i) {
        result = generator.GetNextCode (code, modifiedBits);
    }

    // Assert.
    EXPECT_EQ (false, result);
    EXPECT_EQ (1,     modifiedBits);
    EXPECT_EQ (0x02,  code [0]);
}



// Generator calls more then 255 times, whereby significant bit gone out of last byte.
TEST_F (GeneratorTest, CallWithOverflowLastByteGetNextCodeSuccess)
{
    // Arange.
    Generator generator     {13};
    bool result             {false};
    __s32 modifiedBits      {0};

    // Act.
    for (auto i = 0; i < 256; ++i) {
        result = generator.GetNextCode (code, modifiedBits);
    }

    // Assert.
    EXPECT_EQ (false, result);
    EXPECT_EQ (8,     modifiedBits);
    EXPECT_EQ (0x00,  code [0]);
    EXPECT_EQ (0x01,  code [1]);
}



// Generator calls more then 255 times, whereby significant bit gone out of last byte.
TEST_F (GeneratorTest, CallAfterOverflowLastByteGetNextCodeSuccess)
{
    // Arange.
    Generator generator     {13};
    bool result             {false};
    __s32 modifiedBits      {0};

    // Act.
    for (auto i = 0; i < 257; ++i) {
        result = generator.GetNextCode (code, modifiedBits);
    }

    // Assert.
    EXPECT_EQ (false, result);
    EXPECT_EQ (0,     modifiedBits);
    EXPECT_EQ (0x01,  code [0]);
    EXPECT_EQ (0x01,  code [1]);
}



// Generator generates values for sequence of length four.
TEST_F (GeneratorTest, CalculateAllCombinationForLength_4_Success)
{
    // Arange.
    Generator generator     {13};
    bool result             {false};
    __s32 modifiedBits      {0};

    // Act, Assert.
    for (auto i = 1; i < (1 << 4); ++i) {
        result = generator.GetNextCode (code, modifiedBits);
        EXPECT_EQ (false, result);
        EXPECT_EQ (i,   code [0]);
    }
}



// Generator calculates max value for sequence of length two.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_2_Success)
{
    // Arange.
    GeneratorProxy generator{2};

    // Act, Assert.
    code = generator.CalculateMaxCode (2);

    // Assert.
    EXPECT_EQ (0x01, code [0]);
    for (size_t i = 1; i < code.size (); ++i) {
        EXPECT_EQ (0x00, code [i]);
    }
}



// Generator calculates max value for sequence of length nine.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_9_Success)
{
    // Arange.
    GeneratorProxy generator{9};

    // Act, Assert.
    code = generator.CalculateMaxCode (9);

    // Assert.
    EXPECT_EQ (0xff, code [0]);
    for (size_t i = 1; i < code.size (); ++i) {
        EXPECT_EQ (0x00, code [i]);
    }
}



// Generator calculates max value for sequence of length ten.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_10_Success)
{
    // Arange.
    GeneratorProxy generator{10};

    // Act, Assert.
    code = generator.CalculateMaxCode (10);

    // Assert.
    EXPECT_EQ (0xff, code [0]);
    EXPECT_EQ (0x01, code [1]);
    for (size_t i = 2; i < code.size (); ++i) {
        EXPECT_EQ (0x00, code [i]);
    }
}

