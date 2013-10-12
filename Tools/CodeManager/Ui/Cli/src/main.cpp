#include <stdlib.h>
#include <iostream>
#include <Validator.h>
#include <Calculator.h>
#include <Representer.h>



int main (int argc, char * argv [])
{
    Validator   validator;
    Calculator  calculator;
    Representer representer;

    std::string code = argv [1];
    std::cout << "Input code: " << code << std::endl;
    std::cout << "Validating... ";
    int validationResult = validator.ValidateHexView (code);
    if (-1 == validationResult) {
        std::cout << "valid" << std::endl;
    }
    else {
        std::cout << "valid" << std::endl;
    }

    std::string stringViewOfCode;
    if (argc == 2) {
        stringViewOfCode = representer.HexViewToStringView (code);
    }
    else if (argc == 3) {
        stringViewOfCode = representer.HexViewToStringView (code, std::stoi (argv [2]) );
    }
    std::cout << "String view of code: " << stringViewOfCode << std::endl;

    std::cout << "Autocorrelation function: ";
    auto acf = calculator.CalculateAcf (stringViewOfCode);
    for (auto e : acf) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::cout << "Maximum Peak Sidelobe: " << calculator.CalculateMsl (stringViewOfCode) << std::endl;


    return EXIT_SUCCESS;
}
