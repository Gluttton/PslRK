#include "Representer.h"



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
