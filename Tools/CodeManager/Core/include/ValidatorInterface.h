#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_INTERFACE_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_INTERFACE_H

#include <string>



class IValidator
{
    public:
        virtual int ValidateStringView (const std::string) = 0;
        virtual int ValidateHexView    (const std::string) = 0;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_INTERFACE_H
