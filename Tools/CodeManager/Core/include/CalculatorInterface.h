#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_INTERFACE_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_INTERFACE_H

#include <string>
#include <vector>



class ICalculator
{
    public:
        virtual std::vector <int> CalculateAcf (const std::string) = 0;
        virtual int               CalculateMsl (const std::string) = 0;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_INTERFACE_H
