#include <stdlib.h>
#include <iostream>
#include <Validator.h>
#include <Calculator.h>
#include <Representer.h>



int main (int argc, char * argv [])
{
    if (argc < 2) {
        std::cout << "Input parameters were not passed!" << std::endl;
        return EXIT_FAILURE;
    }


    Validator   validator;
    Calculator  calculator;
    Representer representer;


    std::string code = argv [1];
    std::cout << "Input code:               " << code << std::endl;
    std::cout << "Recognizing format:       ";

    const int validationAsStringResult = validator.ValidateStringView (code);
    if (-1 != validationAsStringResult) {
        const int validationAsHexResult = validator.ValidateHexView (code);
        if (-1 != validationAsHexResult) {
            std::cout << "unsuccessful." << std::endl;
            std::cout << "String wrong symbol:      " << code << std::endl;
            for (int i = 0; i < 26 + validationAsStringResult; ++i) {
                std::cout << " ";
            }
            std::cout << "^" << std::endl;
            std::cout << "Hex wrong symbol:         " << code << std::endl;;
            for (int i = 0; i < 26 + validationAsHexResult; ++i) {
                std::cout << " ";
            }
            std::cout << "^" << std::endl;
            return EXIT_FAILURE;
        }
        else {
            std::cout << "hex." << std::endl;

            if (2 == argc) {
                code = representer.HexViewToStringView (code);
            } else if (3 == argc) {
                code = representer.HexViewToStringView (code, std::stoi (argv [2]) );
            }
        }
    }
    else {
        std::cout << "string." << std::endl;
    }
    std::cout << "String view of code:      " << code << std::endl;


    std::cout << "Autocorrelation function: ";
    auto acf = calculator.CalculateAcf (code);
    for (auto e : acf) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::cout << "Maximum Peak Sidelobe:    " << calculator.CalculateMsl (code) << std::endl;


    return EXIT_SUCCESS;
}
