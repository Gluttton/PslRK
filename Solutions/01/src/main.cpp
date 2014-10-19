#include "generator.h"
#include "validator.h"
#include <iostream>
#include <cstdlib>



int main ()
{
    Generator generator {2, 28};
    Code    * code      {nullptr};

    while ( (code = generator.GetNextCode () ) ) {
        if (Validator::Validate (* code) ) {
            for (const auto & sign : * code) {
                std::cout << sign;
            }
            std::cout << std::endl;
        }
    }


    return EXIT_SUCCESS;
}
