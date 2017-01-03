#include "logger.h"



Logger::Logger (const std::string & directoryName)
            : currentDirectoryName {directoryName}
            , logFileName  {currentDirectoryName + "/lpslcd.log"}
            , datFileName  {currentDirectoryName + "/lpslcd.dat"}
            , statFileName {currentDirectoryName + "/lpslcd.stat"}
{
}



void Logger::LogStatistic (const __s32 length, const __u64 rdtsc, const __u64 codes, const __u64 codesAll)
{
    std::string message;
    message  = std::to_string (length);
    message += "\trdtsc " + std::to_string (rdtsc);
    message += "\tcodes " + std::to_string (codes) + " / " + std::to_string (codesAll);
    message += "\n";

    statFile.open (statFileName, std::fstream::out | std::fstream::app);
    statFile << message;
    statFile.close ();
}



void Logger::LogMessage (const std::string & message)
{
    logFile.open (logFileName, std::fstream::out | std::fstream::app);
    logFile << message;
    logFile.close ();
}



void Logger::LogCode (const __u8 length, const Code & code)
{
    std::string codeString;

    codeString  = std::to_string (length);
    codeString += ":\t";
    for (__u8 i = 0; i < length; ++i) {
        if ( (code [i / 8] >> (i % 8) ) & 0x01) {
            codeString += "+";
        }
        else {
            codeString += "-";
        }
    }
    codeString += "\n";

    datFile.open (datFileName, std::fstream::out | std::fstream::app);
    datFile << codeString;
    datFile.close ();
}
