#ifndef PHCM_VALIDATOR_H
#define PHCM_VALIDATOR_H

#include "generator.h"
#include <stdlib.h>
#include <linux/types.h>
#include <math.h>



class Validator
{
    public:
        Validator (Generator * bindGenerator) : generator (bindGenerator)
        {
            length = 0;
            memset (&code, 0x00, sizeof (code) );
        };



        virtual ~Validator ()
        {
        };



        int SetNextCode ()
        {
            return generator->GetNextCode (length, code);
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
            // N - длина последовательности.

            __s16 sideLobeLimit = length < 14 ? 1 : floor (length / 14.0f);

            for (__u16 shift = 1; shift < length; ++shift) {
                __s16 sideLobe = 0;
                for (__u16 i = 0; i < length - shift; ++i) {
                    sideLobe += ( (code.u8 [(i + shift) / 8] >> ( (i + shift) % 8) ) & 0x01 ? 1 : -1) *
                                ( (code.u8 [ i          / 8] >> (  i          % 8) ) & 0x01 ? 1 : -1);
                }
                if (abs (sideLobe) > sideLobeLimit) {
                    return 1;
                }
            }

            return 0;
        };



        Generator * generator;
        __u8 length;
        CodeContainer code;
};

#endif//PHCM_VALIDATOR_H
