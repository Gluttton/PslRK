#ifndef LPSLCD_VALIDATOR_H
#define LPSLCD_VALIDATOR_H

#include "generator.h"



template <int_t L, int_t SLL>
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
            const auto & m      = generator.modifiedBits;
            const auto & code   = generator.code;
                  auto & cache  = generator.cache;

            static constexpr int_t l = L - SLL;

            for (int_t shift = 1; shift < l; ++shift) {
                int_t j = std::min (L - 1 - shift, std::max (m, cache [shift].second) );
                for (; j >= 0; --j) {
                    cache [shift].first [j] = cache [shift].first [j + 1] + (code [j] == code [j + shift] ? +1 : -1);
                    if (std::abs (cache [shift].first [j]) > SLL + j) {
                        cache [shift].second = j;
                        for (++shift; shift < l; ++shift) {
                            cache [shift].second = std::max (m, cache [shift].second);
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
