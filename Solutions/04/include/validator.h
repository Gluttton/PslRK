#ifndef LPSLCD_VALIDATOR_H
#define LPSLCD_VALIDATOR_H

#include <linux/types.h>
#include "generator.h"



template <int L, int SLL>
class Validator
{
    public:
        Generator <L> & generator;
        int skippedBits;


        Validator (Generator <L> & bindGenerator)
                : generator {bindGenerator}
                , skippedBits {0}
        {
        }



        bool SetNextCode ()
        {
            return generator.NextCode (skippedBits);
        }



        bool Validate ()
        {
            const auto & ltz    = generator.modifiedBits;
            const auto & code   = generator.code;
                  auto & cache  = generator.cache;

            for (int shift = 1; shift < L - SLL; ++shift) {
                int j = std::min (L - 1 - shift, std::max <int> (ltz, cache [shift].second) );
                for (; j >= 0; --j) {
                    const auto k = j + shift;
                    cache [shift].first [j] = cache [shift].first [j + 1] + (code [j] == code [k] ? +1 : -1);
                    if (std::abs (cache [shift].first [j]) > SLL + j) {
                        cache [shift].second = j;
                        for (++shift; shift < L - SLL; ++shift) {
                            cache [shift].second = std::max <int> (cache [shift].second, ltz);
                        }
                        skippedBits = j;
                        return false;
                    }
                }
                cache [shift].second = 0;
            }

            return true;
        }
};

#endif//LPSLCD_VALIDATOR_H
