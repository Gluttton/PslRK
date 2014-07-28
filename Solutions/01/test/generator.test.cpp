#include "generator.h"
#include <gtest/gtest.h>



class GeneratorTest : public ::testing::Test
{
    protected:
        Generator * generator;
        CodeContainer code;

        void SetUp    ();
        void TearDown ();
};



void GeneratorTest::SetUp ()
{
    memset (&code, 0x00, sizeof (code) );
}



void GeneratorTest::TearDown ()
{
}



// Case: generator calls first time.
// Check:
// - exit code must be successful;
// - length of sequence must be equal to the begin value;
// - all significant bits must be dropped.
TEST_F (GeneratorTest, FirstCallGetNextCodeSuccess)
{
    // Arange (not significant).
    const __u8 begin = 2;
    const __u8 end   = 5;
    // Arange (esential).
    generator        = new Generator (nullptr, begin, end);
    __u8 length      = 0;
    int result       = 0;

    // Act.
    for (__u64 i = 0; i < 1; ++i) {
        result = generator->GetNextCode (length, code);
    }

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (length, begin);
    EXPECT_EQ (code.u8 [0], 0x00);

    // Cleaning.
    delete generator;
}



// Case: generator calls second time.
// Check:
// - exit code must be successful;
// - length of sequence must be equal to the begin value;
// - in significant bits one must be returned.
TEST_F (GeneratorTest, SecondCallGetNextCodeSuccess)
{
    // Arange (not significant).
    const __u8 begin = 2;
    const __u8 end   = 5;
    // Arange (esential).
    generator        = new Generator (nullptr, begin, end);
    __u8 length      = 0;
    int result       = 0;

    // Act.
    for (__u64 i = 0; i < 2; ++i) {
        result = generator->GetNextCode (length, code);
    }

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (length, begin);
    EXPECT_EQ (code.u8 [0], 0x01);

    // Cleaning.
    delete generator;
}



// Case: generator calls more then 255 times, whereby significant bit gone out of last byte.
// Check:
// - exit code must be successful;
// - length of sequence must be corresponding;
// - in significant bits ones must be returned.
TEST_F (GeneratorTest, CallWithOverflowLastByteGetNextCodeSuccess)
{
    // Arange.
    const __u8 begin = 11;
    const __u8 end   = 13;
    generator        = new Generator (nullptr, begin, end);
    __u8 length      = 0;
    int result       = 0;

    // Act.
    for (__u64 i = 0; i < 257; ++i) {
        result = generator->GetNextCode (length, code);
    }

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (length, begin);
    EXPECT_EQ (code.u8 [0], 0x00);
    EXPECT_EQ (code.u8 [1], 0x01);

    // Cleaning.
    delete generator;
}



// Case: generator calls more then 255 times, whereby significant bit gone out of last byte.
// Check:
// - exit code must be successful;
// - length of sequence must be corresponding;
// - in significant bits ones must be returned.
TEST_F (GeneratorTest, CallAfterOverflowLastByteGetNextCodeSuccess)
{
    // Arange.
    const __u8 begin = 11;
    const __u8 end   = 13;
    generator        = new Generator (nullptr, begin, end);
    __u8 length      = 0;
    int result       = 0;

    // Act.
    for (__u64 i = 0; i < 258; ++i) {
        result = generator->GetNextCode (length, code);
    }

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (length, begin);
    EXPECT_EQ (code.u8 [0], 0x01);
    EXPECT_EQ (code.u8 [1], 0x01);

    // Cleaning.
    delete generator;
}



// Case: generator generates values for sequence of length four.
// Check:
// - exit code must be successful;
// - length of sequence must be corresponding;
// - all cases from 0000 to 1111 must be looked over.
TEST_F (GeneratorTest, CalculateAllCombinationForLength_4_Success)
{
    // Arange.
    const __u8 begin = 4;
    const __u8 end   = 4;
    generator        = new Generator (nullptr, begin, end);
    __u8 length      = 0;
    int result       = 0;

    // Act, Assert.
    for (__u64 i = 0; i < (1 << 4); ++i) {
        result = generator->GetNextCode (length, code);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, begin);
        EXPECT_EQ (code.u8 [0], i);
    }

    // Cleaning.
    delete generator;
}



// Case: generator generates values for sequences of length three, four and five.
// Check:
// - exit code must be successful;
// - length of sequence must be corresponding;
// - all cases from 000 to 11111 must be looked over.
TEST_F (GeneratorTest, CalculateAllCombinationForLength_3_4_5_Success)
{
    // Arange.
    const __u8 begin = 3;
    const __u8 end   = 5;
    generator        = new Generator (nullptr, begin, end);
    __u8 length      = 0;
    int result       = 0;

    // Act, Assert.
    // Looking over cases for sequence of length three.
    for (__u64 i = 1; i < (1 << 3); ++i) {
        result = generator->GetNextCode (length, code);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, 3);
        EXPECT_EQ (code.u8 [0], i);
        EXPECT_EQ (generator->maxCode.u8 [0], (1 << 3) - 1);
    }

    // Act, Assert.
    // Looking over cases for sequence of length four.
    for (__u64 i = 0; i < (1 << 4); ++i) {
        result = generator->GetNextCode (length, code);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, 4);
        EXPECT_EQ (code.u8 [0], i);
        EXPECT_EQ (generator->maxCode.u8 [0], (1 << 4) - 1);
    }

    // Act, Assert.
    // Looking over cases for sequence of length five.
    for (__u64 i = 0; i < (1 << 5); ++i) {
        result = generator->GetNextCode (length, code);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, 5);
        EXPECT_EQ (code.u8 [0], i);
        EXPECT_EQ (generator->maxCode.u8 [0], (1 << 5) - 1);
    }
    // Sequences of length five are end. Five is last value of length and error returns.
    result = generator->GetNextCode (length, code);
    EXPECT_NE (result, 0);

    // Cleaning.
    delete generator;
}



// Case: generator calculates max value for sequence of length two.
// Check:
// - exit code must be successful;
// - two last bits in last byte must be raised, and other bits must be dropped.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_2_Success)
{
    // Arange (not significant).
    const __u8 begin = 2;
    const __u8 end   = 5;
    // Arange (esential).
    generator        = new Generator (nullptr, begin, end);
    int result       = 0;

    // Act.
    result = generator->CalculateMaxCode (begin, code);

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (code.u8 [0], 0x03);
    for (__u64 i = 1; i < codeU8Count; ++i) {
        EXPECT_EQ (code.u8 [i], 0x00);
    }

    // Cleaning.
    delete generator;
}



// Case: generator calculates max value for sequence of length five.
// Check:
// - exit code must be successful;
// - five last bits in last byte must be raised, and other bits must be dropped.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_5_Success)
{
    // Arange (not significant).
    const __u8 end   = 13;
    // Arange (esential).
    const __u8 begin = 5;
    generator        = new Generator (nullptr, begin, end);
    int result       = 0;

    // Act.
    result = generator->CalculateMaxCode (begin, code);

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (code.u8 [0], 0x1F);
    for (__u64 i = 1; i < codeU8Count; ++i) {
        EXPECT_EQ (code.u8 [i], 0x00);
    }

    // Cleaning.
    delete generator;
}



// Case: generator calculates max value for sequence of length eight.
// Check:
// - exit code must be successful;
// - all bits in last byte must be raised, and other bits must be dropped.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_8_Success)
{
    // Arange (not significant).
    const __u8 end   = 13;
    // Arange (esential).
    const __u8 begin = 8;
    generator        = new Generator (nullptr, begin, end);
    int result       = 0;

    // Act.
    result = generator->CalculateMaxCode (begin, code);

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (code.u8 [0], 0xFF);
    for (__u64 i = 1; i < codeU8Count; ++i) {
        EXPECT_EQ (code.u8 [i], 0x00);
    }

    // Cleaning.
    delete generator;
}



// Case: generator calculates max value for sequence of length nine.
// Check:
// - exit code must be successful;
// - nine last bits must be raised, and other bits must be dropped.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_9_Success)
{
    // Arange (not significant).
    const __u8 end   = 13;
    // Arange (esential).
    const __u8 begin = 9;
    generator        = new Generator (nullptr, begin, end);
    int result       = 0;

    // Act.
    result = generator->CalculateMaxCode (begin, code);

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (code.u8 [0], 0xFF);
    EXPECT_EQ (code.u8 [1], 0x01);
    for (__u64 i = 2; i < codeU8Count; ++i) {
        EXPECT_EQ (code.u8 [i], 0x00);
    }

    // Cleaning.
    delete generator;
}
