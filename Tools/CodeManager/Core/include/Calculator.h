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
        static std::vector <int> CalculateAcf (const std::string &);
        static int               CalculatePsl (const std::string &);
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_H