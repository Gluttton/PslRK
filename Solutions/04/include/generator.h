#ifndef LPSLCD_GENERATOR_H
#define LPSLCD_GENERATOR_H

#include "container.h"
#include "logger.h"
#include <x86intrin.h>
#include <linux/types.h>
#include <string.h>
#include <math.h>



class Generator
{
    public:
        Generator (Logger * const commonLogger, const __s32 begin, const __s32 end)
                    : beginLength {begin < 2 ? 2 : begin}
                    , endLength   {end   > 64 * codeU64Count ? 64 * codeU64Count : end}
                    , length      {begin < 2 ? 2 : begin}
                    , logger      {commonLogger}
        {
            CalculateMaxCode (beginLength, maxCode);
        };



        virtual ~Generator  () = default;



        int CalculateMaxCode (const __s32 requestedLength, CodeContainer & returnedMaxCode) {
            // Utility variables.
            const __s32 x {1 + (requestedLength >> 3)};     // Shift means dividing by 8.

            memset (&returnedMaxCode.u8 [x],      0x00u, codeU8Count - 1 - x);
            memset (&returnedMaxCode.u8 [0],      0xFFu,                   x);
            memset (&returnedMaxCode.u8 [x - 1], (0x01u << (requestedLength & 7) ) - 1, 1);

            return 0;
        };



        virtual int GetNextCode (__s32 & returnedLength, CodeContainer & returnedCode, __s32 & returnedSideLobeLimit)
        {
            static __u64 rdtsc {__rdtsc ()};
            static __u64 codes {0ull};
            __u8 i {0x00u};

            if (memcmp (returnedCode.u8, maxCode.u8, codeU8Count) ) {
                do {
                    ++returnedCode.u64 [i];
                } while (!returnedCode.u64 [i++] && i < codeU64Count);
            }
            else {
                if (logger) {
                    std::string statisticString;
                    statisticString  = std::to_string (length);
                    statisticString += "\trdtsc " + std::to_string (__rdtsc () - rdtsc);
                    statisticString += "\tcodes " + std::to_string (codes) + " / " + std::to_string (1ull << length);
                    statisticString += "\n";
                    logger->LogStatistic (statisticString);
                }

                if (length < endLength) {
                    ++length;
                    returnedSideLobeLimit = length < 14 ? 1 : floor (length / 14.0f);
                    CalculateMaxCode (length, maxCode);
                    memset (returnedCode.u64, 0x00, i + 1);
                    rdtsc = __rdtsc ();
                    codes = 0;
                }
                else {
                    return 1;
                }
            }

            returnedLength = length;

            ++codes;
            return 0;
        };

        const __s32 beginLength {0};
        const __s32 endLength   {0};
        __s32 length            {0};
        CodeContainer maxCode   {};

    private:
        Logger * logger         {nullptr};
};

#endif//LPSLCD_GENERATOR_H
