#ifndef PSLRK_TOOLS_CODE_MANAGER_CORE_EXCEPTION_H
#define PSLRK_TOOLS_CODE_MANAGER_CORE_EXCEPTION_H

#include <exception>



namespace Pslrk
{
namespace Core
{

class Exception : public std::exception
{
    public:
        Exception          () = default;
        virtual ~Exception () = default;

        virtual const char * what () const noexcept (true) override;
};



class ExceptionInvalidView : public Exception
{
    public:
        ExceptionInvalidView          () = default;
        virtual ~ExceptionInvalidView () = default;

        virtual const char * what () const noexcept (true) override;
};



class ExceptionInvalidStringView : public ExceptionInvalidView
{
    public:
        ExceptionInvalidStringView          () = default;
        virtual ~ExceptionInvalidStringView () = default;

        virtual const char * what () const noexcept (true) override;
};



class ExceptionInvalidHexView : public ExceptionInvalidView
{
    public:
        ExceptionInvalidHexView          () = default;
        virtual ~ExceptionInvalidHexView () = default;

        virtual const char * what () const noexcept (true) override;
};



class ExceptionXmlError : public Exception
{
    public:
        ExceptionXmlError          () = default;
        virtual ~ExceptionXmlError () = default;

        virtual const char * what () const noexcept (true) override;
};



class ExceptionXmlErrorLoadFile : public ExceptionXmlError
{
    public:
        ExceptionXmlErrorLoadFile          () = default;
        virtual ~ExceptionXmlErrorLoadFile () = default;

        virtual const char * what () const noexcept (true) override;
};



class ExceptionXmlErrorSaveFile : public ExceptionXmlError
{
    public:
        ExceptionXmlErrorSaveFile          () = default;
        virtual ~ExceptionXmlErrorSaveFile () = default;

        virtual const char * what () const noexcept (true) override;
};

}// namespace Core
}// namespace Pslrk

#endif//PSLRK_TOOLS_CODE_MANAGER_CORE_EXCEPTION_H