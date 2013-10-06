#include <linux/types.h>
#include <sys/stat.h>
#include <x86intrin.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>



#define SIZE 16



static const __s32 TableBitCount [256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};



struct Parameter
{
    __s32 length;
    __u8  beginCode [SIZE] __attribute__ ((aligned (16)));
    __u8  endCode   [SIZE] __attribute__ ((aligned (16)));
};



pthread_mutex_t mutexFileStat = PTHREAD_MUTEX_INITIALIZER;



static void * Validate (void * parameter)
{
    const __s32 length        = ( (struct Parameter *) parameter)->length;
    const __s32 sideLobeLimit = length < 14 ? 1 : floor (length / 14.0f);

    __s32 isFound = 0;

    __u8 code    [SIZE] __attribute__ ((aligned (16)));
    __u8 maxCode [SIZE] __attribute__ ((aligned (16)));

    memcpy (   code, ( (struct Parameter *) parameter)->beginCode, SIZE * sizeof (* code) );
    memcpy (maxCode, ( (struct Parameter *) parameter)->endCode,   SIZE * sizeof (* maxCode) );


    __s32 difference = 1;
    while (difference) {
        __s32 i = 0;
        do {
            ++code [i];
        } while (!code [i++] && i < SIZE);

        i = -1;
        difference = 0;
        while (++i < SIZE && !difference) {
            difference = code [i] - maxCode [i];
        }

        isFound = 1;
        for (__s32 shift = 1; shift < length; ++shift) {
            // Utility variables.
            const __s32 x = (length - shift) >> 3;     // Shift means dividing by 8.
            const __s32 y =           shift  >> 3;     // Shift means dividing by 8.
            const __s32 z =           shift   & 7;     // Remainder of the division by 8.
            // Redundant raised bits which included in sum.
            const __s32 extra = TableBitCount [code [x] >> ( (length - shift) & 7)];

            __s32 sideLobeSum = 0;
            for (__s32 i = 0; i <= x; ++i) {
                sideLobeSum += TableBitCount [
                    (__u8) (
                                  (code [i     + y] >>      z
                                |  code [i + 1 + y] << (8 - z) )
                                ^  code [i]
                    )
                ];
            }

            if (abs (length - shift - (sideLobeSum - extra) * 2) > sideLobeLimit) {
                isFound = 0;
                break;
            }
        }

        if (isFound) {
            pthread_mutex_lock (&mutexFileStat);
            int fileStat = open ("/tmp/lpslcd.dat", O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
            if (write (fileStat, &length, sizeof (length) ) != sizeof (length) ) {
                return (void *) 1;
            }
            if (write (fileStat,  code, sizeof (code [0]) * SIZE) != sizeof (code [0]) * SIZE) {
                return (void *) 1;
            }
            close (fileStat);
            pthread_mutex_unlock (&mutexFileStat);
        }
    }


    return (void *) NULL;
};



int main ()
{
    // Range of lengthes of codes which analyzed.
    const __s32 beginLength   =  8;
    const __s32 endLength     = 28;
    // Threads in which validators will be execute.
    pthread_t        threads    [THREADS];
    // Parameters which will be passed to validators.
    struct Parameter parameters [THREADS];
    // Divisor which used to finding range of data which analyze by one validator.
    __s32 x = 0;
    while (THREADS >> x) {
        ++x;
    }
    --x;


    for (__s32 i = beginLength; i <= endLength; ++i) {
        __u64 rdtsc = __rdtsc ();
        // Calculating and setting of range, initial and final codes.
        __s32 chunkLength = i - x - 1;
        __u8 beginCode [SIZE];
        __u8 endCode   [SIZE];
        __u8 chunkCode [SIZE];
        memset (beginCode, 0x00, sizeof (beginCode [0]) * SIZE);
        memset (endCode,   0x00, sizeof (endCode   [0]) * SIZE);
        memset (chunkCode, 0x00, sizeof (chunkCode [0]) * SIZE);
        memset (&endCode   [0],                0xFF,     chunkLength / 8);
        memset (&endCode   [chunkLength / 8], (0x01U << (chunkLength & 7) ) - 1, 1);
        memset (&chunkCode [chunkLength / 8],  0x01U << (chunkLength & 7),       1);
        // Creation of validators.
        for (__s32 j = 0; j < THREADS; ++j) {
            parameters [j].length = i;
            memcpy (&parameters [j].beginCode, beginCode, sizeof (parameters [j].beginCode [0]) * SIZE);
            memcpy (&parameters [j].endCode,   endCode,   sizeof (parameters [j].endCode   [0]) * SIZE);

            pthread_create (&threads [j], NULL, Validate, &parameters [j]);

            // Preparation of initial and final codes for next validator.
            memcpy (beginCode, endCode, sizeof (beginCode [0]) * SIZE);

            __u16 carry = 0x00;
            for (__s32 k = 0; k <= i / 8; ++k) {
                carry = endCode [k] + chunkCode [k] + (carry >> 8);
                endCode [k] = carry;
            }
        }
        // Waiting for completion of validators tasks.
        for (__s32 j = 0; j < THREADS; ++j) {
            pthread_join (threads [j], NULL);
        }


        // Statistics output.
        rdtsc = __rdtsc () - rdtsc;
        int fileStat = open ("/tmp/lpslcd.stat", O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if (write (fileStat, &rdtsc,  sizeof (rdtsc) ) != sizeof (rdtsc) ) {
            return 1;
        }
        close (fileStat);
    }


    return 0;
}
