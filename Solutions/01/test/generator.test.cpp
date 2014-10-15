#include "generator.h"
#include <gtest/gtest.h>



// Case: generator calls first time.
// Check:
// - not null pointer must be returned;
// - length of sequence must be equal to the begin value;
// - all significant bits must be dropped.
TEST (GeneratorTest, FirstCallGetNextCodeSuccess)
{
    // Arange (not significant).
    constexpr size_t begin          {2};
    constexpr size_t end            {5};
    // Arange (esential).
    constexpr size_t etalonLength   {begin};
    Code * result                   {nullptr};
    const Code etalonResult         {'-', '-'};
    Generator generator             {begin, end};

    // Act.
    for (size_t i = 0; i < 1; ++i) {
        result = generator.GetNextCode ();
    }

    // Assert.
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonLength, result->size () );
    EXPECT_EQ (etalonResult, * result);
}



// Case: generator calls second time.
// Check:
// - not null pointer must be returned;
// - length of sequence must be equal to the begin value;
// - in significant bits one must be returned.
TEST (GeneratorTest, SecondCallGetNextCodeSuccess)
{
    // Arange (not significant).
    constexpr size_t begin          {2};
    constexpr size_t end            {5};
    // Arange (esential).
    constexpr size_t etalonLength   {begin};
    Code * result                   {nullptr};
    const Code etalonResult         {'+', '-'};
    Generator generator             {begin, end};

    // Act.
    for (size_t i = 0; i < 2; ++i) {
        result = generator.GetNextCode ();
    }

    // Assert.
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonLength, result->size () );
    EXPECT_EQ (etalonResult, * result);
}



// Case: generator generates values for sequence of length three.
// Check:
// - not null pointer must be returned;
// - all cases from --- to +++ must be looked over.
TEST (GeneratorTest, CalculateAllCombinationForLength_3_Success)
{
    // Arange.
    constexpr size_t begin          {3};
    constexpr size_t end            {3};
    Generator generator             {begin, end};
    Code * result                   {nullptr};
    Code etalonResult               {};

    // Act, Assert.
    etalonResult = {'-', '-', '-'};
    result = generator.GetNextCode ();
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonResult, * result);

    etalonResult = {'+', '-', '-'};
    result = generator.GetNextCode ();
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonResult, * result);

    etalonResult = {'-', '+', '-'};
    result = generator.GetNextCode ();
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonResult, * result);

    etalonResult = {'-', '-', '+'};
    result = generator.GetNextCode ();
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonResult, * result);

    etalonResult = {'+', '+', '-'};
    result = generator.GetNextCode ();
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonResult, * result);

    etalonResult = {'+', '-', '+'};
    result = generator.GetNextCode ();
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonResult, * result);

    etalonResult = {'-', '+', '+'};
    result = generator.GetNextCode ();
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonResult, * result);

    etalonResult = {'+', '+', '+'};
    result = generator.GetNextCode ();
    ASSERT_NE (nullptr, result);
    EXPECT_EQ (etalonResult, * result);
}



// Case: generator generates values for sequences of length three, four and five.
// Check:
// - not null pointer must be returned;
// - length of sequence must be corresponding;
// - number of sequence of specified length must be corresponding;
TEST (GeneratorTest, CalculateAllCombinationForLength_3_4_5_Success)
{
    // Arange.
    constexpr size_t begin          {3};
    constexpr size_t end            {5};
    Generator generator             {begin, end};
    Code * result                   {nullptr};

    // Act, Assert.
    // Looking over cases for sequence of length three.
    for (size_t i = 0; i < (1 << 3); ++i) {
        result = generator.GetNextCode ();
        ASSERT_NE (nullptr, result);
        EXPECT_EQ (3, result->size () );
    }

    // Act, Assert.
    // Looking over cases for sequence of length four.
    for (size_t i = 0; i < (1 << 4); ++i) {
        result = generator.GetNextCode ();
        ASSERT_NE (nullptr, result);
        EXPECT_EQ (4, result->size () );
    }

    // Act, Assert.
    // Looking over cases for sequence of length five.
    for (size_t i = 0; i < (1 << 5); ++i) {
        result = generator.GetNextCode ();
        ASSERT_NE (nullptr, result);
        EXPECT_EQ (5, result->size () );
    }
}
