#include "XmlManager.h"
#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>



using Pslrk::Core::XmlManager;
using Pslrk::Core::Exception;
using Pslrk::Core::ExceptionXmlError;
using Pslrk::Core::ExceptionXmlErrorLoadFile;
using Pslrk::Core::ExceptionXmlErrorSaveFile;

namespace bfs = boost::filesystem;



class XmlManagerTest : public ::testing::Test
{
    public:
        XmlManagerTest          ();
        virtual ~XmlManagerTest ();
    protected:
        void SetUp              () override;
        void TearDown           () override;

        void CompareNodes       (const pugi::xml_node &, const pugi::xml_node &);

        const std::string       dummyGoodXmlFileName;
        const std::string       dummyBadXmlFileName;
};



XmlManagerTest::XmlManagerTest ()
            : dummyGoodXmlFileName ("DummyGood.xml")
            , dummyBadXmlFileName  ("DummyBad.xml")
{
}



XmlManagerTest::~XmlManagerTest ()
{
}



void XmlManagerTest::SetUp ()
{
    bfs::ofstream goodFile (dummyGoodXmlFileName);
    goodFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    goodFile << "<codes>" << std::endl;
    goodFile << "<code id=\"2\" length=\"2\" maxpsl=\"1\">" << std::endl;
    goodFile << "<sequence>+-</sequence>" << std::endl;
    goodFile << "<reference" << std::endl;
    goodFile << "    article=\"Group synchronization of binary digital systems\"" << std::endl;
    goodFile << "    author=\"R.H. Barker\"" << std::endl;
    goodFile << "    link=\"http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems\">" << std::endl;
    goodFile << "</reference>" << std::endl;
    goodFile << "</code>" << std::endl;
    goodFile << "</codes>" << std::endl;
    goodFile.close ();

    bfs::ofstream badFile (dummyBadXmlFileName);
    badFile  << "<?xml version=\"1.0\" encoding=\"UTF-3\"?>" << std::endl;
    badFile  << "<codes>" << std::endl;
    badFile.close ();
}



void XmlManagerTest::TearDown ()
{
    if (bfs::exists (dummyGoodXmlFileName) ) {
        bfs::remove (dummyGoodXmlFileName);
    }
    if (bfs::exists (dummyBadXmlFileName) ) {
        bfs::remove (dummyBadXmlFileName);
    }
}



void XmlManagerTest::CompareNodes (const pugi::xml_node & etalonNode, const pugi::xml_node & testNode)
{
    ASSERT_EQ (0, strcmp (etalonNode.attribute ("id").value     (), testNode.attribute("id").value     () ) );
    ASSERT_EQ (0, strcmp (etalonNode.attribute ("length").value (), testNode.attribute("length").value () ) );
    ASSERT_EQ (0, strcmp (etalonNode.attribute ("maxpsl").value (), testNode.attribute("maxpsl").value () ) );
    ASSERT_EQ (0, strcmp (etalonNode.child_value ("sequence")     , testNode.child_value ("sequence")     ) );
    // FIXME: Error! References is missed.
}



TEST_F (XmlManagerTest, OpenNoThrow)
{
    // Arrange, Act, Assert.
    ASSERT_NO_THROW (XmlManager xmlManager (dummyGoodXmlFileName) );
}



TEST_F (XmlManagerTest, OpenThrow)
{
    // Arrange, Act, Assert.
    ASSERT_THROW (XmlManager xmlManager (dummyBadXmlFileName), ExceptionXmlErrorLoadFile);
}



TEST_F (XmlManagerTest, SaveNoThrow)
{
    // Arrange.
    XmlManager xmlManager (dummyGoodXmlFileName);

    // Act, Assert.
    ASSERT_NO_THROW (xmlManager.Save () );
}



TEST_F (XmlManagerTest, AddCodeSuccess)
{
    // Arrange.
    XmlManager xmlManager (dummyGoodXmlFileName);
    pugi::xml_document document;
    pugi::xml_node nodeCodes = document.append_child ("codes");
    pugi::xml_node nodeCode  = nodeCodes.append_child ("code");
    nodeCode.append_attribute ("id")     = "3";
    nodeCode.append_attribute ("length") = 2;
    nodeCode.append_attribute ("maxpsl") = 1;
    nodeCode.append_child ("sequence").text ().set ("++");
    pugi::xml_node nodeReference = nodeCode.append_child ("reference");
    nodeReference.append_attribute ("article") = "Group synchronization of binary digital systems";
    nodeReference.append_attribute ("author")  = "R.H. Barker";
    nodeReference.append_attribute ("link")    = "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems";
    const pugi::xpath_node etalonBeforeResult;
    const pugi::xpath_node etalonAfterResult (nodeCode);

    const std::string xPathQuery ("codes/code[@id=\"3\"]");

    // Act.
    const pugi::xpath_node testBeforeResult = xmlManager.Select (xPathQuery);
    xmlManager.Insert ("3", 2, 1, "++",
                       { {"Group synchronization of binary digital systems",
                          "R.H. Barker",
                          "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems"
                       } }
    );
    const pugi::xpath_node testAfterResult  = xmlManager.Select (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node  (), testAfterResult.node  () );
}



TEST_F (XmlManagerTest, RemoveCodeSuccess)
{
    // Arrange.
    XmlManager xmlManager (dummyGoodXmlFileName);
    pugi::xml_document document;
    pugi::xml_node nodeCodes = document.append_child ("codes");
    pugi::xml_node nodeCode  = nodeCodes.append_child ("code");
    nodeCode.append_attribute ("id")     = "2";
    nodeCode.append_attribute ("length") = 2;
    nodeCode.append_attribute ("maxpsl") = 1;
    nodeCode.append_child ("sequence").text ().set ("+-");
    pugi::xml_node nodeReference = nodeCode.append_child ("reference");
    nodeReference.append_attribute ("article") = "Group synchronization of binary digital systems";
    nodeReference.append_attribute ("author")  = "R.H. Barker";
    nodeReference.append_attribute ("link")    = "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems";
    const pugi::xpath_node etalonBeforeResult (nodeCode);
    const pugi::xpath_node etalonAfterResult;

    const std::string xPathQuery ("codes/code[@id=\"2\"]");

    // Act.
    const pugi::xpath_node testBeforeResult = xmlManager.Select (xPathQuery);
    xmlManager.Remove ("2");
    const pugi::xpath_node testAfterResult  = xmlManager.Select (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node  (), testAfterResult.node  () );
}