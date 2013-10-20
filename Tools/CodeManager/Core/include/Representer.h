#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H

#include <string>
#include <array>
#include <map>



namespace Pslrk
{
namespace Core
{

constexpr int codeFamilySize {4};



class Representer
{
    public:
        std::string HexViewToStringView (const std::string &) const;
        std::string HexViewToStringView (const std::string &, const size_t) const;
        std::string StringViewToHexView (const std::string &) const;
        std::string ReverseCode (const std::string &) const;
        std::string InverseCode (const std::string &) const;
        std::array <std::string, codeFamilySize> GenerateCodeFamily (const std::string &) const;
        std::string DetectCodeId (const std::string &) const;

    private:
        static std::map <char, std::string> conversionTable;
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H