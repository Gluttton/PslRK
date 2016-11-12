#include <stdio.h>
#include <linux/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>



int main (int argc, char * argv [])
{
    __u64 rdtsc = 0;
    __u64 i     = 0;
    int fileStat = open (argv [1], O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    while (read (fileStat, &rdtsc,  sizeof (rdtsc) ) > 0) {
        printf ("%llu:\t%llu\n", ++i, rdtsc);
    }
    close (fileStat);

    return EXIT_SUCCESS;
}
