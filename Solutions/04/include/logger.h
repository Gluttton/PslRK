#ifndef LPSLCD_LOGGER_H
#define LPSLCD_LOGGER_H

#include "container.h"
#include <linux/types.h>
#include <fstream>
#include <string>



class Logger
{
    public:
        explicit Logger (const std::string &);
        virtual ~Logger () = default;

        void LogMessage   (const std::string &);
        void LogCode      (const __u8, const CodeContainer &);
        void LogStatistic (const std::string &);
    private:
        const std::string currentDirectoryName;
        const std::string logFileName;
        const std::string datFileName;
        const std::string statFileName;

        std::fstream logFile;
        std::fstream datFile;
        std::fstream statFile;
};

#endif//LPSLCD_LOGGER_H
