#include "environment.h"
#include "generator.h"
#include <cstring>
#include <algorithm>



Environment::Environment (const __s32 length)
            : length        {length}
            , modifiedBits  {length - 1}
{
    memset (code.data (), 0x00, sizeof (code) );
    maxCode = Generator::CalculateMaxCode (length);

    sums.resize (length);
    for (int i = 1; i < length; ++i) {
        for (int j = 0; j < length - i + 1; ++j) {
            sums [i].push_back (length - i - j);
        }
    }
}
