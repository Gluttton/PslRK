#ifndef LPSLCD_VALIDATOR_H
#define LPSLCD_VALIDATOR_H

#include <linux/types.h>



class Generator;



class Validator
{
    public:
        explicit Validator              (Generator &);
        virtual ~Validator              () = default;

        bool SetNextCode                ();
        bool Validate                   ();

        Generator & generator;
        __s32 sideLobeLimit             {2};
};

#endif//LPSLCD_VALIDATOR_H
