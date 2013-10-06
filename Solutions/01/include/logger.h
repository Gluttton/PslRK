#ifndef LPSLCD_LOGGER_H
#define LPSLCD_LOGGER_H

#include "container.h"
#include <linux/types.h>
#include <fstream>
#include <string>



class Logger
{
    public:
        Logger  (std::string directoryName);
        ~Logger ();

        void LogMessage   (std::string & message);
        void LogCode      (__u8 length, CodeContainer & code);
        void LogStatistic (std::string & message);
    private:
        Logger  ();

        const std::string currentDirectoryName;
        const std::string logFileName;
        const std::string datFileName;
        const std::string statFileName;

        std::fstream logFile;
        std::fstream datFile;
        std::fstream statFile;
};

#endif//LPSLCD_LOGGER_H
