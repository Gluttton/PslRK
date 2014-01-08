#include <stdlib.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <Validator.h>
#include <Calculator.h>
#include <Representer.h>
#include <XmlManager.h>



// Some kind of RAII helper.
struct Finally
{
    Finally  (const std::function <void ()> action) : finalAction (action) {};
    ~Finally ()                                      {finalAction ();};
    const std::function <void ()>                     finalAction;
};



int main (int argc, char * argv [])
{
    using Pslrk::Core::Exception;
    using Pslrk::Core::Validator;
    using Pslrk::Core::Calculator;
    using Pslrk::Core::Representer;
    using Pslrk::Core::XmlManager;


    std::vector <std::string> codes;
    XmlManager * xmlManager {nullptr};
    Finally xmlManagerFinally ([&](){delete xmlManager;});


    auto actionHelp = []() {
        std::cout << "[Command]         [Parameters]    [Description]" << std::endl;
        std::cout << "help                              Print this message." << std::endl;
        std::cout << "push code         <string>        Put specified code into local storage." << std::endl;
        std::cout << "push family       <string>        Put family of specified code into local storage." << std::endl;
        std::cout << "show codes                        Print local storage." << std::endl;
        std::cout << "show psl                          Print PSL for each of codes from local storage." << std::endl;
        std::cout << "show family                       Print family for each of codes from local storage." << std::endl;
        std::cout << "show id                           Print ID for each of codes from local storage." << std::endl;
        std::cout << "to string         <int>           Convert each of codes from local storage into string format." << std::endl;
        std::cout << "to hex                            Convert each of codes from local storage into hex format." << std::endl;
        std::cout << "erase code        <int>           Erase code with specified index from local storage." << std::endl;
        std::cout << "clear codes                       Clear local storage." << std::endl;
        std::cout << "open base         <string>        Open XML file (whith codes)." << std::endl;
        std::cout << "close base                        Close XML file." << std::endl;
        std::cout << "save base                         Save XML file." << std::endl;
        std::cout << "show base                         Print codes which contained in XML file." << std::endl;
        std::cout << "add base                          Add code to XML file." << std::endl;
        std::cout << "remove base       <string>        Remove code from XML file." << std::endl;
        std::cout << "search base       <string>        Search code in XML file." << std::endl;
        std::cout << "quit                              Exit the program." << std::endl;
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

    auto actionShowPsl = [&]() {
        for (const auto & code : codes) {
            std::cout << Calculator::CalculatePsl (code) << std::endl;
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

    auto actionToString = [&](const size_t length = 0) {
        for (auto & code : codes) {
            if (length) {
                code = Representer::HexViewToStringView (code, length);
            }
            else {
                code = Representer::HexViewToStringView (code);
            }
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

    auto actionOpenBase = [&](const std::string & fileName) {
        try {
            xmlManager = new XmlManager (fileName);
        }
        catch (Exception & e) {
            std::cout << e.what () << std::endl;
        }
    };

    auto actionCloseBase = [&]() {
        delete xmlManager;
        xmlManager = nullptr;
    };

    auto actionSaveBase = [&]() {
        if (xmlManager) {
            try {
                xmlManager->Save ();
            }
            catch (Exception & e) {
                std::cout << e.what () << std::endl;
            }
        }
        else {
            std::cout << "Attempting to save file which was not opened." << std::endl;
        }
    };

    auto actionShowBase = [&]() {
        if (xmlManager) {
            const pugi::xml_node codes = xmlManager->Select ("/").node ();
            for (const auto & code : codes.child ("codes").children ("code") ) {
                std::cout << " Code: id       = " << code.attribute ("id").value     () << std::endl <<
                             "       length   = " << code.attribute ("length").value () << std::endl <<
                             "       PSL      = " << code.attribute ("psl").value    () << std::endl <<
                             "       sequence = " << code.child_value ("sequence")      << std::endl;
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "Attempting to print file which was not opened." << std::endl;
        }
    };

    auto actionAddBase = [&]() {
        if (xmlManager) {
            std::string input {""};
            std::cout << "Input code: > ";
            std::getline (std::cin, input);
            std::string stringView;
            if      (Validator::ValidateStringView (input) == Pslrk::Core::viewIsValid) {
                stringView = input;
            }
            else if (Validator::ValidateHexView    (input) == Pslrk::Core::viewIsValid) {
                stringView = Representer::HexViewToStringView (input);
            }
            else {
                std::cout << "Invalid code, stop adding!" << std::endl;
                return;
            }

            const std::string codeId {Representer::DetectCodeId (stringView)};
            const int codeLength = stringView.length ();
            const int psl {Calculator::CalculatePsl (stringView)};

            std::cout << "Sequence: " << stringView << std::endl;
            std::cout << "ID:       " << codeId     << std::endl;
            std::cout << "Length:   " << codeLength << std::endl;
            std::cout << "PSL:      " << psl        << std::endl;

            std::cout << "Input reference article: > ";
            std::getline (std::cin, input);
            const std::string referenceArticle  {input};
            std::cout << "Input reference author: > ";
            std::getline (std::cin, input);
            const std::string referenceAuthor {input};
            std::cout << "Input reference link: > ";
            std::getline (std::cin, input);
            const std::string referenceLink   {input};

            xmlManager->InsertCode (codeId, codeLength, psl, {stringView}, { {referenceArticle, referenceAuthor, referenceLink} });
        }
        else {
            std::cout << "Attempting to process file which was not opened." << std::endl;
        }
    };

    auto actionRemoveBase = [&](const std::string & id) {
        if (xmlManager) {
            try {
                xmlManager->RemoveCode (id);
            }
            catch (Exception & e) {
                std::cout << e.what () << std::endl;
            }
        }
        else {
            std::cout << "Attempting to process file which was not opened." << std::endl;
        }
    };

    auto actionSearchBase = [&](const std::string & xPathQuery) {
        if (xmlManager) {
            try {
                pugi::xml_document result;
                result.append_child () = xmlManager->Select (xPathQuery).node ();
                result.print (std::cout);
            }
            catch (Exception & e) {
                std::cout << e.what () << std::endl;
            }
        }
        else {
            std::cout << "Attempting to process file which was not opened." << std::endl;
        }
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
            else if (0 == command.find ("show psl") ) {
                actionShowPsl ();
            }
            else if (0 == command.find ("show family") ) {
                actionShowFamily ();
            }
            else if (0 == command.find ("show id") ) {
                actionShowId ();
            }
            else if (0 == command.find ("to string") ) {
                if (command.length () > std::string ("to string ").length () ) {
                    actionToString (boost::lexical_cast <int> (command.substr (std::string ("to string ").length () ) ) );
                }
                else {
                    actionToString ();
                }
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
            else if (0 == command.find ("open base") ) {
                actionOpenBase (command.substr (std::string ("open base ").length () ) );
            }
            else if (0 == command.find ("close base") ) {
                actionCloseBase ();
            }
            else if (0 == command.find ("save base") ) {
                actionSaveBase ();
            }
            else if (0 == command.find ("show base") ) {
                actionShowBase ();
            }
            else if (0 == command.find ("add base") ) {
                actionAddBase ();
            }
            else if (0 == command.find ("remove base") ) {
                actionRemoveBase (command.substr (std::string ("remove base ").length () ) );
            }
            else if (0 == command.find ("search base") ) {
                actionSearchBase (command.substr (std::string ("search base ").length () ) );
            }
            else {
                std::cout << "Unrecognized command: " << command << std::endl;
            }
        }
    }


    return EXIT_SUCCESS;
}