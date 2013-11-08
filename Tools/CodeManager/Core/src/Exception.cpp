#include "Exception.h"



namespace Pslrk
{
namespace Core
{

const char * Exception::what () const noexcept (true)
{
    return "PslRK base exception.";
}



const char * ExceptionInvalidView::what () const noexcept (true)
{
    return "Invalid view of code.";
}



const char * ExceptionInvalidStringView::what () const noexcept (true)
{
    return "Invalid string (based on '+' and '-') view of code.";
}



const char * ExceptionInvalidHexView::what () const noexcept (true)
{
    return "Invalid hex view of code.";
}



const char * ExceptionXmlError::what () const noexcept (true)
{
    return "Unsuccessful operation with XML document.";
}



const char * ExceptionXmlErrorLoadFile::what () const noexcept (true)
{
    return "Unsuccessful attempt to load XML document from file.";
}



const char * ExceptionXmlErrorSaveFile::what () const noexcept (true)
{
    return "Unsuccessful attempt to save XML document to file.";
}

}// namespace Core
}// namespace Pslrk