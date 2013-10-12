#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H

#include "RepresenterInterface.h"



class Representer : public IRepresenter
{
    public:
        std::string HexViewToStringView (const std::string) override;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H
