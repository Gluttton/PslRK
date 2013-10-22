#include "Representer.h"
#include "Exception.h"
#include "Validator.h"
#include <algorithm>



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



std::string Representer::HexViewToStringView (const std::string & hexView)
{
    if (Validator::ValidateHexView (hexView) != viewIsValid) {
        throw ExceptionInvalidHexView ();
    }

    std::string stringView;

    for (size_t i = 0; i < hexView.length (); ++i) {
        stringView.append (conversionHexToStringTable [hexView [i] ]);
    }

    stringView = stringView.substr (stringView.find_first_of ('+') );

    return stringView;
}



std::string Representer::HexViewToStringView (const std::string & hexView, const size_t length)
{
    if (Validator::ValidateHexView (hexView) != viewIsValid) {
        throw ExceptionInvalidHexView ();
    }

    std::string stringView;

    for (size_t i = 0; i < hexView.length (); ++i) {
        stringView.append (conversionHexToStringTable [hexView [i] ]);
    }

    stringView = stringView.substr (stringView.length () - length);

    return stringView;
}



std::string Representer::StringViewToHexView (const std::string & stringView)
{
    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

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



std::string Representer::ReverseCode (const std::string & stringView)
{
    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    std::string reversedStringView (stringView);
    std::reverse (reversedStringView.begin (), reversedStringView.end () );

    return reversedStringView;
}



std::string Representer::InverseCode (const std::string & stringView)
{
    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    return std::accumulate (stringView.begin (), stringView.end (), std::string (),
                [& stringView](std::string & result, const char & c) {
                    switch (c) {
                        case '+': return result.append ("-");
                        case '-': return result.append ("+");
                        default : return result;
                    }
                }
    );
}



std::array <std::string, codeFamilySize> Representer::GenerateCodeFamily (const std::string & stringView)
{
    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    std::array <std::string, codeFamilySize> family;

    static_assert (codeFamilySize == 4, "Constant codeFamilySize must be equal to 4 (view, reversed view, inversed view, inversed and reversed view).");
    family [0] = stringView;
    family [1] = ReverseCode (stringView);
    family [2] = InverseCode (stringView);
    family [3] = ReverseCode (InverseCode (stringView) );

    return family;
}



std::string Representer::DetectCodeId (const std::string & stringView)
{
    if (Validator::ValidateStringView (stringView) != viewIsValid) {
        throw ExceptionInvalidStringView ();
    }

    const auto family = GenerateCodeFamily (stringView);

    return StringViewToHexView (* std::min_element (family.begin (), family.end () ) );
}

}// namespace Core
}// namespace Pslrk