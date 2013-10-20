#include "Calculator.h"



namespace Pslrk
{
namespace Core
{

std::vector <int> Calculator::CalculateAcf (const std::string code)
{
    std::vector <int> acf {};

    //   |+--|
    // +-|-  |
    //  +|-- |
    //   |+--|
    //   | +-|-
    //   |  +|--
    const int range = code.length () - 1;
    for (int i = range; i >= -range; --i) {
        const int begin {      - i >     0 ?        -i :     0};
        const int end   {range - i < range ? range - i : range};
        int sum {0};
        for (int j = begin; j <= end; ++j) {
            const int a {code [    j] == '+' ? 1 : -1};
            const int b {code [i + j] == '+' ? 1 : -1};
            sum += a * b;
        }
        acf.push_back (sum);
    }

    return acf;
}



int Calculator::CalculateMsl (const std::string code)
{
    int msl {0};

    std::vector <int> acf {CalculateAcf (code)};
    for (int i = 0; i < code.length () - 1; ++i) {
        msl = std::max (msl, abs (acf [i]) );
    }

    return msl;
}

}// namespace Core
}// namespace Pslrk