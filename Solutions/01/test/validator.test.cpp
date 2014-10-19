#include "generator.h"
#include "validator.h"
#include <gtest/gtest.h>
#include <map>



// Case: validating of Barker code of length two.
// Check:
// - exit code must be successful.
TEST (ValidatorTest, Validate_00_Success)
{
    // Arange.
    Code code {'-', '-'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_TRUE (result);
}



// Case: validating of Barker code of length two.
// Check:
// - exit code must be successful.
TEST (ValidatorTest, Validate_10_Success)
{
    // Arange.
    Code code {'+', '-'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_TRUE (result);
}



// Case: validating of Barker code of length three.
// Check:
// - exit code must be successful.
TEST (ValidatorTest, Validate_001_Success)
{
    // Arange.
    Code code {'-', '-', '+'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_TRUE (result);
}



// Case: validating of Barker code of length four.
// Check:
// - exit code must be successful.
TEST (ValidatorTest, Validate_0001_Success)
{
    // Arange.
    Code code {'-', '-', '-', '+'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_TRUE (result);
}



// Case: validating of Barker code of length four.
// Check:
// - exit code must be successful.
TEST (ValidatorTest, Validate_0100_Success)
{
    // Arange.
    Code code {'-', '+', '-', '-'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_TRUE (result);
}



// Case: validating of Barker code of length five.
// Check:
// - exit code must be successful.
TEST (ValidatorTest, Validate_00010_Success)
{
    // Arange.
    Code code {'-', '-', '-', '+', '-'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_TRUE (result);
}



// Case: validating of Barker code of length seven.
// Check:
// - exit code must be successful.
TEST (ValidatorTest, Validate_0001101_Success)
{
    // Arange.
    Code code {'-', '-', '-', '+', '+', '-', '+'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_TRUE (result);
}



// Case: validating of Barker code of length eleven.
// Check:
// - exit code must be successful.
TEST (ValidatorTest, Validate_00011101101_Success)
{
    // Arange.
    Code code {'-', '-', '-', '+', '+', '+', '-', '+', '+', '-', '+'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_TRUE (result);
}



// Case: validating of Barker code of length thirteen.
// Check:
// - exit code must be successful.
TEST (ValidatorTest, Validate_0000011001010_Success)
{
    // Arange.
    Code code {'-', '-', '-', '-', '-', '+', '+', '-', '-', '+', '-', '+', '-'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_TRUE (result);
}



// Case: validating of code of length five which is not Barker code.
// Check:
// - exit code must be unsuccessful.
TEST (ValidatorTest, Validate_10110_Fail)
{
    // Arange.
    Code code {'+', '-', '+', '+', '-'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_FALSE (result);
}



// Case: validating of code of length thirteen which is not Barker code.
// Check:
// - exit code must be unsuccessful.
TEST (ValidatorTest, Validate_1111100110110_Fail)
{
    // Arange.
    Code code {'+', '+', '+', '+', '+', '-', '-', '+', '+', '-', '+', '+', '-'};

    // Act.
    const bool result = Validator::Validate (code);

    // Assert.
    EXPECT_FALSE (result);
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
TEST (ValidatorTest, ValidateAllCombinationsOfLenth_4_Success)
{
    // Arange.
    constexpr size_t begin          {4};
    constexpr size_t end            {4};
    Generator generator             {begin, end};
    Code * result                   {nullptr};

    std::map <Code, bool> etalon {
        {{'-', '-', '-', '-'}, false},
        {{'+', '-', '-', '-'}, true},
        {{'-', '+', '-', '-'}, true},
        {{'-', '-', '+', '-'}, true},
        {{'-', '-', '-', '+'}, true},
        {{'+', '+', '-', '-'}, false},
        {{'+', '-', '+', '-'}, false},
        {{'+', '-', '-', '+'}, false},
        {{'-', '+', '+', '-'}, false},
        {{'-', '+', '-', '+'}, false},
        {{'-', '-', '+', '+'}, false},
        {{'+', '+', '+', '-'}, true},
        {{'+', '+', '-', '+'}, true},
        {{'+', '-', '+', '+'}, true},
        {{'-', '+', '+', '+'}, true},
        {{'+', '+', '+', '+'}, false}
    };
    std::map <Code, bool> test {};

    // Act.
    while ( (result = generator.GetNextCode () ) ) {
        test [* result] = Validator::Validate (* result);
    }

    // Assert.
    EXPECT_EQ (etalon, test);
}
