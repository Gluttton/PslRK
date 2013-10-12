#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_H

#include "CalculatorInterface.h"



class Calculator : public ICalculator
{
    public:
        std::vector <int> CalculateAcf (const std::string) override;
        int               CalculateMsl (const std::string) override;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_H
