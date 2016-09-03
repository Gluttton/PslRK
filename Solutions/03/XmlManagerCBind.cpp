#include "XmlManagerCBind.h"
#include "Representer.h"
#include "Calculator.h"



extern "C"
{

void XmlManagerSaveCode (char * xmlFileName, const __u8 length, const __u64 code)
{
    using Pslrk::Core::XmlManager;
    using Pslrk::Core::Representer;
    using Pslrk::Core::Calculator;

    std::string stringView;
    for (__u8 i = 0; i < length; ++i) {
        stringView += (code >> i) & 0x01 ? "+" : "-";
    }
    std::string id = Representer::DetectCodeId (stringView);

    std::string xPathQuery;
    xPathQuery += ("codes/code[@id=\"");
    xPathQuery += id;
    xPathQuery += "\"]";

    const std::string article = "PSL Research Kit";
    const std::string author  = "PslRK";
    const std::string link    = "https://github.com/Gluttton/PslRK";

    XmlManager xmlManager (xmlFileName);

    if (!xmlManager.Select (xPathQuery) ) {
        xmlManager.InsertCode (
                id
              , Representer::HexViewToStringView (id).length ()
              , Calculator::Psl (stringView)
              ,{Representer::HexViewToStringView (id)}
              ,{ {article, author, link} }
        );
    }
    else {
        xPathQuery += "/reference[@link=\"";
        xPathQuery += link;
        xPathQuery += "\"]";
        if (!xmlManager.Select (xPathQuery) ) {
            xmlManager.InsertCodeReference (id, article, author, link);
        }
    }

    xmlManager.Save ();
}

}// extern "C"
