#include "Representer.h"
#include <algorithm>



namespace Pslrk
{
namespace Core
{

std::map <char, std::string> Representer::conversionTable {
    {'0', "----"},
    {'1', "---+"},
    {'2', "--+-"},
    {'3', "--++"},
    {'4', "-+--"},
    {'5', "-+-+"},
    {'6', "-++-"},
    {'7', "-+++"},
    {'8', "+---"},
    {'9', "+--+"},
    {'a', "+-+-"},
    {'A', "+-+-"},
    {'b', "+-++"}, {'B', "+-++"},
    {'c', "++--"}, {'C', "++--"},
    {'d', "++-+"}, {'D', "++-+"},
    {'e', "+++-"}, {'E', "+++-"},
    {'f', "++++"}, {'F', "++++"}
};



std::string Representer::HexViewToStringView (const std::string hexView)
{
    std::string stringView;

    for (size_t i = 0; i < hexView.length (); ++i) {
        stringView.append (conversionTable [hexView [i] ]);
    }

    stringView = stringView.substr (stringView.find_first_of ('+') );

    return stringView;
}



std::string Representer::HexViewToStringView (const std::string hexView, const size_t length)
{
    std::string stringView;

    for (size_t i = 0; i < hexView.length (); ++i) {
        stringView.append (conversionTable [hexView [i] ]);
    }

    stringView = stringView.substr (stringView.length () - length);

    return stringView;
}



std::string Representer::StringViewToHexView (const std::string stringView)
{
    std::string hexView;
    int extendedSize = stringView.length () & 3;
    extendedSize = extendedSize ? 4 - extendedSize : 0;
    std::string extendedStringView (extendedSize, '-');
    extendedStringView.append (stringView);

    for (int i = 0; i < stringView.length (); i += 4) {
        const std::string tetrad = extendedStringView.substr (i, 4);
        for (auto x : conversionTable) {
            if (x.second == tetrad) {
                const std::string symbol (1, x.first);
                hexView.append (symbol);
                break;
            }
        }
    }

    std::transform (hexView.begin (), hexView.end (), hexView.begin (), ::tolower);

    return hexView;
}



std::string Representer::ReverseCode (const std::string code)
{
    std::string reversedCode (code);

    std::reverse (reversedCode.begin (), reversedCode.end () );

    return reversedCode;
}



std::string Representer::InverseCode (const std::string code)
{
    std::string inversedCode;

    for (int i = 0; i < code.length (); ++i) {
        switch (code [i]) {
            case '+': inversedCode.append ("-"); break;
            case '-': inversedCode.append ("+"); break;
        }
    }


    return inversedCode;
}



std::array <std::string, 4> Representer::GenerateCodeFamily (const std::string code)
{
    std::array <std::string, 4> family;

    family [0] = code;
    family [1] = ReverseCode (code);
    family [2] = InverseCode (code);
    family [3] = ReverseCode (InverseCode (code) );

    return family;
}



std::string Representer::DetectCodeId (const std::string code)
{
    const std::array <std::string, 4> family = GenerateCodeFamily (code);

    return StringViewToHexView (std::min (std::min (family [0], family [1]), std::min (family [2], family [3]) ) );
}

}// namespace Core
}// namespace Pslrk