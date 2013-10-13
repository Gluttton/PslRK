#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_INTERFACE_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_INTERFACE_H

#include <string>
#include <array>



class IRepresenter
{
    public:
        virtual std::string HexViewToStringView (const std::string)                = 0;
        virtual std::string HexViewToStringView (const std::string, const size_t)  = 0;
        virtual std::string StringViewToHexView (const std::string)                = 0;
        virtual std::string ReverseCode (const std::string)                        = 0;
        virtual std::string InverseCode (const std::string)                        = 0;
        virtual std::array <std::string, 4> GenerateCodeFamily (const std::string) = 0;
        virtual std::string DetectCodeId (const std::string)                       = 0;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_INTERFACE_H
