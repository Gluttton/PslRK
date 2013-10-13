#include "Calculator.h"
//#include <iostream>



std::vector <int> Calculator::CalculateAcf (const std::string code)
{
    std::vector <int> acf {};

    const int range = code.length () - 1;
    for (int i = range, b = -range, e = 0; i >= -range; --i, ++b, ++e) {
        const int begin {b >     0 ? b :     0};
        const int end   {e < range ? e : range};
        int sum {0};
        //std::cout << "i=" << i << ", b=" << b << ", begin=" << begin << ", e=" << e << ", end=" << end << std::endl;
        for (int j = begin; j <= end; ++j) {
            const int a {code [    j] == '+' ? 1 : -1};
            const int b {code [i + j] == '+' ? 1 : -1};
            //std::cout << "        " << j << " x " << i + j << "    " << a << " x " << b << " = " << a * b << std::endl;
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
