#ifndef LPSLCD_GENERATOR_H
#define LPSLCD_GENERATOR_H

#include <array>
#include <vector>
#include <linux/types.h>



using Code = std::array <__u8, 32>;



class Generator
{
    public:
        Generator                       (const __s32);
        virtual ~Generator              () = default;

        virtual bool GetNextCode        (Code &, __s32 &);

        static Code CalculateMaxCode    (const __s32);

        std::vector <std::pair <std::vector <__s8>, __u8> >
                                        sums;

        Code code                       {};
        Code maxCode                    {};
        __s32 length                    {0};
        __s32 modifiedBits              {0};
};

#endif//LPSLCD_GENERATOR_H
