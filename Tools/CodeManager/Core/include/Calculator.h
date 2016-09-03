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
        static std::vector <int> Acf (const std::string &);
        static std::vector <int> Ccf (const std::string &, const std::string &);
        static int               Psl (const std::string &);
        static unsigned int      E   (const std::string &);
        static float             Isl (const std::string &);
        static float             Mf  (const std::string &);
        static float             Db  (const int, const int);
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_CALCULATOR_H
