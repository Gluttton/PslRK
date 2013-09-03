#ifndef PHCM_GENERATOR_H
#define PHCM_GENERATOR_H

#include "container.h"
#include "logger.h"
#include <x86intrin.h>
#include <linux/types.h>
#include <string.h>



class Generator
{
    public:
        Generator (Logger * commonLogger, __u8 begin, __u8 end) : 
                                                            beginLength (begin < 2 ? 1 : begin - 1),
                                                            endLength   (end   > 8 * codeU8Count ? 8 * codeU8Count : end),
                                                            length      (begin < 2 ? 1 : begin - 1),
                                                            logger      (commonLogger)
        {
            CalculateMaxCode (beginLength, maxCode);
            memcpy (&code, &maxCode, sizeof (code) );
        };



        virtual ~Generator  ()
        {
        };



        int CalculateMaxCode (const __u8 requestedLength, CodeContainer & returnedMaxCode) {
            memset (&returnedMaxCode, 0x00, sizeof (returnedMaxCode) );

            __u64 i = 0;
            while (i < requestedLength / 8) {
                memset (&returnedMaxCode.u8 [i], 0xFF, 1);
                ++i;
            }
            returnedMaxCode.u8 [i] = (0x01U << (requestedLength % 8) ) - 1;

            return 0;
        };



        int GetNextCode (__u8 &returnedLength, CodeContainer &returnedCode)
        {
            static __u64 rdtsc = __rdtsc ();
            __u8 i = 0;


            if (memcmp (&code, &maxCode, sizeof (code) ) != 0) {
                do {
                    ++code.u8 [i];
                } while (!code.u8 [i++] && i < codeU8Count);
            }
            else {
                if (logger) {
                    std::string statisticString;
                    statisticString  = std::to_string (length);
                    statisticString += ":\t";
                    statisticString += std::to_string (__rdtsc () - rdtsc);
                    statisticString += "\n";
                    logger->LogStatistic (statisticString);
                }

                if (length < endLength) {
                    ++length;
                    CalculateMaxCode (length, maxCode);
                    memset (&code, 0x00, sizeof (code) );
                    rdtsc = __rdtsc ();
                }
                else {
                    return 1;
                }
            }

            memcpy (&returnedLength, &length, sizeof (returnedLength) );
            memcpy (&returnedCode,   &code,   sizeof (returnedCode) );

            return 0;
        };

        const __u8 beginLength;
        const __u8 endLength;
        __u8 length;
        CodeContainer code;
        CodeContainer maxCode;

    private:
        Generator ();
        Logger * logger;
};

#endif//PHCM_GENERATOR_H
