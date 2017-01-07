#include "validator.h"
#include <gtest/gtest.h>



class ValidatorTest : public ::testing::Test
{
};



// Validating of Barker code of length two.
TEST_F (ValidatorTest, Validate_00_Success)
{
    // Arange.
    constexpr int L {2};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("00");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length two.
TEST_F (ValidatorTest, Validate_10_Success)
{
    // Arange.
    constexpr int L {2};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("10");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length three.
TEST_F (ValidatorTest, Validate_001_Success)
{
    // Arange.
    constexpr int L {3};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("001");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length four.
TEST_F (ValidatorTest, Validate_0001_Success)
{
    // Arange.
    constexpr int L {4};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("0001");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length four.
TEST_F (ValidatorTest, Validate_0100_Success)
{
    // Arange.
    constexpr int L {4};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("0100");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length five.
TEST_F (ValidatorTest, Validate_00010_Success)
{
    // Arange.
    constexpr int L {5};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("00010");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length seven.
TEST_F (ValidatorTest, Validate_0001101_Success)
{
    // Arange.
    constexpr int L {7};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("0001101");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length eleven.
TEST_F (ValidatorTest, Validate_00011101101_Success)
{
    // Arange.
    constexpr int L {11};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("00011101101");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length thirteen.
TEST_F (ValidatorTest, Validate_0000011001010_Success)
{
    // Arange.
    constexpr int L {13};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("0000011001010");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of code of length five which is not Barker code.
TEST_F (ValidatorTest, Validate_10110_Fail)
{
    // Arange.
    constexpr int L {5};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("10110");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (false, result);
}



// Validating of code of length thirteen which is not Barker code.
TEST_F (ValidatorTest, Validate_1111100110110_Fail)
{
    // Arange.
    constexpr int L {13};
    Generator <L> generator {};
    Validator <L, 1> validator {generator};
    generator.code = std::bitset <L> ("1111100110110");

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (false, result);
}



// Validating all sequences of length four.
// Check:
// - code 1101 must be detected;
// - code 1011 must be detected;
// - code 0010 must be detected;
// - code 0100 must be detected;
// - code 1110 must be detected;
// - code 0111 must be detected;
// - code 0001 must be detected;
// - code 1000 must be detected.
TEST_F (ValidatorTest, ValidateAllCombinationsOfLenth_4_Success)
{
    // Arange.
    constexpr int L {4};
    Generator <L>    generator {};
    Validator <L, 1> validator {generator};
    int etalon [] {0,   1,   1,   0,   1,   0,   0,   1,   1/*,   0,   0,   1,   0,   1,   1,   0*/};
    //             0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
    //               0001 0010      0100           0111 1000           1011      1101 1110
    int test   [] {0,   0,   0,   0,   0,   0,   0,   0,   0/*,   0,   0,   0,   0,   0,   0,   0*/};

    // Act.
    while (!validator.SetNextCode () ) {
        if (validator.Validate () ) {
            test [generator.code.to_ulong () & 0x0F] = 1;
        }
    }

    // Assert.
    for (size_t i = 0; i < sizeof (etalon) / sizeof (etalon [0]); ++i) {
        SCOPED_TRACE (i);
        EXPECT_EQ (etalon [i], test [i]);
    }
}
