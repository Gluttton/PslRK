#ifndef LPSLCD_VALIDATOR_H
#define LPSLCD_VALIDATOR_H

#include "generator.h"



class Validator
{
    public:
        explicit Validator              (Generator * const);
        virtual ~Validator              () = default;

        int SetNextCode                 ();
        int Validate                    ();

        Generator * const generator     {nullptr};
        Code code                       {};
        __s32 length                    {0};
        __s32 sideLobeLimit             {0};
};

#endif//LPSLCD_VALIDATOR_H
