#ifndef LPSLCD_GENERATOR_H
#define LPSLCD_GENERATOR_H

#include <array>
#include <bitset>



using int_t = int_fast32_t;



template <int_t L>
class Generator
{
    public:
        std::array <std::pair <std::array <int_t, L>, int_t>, L> cache;

        std::bitset <L> code    {};
        int_t modifiedBits      {0};



        Generator ()
                : modifiedBits  {L - 1}
        {
            for (int i = 1; i < L; ++i) {
                for (int j = 0; j < L - i + 1; ++j) {
                    cache [i].first [j] = L - i - j;
                }
                cache [i].second = 0;
            }
        }



        bool NextCode (const int skippedBits)
        {
            if ( (code >> (L - 1) ).none () ) {
                modifiedBits = 0;
                for (; modifiedBits < skippedBits; ++modifiedBits) {
                    code.reset (modifiedBits);
                }
                for (; modifiedBits < L; ++modifiedBits) {
                    if (code.flip (modifiedBits).test (modifiedBits) ) {
                        break;
                    }
                }
                return false;
            }

            return true;
        }
};

#endif//LPSLCD_GENERATOR_H
