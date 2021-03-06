#include "Calculator.h"
#include "Validator.h"
#include "Exception.h"
#include <algorithm>
#include <numeric>
#include <cmath>



namespace Pslrk
{
namespace Core
{

std::vector <int> Calculator::Acf (const std::string & stringView)
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



std::vector <int> Calculator::Ccf (const std::string & stringViewOne, const std::string & stringViewTwo)
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



int Calculator::Ml (const std::string & stringView)
{
    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    return stringView.length ();
}



int Calculator::Ml (const std::string & stringViewOne, const std::string & stringViewTwo)
{
    if (stringViewOne.empty ()
     || stringViewTwo.empty () ) {
        return 0;
    }

    if (Validator::ValidateStringView (stringViewTwo) != viewIsValid
     || Validator::ValidateStringView (stringViewTwo) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    std::vector <int> ccf {Ccf (stringViewOne, stringViewTwo)};
    std::transform (ccf.begin (), ccf.end (), ccf.begin (), abs);
    return * std::max_element (ccf.begin (), ccf.end () );
}



int Calculator::Psl (const std::string & stringView)
{
    if (stringView.empty () ) {
        return 0;
    }

    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    const size_t range {stringView.length () - 1};
    std::vector <int> acf {Acf (stringView)};
    std::transform (acf.begin (), acf.begin () + range, acf.begin (), abs);
    return * std::max_element (acf.begin (), acf.begin () + range);
}



int Calculator::Psl (const std::string & stringViewOne, const std::string & stringViewTwo)
{
    if (stringViewOne.empty ()
     || stringViewTwo.empty () ) {
        return 0;
    }

    if (Validator::ValidateStringView (stringViewTwo) != viewIsValid
     || Validator::ValidateStringView (stringViewTwo) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    std::vector <int> ccf {Ccf (stringViewOne, stringViewTwo)};
    std::transform (ccf.begin (), ccf.end (), ccf.begin (), abs);
    std::nth_element (ccf.begin (), ccf.begin () + 1, ccf.end (), std::greater <int> () );
    return * (ccf.begin () + 1);
}



// Calculate energy of binary sequence.
//
//        N - 1  / N - k            \ 2
//        ____   | ____             |
// E = 2  \      | \     a * a      |
//        /___   | /___   i   i + k |
//        n = 1  \ i = 1            /
//
// N - energy of sequence.
// n - 0 < n < N;
// k - 0 < k < N;
// N - length of sequence.
unsigned int Calculator::E (const std::string & stringView)
{
    unsigned int e {0u};

    if (stringView.size () ) {
        const auto acf = Acf (stringView);
        e = std::accumulate (acf.begin (), acf.begin () + stringView.size () - 1, e, [](const int a, const int x){return a + std::pow (x, 2);});
        e *= 2u;
    }

    return e;
}



unsigned int Calculator::E (const std::string & stringViewOne, const std::string & stringViewTwo)
{
    unsigned int e {0u};

    if (stringViewOne.length () && stringViewTwo.length () ) {
        const auto ccf = Ccf (stringViewOne, stringViewTwo);
        e = std::accumulate (ccf.begin (), ccf.end (), e, [](const int a, const int x){return a + std::pow (x, 2);});
        e -= std::pow (Ml (stringViewOne, stringViewTwo), 2);
    }

    return e;
}



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
float Calculator::Isl (const std::string & stringView)
{
    return 10 * std::log10 (E (stringView) / std::pow (stringView.size (), 2) );
}



float Calculator::Isl (const std::string & stringViewOne, const std::string & stringViewTwo)
{
    const auto e = E (stringViewOne, stringViewTwo);
    const auto n = (stringViewOne.length () + stringViewTwo.length () ) / 2;

    const float isl = 10 * std::log10 (e / std::pow (n, 2) );

    return isl;
}



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
float Calculator::Mf (const std::string & stringView)
{
    return std::pow (stringView.size (), 2) / E (stringView);
}



float Calculator::Mf (const std::string & stringViewOne, const std::string & stringViewTwo)
{
    const auto e = E (stringViewOne, stringViewTwo);
    const auto n = (stringViewOne.length () + stringViewTwo.length () ) / 2;

    const float mf = std::pow (n, 2) / e;

    return mf;
}



float Calculator::Db (const int ml, const int psl)
{
    return 20.0f * log10f (static_cast <float> (psl) / static_cast <float> (ml) );
}

}// namespace Core
}// namespace Pslrk
