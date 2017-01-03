#ifndef LPSLCD_GENERATOR_TEST_H
#define LPSLCD_GENERATOR_TEST_H

#include "generator.h"



class GeneratorProxy : public Generator
{
    public:
        GeneratorProxy (const __s32 length)
                    : Generator {length}
        {
        };

        virtual ~GeneratorProxy () = default;

        using Generator::CalculateMaxCode;
};

#endif//LPSLCD_GENERATOR_TEST_H
