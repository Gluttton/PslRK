#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H

#include <string>



class Validator
{
    public:
        int ValidateStringView (const std::string);
        int ValidateHexView    (const std::string);
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H