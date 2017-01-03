#include "generator.h"
#include <x86intrin.h>
#include <cstring>
#include <cmath>
#include <limits>



Generator::Generator (const __s32 length)
            : environment {length}
{
}



Code Generator::CalculateMaxCode (const __s32 length)
{
    Code code;
    const auto a = std::numeric_limits <Code::value_type>::digits;

    for (__s32 i = 0; i < static_cast <__s32> (code.size () * a); ++i) {
        Code::value_type b = 1 << (i % a);
        if (i < length) {
            code [i / a] |= b;
        }
        else {
            code [i / a] &=~b;
        }
    }

    return code;
}



bool Generator::GetNextCode (Code & returnedCode, __s32 & modifiedBits)
{
    if (memcmp (returnedCode.data (), environment.maxCode.data (), environment.length / std::numeric_limits <Code::value_type>::digits + 1) ) {
        __u8 i = 0;
        do {
            ++returnedCode [i];
        } while (!returnedCode [i++] && i < returnedCode.size () );

        __s32 b = 0;
        //if (returnedCode [i - 1]) {
            b = __builtin_ctz (returnedCode [i - 1]);
        //}
        modifiedBits = (i - 1) * std::numeric_limits <Code::value_type>::digits + b;

        return false;
    }

    return true;
}
