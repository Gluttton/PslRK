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
        static std::string HexViewToStringView (const std::string &);
        static std::string HexViewToStringView (const std::string &, const size_t);
        static std::string StringViewToHexView (const std::string &);
        static std::string ReverseCode (const std::string &);
        static std::string InverseCode (const std::string &);
        static std::array <std::string, codeFamilySize> GenerateCodeFamily (const std::string &);
        static std::string DetectCodeId (const std::string &);

    private:
        static std::map <char, std::string> conversionHexToStringTable;
        static std::map <std::string, char> conversionStringToHexTable;
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_REPRESENTER_H