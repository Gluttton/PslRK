#ifndef LPSLCD_ENVIRONMENT_H
#define LPSLCD_ENVIRONMENT_H

#include <array>
#include <vector>
#include <linux/types.h>



using Code = std::array <__u8, 32>;



struct Environment
{
    public:
        Environment                     (const __s32);
        virtual ~Environment            () = default;

        std::vector <std::vector <__s8> >
                                        sums;

        Code code                       {};
        Code maxCode                    {};
        __s32 length                    {0};
        __s32 modifiedBits              {0};
};

#endif//LPSLCD_ENVIRONMENT_H
