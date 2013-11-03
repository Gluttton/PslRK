#include <stdlib.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <Validator.h>
#include <Calculator.h>
#include <Representer.h>



int main (int argc, char * argv [])
{
    using Pslrk::Core::Validator;
    using Pslrk::Core::Calculator;
    using Pslrk::Core::Representer;


    std::vector <std::string> codes;

    auto actionHelp = []() {
        std::cout << "help              Produce this message." << std::endl;
        std::cout << "push code         " << std::endl;
        std::cout << "push family       " << std::endl;
        std::cout << "show codes        " << std::endl;
        std::cout << "show msl          " << std::endl;
        std::cout << "show family       " << std::endl;
        std::cout << "show id           " << std::endl;
        std::cout << "to string         " << std::endl;
        std::cout << "to hex            " << std::endl;
        std::cout << "erase code        " << std::endl;
        std::cout << "clear codes       " << std::endl;
        std::cout << "quit              " << std::endl;
    };

    auto actionPushCode = [&](const std::string & code) {
        codes.push_back (code);
    };

    auto actionPushFamily = [&](const std::string & code) {
        for (const auto & variant : Representer::GenerateCodeFamily (code) ) {
            codes.push_back (variant);
        }
    };

    auto actionShowCodes = [&]() {
        for (const auto & code : codes) {
            std::cout << code << std::endl;
        }
    };

    auto actionShowMsl = [&]() {
        for (const auto & code : codes) {
            std::cout << Calculator::CalculateMsl (code) << std::endl;
        }
    };

    auto actionShowFamily = [&]() {
        for (const auto & code : codes) {
            for (const auto & variant : Representer::GenerateCodeFamily (code) ) {
                std::cout << code << " - " << variant << std::endl;
            }
        }
    };

    auto actionShowId = [&]() {
        for (const auto & code : codes) {
            std::cout << code << " - " << Representer::DetectCodeId (code) << std::endl;
        }
    };

    auto actionToString = [&]() {
        for (auto & code : codes) {
            code = Representer::HexViewToStringView (code);
        }
    };

    auto actionToHex = [&]() {
        for (auto & code : codes) {
            code = Representer::StringViewToHexView (code);
        }
    };

    auto actionEraseCode = [&](const int position) {
        if (position < codes.size () ) {
            codes.erase (codes.begin () + position);
        }
    };

    auto actionClearCodes = [&]() {
        codes.clear ();
    };


    while (true) {
        std::cout << "> ";
        {
            std::string command {""};
            std::getline (std::cin, command);

            if      (0 == command.find ("help") ) {
                actionHelp ();
            }
            else if (0 == command.find ("push code ") ) {
                actionPushCode (command.substr (std::string ("push code ").length () ) );
            }
            else if (0 == command.find ("push family ") ) {
                actionPushFamily (command.substr (std::string ("push family ").length () ) );
            }
            else if (0 == command.find ("show codes") ) {
                actionShowCodes ();
            }
            else if (0 == command.find ("show msl") ) {
                actionShowMsl ();
            }
            else if (0 == command.find ("show family") ) {
                actionShowFamily ();
            }
            else if (0 == command.find ("show id") ) {
                actionShowId ();
            }
            else if (0 == command.find ("to string") ) {
                actionToString ();
            }
            else if (0 == command.find ("to hex") ) {
                actionToHex ();
            }
            else if (0 == command.find ("quit") ) {
                return EXIT_SUCCESS;
            }
            else if (0 == command.find ("erase code ") ) {
                actionEraseCode (boost::lexical_cast <int> (command.substr (std::string ("erase code ").length () ) ) );
            }
            else if (0 == command.find ("clear codes") ) {
                actionClearCodes ();
            }
            else {
                std::cout << "Unrecognized command: " << command << std::endl;
            }
        }

    }


    return EXIT_SUCCESS;
}