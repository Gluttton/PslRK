#ifndef LPSLCD_VALIDATOR_H
#define LPSLCD_VALIDATOR_H

#include "generator.h"
#include <cmath>



class Validator
{
    public:
        static bool Validate (Code * const code)
        {
            // | N - k            |
            // | ____             |
            // | \     a + a      | < 2
            // | /___   i   i + k |
            // | i = 1            |
            //
            // k - 0 < k < N;
            // N - length of sequence.

            const uint16_t length = code->size ();
            const int16_t  sideLobeLimit = length < 14 ? 1 : floor (length / 14.0f);

            for (uint16_t shift = 1; shift < length; ++shift) {
                int16_t sideLobe = 0;
                for (uint16_t i = 0; i < length - shift; ++i) {
                    sideLobe += ( (* code) [i + shift] == '+' ? 1 : -1) *
                                ( (* code) [i        ] == '+' ? 1 : -1);
                }
                if (abs (sideLobe) > sideLobeLimit) {
                    return false;
                }
            }

            return true;
        };
};

#endif//LPSLCD_VALIDATOR_H
