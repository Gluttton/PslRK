#ifndef BARK_CONTAINER_H
#define BARK_CONTAINER_H

#include <linux/types.h>
#include <x86intrin.h>



const __u8 codeU8Count   = 16;
const __u8 codeU16Count  =  8;
const __u8 codeU32Count  =  4;
const __u8 codeU64Count  =  2;
const __u8 codeM128Count =  1;
const __u8 codeM256Count =  0;



union CodeContainer
{
    __u8     u8    [codeU8Count];
    __u16    u16   [codeU16Count];
    __u32    u32   [codeU32Count];
    __u64    u64   [codeU64Count];
    __m128i  m128i [codeM128Count];
}   __attribute__ ((aligned (16)));

#endif//BARK_CONTAINER_H
