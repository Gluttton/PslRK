#ifndef LPSLCD_CONTAINER_H
#define LPSLCD_CONTAINER_H

#include <linux/types.h>
#include <x86intrin.h>



const __u8 codeU8Count   = 16;
const __u8 codeU16Count  =  8;
const __u8 codeU32Count  =  4;
const __u8 codeU64Count  =  2;
const __u8 codeM128Count =  1;
const __u8 codeM256Count =  0;



typedef __u8    u8_128      __attribute__ ((vector_size (16)));
typedef __u16   u16_128     __attribute__ ((vector_size (16)));
typedef __u32   u32_128     __attribute__ ((vector_size (16)));
typedef __u64   u64_128     __attribute__ ((vector_size (16)));



union CodeContainer
{
    u8_128   u8v;
    u16_128  u16v;
    u32_128  u32v;
    u64_128  u64v;
    __u8     u8    [codeU8Count];
    __u16    u16   [codeU16Count];
    __u32    u32   [codeU32Count];
    __u64    u64   [codeU64Count];
    __m128i  m128i [codeM128Count];
}   __attribute__ ((aligned (16)));

#endif//LPSLCD_CONTAINER_H
