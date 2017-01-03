#ifndef LPSLCD_GENERATOR_MOCK_H
#define LPSLCD_GENERATOR_MOCK_H

#include "generator.h"
#include <gmock/gmock.h>



class GeneratorMock : public Generator
{
    public:
        GeneratorMock (const __s32 length)
                    : Generator {length}
        {
        };

        virtual ~GeneratorMock () = default;

        MOCK_METHOD2 (GetNextCode, bool (Code &, __s32 &) );
};

#endif//LPSLCD_GENERATOR_MOCK_H
