#include "XmlManager.h"
#include <iostream>
#include <cstring>



namespace Pslrk
{
namespace Core
{

XmlManager::XmlManager (const std::string & fileName)
            : xmlDocument ()
            , fileName    (fileName)
{
    if (!xmlDocument.load_file (fileName.c_str () ) ) {
        throw ExceptionXmlErrorLoadFile ();
    }
}



XmlManager::~XmlManager ()
{
}



void XmlManager::Save ()
{
    if (!xmlDocument.save_file (fileName.c_str () ) ) {
        throw ExceptionXmlErrorSaveFile ();
    }
}



const pugi::xpath_node XmlManager::Select (const std::string & xPathQuery)
{
    return xmlDocument.select_single_node (xPathQuery.c_str () );
}



void XmlManager::Insert (const std::string & id,
                         const std::string & length,
                         const std::string & maxPsl,
                         const std::string & sequence,
                         const std::vector <std::array <std::string, 3> > & references)
{
    pugi::xml_node nodeCode = xmlDocument.child ("codes").append_child ("code");
    nodeCode.append_attribute ("id")     = id.c_str ();
    nodeCode.append_attribute ("length") = length.c_str ();
    nodeCode.append_attribute ("maxpsl") = maxPsl.c_str ();
    nodeCode.append_child ("sequence").text ().set (sequence.c_str () );
    for (const auto & reference : references) {
        pugi::xml_node nodeReference = nodeCode.append_child ("reference");
        nodeReference.append_attribute ("article") = reference [0].c_str ();
        nodeReference.append_attribute ("author")  = reference [1].c_str ();
        nodeReference.append_attribute ("link")    = reference [2].c_str ();
    }
}



void XmlManager::Remove (const std::string & id)
{
    for (auto & node : xmlDocument.child ("codes").children ("code") ) {
        for (auto & attribute : node.attributes () ) {
            if (!(strcmp (attribute.name (), "id") || strcmp (attribute.value (), id.c_str () ) ) ) {
                xmlDocument.child ("codes").remove_child (node);
                return;
            }
        }
    }
}

}// namespace Core
}// namespace Pslrk