#include "logger.h"



Logger::Logger (const std::string & directoryName)
            : currentDirectoryName {directoryName}
            , logFileName  {currentDirectoryName + "/lpslcd.log"}
            , datFileName  {currentDirectoryName + "/lpslcd.dat"}
{
}



void Logger::LogMessage (const std::string & message)
{
    logFile.open (logFileName, std::fstream::out | std::fstream::app);
    logFile << message;
    logFile.close ();
}



void Logger::LogCode (const int_t length, const std::string & code)
{
    std::string codeString;

    codeString  = std::to_string (length);
    codeString += ":\t";
    for (int i = 0; i < length; ++i) {
        codeString += code [i] == '0' ? "+" : "-";
    }
    codeString += "\n";

    datFile.open (datFileName, std::fstream::out | std::fstream::app);
    datFile << codeString;
    datFile.close ();
}
