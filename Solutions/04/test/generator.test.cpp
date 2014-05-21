#include "generator.h"
#include <gtest/gtest.h>



class GeneratorTest : public ::testing::Test
{
    protected:
        Code code;

        void SetUp    () override;
        void TearDown () override;
};



void GeneratorTest::SetUp ()
{
    memset (&code, 0x00u, sizeof (code) );
}



void GeneratorTest::TearDown ()
{
}



// Case: generator calls first time.
// Check:
// - exit code must be successful;
// - length of sequence must be equal to the begin value;
// - in significant bits one must be returned.
TEST_F (GeneratorTest, FirstCallGetNextCodeSuccess)
{
    // Arange (not significant).
    constexpr __s32 begin   {3};
    constexpr __s32 end     {5};
    __s32 sideLobeLimit     {0};
    // Arange (esential).
    Generator generator     {nullptr, begin, end};
    __s32 length            {0};
    int result              {0};

    // Act.
    for (auto i = 0; i < 1; ++i) {
        result = generator.GetNextCode (length, code, sideLobeLimit);
    }

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (length, begin);
    EXPECT_EQ (code.u64 [0], 0x01);
}



// Case: generator calls second time.
// Check:
// - exit code must be successful;
// - length of sequence must be equal to the begin value;
// - in significant bits two must be returned.
TEST_F (GeneratorTest, SecondCallGetNextCodeSuccess)
{
    // Arange (not significant).
    constexpr __s32 begin   {3};
    constexpr __s32 end     {5};
    __s32 sideLobeLimit     {0};
    // Arange (esential).
    Generator generator     {nullptr, begin, end};
    __s32 length            {0};
    int result              {0};

    // Act.
    for (auto i = 0; i < 2; ++i) {
        result = generator.GetNextCode (length, code, sideLobeLimit);
    }

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (length, begin);
    EXPECT_EQ (code.u64 [0], 0x02);
}



// Case: generator calls more then 255 times, whereby significant bit gone out of last byte.
// Check:
// - exit code must be successful;
// - length of sequence must be corresponding;
// - in significant bits ones must be returned.
TEST_F (GeneratorTest, CallWithOverflowLastByteGetNextCodeSuccess)
{
    // Arange.
    constexpr __s32 begin   {11};
    constexpr __s32 end     {13};
    __s32 sideLobeLimit     {0};
    Generator generator     {nullptr, begin, end};
    __s32 length            {0};
    int result              {0};

    // Act.
    for (auto i = 0; i < 256; ++i) {
        result = generator.GetNextCode (length, code, sideLobeLimit);
    }

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (length, begin);
    EXPECT_EQ (code.u64 [0], 0x0100);
}



// Case: generator calls more then 255 times, whereby significant bit gone out of last byte.
// Check:
// - exit code must be successful;
// - length of sequence must be corresponding;
// - in significant bits ones must be returned.
TEST_F (GeneratorTest, CallAfterOverflowLastByteGetNextCodeSuccess)
{
    // Arange.
    constexpr __s32 begin   {11};
    constexpr __s32 end     {13};
    __s32 sideLobeLimit     {0};
    Generator generator     {nullptr, begin, end};
    __s32 length            {0};
    int result              {0};

    // Act.
    for (auto i = 0; i < 257; ++i) {
        result = generator.GetNextCode (length, code, sideLobeLimit);
    }

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (length, begin);
    EXPECT_EQ (code.u64 [0], 0x0101);
}



// Case: generator generates values for sequence of length four.
// Check:
// - exit code must be successful;
// - length of sequence must be corresponding;
// - all cases from 0001 to 1111 must be looked over.
TEST_F (GeneratorTest, CalculateAllCombinationForLength_4_Success)
{
    // Arange.
    constexpr __s32 begin   {4};
    constexpr __s32 end     {4};
    __s32 sideLobeLimit     {0};
    Generator generator     {nullptr, begin, end};
    __s32 length            {0};
    int result              {0};

    // Act, Assert.
    for (auto i = 1; i < (1 << 4); ++i) {
        result = generator.GetNextCode (length, code, sideLobeLimit);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, begin);
        EXPECT_EQ (code.u64 [0], i);
    }
}



// Case: generator generates values for sequences of length three, four and five.
// Check:
// - exit code must be successful;
// - length of sequence must be corresponding;
// - all cases from 001 to 11111 must be looked over.
TEST_F (GeneratorTest, CalculateAllCombinationForLength_3_4_5_Success)
{
    // Arange.
    constexpr __s32 begin   {3};
    constexpr __s32 end     {5};
    __s32 sideLobeLimit     {0};
    Generator generator     {nullptr, begin, end};
    __s32 length            {0};
    int result              {0};

    // Act, Assert.
    // Looking over cases for sequence of length three.
    for (auto i = 1; i < (1 << 3); ++i) {
        result = generator.GetNextCode (length, code, sideLobeLimit);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, 3);
        EXPECT_EQ (code.u64 [0], i);
        EXPECT_EQ (generator.maxCode.u64 [0], (1 << 3) - 1);
    }

    // Act, Assert.
    // Looking over cases for sequence of length four.
    for (auto i = 0; i < (1 << 4); ++i) {
        result = generator.GetNextCode (length, code, sideLobeLimit);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, 4);
        EXPECT_EQ (code.u64 [0], i);
        EXPECT_EQ (generator.maxCode.u64 [0], (1 << 4) - 1);
    }

    // Act, Assert.
    // Looking over cases for sequence of length five.
    for (auto i = 0; i < (1 << 5); ++i) {
        result = generator.GetNextCode (length, code, sideLobeLimit);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, 5);
        EXPECT_EQ (code.u64 [0], i);
        EXPECT_EQ (generator.maxCode.u64 [0], (1 << 5) - 1);
    }
    // Sequences of length five are end. Five is last value of length and error returns.
    result = generator.GetNextCode (length, code, sideLobeLimit);
    EXPECT_NE (result, 0);
}



// Case: generator calculates max value for sequence of length two.
// Check:
// - exit code must be successful;
// - two last bits in last byte must be raised, and other bits must be dropped.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_2_Success)
{
    // Arange (not significant).
    constexpr __s32 begin   {2};
    constexpr __s32 end     {5};
    // Arange (esential).
    Generator generator     {nullptr, begin, end};
    int result              {0};

    // Act.
    result = generator.CalculateMaxCode (begin, code);

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (code.u64 [0], 0x03);
    for (auto i = 1; i < Code::u64ChunkCount; ++i) {
        EXPECT_EQ (code.u64 [i], 0x00);
    }
}



// Case: generator calculates max value for sequence of length five.
// Check:
// - exit code must be successful;
// - five last bits in last byte must be raised, and other bits must be dropped.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_5_Success)
{
    // Arange (not significant).
    constexpr __s32 end     {13};
    // Arange (esential).
    constexpr __s32 begin   {5};
    Generator generator     {nullptr, begin, end};
    int result              {0};

    // Act.
    result = generator.CalculateMaxCode (begin, code);

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (code.u64 [0], 0x1F);
    for (auto i = 1; i < Code::u64ChunkCount; ++i) {
        EXPECT_EQ (code.u64 [i], 0x00);
    }
}



// Case: generator calculates max value for sequence of length eight.
// Check:
// - exit code must be successful;
// - all last bits in last byte must be raised, and other bits must be dropped.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_8_Success)
{
    // Arange (not significant).
    constexpr __s32 end     {13};
    // Arange (esential).
    constexpr __s32 begin   {8};
    Generator generator     {nullptr, begin, end};
    int result              {0};

    // Act.
    result = generator.CalculateMaxCode (begin, code);

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (code.u64 [0], 0xFF);
    for (auto i = 1; i < Code::u64ChunkCount; ++i) {
        EXPECT_EQ (code.u64 [i], 0x00);
    }
}



// Case: generator calculates max value for sequence of length nine.
// Check:
// - exit code must be successful;
// - nine last bits must be raised, and other bits must be dropped.
TEST_F (GeneratorTest, CalculateMaxCodeForLength_9_Success)
{
    // Arange (not significant).
    constexpr __s32 end     {13};
    // Arange (esential).
    constexpr __s32 begin   {9};
    Generator generator     {nullptr, begin, end};
    int result              {0};

    // Act.
    result = generator.CalculateMaxCode (begin, code);

    // Assert.
    EXPECT_EQ (result, 0);
    EXPECT_EQ (code.u64 [0], 0x01FF);
    for (auto i = 1; i < Code::u64ChunkCount; ++i) {
        EXPECT_EQ (code.u64 [i], 0x00);
    }
}
