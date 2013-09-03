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



// Случай: генератор вызывается впервые.
// Проверки:
// - код возврата - успешный;
// - длительность кода равна начальной;
// - возвращается ноль в значащих битах.
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



// Случай: генератор вызывается второй раз.
// Проверки:
// - код возврата - успешный;
// - длительность кода равна начальной;
// - возвращается единица в значащих битах.
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



// Случай: генератор вызывается более 255 раз, что вызывает выход значащего бита
// за пределы крайнего байта.
// Проверки:
// - код возврата - успешный;
// - длительность кода соответствующая;
// - возвращаются единицы в значащих битах.
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



// Случай: генератор вызывается более 255 раз, что вызывает выход значащего бита
// за пределы крайнего байта.
// Проверки:
// - код возврата - успешный;
// - длительность кода соответствующая;
// - возвращаются единицы в значащих битах.
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



// Случай: генератор генерирует значения для кода длиною четыре.
// Проверки:
// - код возврата - успешный;
// - длина соответствующая;
// - перебираются все варианты от 0000 до 1111.
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



// Случай: генератор генерирует значения для кодов длиною три, четыре и пять.
// Проверки:
// - код возврата - успешный;
// - длина соответствующая;
// - перебираются все варианты от 000 до 11111.
TEST_F (GeneratorTest, CalculateAllCombinationForLength_3_4_5_Success)
{
    // Arange.
    const __u8 begin = 3;
    const __u8 end   = 5;
    generator        = new Generator (nullptr, begin, end);
    __u8 length      = 0;
    int result       = 0;

    // Act, Assert.
    // Перебираются все коды для длины три.
    for (__u64 i = 0; i < (1 << 3); ++i) {
        result = generator->GetNextCode (length, code);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, 3);
        EXPECT_EQ (code.u8 [0], i);
        EXPECT_EQ (generator->maxCode.u8 [0], (1 << 3) - 1);
    }

    // Act, Assert.
    // Перебираются все коды для длины четыре.
    for (__u64 i = 0; i < (1 << 4); ++i) {
        result = generator->GetNextCode (length, code);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, 4);
        EXPECT_EQ (code.u8 [0], i);
        EXPECT_EQ (generator->maxCode.u8 [0], (1 << 4) - 1);
    }

    // Act, Assert.
    // Перебираются все коды для длины пять.
    for (__u64 i = 0; i < (1 << 5); ++i) {
        result = generator->GetNextCode (length, code);
        EXPECT_EQ (result, 0);
        EXPECT_EQ (length, 5);
        EXPECT_EQ (code.u8 [0], i);
        EXPECT_EQ (generator->maxCode.u8 [0], (1 << 5) - 1);
    }
    // Коды длины пять кончились и поскольку это максимальная длина, то возвращается код ошибки.
    result = generator->GetNextCode (length, code);
    EXPECT_NE (result, 0);

    // Cleaning.
    delete generator;
}



// Случай: генератор расчитывает максимальное значение для кода длиною два.
// Проверки:
// - код возврата - успешный;
// - возвращаются поднятые два бита в младшем байте, все остальные - равны нулю.
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



// Случай: генератор расчитывает максимальное значение для кода длиною пять.
// Проверки:
// - код возврата - успешный;
// - возвращаются поднятые пять бит в младшем байте, все остальные - равны нулю.
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



// Случай: генератор расчитывает максимальное значение для кода длиною восемь.
// Проверки:
// - код возврата - успешный;
// - возвращаются поднятые восемь бит в младшем байте, все остальные - равны нулю.
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



// Случай: генератор расчитывает максимальное значение для кода длиною девять.
// Проверки:
// - код возврата - успешный;
// - возвращаются поднятые девять бит в младших байтах, все остальные - равны нулю.
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
