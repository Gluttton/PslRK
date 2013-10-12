#include "Representer.h"
#include <map>



std::string Representer::HexViewToStringView (const std::string hexView)
{
    std::map <char, std::string> conversionTable {
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


    std::string stringView;

    for (size_t i = 0; i < hexView.length (); ++i) {
        stringView.append (conversionTable [hexView [i] ]);
    }

    stringView = stringView.substr (stringView.find_first_of ('+') );

    return stringView;
}
