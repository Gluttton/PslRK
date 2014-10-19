#ifndef LPSLCD_GENERATOR_H
#define LPSLCD_GENERATOR_H

#include <vector>
#include <algorithm>
#include <cstdint>



using Code = std::vector <char>;



class Generator
{
    public:
        Generator (const size_t beginLength, const size_t endLength)
                    : population    {0}
                    , code          {}
        {
            code.reserve (endLength);
            code.resize  (beginLength);
            std::fill    (code.begin (), code.begin () + beginLength, '-');
        };



        Code * GetNextCode ()
        {
            if (!std::next_permutation (code.begin (), code.end () ) ) {
                if (population > code.size () ) {
                    if (code.size () < code.capacity () ) {
                        code.resize (code.size () + 1);
                        population = 0;
                    }
                    else {
                        return nullptr;
                    }
                }
                std::fill (code.begin (), code.begin () + code.size (), '-');
                std::fill (code.begin (), code.begin () + population,   '+');
                ++population;
            }

            return & code;
        };



        size_t      population;
        Code        code;
};

#endif//LPSLCD_GENERATOR_H
