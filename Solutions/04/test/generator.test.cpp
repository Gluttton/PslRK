#include "generator.h"
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
    EXPECT_EQ (Code ("0000000000001"), code);
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
    EXPECT_EQ (Code ("0000000000010"), code);
}



// Generator calls more then 255 times.
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
    EXPECT_EQ (Code ("0000100000000"), code);
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
        EXPECT_EQ (i,   code.to_ulong () );
    }
}

