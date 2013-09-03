#include "logger.h"



Logger::Logger (std::string directoryName) : currentDirectoryName (directoryName),
                                             logFileName  (currentDirectoryName + "/lpslcd.log"),
                                             datFileName  (currentDirectoryName + "/lpslcd.dat"),
                                             statFileName (currentDirectoryName + "/lpslcd.stat")
{
}



Logger::Logger ()
{
}



Logger::~Logger ()
{
}



void Logger::LogStatistic (std::string & message)
{
    statFile.open (statFileName, std::fstream::out | std::fstream::app);
    statFile << message;
    statFile.close ();
}



void Logger::LogMessage (std::string & message)
{
    logFile.open (logFileName, std::fstream::out | std::fstream::app);
    logFile << message;
    logFile.close ();
}



void Logger::LogCode (__u8 length, CodeContainer & code)
{
    std::string codeString;

    codeString  = std::to_string (length);
    codeString += ":\t";
    for (__u8 i = 0; i < length; ++i) {
        if ( (code.u64 [i / 64] >> (i % 64) ) & 0x01) {
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
