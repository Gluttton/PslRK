Set of solutions of the problem of finding binary sequences with low PSL level
==============================================================================
 - [01](01) - canonical solution implemented on C++:
    - optimization: none;
    - portability:  C++11;
    - build:        make;
    - contribution: none.
 - [02](02) - minimalistic solution implemented on pure C;
 - [03](03) - minimalistic solution implemented on C with inline assembly;
    - optimization:
        - multithreading;
        - skipped inverse-time sequences;
        - skipped sequences based on the already calculated sidelobe level of current sequence.
    - portability:  C++11;
    - build:        cmake;
    - contribution:
        - version 6b7fa8fa499df80824719e8a9b91ab7f062015b8 was used to proving sequences with length from 2 up to 13;
        - version 94bdafaabff628a155202d223ae583bd09f1604b was used to finding and proving sequences with length from 28 up to 47;
        - version 94bdafaabff628a155202d223ae583bd09f1604b with manually defined PSL limit 3 was used to finding and proving sequences with length 48. 
 - [04](04) - yet another solution implemented on C++.
