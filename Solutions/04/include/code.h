#ifndef LPSLCD_CODE_H
#define LPSLCD_CODE_H

#include <linux/types.h>
#include <x86intrin.h>
#include <initializer_list>



struct Code
{
    public:
        static constexpr __u8 u8ChunkCount      {32};
        static constexpr __u8 u16ChunkCount     {16};
        static constexpr __u8 u32ChunkCount     { 8};
        static constexpr __u8 u64ChunkCount     { 4};
        static constexpr __u8 m128ChunkCount    { 2};
        static constexpr __u8 m256ChunkCount    { 1};

        Code                ();
        Code                (const std::initializer_list <__u8>);
        ~Code               () = default;

        union
        {
            __u8     u8    [u8ChunkCount];
            __u16    u16   [u16ChunkCount];
            __u32    u32   [u32ChunkCount];
            __u64    u64   [u64ChunkCount];
            __m128i  m128i [m128ChunkCount];
            __m128i  m256i [m256ChunkCount];
        }   __attribute__ ((aligned (32)));
};

#endif//LPSLCD_CODE_H
