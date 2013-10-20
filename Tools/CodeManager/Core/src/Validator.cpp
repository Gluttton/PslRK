#include "Validator.h"
#include <limits>



namespace Pslrk
{
namespace Core
{

int Validator::ValidateStringView (const std::string validatingView)
{
    const std::string allowedSymbols {"-+"};

    for (size_t i = 0; i < validatingView.length (); ++i) {
        if (allowedSymbols.find (validatingView [i]) == std::string::npos) {
            return i > std::numeric_limits <int>::max () ? std::numeric_limits <int>::max () : i;
        }
    }

    constexpr int success {-1};
    return success;
}



int Validator::ValidateHexView (const std::string validatingView)
{
    const std::string allowedSymbols {"01234567890abcdefABCDEF"};

    for (size_t i = 0; i < validatingView.length (); ++i) {
        if (allowedSymbols.find (validatingView [i]) == std::string::npos) {
            return i > std::numeric_limits <int>::max () ? std::numeric_limits <int>::max () : i;
        }
    }

    constexpr int success {-1};
    return success;
}

}// namespace Core
}// namespace Pslrk