#include <stdio.h>
#include <linux/types.h>
#include <unistd.h>
#include <fcntl.h>



#define SIZE 16



struct Record
{
    __s32 length;
    __u8  code [SIZE];
}   __attribute__ ((packed));



int main (int argc, char * argv [])
{
    struct Record record;
    __u32 i = 0;
    int fileStat = open (argv [1], O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    while (read (fileStat, &record,  sizeof (record) ) > 0) {
        printf ("%i:\t", record.length);
        for (i = 0; i < record.length; ++i) {
            (record.code [i / 8] >> (i & 7) ) & 0x01 ? printf ("+") : printf ("-");
        }
        printf ("\n");
    } 
    close (fileStat);
}
