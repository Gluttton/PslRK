#include "generator.h"
#include <cstring>
#include <cmath>
#include <limits>



Generator::Generator (const __s32 length)
            : length        {length}
            , modifiedBits  {length - 1}
{
    sums.resize (length);
    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < length - i + 1; ++j) {
            sums [i].first.push_back (length - i - j);
        }
        sums [i].second = 0;
    }
}



bool Generator::GetNextCode (Code & returnedCode, __s32 & modifiedBits)
{
    if ( (code >> (length - 1) ).none () ) {
        modifiedBits = 0;
        for (; modifiedBits < length; ++modifiedBits) {
            if (returnedCode.flip (modifiedBits).test (modifiedBits) ) {
                break;
            }
        }
        return false;
    }

    return true;
}
