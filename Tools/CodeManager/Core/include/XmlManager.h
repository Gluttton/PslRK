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
        void Save                       ();
        const pugi::xpath_node Select   (const std::string &);
        void Insert                     (const std::string &,
                                         const int,
                                         const int,
                                         const std::string &,
                                         const std::vector <std::array <std::string, 3> > &);
        void Remove                     (const std::string &);

    private:
        pugi::xml_document              xmlDocument;
        const std::string               fileName;
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_XML_MANAGER_H