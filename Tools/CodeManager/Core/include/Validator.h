#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H

#include <string>



namespace Pslrk
{
namespace Core
{

class Validator
{
    public:
        int ValidateStringView (const std::string &) const;
        int ValidateHexView    (const std::string &) const;
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H