#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_H

#include <string>
#include <vector>



namespace Pslrk
{
namespace Core
{

class Calculator
{
    public:
        std::vector <int> CalculateAcf (const std::string);
        int               CalculateMsl (const std::string);
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_H