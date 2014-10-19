#ifndef LPSLCD_VALIDATOR_H
#define LPSLCD_VALIDATOR_H

#include "generator.h"



class Validator
{
    public:
        static bool Validate (const Code & code)
        {
            // | N - k            |
            // | ____             |
            // | \     a + a      | < L
            // | /___   i   i + k |
            // | i = 1            |
            //
            // k - 0 < k < N;
            // N - length of sequence.
            // L - limit of sidelobe level.

            const ssize_t  sideLobeLimit = code.size () < 14 ? 1 : floor (code.size () / 14.0f);

            for (size_t shift = 1; shift < code.size (); ++shift) {
                ssize_t sideLobe = 0;
                for (size_t i = 0; i < code.size () - shift; ++i) {
                    sideLobe += (code [i + shift] == '+' ? 1 : -1) *
                                (code [i        ] == '+' ? 1 : -1);
                }
                if (std::abs (sideLobe) > sideLobeLimit) {
                    return false;
                }
            }

            return true;
        };
};

#endif//LPSLCD_VALIDATOR_H
