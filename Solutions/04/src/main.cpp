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
    Logger    logger      {currentDirectoryName};

    Generator generator   {13};
    Validator validator   {generator};


    while (!validator.SetNextCode () ) {
        if (validator.Validate () ) {
            logger.LogCode (generator.length, generator.code);
        }
    }


    return EXIT_SUCCESS;
}
