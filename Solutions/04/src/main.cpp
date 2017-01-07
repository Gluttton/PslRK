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
    Logger logger {currentDirectoryName};

    constexpr int_t L   {28};
    constexpr int_t SLL {2};
    Generator <L>       generator   {};
    Validator <L, SLL>  validator   {generator};


    while (!validator.SetNextCode () ) {
        if (validator.Validate () ) {
            logger.LogCode (L, generator.code.to_string () );
        }
    }


    return EXIT_SUCCESS;
}
