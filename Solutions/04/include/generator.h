#ifndef LPSLCD_GENERATOR_H
#define LPSLCD_GENERATOR_H

#include "code.h"
#include "logger.h"
#include <cstring>
#include <math.h>



class Generator
{
    public:
        Generator                       (Logger * const, const __s32, const __s32);
        virtual ~Generator              () = default;

        int CalculateMaxCode            (const __s32, Code &);

        virtual int GetNextCode         (__s32 &, Code &, __s32 &);

        const __s32 beginLength         {0};
        const __s32 endLength           {0};
        __s32 length                    {0};
        Code maxCode                    {};

    private:
        Logger * const logger           {nullptr};
};

#endif//LPSLCD_GENERATOR_H
