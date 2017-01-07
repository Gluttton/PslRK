#include "generator.h"
#include <gtest/gtest.h>



class GeneratorTest : public ::testing::Test
{
};



// Generator calls first time.
TEST_F (GeneratorTest, FirstCallNextCodeSuccess)
{
    // Arange.
    Generator <13> generator{};

    // Act.
    bool result = generator.NextCode (0);

    // Assert.
    EXPECT_EQ (false, result);
    EXPECT_EQ (0,     generator.modifiedBits);
    EXPECT_EQ (std::bitset <13> ("0000000000001"), generator.code);
}



// Generator calls second time.
TEST_F (GeneratorTest, SecondCallNextCodeSuccess)
{
    // Arange.
    Generator <13> generator {};
    bool result {false};

    // Act.
    for (auto i = 0; i < 2; ++i) {
        result = generator.NextCode (0);
    }

    // Assert.
    EXPECT_EQ (false, result);
    EXPECT_EQ (1,     generator.modifiedBits);
    EXPECT_EQ (std::bitset <13> ("0000000000010"), generator.code);
}



// Generator generates values for sequence of length four.
TEST_F (GeneratorTest, CalculateAllCombinationForLength_4_Success)
{
    // Arange.
    Generator <4> generator {};
    bool result {false};

    // Act, Assert.
    for (auto i = 1; i < (1 << 3); ++i) {
        result = generator.NextCode (0);
        EXPECT_EQ (false, result);
        EXPECT_EQ (i,     generator.code.to_ulong () );
    }
}
