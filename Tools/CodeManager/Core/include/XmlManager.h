#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_XML_MANAGER_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_XML_MANAGER_H

#include "Exception.h"
#include <pugixml.hpp>
#include <string>
#include <vector>
#include <array>



namespace Pslrk
{
namespace Core
{

class XmlManager
{
    public:
        XmlManager                      (const std::string &);
        virtual ~XmlManager             ();

        static constexpr int            referenceAttributeCount {3};

        void Clear                      ();
        void Save                       ();
        const pugi::xpath_node Select   (const std::string &);
        void InsertCode                 (const std::string &, const int, const int,
                                         std::vector <std::string>,
                                         std::vector <std::array <std::string, referenceAttributeCount> >);
        void InsertCode                 (const std::string &, const int, const int);
        void InsertCodeSequence         (const std::string &, const std::string &);
        void InsertCodeReference        (const std::string &, const std::string &, const std::string &, const std::string &);

        void RemoveCode                 (const std::string &);
        void RemoveCodeSequence         (const std::string &, const std::string &);
        void RemoveCodeReference        (const std::string &, const std::string &, const std::string &, const std::string &);

    private:
        pugi::xml_document              xmlDocument;
        const std::string               fileName;
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_XML_MANAGER_H