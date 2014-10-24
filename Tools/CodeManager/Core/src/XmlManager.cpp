#include "XmlManager.h"
#include <cstring>



namespace Pslrk
{
namespace Core
{

XmlManager::XmlManager (const std::string & fileName)
            : xmlDocument ()
            , fileName    (fileName)
{
    if (!xmlDocument.load_file (fileName.c_str (), pugi::parse_default | pugi::parse_comments | pugi::parse_declaration) ) {
        throw ExceptionXmlErrorLoadFile ();
    }
}



XmlManager::~XmlManager ()
{
}



void XmlManager::Clear ()
{
    for (auto & node : xmlDocument.child ("codes").children ("code") ) {
        xmlDocument.child ("codes").remove_child (node);
    }
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



void XmlManager::InsertCode (const std::string & id, const int length, const int psl,
                             std::vector <std::string> sequences,
                             std::vector <std::array <std::string, referenceAttributeCount> > references)
{
    InsertCode (id, length, psl);
    for (const auto & sequence : sequences) {
        InsertCodeSequence (id, sequence);
    }
    for (const auto & reference : references) {
        InsertCodeReference (id, reference [0], reference [1], reference [2]);
    }
}



void XmlManager::InsertCode (const std::string & id, const int length, const int psl)
{
    pugi::xml_node nodeCode = xmlDocument.child ("codes").append_child ("code");
    nodeCode.append_attribute ("id")     = id.c_str ();
    nodeCode.append_attribute ("length") = length;
    nodeCode.append_attribute ("psl")    = psl;
}



void XmlManager::InsertCodeSequence (const std::string & id, const std::string & sequence)
{
    for (auto & node : xmlDocument.child ("codes").children ("code") ) {
        for (auto & attribute : node.attributes () ) {
            if (!(strcmp (attribute.name (), "id") || strcmp (attribute.value (), id.c_str () ) ) ) {
                node.append_child ("sequence").text ().set (sequence.c_str () );
                return;
            }
        }
    }
}



void XmlManager::InsertCodeReference (const std::string & id, const std::string & article, const std::string & author, const std::string & link)
{
    for (auto & node : xmlDocument.child ("codes").children ("code") ) {
        for (auto & attribute : node.attributes () ) {
            if (!(strcmp (attribute.name (), "id") || strcmp (attribute.value (), id.c_str () ) ) ) {
                pugi::xml_node nodeReference = node.append_child ("reference");
                nodeReference.append_attribute ("article") = article.c_str ();
                nodeReference.append_attribute ("author")  = author.c_str  ();
                nodeReference.append_attribute ("link")    = link.c_str    ();
                return;
            }
        }
    }
}



void XmlManager::RemoveCode (const std::string & id)
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



void XmlManager::RemoveCodeSequence (const std::string & id, const std::string & sequence)
{
    for (auto & node : xmlDocument.child ("codes").children ("code") ) {
        for (auto & attribute : node.attributes () ) {
            if (!(strcmp (attribute.name (), "id") || strcmp (attribute.value (), id.c_str () ) ) ) {
                for (const auto & child : node.children ("sequence") ) {
                    if (!strcmp (child.text ().get (), sequence.c_str () ) ) {
                        node.remove_child (child);
                        return;
                    }
                }
            }
        }
    }
}



void XmlManager::RemoveCodeReference (const std::string & id, const std::string & article, const std::string & author, const std::string & link)
{
    for (auto & node : xmlDocument.child ("codes").children ("code") ) {
        for (auto & attribute : node.attributes () ) {
            if (!(strcmp (attribute.name (), "id") || strcmp (attribute.value (), id.c_str () ) ) ) {
                for (const auto & child : node.children ("reference") ) {
                    int matches {0};
                    for (const auto & childAttribute : child.attributes () ) {
                        if (!(strcmp (childAttribute.name (), "article") || strcmp (childAttribute.value (), article.c_str () ) ) ) {
                            ++matches;
                        }
                        if (!(strcmp (childAttribute.name (), "author")  || strcmp (childAttribute.value (), author.c_str () ) ) ) {
                            ++matches;
                        }
                        if (!(strcmp (childAttribute.name (), "link")    || strcmp (childAttribute.value (), link.c_str () ) ) ) {
                            ++matches;
                        }
                    }
                    if (referenceAttributeCount == matches) {
                        node.remove_child (child);
                        return;
                    }
                }
            }
        }
    }
}

}// namespace Core
}// namespace Pslrk
