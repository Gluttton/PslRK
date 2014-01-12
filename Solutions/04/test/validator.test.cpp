#include "validator.h"
#include "generator.mock.h"
#include <gtest/gtest.h>



using testing::_;



class ValidatorTest : public ::testing::Test
{
};



// Case: validating of Barker code of length two.
// Check:
// - exit code must be successful.
TEST_F (ValidatorTest, Validate_00_Success)
{
    // Arange.
    constexpr __s32 length          {2};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 0);
}



// Case: validating of Barker code of length two.
// Check:
// - exit code must be successful.
TEST_F (ValidatorTest, Validate_10_Success)
{
    // Arange.
    constexpr __s32 length          {2};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0x02u}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 0);
}



// Case: validating of Barker code of length three.
// Check:
// - exit code must be successful.
TEST_F (ValidatorTest, Validate_001_Success)
{
    // Arange.
    constexpr __s32 length          {3};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0x01u}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 0);
}



// Case: validating of Barker code of length four.
// Check:
// - exit code must be successful.
TEST_F (ValidatorTest, Validate_0001_Success)
{
    // Arange.
    constexpr __s32 length          {4};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0x01u}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 0);
}



// Case: validating of Barker code of length four.
// Check:
// - exit code must be successful.
TEST_F (ValidatorTest, Validate_0100_Success)
{
    // Arange.
    constexpr __s32 length          {4};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0x04u}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 0);
}



// Case: validating of Barker code of length five.
// Check:
// - exit code must be successful.
TEST_F (ValidatorTest, Validate_00010_Success)
{
    // Arange.
    constexpr __s32 length          {5};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0x02u}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 0);
}



// Case: validating of Barker code of length seven.
// Check:
// - exit code must be successful.
TEST_F (ValidatorTest, Validate_0001101_Success)
{
    // Arange.
    constexpr __s32 length          {7};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0x0Du}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 0);
}



// Case: validating of Barker code of length eleven.
// Check:
// - exit code must be successful.
TEST_F (ValidatorTest, Validate_00011101101_Success)
{
    // Arange.
    constexpr __s32 length          {11};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0xEDu}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 0);
}



// Case: validating of Barker code of length thirteen.
// Check:
// - exit code must be successful.
TEST_F (ValidatorTest, Validate_0000011001010_Success)
{
    // Arange.
    constexpr __s32 length          {13};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0xCAu}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 0);
}



// Case: validating of code of length five which is not Barker code.
// Check:
// - exit code must be unsuccessful.
TEST_F (ValidatorTest, Validate_10110_Fail)
{
    // Arange.
    constexpr __s32 length          {5};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0x16u}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 1);
}



// Case: validating of code of length thirteen which is not Barker code.
// Check:
// - exit code must be unsuccessful.
TEST_F (ValidatorTest, Validate_1111100110110_Fail)
{
    // Arange.
    constexpr __s32 length          {13};
    constexpr __s32 sideLobeLimit   {1};
    GeneratorMock generator {nullptr, length, length};
    Validator validator {& generator};
    EXPECT_CALL (generator, GetNextCode (_, _, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (length),
                    testing::SetArgReferee <1> (CodeContainer {0x36u, 0x1Fu}),
                    testing::SetArgReferee <2> (sideLobeLimit)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (result, 1);
}



// Case: validating all sequences of length four.
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
    constexpr __s32 begin   {3};
    constexpr __s32 end     {5};
    Generator generator     {nullptr, begin, end};
    Validator validator     {&generator};
    __u8 etalon [] {0,   1,   1,   0,   1,   0,   0,   1,   1,   0,   0,   1,   0,   1,   1,   0};
    //              0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
    //                0001 0010      0100           0111 1000           1011      1101 1110
    __u8 test   [] {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};

    // Act.
    while (!validator.SetNextCode () ) {
        if (!validator.Validate () && validator.length == 4) {
            test [validator.code.u64 [0] & 0x0F] = 1;
        }
    }

    // Assert.
    for (size_t i = 0; i < sizeof (etalon); ++i) {
        EXPECT_EQ (etalon [i], test [i]);
    }
}
