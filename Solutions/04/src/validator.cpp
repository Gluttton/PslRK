#include "validator.h"



Validator::Validator (Generator * const bindGenerator)
            : generator {bindGenerator}
{
    memset (&code, 0x00u, sizeof (code) );
}



int Validator::SetNextCode ()
{
    return generator->GetNextCode (length, code, sideLobeLimit);
}



int Validator::Validate ()
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
        const __s32 x {(length - shift) >> 6};  // Shift means dividing by 64.
        const __s32 y {          shift  >> 6};  // Shift means dividing by 64.
        // Redundant raised bits which included in sum.
        const __s32 extra {__builtin_popcountll (code.u64 [x] >> ( (length - shift) & 63) )};

        __s32 sideLobeSum {0};
        for (__s32 i = 0; i <= x; ++i) {
            sideLobeSum += __builtin_popcountll (
                                  (code.u64 [i     + y] >> (      shift & 63)
                                |  code.u64 [i + 1 + y] << (64 - (shift & 63) ) )
                                ^  code.u64 [i]
                );
        }

        // Shift means multiply by two.
        if (abs (length - shift - ( (sideLobeSum - extra) << 1) ) > sideLobeLimit) {
            return 1;
        }
    }

    return 0;
}
