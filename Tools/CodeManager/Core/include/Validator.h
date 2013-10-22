#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H

#include <string>



namespace Pslrk
{
namespace Core
{

constexpr int viewIsValid {-1};



class Validator
{
    public:
        static int ValidateStringView (const std::string &);
        static int ValidateHexView    (const std::string &);
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H