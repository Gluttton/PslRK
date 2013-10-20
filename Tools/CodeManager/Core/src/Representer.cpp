#include "Representer.h"
#include <algorithm>
#include <iostream>



namespace Pslrk
{
namespace Core
{

std::map <char, std::string> Representer::conversionHexToStringTable {
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
    {'a', "+-+-"}, {'A', "+-+-"},
    {'b', "+-++"}, {'B', "+-++"},
    {'c', "++--"}, {'C', "++--"},
    {'d', "++-+"}, {'D', "++-+"},
    {'e', "+++-"}, {'E', "+++-"},
    {'f', "++++"}, {'F', "++++"}
};



std::map <std::string, char> Representer::conversionStringToHexTable {
    {"----", '0'},
    {"---+", '1'},
    {"--+-", '2'},
    {"--++", '3'},
    {"-+--", '4'},
    {"-+-+", '5'},
    {"-++-", '6'},
    {"-+++", '7'},
    {"+---", '8'},
    {"+--+", '9'},
    {"+-+-", 'a'},
    {"+-++", 'b'},
    {"++--", 'c'},
    {"++-+", 'd'},
    {"+++-", 'e'},
    {"++++", 'f'}
};



std::string Representer::HexViewToStringView (const std::string & hexView) const
{
    std::string stringView;

    for (size_t i = 0; i < hexView.length (); ++i) {
        stringView.append (conversionHexToStringTable [hexView [i] ]);
    }

    stringView = stringView.substr (stringView.find_first_of ('+') );

    return stringView;
}



std::string Representer::HexViewToStringView (const std::string & hexView, const size_t length) const
{
    std::string stringView;

    for (size_t i = 0; i < hexView.length (); ++i) {
        stringView.append (conversionHexToStringTable [hexView [i] ]);
    }

    stringView = stringView.substr (stringView.length () - length);

    return stringView;
}



std::string Representer::StringViewToHexView (const std::string & stringView) const
{
    constexpr int tetradSize {4};
    std::string hexView;
    const size_t shortageSize {stringView.length () % tetradSize};
    const size_t extendedSize {shortageSize ? tetradSize - shortageSize : 0};
    std::string extendedStringView (extendedSize, '-');
    extendedStringView.append (stringView);

    for (int i {0}; i < stringView.length (); i += tetradSize) {
        hexView.append (1, conversionStringToHexTable [extendedStringView.substr(i, tetradSize)]);
    }

    return hexView;
}



std::string Representer::ReverseCode (const std::string & code) const
{
    std::string reversedCode (code);

    std::reverse (reversedCode.begin (), reversedCode.end () );

    return reversedCode;
}



std::string Representer::InverseCode (const std::string & code) const
{
    return std::accumulate (code.begin (), code.end (), std::string (),
                [& code](std::string & result, const char & c) {
                    switch (c) {
                        case '+': return result.append ("-");
                        case '-': return result.append ("+");
                        default : return result;
                    }
                }
    );
}



std::array <std::string, codeFamilySize> Representer::GenerateCodeFamily (const std::string & code) const
{
    std::array <std::string, codeFamilySize> family;

    // TODO: Add invariant checking (codeFamilySize great or equal 4) and declare suitable exception class.
    family [0] = code;
    family [1] = ReverseCode (code);
    family [2] = InverseCode (code);
    family [3] = ReverseCode (InverseCode (code) );

    
    return family;
}



std::string Representer::DetectCodeId (const std::string & code) const
{
    const auto family = GenerateCodeFamily (code);

    return StringViewToHexView (* std::min_element (family.begin (), family.end () ) );
}

}// namespace Core
}// namespace Pslrk