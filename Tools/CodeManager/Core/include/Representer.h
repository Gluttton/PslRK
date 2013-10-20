#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H

#include <string>
#include <array>
#include <map>



class Representer
{
    public:
        std::string HexViewToStringView (const std::string);
        std::string HexViewToStringView (const std::string, const size_t);
        std::string StringViewToHexView (const std::string);
        std::string ReverseCode (const std::string);
        std::string InverseCode (const std::string);
        std::array <std::string, 4> GenerateCodeFamily (const std::string);
        std::string DetectCodeId (const std::string);

    private:
        static std::map <char, std::string> conversionTable;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H