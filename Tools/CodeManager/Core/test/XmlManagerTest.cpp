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

    std::vector <std::string> etalonSequences;
    for (const auto & sequence : etalonNode.children ("sequence") ) {
        etalonSequences.push_back (sequence.text ().get () );
    }
    std::vector <std::string> testSequences;
    for (const auto & sequence : testNode.children ("sequence") ) {
        testSequences.push_back (sequence.text ().get () );
    }
    ASSERT_EQ (etalonSequences.size (), testSequences.size () );
    for (size_t i = 0; i < etalonSequences.size (); ++i) {
        ASSERT_EQ (0, etalonSequences [i].compare (testSequences [i]) );
    }

    std::vector <std::string> etalonReferences;
    for (const auto & reference : etalonNode.children ("reference") ) {
        etalonReferences.push_back (reference.text ().get () );
    }
    std::vector <std::string> testReferences;
    for (const auto & reference : testNode.children ("reference") ) {
        testReferences.push_back (reference.text ().get () );
    }
    ASSERT_EQ   (etalonReferences.size (), testReferences.size () );
    for (size_t i = 0; i < etalonReferences.size (); ++i) {
        ASSERT_EQ (0, etalonReferences [i].compare (testReferences [i]) );
    }
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



TEST_F (XmlManagerTest, ClearSuccess)
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
    nodeReference.append_attribute ("author") = "R.H. Barker";
    nodeReference.append_attribute ("link") = "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems";
    const pugi::xpath_node etalonBeforeResult (nodeCode);
    const pugi::xpath_node etalonAfterResult;

    const std::string xPathQuery ("codes/code[@id=\"2\"]");

    // Act.
    const pugi::xpath_node testBeforeResult = xmlManager.Select (xPathQuery);
    xmlManager.Clear ();
    const pugi::xpath_node testAfterResult  = xmlManager.Select (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node  (), testAfterResult.node  () );
}



TEST_F (XmlManagerTest, SaveNoThrow)
{
    // Arrange.
    XmlManager xmlManager (dummyGoodXmlFileName);

    // Act, Assert.
    ASSERT_NO_THROW (xmlManager.Save () );
}



TEST_F (XmlManagerTest, InsertCodeSuccess)
{
    // Arrange.
    XmlManager xmlManager (dummyGoodXmlFileName);
    pugi::xml_document document;
    pugi::xml_node nodeCodes = document.append_child ("codes");
    pugi::xml_node nodeCode  = nodeCodes.append_child ("code");
    nodeCode.append_attribute ("id")     = "3";
    nodeCode.append_attribute ("length") = 2;
    nodeCode.append_attribute ("maxpsl") = 1;
    const pugi::xpath_node etalonBeforeResult;
    const pugi::xpath_node etalonAfterResult (nodeCode);

    const std::string xPathQuery ("codes/code[@id=\"3\"]");

    // Act.
    const pugi::xpath_node testBeforeResult = xmlManager.Select (xPathQuery);
    xmlManager.InsertCode ("3", 2, 1);
    const pugi::xpath_node testAfterResult  = xmlManager.Select (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node  (), testAfterResult.node  () );
}



TEST_F (XmlManagerTest, InsertCodeCompletelySuccess)
{
    // Arrange.
    XmlManager xmlManager (dummyGoodXmlFileName);
    pugi::xml_document document;
    pugi::xml_node nodeCodes = document.append_child ("codes");
    pugi::xml_node nodeCode = nodeCodes.append_child ("code");
    nodeCode.append_attribute ("id") = "3";
    nodeCode.append_attribute ("length") = 2;
    nodeCode.append_attribute ("maxpsl") = 1;
    nodeCode.append_child ("sequence").text ().set ("++");
    pugi::xml_node nodeReference = nodeCode.append_child ("reference");
    nodeReference.append_attribute ("article") = "Group synchronization of binary digital systems";
    nodeReference.append_attribute ("author") = "R.H. Barker";
    nodeReference.append_attribute ("link") = "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems";
    const pugi::xpath_node etalonBeforeResult;
    const pugi::xpath_node etalonAfterResult (nodeCode);

    const std::string xPathQuery ("codes/code[@id=\"3\"]");

    // Act.
    const pugi::xpath_node testBeforeResult = xmlManager.Select (xPathQuery);
    xmlManager.InsertCode (
        "3", 2, 1,
        {"++"},
        { {"Group synchronization of binary digital systems",
           "R.H. Barker",
           "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems"
        } }
    );
    const pugi::xpath_node testAfterResult = xmlManager.Select (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node (), testAfterResult.node () );
}



TEST_F (XmlManagerTest, InsertCodeSequenceSuccess)
{
    // Arrange.
    bfs::ofstream goodFile (dummyGoodXmlFileName);
    goodFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    goodFile << "<codes>" << std::endl;
    goodFile << "<code id=\"3\" length=\"2\" maxpsl=\"1\">" << std::endl;
    goodFile << "</code>" << std::endl;
    goodFile << "</codes>" << std::endl;
    goodFile.close ();
    XmlManager xmlManager (dummyGoodXmlFileName);
    pugi::xml_document document;
    pugi::xml_node nodeCodes = document.append_child ("codes");
    pugi::xml_node nodeCode  = nodeCodes.append_child ("code");
    nodeCode.append_attribute ("id")     = "3";
    nodeCode.append_attribute ("length") = 2;
    nodeCode.append_attribute ("maxpsl") = 1;
    const pugi::xpath_node etalonBeforeResult (nodeCode);
    nodeCode.append_child ("sequence").text ().set ("++");
    const pugi::xpath_node etalonAfterResult  (nodeCode);

    const std::string xPathQuery ("codes/code[@id=\"3\"]");

    // Act.
    const pugi::xpath_node testBeforeResult = xmlManager.Select (xPathQuery);
    xmlManager.InsertCodeSequence ("3", "++");
    const pugi::xpath_node testAfterResult  = xmlManager.Select (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node  (), testAfterResult.node  () );
    // Clearing.
    if (bfs::exists (dummyGoodXmlFileName) ) {
        bfs::remove (dummyGoodXmlFileName);
    }
}



TEST_F (XmlManagerTest, InsertCodeReferenceSuccess)
{
    // Arrange.
    bfs::ofstream goodFile (dummyGoodXmlFileName);
    goodFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    goodFile << "<codes>" << std::endl;
    goodFile << "<code id=\"3\" length=\"2\" maxpsl=\"1\">" << std::endl;
    goodFile << "</code>" << std::endl;
    goodFile << "</codes>" << std::endl;
    goodFile.close ();
    XmlManager xmlManager (dummyGoodXmlFileName);
    pugi::xml_document document;
    pugi::xml_node nodeCodes = document.append_child ("codes");
    pugi::xml_node nodeCode  = nodeCodes.append_child ("code");
    nodeCode.append_attribute ("id")     = "3";
    nodeCode.append_attribute ("length") = 2;
    nodeCode.append_attribute ("maxpsl") = 1;
    const pugi::xpath_node etalonBeforeResult (nodeCode);
    pugi::xml_node nodeReference = nodeCode.append_child ("reference");
    nodeReference.append_attribute ("article") = "Group of systems";
    nodeReference.append_attribute ("author")  = "R.H. Barker";
    nodeReference.append_attribute ("link")    = "http://systems";
    const pugi::xpath_node etalonAfterResult  (nodeCode);

    const std::string xPathQuery ("codes/code[@id=\"3\"]");

    // Act.
    const pugi::xpath_node testBeforeResult = xmlManager.Select (xPathQuery);
    xmlManager.InsertCodeReference ("3", "Group of systems", "R.H. Barker", "http://systems");
    const pugi::xpath_node testAfterResult  = xmlManager.Select (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node  (), testAfterResult.node  () );
    // Clearing.
    if (bfs::exists (dummyGoodXmlFileName) ) {
        bfs::remove (dummyGoodXmlFileName);
    }
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
    xmlManager.RemoveCode ("2");
    const pugi::xpath_node testAfterResult  = xmlManager.Select (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node  (), testAfterResult.node  () );
}



TEST_F (XmlManagerTest, RemoveCodeSequenceSuccess)
{
    // Arrange.
    XmlManager xmlManagerBefore (dummyGoodXmlFileName);
    XmlManager xmlManagerAfter  (dummyGoodXmlFileName);

    pugi::xml_document documentAfter;
    pugi::xml_node nodeCodesAfter = documentAfter.append_child  ("codes");
    pugi::xml_node nodeCodeAfter  = nodeCodesAfter.append_child ("code");
    nodeCodeAfter.append_attribute ("id")     = "2";
    nodeCodeAfter.append_attribute ("length") = 2;
    nodeCodeAfter.append_attribute ("maxpsl") = 1;
    pugi::xml_node nodeReferenceAfter = nodeCodeAfter.append_child ("reference");
    nodeReferenceAfter.append_attribute ("article") = "Group synchronization of binary digital systems";
    nodeReferenceAfter.append_attribute ("author")  = "R.H. Barker";
    nodeReferenceAfter.append_attribute ("link")    = "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems";
    const pugi::xpath_node etalonAfterResult (nodeCodeAfter);

    pugi::xml_document documentBefore;
    pugi::xml_node nodeCodesBefore = documentBefore.append_child  ("codes");
    pugi::xml_node nodeCodeBefore  = nodeCodesBefore.append_child ("code");
    nodeCodeBefore.append_attribute ("id")     = "2";
    nodeCodeBefore.append_attribute ("length") = 2;
    nodeCodeBefore.append_attribute ("maxpsl") = 1;
    nodeCodeBefore.append_child ("sequence").text ().set ("+-");
    pugi::xml_node nodeReferenceBefore = nodeCodeBefore.append_child ("reference");
    nodeReferenceBefore.append_attribute ("article") = "Group synchronization of binary digital systems";
    nodeReferenceBefore.append_attribute ("author")  = "R.H. Barker";
    nodeReferenceBefore.append_attribute ("link")    = "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems";
    const pugi::xpath_node etalonBeforeResult (nodeCodeBefore);

    const std::string xPathQuery ("codes/code[@id=\"2\"]");

    // Act.
    const pugi::xpath_node testBeforeResult = xmlManagerBefore.Select (xPathQuery);
    xmlManagerAfter.RemoveCodeSequence ("2", "+-");
    const pugi::xpath_node testAfterResult  = xmlManagerAfter.Select  (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node  (), testAfterResult.node  () );
}



TEST_F (XmlManagerTest, RemoveCodeReferenceSuccess)
{
    // Arrange.
    XmlManager xmlManagerBefore (dummyGoodXmlFileName);
    XmlManager xmlManagerAfter  (dummyGoodXmlFileName);

    pugi::xml_document documentAfter;
    pugi::xml_node nodeCodesAfter = documentAfter.append_child  ("codes");
    pugi::xml_node nodeCodeAfter  = nodeCodesAfter.append_child ("code");
    nodeCodeAfter.append_attribute ("id")     = "2";
    nodeCodeAfter.append_attribute ("length") = 2;
    nodeCodeAfter.append_attribute ("maxpsl") = 1;
    nodeCodeAfter.append_child ("sequence").text ().set ("+-");
    const pugi::xpath_node etalonAfterResult (nodeCodeAfter);

    pugi::xml_document documentBefore;
    pugi::xml_node nodeCodesBefore = documentBefore.append_child  ("codes");
    pugi::xml_node nodeCodeBefore  = nodeCodesBefore.append_child ("code");
    nodeCodeBefore.append_attribute ("id")     = "2";
    nodeCodeBefore.append_attribute ("length") = 2;
    nodeCodeBefore.append_attribute ("maxpsl") = 1;
    nodeCodeBefore.append_child ("sequence").text ().set ("+-");
    pugi::xml_node nodeReferenceBefore = nodeCodeBefore.append_child ("reference");
    nodeReferenceBefore.append_attribute ("article") = "Group synchronization of binary digital systems";
    nodeReferenceBefore.append_attribute ("author")  = "R.H. Barker";
    nodeReferenceBefore.append_attribute ("link")    = "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems";
    const pugi::xpath_node etalonBeforeResult (nodeCodeBefore);

    const std::string xPathQuery ("codes/code[@id=\"2\"]");

    // Act.
    const pugi::xpath_node testBeforeResult = xmlManagerBefore.Select (xPathQuery);
    xmlManagerAfter.RemoveCodeReference (
        "2",
        "Group synchronization of binary digital systems",
        "R.H. Barker",
        "http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems"
    );
    const pugi::xpath_node testAfterResult  = xmlManagerAfter.Select  (xPathQuery);

    // Assert.
    CompareNodes (etalonBeforeResult.node (), testBeforeResult.node () );
    CompareNodes (etalonAfterResult.node  (), testAfterResult.node  () );
}