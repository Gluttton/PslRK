#include "Calculator.h"
#include "Validator.h"
#include "Exception.h"
#include <algorithm>



namespace Pslrk
{
namespace Core
{

std::vector <int> Calculator::CalculateAcf (const std::string & stringView)
{
    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    std::vector <int> acf {};

    //   |+--|
    // +-|-  |
    //  +|-- |
    //   |+--|
    //   | +-|-
    //   |  +|--
    const int range = stringView.length () - 1;
    for (int i {range}; i >= -range; --i) {
        const int begin {      - i >     0 ?        -i :     0};
        const int end   {range - i < range ? range - i : range};
        int sum {0};
        for (int j {begin}; j <= end; ++j) {
            const int a {stringView [    j] == '+' ? 1 : -1};
            const int b {stringView [i + j] == '+' ? 1 : -1};
            sum += a * b;
        }
        acf.push_back (sum);
    }

    return acf;
}



int Calculator::CalculateMsl (const std::string & stringView)
{
    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    const size_t range {stringView.length () - 1};
    std::vector <int> acf {CalculateAcf (stringView)};
    std::transform (acf.begin (), acf.begin () + range, acf.begin (), abs);
    return * std::max_element (acf.begin (), acf.begin () + range);
}

}// namespace Core
}// namespace Pslrk