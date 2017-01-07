#ifndef LPSLCD_LOGGER_H
#define LPSLCD_LOGGER_H

#include <fstream>
#include <string>
#include "generator.h"



class Logger
{
    public:
        explicit Logger (const std::string &);
        virtual ~Logger () = default;

        virtual void LogMessage   (const std::string &);
        virtual void LogCode      (const int_t, const std::string &);
    private:
        const std::string currentDirectoryName;
        const std::string logFileName;
        const std::string datFileName;

        std::fstream logFile;
        std::fstream datFile;
};

#endif//LPSLCD_LOGGER_H
