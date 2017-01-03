#ifndef LPSLCD_LOGGER_MOCK_H
#define LPSLCD_LOGGER_MOCK_H

#include "logger.h"
#include <gmock/gmock.h>



class LoggerMock : public Logger
{
    public:
        LoggerMock (const std::string & currentDirectory)
                    : Logger {currentDirectory}
        {
        };

        virtual ~LoggerMock () = default;

        MOCK_METHOD1 (LogMessage,   void (const std::string &) );
        MOCK_METHOD2 (LogCode,      void (const __u8, const Code &) );
        MOCK_METHOD4 (LogStatistic, void (const __s32, const __u64, const __u64, const __u64) );
};

#endif//LPSLCD_LOGGER_MOCK_H
