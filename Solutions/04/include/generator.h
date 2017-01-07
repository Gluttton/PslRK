#ifndef LPSLCD_GENERATOR_H
#define LPSLCD_GENERATOR_H

#include <array>
#include <bitset>
#include <linux/types.h>



template <int L>
class Generator
{
    public:
        using Code = std::bitset <L>;

        std::array <std::pair <std::array <__s8, L>, __u8>, L>
                                        cache;

        Code code                       {};
        __s32 modifiedBits              {0};



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



        virtual ~Generator () = default;



        virtual bool NextCode (const int skippedBits)
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
