#ifndef LPSLCD_LOGGER_H
#define LPSLCD_LOGGER_H

#include <linux/types.h>
#include <fstream>
#include <string>
#include "generator.h"



class Logger
{
    public:
        explicit Logger (const std::string &);
        virtual ~Logger () = default;

        virtual void LogMessage   (const std::string &);
        virtual void LogCode      (const __u8, const std::string &);
        virtual void LogStatistic (const __s32, const __u64, const __u64, const __u64);
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
