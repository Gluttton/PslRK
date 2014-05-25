#include "Calculator.h"
#include "Validator.h"
#include "Exception.h"
#include <algorithm>
#include <iostream>



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



std::vector <int> Calculator::CalculateCcf (const std::string & stringViewOne, const std::string & stringViewTwo)
{
    if (Validator::ValidateStringView (stringViewOne) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    if (Validator::ValidateStringView (stringViewTwo) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    std::vector <int> ccf {};

    //    |+-++|
    //  +-|-   |
    //   +|--  |
    //    |+-- |
    //    | +--|
    //    |  +-|-
    //    |   +|--

    //    |+--|
    // +-+|+  |
    //  +-|++ |
    //   +|-++|
    //    |+-+|+
    //    | +-|++
    //    |  +|-++
    const int rangeOne = stringViewOne.length () - 1;
    const int rangeTwo = stringViewTwo.length () - 1;
    for (int i {-rangeTwo}; i <= rangeOne; ++i) {
        const int begin {i <                   0 ?       -i :            0};
        const int end   {i < rangeOne - rangeTwo ? rangeTwo : rangeOne - i};
        int sum {0};
        for (int j {begin}; j <= end; ++j) {
            const int a {stringViewTwo [    j] == '+' ? 1 : -1};
            const int b {stringViewOne [i + j] == '+' ? 1 : -1};
            sum += a * b;
        }
        ccf.push_back (sum);
    }

    return ccf;
}



int Calculator::CalculatePsl (const std::string & stringView)
{
    if (stringView.empty () ) {
        return 0;
    }

    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    const size_t range {stringView.length () - 1};
    std::vector <int> acf {CalculateAcf (stringView)};
    std::transform (acf.begin (), acf.begin () + range, acf.begin (), abs);
    return * std::max_element (acf.begin (), acf.begin () + range);
}



float Calculator::CalculateDb (const int ml, const int psl)
{
    return 20.0f * log10f (static_cast <float> (psl) / static_cast <float> (ml) );
}

}// namespace Core
}// namespace Pslrk