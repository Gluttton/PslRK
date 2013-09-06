#ifndef LPSLCD_VALIDATOR_H
#define LPSLCD_VALIDATOR_H

#include "generator.h"
#include <stdlib.h>
#include <linux/types.h>



class Validator
{
    public:
        Validator (Generator * bindGenerator) : generator (bindGenerator)
        {
            length        = 0;
            sideLobeLimit = 0;
            memset (&code, 0x00, sizeof (code) );
        };



        virtual ~Validator ()
        {
        };



        int SetNextCode ()
        {
            return generator->GetNextCode (length, code, sideLobeLimit);
        };



        int Validate ()
        {
            // | N - k            |
            // | ____             |
            // | \     a + a      | < 2
            // | /___   i   i + k |
            // | i = 1            |
            //
            // k - 0 < k < N;
            // N - length of sequence.

            for (__s32 shift = 1; shift < length; ++shift) {
                // Utility variables.
                __s32 x = (length - shift) >> 6;     // Shift means dividing by 64.
                __s32 y =           shift  >> 6;     // Shift means dividing by 64.
                // Redundant raised bits which included in sum.
                __s32 extra = __builtin_popcountll (code.u64 [x] >> ( (length - shift) & 63) );

                __s32 sideLobeSum = 0;
                for (__s32 i = 0; i <= x; ++i) {
                    sideLobeSum += __builtin_popcountll (
                                          (code.u64 [i     + y] >> (      shift & 63)
                                        |  code.u64 [i + 1 + y] << (64 - (shift & 63) ) )
                                        ^  code.u64 [i]
                        );
                }

                if (abs (length - shift - (sideLobeSum - extra) * 2) > sideLobeLimit) {
                    return 1;
                }
            }

            return 0;
        };



        Generator * generator;
        CodeContainer code;
        __s32 length;
        __s32 sideLobeLimit;
};

#endif//LPSLCD_VALIDATOR_H
