#ifndef LPSLCD_GENERATOR_MOCK_H
#define LPSLCD_GENERATOR_MOCK_H

#include "generator.h"
#include <gmock/gmock.h>



class GeneratorMock : public Generator
{
    public:
        GeneratorMock (Logger * const logger, const __s32 begin, const __s32 end)
                    : Generator {logger, begin, end}
        {
        };

        virtual ~GeneratorMock () = default;

        MOCK_METHOD3 (GetNextCode, int (__s32 &, Code &, __s32 &) );
};

#endif//LPSLCD_GENERATOR_MOCK_H
