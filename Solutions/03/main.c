#include <linux/types.h>
#include <sys/stat.h>
#include <x86intrin.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <pthread.h>



struct Parameter
{
    __u8  length;
    __u64 beginCode;
    __u64 endCode;
};



pthread_mutex_t mutexFileData = PTHREAD_MUTEX_INITIALIZER;



void XmlManagerSaveCode (const char *, const __u8, const __u64);

char * xmlFileName = "LowPslCodes.xml";

void SaveCode (const __u8 length, const __u64 code) __attribute__ ((noinline));
void SaveCode (const __u8 length, const __u64 code)
{
    pthread_mutex_lock (&mutexFileData);
    XmlManagerSaveCode (xmlFileName, length, code);
    pthread_mutex_unlock (&mutexFileData);
}



static void * Validate (void * parameter)
{
    const __u8 sideLobeLimit =                 3;
    const __u8 optimizeLimit = sideLobeLimit + 3;

    const __u64 mask = (1ULL << ( ( (struct Parameter *) parameter)->length - 1) ) - 1ULL;


    __asm__ __volatile__ (
        "INIT:                                      \n\t"   //  Prepare for computation.
        "       xorq       %%rax,      %%rax        \n\t"   //      Clear all using registers.
        "       xorq       %%rcx,      %%rcx        \n\t"   //      .
        "       xorq       %%rdi,      %%rdi        \n\t"   //      .
        "       xorq       %%rsi,      %%rsi        \n\t"   //      .
        "       xorq       %%r8,       %%r8         \n\t"   //      .
        "       xorq       %%r9,       %%r9         \n\t"   //      .
        "       xorq       %%r10,      %%r10        \n\t"   //      .
        "       xorq       %%r11,      %%r11        \n\t"   //      .
        "       xorq       %%r12,      %%r12        \n\t"   //      .
        "       xorq       %%r13,      %%r13        \n\t"   //      .
        "       xorq       %%r14,      %%r14        \n\t"   //      .
        "       movb %[length],        %%r8b        \n\t"   //      Load length of sequences into CPU register.
        "       movq %[beginCode],     %%r9         \n\t"   //      Load first sequence of the range into CPU register.
        "       movq %[endCode],       %%r10        \n\t"   //      Load last sequence of the range into CPU register.
        "       movb %[sideLobeLimit], %%r11b       \n\t"   //      Load maximum allowed level of sidelobes into CPU register.
        "       addb       $1,         %%r11b       \n\t"   //          To optimization issue used 'level + 1' instead of 'level'.
        "       movb %[optimizeLimit], %%r14b       \n\t"   //      Load level of sidelobes which indicates the possibility of skipping sequences.
        "       movq %[mask],          %%r12        \n\t"   //      Load mask for extracting significant bits into CPU register.
        "CHECK_CODE:                                \n\t"   //  Body of loop through sequence (like the "do-while" loop).
        "       movb       $1,         %%cl         \n\t"   //      Set the offset value.
        "       movq       %%r12,      %%r13        \n\t"   //      Set mask into mutable variable.
        "NEXT_SHIFT:                                \n\t"   //      Beginning of loop through shift of sequence (like the "do-while" loop).
        "       movq       %%r9,       %%rdi        \n\t"   //          Shifting sequence.
        "       shrq       %%cl,       %%rdi        \n\t"   //          Shift.
        "       xorq       %%r9,       %%rdi        \n\t"   //          Counting level of sidelobes.
        "       andq       %%r13,      %%rdi        \n\t"   //              Remove extra bits.
        #ifdef __POPCNT__
        "       popcntq    %%rdi,      %%rax        \n\t"   //              al =         n         (number of the different bits).
        #else
        "       pushq      %%rcx                    \n\t"   //              .
        "       callq      __popcountdi2            \n\t"   //              .
        "       popq       %%rcx                    \n\t"   //              .
        #endif
        "       shlb       $1,         %%al         \n\t"   //              al =     2 * n.
        "       subb       %%r8b,      %%al         \n\t"   //              al =     2 * n - l     (l - length of the sequence).
        "       addb       %%cl,       %%al         \n\t"   //              al = o + 2 * n - l     (o - current offset).
        "       jge        ABS                      \n\t"   //              al =|o + 2 * n - l|    (now al contain the sidelobe level).
        "       negb       %%al                     \n\t"   //              .
        "       ABS:                                \n\t"   //              .
        "       cmpb       %%r14b,     %%al         \n\t"   //          Check sidelobe so big that some sequences can be skipped.
        "       jge        OPTIMIZE_SKIP            \n\t"   //              If it is, then go to the optimization procedure.
        "       cmpb       %%r11b,     %%al         \n\t"   //          Check if the sidelobe level acceptable?
        "       jge        NEXT_CODE                \n\t"   //              If it is not, then go to the next sequence.
        "       addb       $1,         %%cl         \n\t"   //          Increment the offset for creating next shifted sequence.
        "       cmpb       %%cl,       %%r8b        \n\t"   //          Check if is it the lass offset.
        "       jbe        SAVE_CODE                \n\t"   //              If it is, then save cureent sequence.
        "       shrq       $1,         %%r13        \n\t"   //          Shift mask for next shifted sequence.
        "       jmp        NEXT_SHIFT               \n\t"   //      End of loop through shift of sequence.
        "OPTIMIZE_SKIP:                             \n\t"   //      Beginning of procedure to skipping wrong sequences.
        "       subb       %%r11b,      %%al        \n\t"   //              al = |o + 2 * n - l| - (s + 1)  (s - sidelobe limit).
        "       shr        $1,          %%al        \n\t"   //              al =(|o + 2 * n - l| - (s + 1) ) / 2.
        "       movb       %%al,        %%cl        \n\t"   //              al now contain number of bits which can be skipped.
        "       shrq       %%cl,        %%r9        \n\t"   //              .
        "       incq       %%r9                     \n\t"   //              Set next sequence.
        "       shlq       %%cl,        %%r9        \n\t"   //              .
        "       jmp        CHECK_CODE               \n\t"   //      End of procedure of skipping wrong sequnces.
        "NEXT_CODE:                                 \n\t"   //  Control of loop through sequence.
        "       addq       $1,          %%r9        \n\t"   //      Set next sequence.
        "       cmpq       %%r10,       %%r9        \n\t"   //      Check if the sequence inside the range.
        "       jbe        CHECK_CODE               \n\t"   //          If it is, then go to the begining of the loops body.
        "       jmp        QUIT                     \n\t"   //          If it is not, then go to the end of procedure.
        "SAVE_CODE:                                 \n\t"   //  Saving sequence with accepted level of sidelobes.
        "       pushq      %%r8                     \n\t"   //      Store registers.
        "       pushq      %%r9                     \n\t"   //      .
        "       pushq      %%r10                    \n\t"   //      .
        "       pushq      %%r11                    \n\t"   //      .
        "       pushq      %%r12                    \n\t"   //      .
        "       pushq      %%r14                    \n\t"   //      .
        "       movl       %%r8d,      %%edi        \n\t"   //      .
        "       movq       %%r9,       %%rsi        \n\t"   //      .
        "       call       SaveCode                 \n\t"   //      Calling external function for saving the sequence.
        "       popq       %%r14                    \n\t"   //      Restore registers.
        "       popq       %%r12                    \n\t"   //      .
        "       popq       %%r11                    \n\t"   //      .
        "       popq       %%r10                    \n\t"   //      .
        "       popq       %%r9                     \n\t"   //      .
        "       popq       %%r8                     \n\t"   //      .
        "       jmp        NEXT_CODE                \n\t"   //      Continue test sequences.
        "QUIT:                                      \n\t"   //  Exit of procedure.
        "       nop                                 \n\t"   //  .
        :
        : [length       ] "m" ( (__u8)  ( (struct Parameter *) parameter)->length),
          [beginCode    ] "m" ( (__u64) ( (struct Parameter *) parameter)->beginCode),
          [endCode      ] "m" ( (__u64) ( (struct Parameter *) parameter)->endCode),
          [sideLobeLimit] "m" (sideLobeLimit),
          [optimizeLimit] "m" (optimizeLimit),
          [mask         ] "m" (mask)
        : "%rax", "%rcx", "%rdi", "%rsi",
          "%r8",  "%r9",  "%r10", "%r11", "%r12", "%r13", "%r14"
    );


    return (void *) NULL;
};



int main (int argc, char * argv [])
{
    if (1 < argc) {
        xmlFileName = argv [1];
    }

    // Range of lengthes of codes which analyzed.
    const __u8 beginLength    = 51;
    const __u8 endLength      = 51;
    // Threads in which validators will be execute.
    pthread_t        threads    [THREADS];
    // Parameters which will be passed to validators.
    struct Parameter parameters [THREADS];
    // Divisor which used for finding range of data which analyze by one validator.
    __u8 x = 0;
    while (THREADS >> x) {
        ++x;
    }
    --x;


    for (__u8 i = beginLength; i <= endLength; ++i) {
        __u32 dummy  = 0;
        __u64 rdtscp = __rdtscp (&dummy);
        // Calculating and setting of range, inital and final codes.
        __u8  chunkLength = i - x - 1;
        __u64 beginCode =  0x00ULL;
        __u64 endCode   = (0x01ULL << chunkLength) - 1;
        __u64 chunkCode = (0x01ULL << chunkLength);
        // Creation of validators.
        for (__u8 j = 0; j < THREADS; ++j) {
            parameters [j].length = i;
            parameters [j].beginCode = beginCode;
            parameters [j].endCode   = endCode;
            pthread_create (&threads [j], NULL, Validate, &parameters [j]);
            pthread_setschedprio (threads [j], sched_get_priority_max (sched_getscheduler (threads [j]) ) );

            // Preparation of initial and final codes for next validator.
            beginCode = endCode;
            endCode  += chunkCode;
        }
        // Waiting for completion of validators tasks.
        for (__u8 j = 0; j < THREADS; ++j) {
            pthread_join (threads [j], NULL);
        }


        // Statistics output.
        rdtscp = __rdtscp (&dummy) - rdtscp;
        int fileStat = open ("/tmp/lpslcd.stat", O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if (write (fileStat, &rdtscp,  sizeof (rdtscp) ) != sizeof (rdtscp) ) {
            return 1;
        }
        close (fileStat);
    }


    return EXIT_SUCCESS;
}
