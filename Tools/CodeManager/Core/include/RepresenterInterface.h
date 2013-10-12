#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_INTERFACE_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_INTERFACE_H

#include <string>



class IRepresenter
{
    public:
        virtual std::string HexViewToStringView (const std::string) = 0;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_INTERFACE_H
