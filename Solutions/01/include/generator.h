#ifndef LPSLCD_GENERATOR_H
#define LPSLCD_GENERATOR_H

#include <vector>
#include <algorithm>
#include <cstdint>



using Code = std::vector <char>;



class Generator
{
    public:
        Generator (const uint8_t beginLength, const uint8_t endLength)
                    : endLength     {endLength}
                    , length        {beginLength}
                    , population    {0}
                    , code          {}
        {
            code.resize (length);
            std::fill (code.begin (), code.begin () + length, '-');
        };



        Code * GetNextCode ()
        {
            if (!std::next_permutation (code.begin (), code.end () ) ) {
                if (population > length) {
                    if (length < endLength) {
                        ++length;
                        code.resize (length);
                        population = 0;
                    }
                    else {
                        return nullptr;
                    }
                }
                std::fill (code.begin (), code.begin () + length,     '-');
                std::fill (code.begin (), code.begin () + population, '+');
                ++population;
            }

            return & code;
        };

        const uint8_t   endLength;
        uint8_t         length;
        uint8_t         population;
        Code            code;
};

#endif//LPSLCD_GENERATOR_H
