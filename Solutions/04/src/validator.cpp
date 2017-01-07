#include "validator.h"
#include "generator.h"
#include <limits>



Validator::Validator (Generator & bindGenerator)
            : generator {bindGenerator}
{
}



bool Validator::SetNextCode ()
{
    return generator.GetNextCode (generator.code, generator.modifiedBits);
}



bool Validator::Validate ()
{
    const auto & length = generator.length;
    const auto & ltz    = generator.modifiedBits;
    const auto & code   = generator.code;
          auto & sums   = generator.sums;
    const auto & limit  = sideLobeLimit;

    for (int shift = 1; shift < length - limit; ++shift) {
        int j = std::min (length - 1 - shift, std::max <int> (ltz, sums [shift].second) );
        for (; j >= 0; --j) {
            const auto k = j + shift;
            sums [shift].first [j] = sums [shift].first [j + 1] + (code [j] == code [k] ? +1 : -1);
            if (std::abs (sums [shift].first [j]) > limit + j) {
                sums [shift].second = j;
                for (++shift; shift < length - limit; ++shift) {
                    sums [shift].second = std::max <int> (sums [shift].second, ltz);
                }
                return false;
            }
        }
        sums [shift].second = 0;
    }

    return true;
}
