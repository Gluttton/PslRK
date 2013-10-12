#include "Calculator.h"



std::vector <int> Calculator::CalculateAcf (const std::string code)
{
    std::vector <int> acf {};

    for (size_t i = 1; i < code.length (); ++i) {
        int sum {0};
        for (size_t j = 0; j < i; ++j) {
            const int a {code [                     j] == '+' ? 1 : -1};
            const int b {code [code.length () - 1 - j] == '+' ? 1 : -1};
            sum += a * b;
        }
        acf.push_back (sum);
    }

    acf.push_back (code.length () );

    for (size_t i = 1; i < code.length (); ++i) {
        int sum {0};
        for (size_t j = 0; j < code.length () - i; ++j) {
            const int a {code [i + j] == '+' ? 1 : -1};
            const int b {code [    j] == '+' ? 1 : -1};
            sum += a * b;
        }
        acf.push_back (sum);
    }


    return acf;
}



int Calculator::CalculateMsl (const std::string code)
{
    int msl {0};

    for (size_t i = 1; i < code.length (); ++i) {
        int sum {0};
        for (size_t j = 0; j < i; ++j) {
            const int a {code [                     j] == '+' ? 1 : -1};
            const int b {code [code.length () - 1 - j] == '+' ? 1 : -1};
            sum += a * b;
        }
        msl = std::max (msl, sum);
    }


    return msl;
}
