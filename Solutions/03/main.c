#include <linux/types.h>
#include <sys/stat.h>
#include <x86intrin.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>



struct Parameter
{
    __s32 length;
    __u64 beginCode;
    __u64 endCode;
};



pthread_mutex_t mutexFileData = PTHREAD_MUTEX_INITIALIZER;



void SaveCode (__s32 length, __u64 code) __attribute__ ((noinline));
void SaveCode (__s32 length, __u64 code)
{
    pthread_mutex_lock (&mutexFileData);
    int fileStat = open ("/tmp/lpslcd.dat", O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (write (fileStat, &length, sizeof (length) ) != sizeof (length) ) {
        return;
    }
    if (write (fileStat,  &code, sizeof (code) ) != sizeof (code) ) {
        return;
    }
    close (fileStat);
    pthread_mutex_unlock (&mutexFileData);
}



static void * Validate (void * parameter)
{
    const __s32 sideLobeLimit = ( (struct Parameter *) parameter)->length < 14 ? 1 :
                        floor ( ( (struct Parameter *) parameter)->length / 14.0f);

    const __u64 mask = (1ULL << ( ( (struct Parameter *) parameter)->length - 1) ) - 1ULL;


    __asm__ __volatile__ (
        "INIT:                                      \n\t"
        "       xorq       %%r8,       %%r8         \n\t"
        "       mov        %[length],  %%r8w        \n\t"
        "       movq       %[code],    %%r9         \n\t"
        "       movq       %[maxcode], %%r10        \n\t"
        "       xorq       %%r11,      %%r11        \n\t"
        "       mov        %[limit],   %%r11w       \n\t"
        "       movq       %[mask],    %%r12        \n\t"

        "NEXT_CODE:                                 \n\t"
        "       incq       %%r9                     \n\t"
        "       cmpq       %%r9,       %%r10        \n\t"
        "       jbe        QUIT                     \n\t"
        "       mov        $1,         %%cx         \n\t"
        "       movq       %%r12,      %%r13        \n\t"
        "NEXT_SHIFT:                                \n\t"
        "       movq       %%r9,       %%rdi        \n\t"
        "       shrq       %%cl,       %%rdi        \n\t"
        "       xorq       %%r9,       %%rdi        \n\t"
        "       andq       %%r13,      %%rdi        \n\t"
        #ifdef __POPCNT__
        "       popcntq    %%rdi,      %%rax        \n\t"
        #else
        "       pushq      %%rcx                    \n\t"
        "       callq      __popcountdi2            \n\t"
        "       popq       %%rcx                    \n\t"
        #endif
        "       shl        $1,         %%ax         \n\t"
        "       sub        %%r8w,      %%ax         \n\t"
        "       add        %%cx,       %%ax         \n\t"
        "       jge        ABS                      \n\t"
        "       neg        %%ax                     \n\t"
        "       ABS:                                \n\t"
        "       cmp        %%r11w,     %%ax         \n\t"
        "       jg         NEXT_CODE                \n\t"
        "       inc        %%cx                     \n\t"
        "       cmp        %%cx,       %%r8w        \n\t"
        "       jbe        SAVE_CODE                \n\t"
        "       shrq       $1,         %%r13        \n\t"
        "       jmp        NEXT_SHIFT               \n\t"

        "SAVE_CODE:                                 \n\t"
        "       pushq      %%r8                     \n\t"
        "       pushq      %%r9                     \n\t"
        "       pushq      %%r10                    \n\t"
        "       pushq      %%r11                    \n\t"
        "       pushq      %%r12                    \n\t"
        "       movl       %%r8d,      %%edi        \n\t"
        "       movq       %%r9,       %%rsi        \n\t"
        "       call       SaveCode                 \n\t"
        "       popq       %%r12                    \n\t"
        "       popq       %%r11                    \n\t"
        "       popq       %%r10                    \n\t"
        "       popq       %%r9                     \n\t"
        "       popq       %%r8                     \n\t"
        "       jmp        NEXT_CODE                \n\t"

        "QUIT:                                      \n\t"
        "       nop                                 \n\t"
        :
        : [length ] "m" ( (__s32) ( (struct Parameter *) parameter)->length),
          [code   ] "m" ( (__u64) ( (struct Parameter *) parameter)->beginCode),
          [maxcode] "m" ( (__u64) ( (struct Parameter *) parameter)->endCode),
          [limit  ] "m" (sideLobeLimit),
          [mask   ] "m" (mask)
        : "%rax", "%rcx", "%rdi", "%rsi",
          "%r8",  "%r9",  "%r10", "%r11", "%r12", "%r13"
    );


    return (void *) NULL;
};



int main ()
{
    // Range of lengthes of codes which analyzed.
    const __s32 beginLength   = 13;
    const __s32 endLength     = 28;
    // Threads in which validators will be execute.
    pthread_t        threads    [THREADS];
    // Parameters which will be passed to validators.
    struct Parameter parameters [THREADS];
    // Divisor which used for finding range of data which analyze by one validator.
    __s32 x = 0;
    while (THREADS >> x) {
        ++x;
    }
    --x;


    for (__s32 i = beginLength; i <= endLength; ++i) {
        __u64 rdtsc = __rdtsc ();
        // Calculating and setting of range, inital and final codes.
        __s32 chunkLength = i - x - 1;
        __u64 beginCode =  0x00ULL;
        __u64 endCode   = (0x01ULL << chunkLength) - 1;
        __u64 chunkCode = (0x01ULL << chunkLength);
        // Creation of validators.
        for (__s32 j = 0; j < THREADS; ++j) {
            parameters [j].length = i;
            parameters [j].beginCode = beginCode;
            parameters [j].endCode   = endCode;

            pthread_create (&threads [j], NULL, Validate, &parameters [j]);

            // Preparation of initial and final codes for next validator.
            beginCode = endCode;
            endCode  += chunkCode;
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
