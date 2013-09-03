#include "generator.h"
#include "validator.h"
#include <gtest/gtest.h>



class ValidatorTest : public ::testing::Test
{
    protected:
        Generator * generator;
        Validator * validator;
        CodeContainer code;

        void SetUp    ();
        void TearDown ();
};



void ValidatorTest::SetUp ()
{
    memset (&code, 0x00, sizeof (code) );
}



void ValidatorTest::TearDown ()
{
}



// Случай: проверяется двузначный код Баркера.
// Проверки:
// - код возврата - успешный.
TEST_F (ValidatorTest, Validate_00_Success)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 2;
    validator->code.u8 [0] = 0x00;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 0);

    // Cleaning.
    delete validator;
}



// Случай: проверяется двузначный код Баркера.
// Проверки:
// - код возврата - успешный.
TEST_F (ValidatorTest, Validate_10_Success)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 2;
    validator->code.u8 [0] = 0x02;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 0);

    // Cleaning.
    delete validator;
}



// Случай: проверяется трехзначный код Баркера.
// Проверки:
// - код возврата - успешный.
TEST_F (ValidatorTest, Validate_001_Success)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 3;
    validator->code.u8 [0] = 0x01;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 0);

    // Cleaning.
    delete validator;
}



// Случай: проверяется четырехзначный код Баркера.
// Проверки:
// - код возврата - успешный.
TEST_F (ValidatorTest, Validate_0001_Success)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 4;
    validator->code.u8 [0] = 0x01;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 0);

    // Cleaning.
    delete validator;
}



// Случай: проверяется четырехзначный код Баркера.
// Проверки:
// - код возврата - успешный.
TEST_F (ValidatorTest, Validate_0100_Success)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 4;
    validator->code.u8 [0] = 0x04;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 0);

    // Cleaning.
    delete validator;
}



// Случай: проверяется пятизначный код Баркера.
// Проверки:
// - код возврата - успешный.
TEST_F (ValidatorTest, Validate_00010_Success)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 5;
    validator->code.u8 [0] = 0x02;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 0);

    // Cleaning.
    delete validator;
}



// Случай: проверяется семизначный код Баркера.
// Проверки:
// - код возврата - успешный.
TEST_F (ValidatorTest, Validate_0001101_Success)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 7;
    validator->code.u8 [0] = 0x0D;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 0);

    // Cleaning.
    delete validator;
}



// Случай: проверяется одинадцатизначный код Баркера.
// Проверки:
// - код возврата - успешный.
TEST_F (ValidatorTest, Validate_00011101101_Success)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 11;
    validator->code.u8 [0] = 0xED;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 0);

    // Cleaning.
    delete validator;
}



// Случай: проверяется тринадцатизначный код Баркера.
// Проверки:
// - код возврата - успешный.
TEST_F (ValidatorTest, Validate_0000011001010_Success)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 13;
    validator->code.u8 [0] = 0xCA;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 0);

    // Cleaning.
    delete validator;
}



// Случай: проверяется пятизначный код не являющийся кодом Баркера.
// Проверки:
// - код возврата - отрицательный.
TEST_F (ValidatorTest, Validate_10110_Fail)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 5;
    validator->code.u8 [0] = 0x16;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 1);

    // Cleaning.
    delete validator;
}



// Случай: проверяется тринадцатизначный код не являющийся кодом Баркера.
// Проверки:
// - код возврата - отрицательный.
TEST_F (ValidatorTest, Validate_1111100110110_Fail)
{
    // Arange.
    validator = new Validator (NULL);
    validator->length = 13;
    validator->code.u8 [0] = 0x1F;
    validator->code.u8 [1] = 0x36;
    int result = -1;

    // Act.
    result = validator->Validate ();

    // Assert.
    EXPECT_EQ (result, 1);

    // Cleaning.
    delete validator;
}



// Случай: проверяются все четырехзначные коды Баркера.
// Проверки:
// - обнаружен код: 1101;
// - обнаружен код: 1011;
// - обнаружен код: 0010;
// - обнаружен код: 0100;
// - обнаружен код: 1110;
// - обнаружен код: 0111;
// - обнаружен код: 0001;
// - обнаружен код: 1000.
TEST_F (ValidatorTest, ValidateAllCombinationsOfLenth_4_Success)
{
    // Arange.
    const __u8 begin = 3;
    const __u8 end   = 5;
    generator = new Generator (nullptr, begin, end);
    validator = new Validator (generator);
    __u8 etalon [] = {0,   1,   1,   0,   1,   0,   0,   1,   1,   0,   0,   1,   0,   1,   1,   0};
    //                0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
    //                  0001 0010      0100           0111 1000           1011      1101 1110
    __u8 test   [] = {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};

    // Act.
    while (!validator->SetNextCode () ) {
        if (!validator->Validate () && validator->length == 4) {
            test [validator->code.u8 [0] & 0x0F] = 1;
        }
    }

    // Assert.
    for (__u8 i = 0; i < sizeof (etalon); ++i) {
        EXPECT_EQ (etalon [i], test [i]);
    }

    // Cleaning.
    delete generator;
    delete validator;
}
