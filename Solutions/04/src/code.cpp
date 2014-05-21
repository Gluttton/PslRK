#include "code.h"



Code::Code ()
            : Code { {} }
{
}



Code::Code (const std::initializer_list <__u8> list)
{
    size_t i {0};

    if (list.size () >= u8ChunkCount) {
        for (; i < u8ChunkCount; ++i) {
            u8 [i] = * (list.begin () + i);
        }
    }
    else {
        for (; i < list.size (); ++i) {
            u8 [i] = * (list.begin () + i);
        }
        for (; i < u8ChunkCount; ++i) {
            u8 [i] = 0x00u;
        }
    }
}
