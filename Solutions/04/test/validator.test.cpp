#include "validator.h"
#include "generator.mock.h"
#include <gtest/gtest.h>



using testing::_;
using testing::AtLeast;



class ValidatorTest : public ::testing::Test
{
};



// Validating of Barker code of length two.
TEST_F (ValidatorTest, Validate_00_Success)
{
    // Arange.
    GeneratorMock generator {2};

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length two.
TEST_F (ValidatorTest, Validate_10_Success)
{
    // Arange.
    GeneratorMock generator {2};
    generator.code = Code ("000000000010");

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length three.
TEST_F (ValidatorTest, Validate_001_Success)
{
    // Arange.
    GeneratorMock generator {3};
    generator.code = Code ("000000000001");

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length four.
TEST_F (ValidatorTest, Validate_0001_Success)
{
    // Arange.
    GeneratorMock generator {4};
    generator.code = Code ("000000000001");

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length four.
TEST_F (ValidatorTest, Validate_0100_Success)
{
    // Arange.
    GeneratorMock generator {4};
    generator.code = Code ("000000000100");

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length five.
TEST_F (ValidatorTest, Validate_00010_Success)
{
    // Arange.
    GeneratorMock generator {5};
    generator.code = Code ("000000000010");

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length seven.
TEST_F (ValidatorTest, Validate_0001101_Success)
{
    // Arange.
    GeneratorMock generator {7};
    generator.code = Code ("000000001101");

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length eleven.
TEST_F (ValidatorTest, Validate_00011101101_Success)
{
    // Arange.
    GeneratorMock generator {11};
    generator.code = Code ("000011101101");

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of Barker code of length thirteen.
TEST_F (ValidatorTest, Validate_0000011001010_Success)
{
    // Arange.
    GeneratorMock generator {13};
    generator.code = Code ("000011001010");

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (true, result);
}



// Validating of code of length five which is not Barker code.
TEST_F (ValidatorTest, Validate_10110_Fail)
{
    // Arange.
    GeneratorMock generator {5};
    generator.code [0] = 0x16;

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

    // Act.
    const auto result = validator.Validate ();

    // Assert.
    EXPECT_EQ (false, result);
}



// Validating of code of length thirteen which is not Barker code.
TEST_F (ValidatorTest, Validate_1111100110110_Fail)
{
    // Arange.
    GeneratorMock generator {13};
    generator.code [0] = 0x1F;

    Validator validator {generator};
    EXPECT_CALL (generator, GetNextCode (_, _) )
            .WillOnce (
                DoAll (
                    testing::SetArgReferee <0> (generator.code),
                    testing::SetArgReferee <1> (generator.modifiedBits)
                )
            );
    validator.SetNextCode ();

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
    Generator generator     {4};
    Validator validator     {generator};
    __u32 etalon [] {0,   1,   1,   0,   1,   0,   0,   1/*,   1,   0,   0,   1,   0,   1,   1,   0*/};
    //               0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
    //                 0001 0010      0100           0111 1000           1011      1101 1110
    __u32 test   [] {0,   0,   0,   0,   0,   0,   0,   0/*,   0,   0,   0,   0,   0,   0,   0,   0*/};

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
