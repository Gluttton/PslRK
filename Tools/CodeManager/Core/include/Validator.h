#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H

#include "ValidatorInterface.h"



class Validator : public IValidator
{
    public:
        int ValidateStringView (const std::string) override;
        int ValidateHexView    (const std::string) override;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_VALIDATOR_H
