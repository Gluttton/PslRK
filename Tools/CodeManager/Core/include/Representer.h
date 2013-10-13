#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H

#include "RepresenterInterface.h"
#include <map>



class Representer : public IRepresenter
{
    public:
        std::string HexViewToStringView (const std::string)                override;
        std::string HexViewToStringView (const std::string, const size_t)  override;
        std::string StringViewToHexView (const std::string)                override;
        std::string ReverseCode (const std::string)                        override;
        std::string InverseCode (const std::string)                        override;
        std::array <std::string, 4> GenerateCodeFamily (const std::string) override;
        std::string DetectCodeId (const std::string)                       override;

    private:
        static std::map <char, std::string> conversionTable;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H
