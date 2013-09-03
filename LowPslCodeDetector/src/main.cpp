#include "generator.h"
#include "validator.h"
#include "logger.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <unistd.h>
#include <linux/types.h>
#include <linux/limits.h>



int main ()
{
    char currentDirectoryName [PATH_MAX];
    if (currentDirectoryName != getcwd (currentDirectoryName, PATH_MAX) ) {
        std::cout << "Abnormal exit (unable to detect current directory)!" << std::endl;
        return EXIT_FAILURE;
    }
    Logger    * logger    = new Logger    (currentDirectoryName);

    Generator * generator = new Generator (logger, 3, 32);
    Validator * validator = new Validator (generator);


    while (!validator->SetNextCode () ) {
        if (!validator->Validate () ) {
            logger->LogCode (validator->length, validator->code);
        }
    }


    return 0;
}
