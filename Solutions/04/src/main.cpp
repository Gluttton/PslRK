#include "generator.h"
#include "validator.h"
#include "logger.h"
#include <iostream>
#include <unistd.h>
#include <linux/limits.h>



int main ()
{
    char currentDirectoryName [PATH_MAX];
    if (currentDirectoryName != getcwd (currentDirectoryName, PATH_MAX) ) {
        std::cout << "Abnormal exit (unable to detect current directory)!" << std::endl;
        return EXIT_FAILURE;
    }
    Logger    * logger    {new Logger    (currentDirectoryName)};

    constexpr __s32 begin {3};
    constexpr __s32 end   {13};
    Generator * generator {new Generator (logger, begin, end)};
    Validator * validator {new Validator (generator)};


    while (!validator->SetNextCode () ) {
        if (!validator->Validate () ) {
            logger->LogCode (validator->length, validator->code);
        }
    }


    return EXIT_SUCCESS;
}
