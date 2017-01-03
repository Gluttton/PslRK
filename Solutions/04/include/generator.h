#ifndef LPSLCD_GENERATOR_H
#define LPSLCD_GENERATOR_H

#include <array>
#include <linux/types.h>
#include "environment.h"



class Generator
{
    public:
        Generator                       (const __s32);
        virtual ~Generator              () = default;

        virtual bool GetNextCode        (Code &, __s32 &);

        Environment environment;

        static Code CalculateMaxCode    (const __s32);
};

#endif//LPSLCD_GENERATOR_H
