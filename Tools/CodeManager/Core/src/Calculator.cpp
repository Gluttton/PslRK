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



unsigned int Calculator::CalculateE (const std::string & stringView)
{
    // Calculate energy of binary sequence.
    //
    //        N - 1  / N - k            \ 2
    //        ____   | ____             |
    // E = 2  \      | \     a + a      |
    //        /___   | /___   i   i + k |
    //        n = 1  \ i = 1            /
    //
    // N - energy of sequence.
    // n - 0 < n < N;
    // k - 0 < k < N;
    // N - length of sequence.

    unsigned int e {0u};

    const auto acf = CalculateAcf (stringView);
    for (size_t i = 0; i < stringView.size () - 1; ++i) {
        e += pow (acf [i], 2);
    }
    e *= 2u;

    return e;
}



float Calculator::CalculateIsl (const std::string & stringView)
{
    // Calculate integrated sidelobe level of binary sequence.
    //
    //              /  E  |
    // I = 10 log   | ----|
    //          10  |   2 |
    //              \  N  /
    //
    // I - integrated sidelobe level of sequence.
    // E - energy of sequence.
    // N - length of sequence.

    const auto e = CalculateE (stringView);

    const float isl = 10 * log10 (e / pow (stringView.size (), 2) );

    return isl;
}



float Calculator::CalculateMf (const std::string & stringView)
{
    // Calculate merit factor of binary sequence.
    //
    //       2
    //      N
    // M = ----
    //      E
    //
    // M - merit factor of sequence.
    // E - energy of sequence.
    // N - length of sequence.

    const auto e = CalculateE (stringView);

    const float mf = pow (stringView.size (), 2) / e;

    return mf;
}



float Calculator::CalculateDb (const int ml, const int psl)
{
    return 20.0f * log10f (static_cast <float> (psl) / static_cast <float> (ml) );
}

}// namespace Core
}// namespace Pslrk
