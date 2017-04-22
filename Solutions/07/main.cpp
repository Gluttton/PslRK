#include <bitset>
#include <iostream>

int main ()
{
    static constexpr int L   {28};      // Length.
    static constexpr int SLL {2};       // Sidelobe limit.
    static constexpr int TL  {SLL + 3}; // Threshold value of SLL,
                                        // when optimization is still possible.

    std::bitset <L> s {};
    for (int l, i = 0; i < L - 1; ++i)
        if (s.flip (i).test (i) ) {
            for (i = 1; i < L - SLL; ++i)
                if ( (l = abs ( ( (s >> i ^ s) << i).count () * 2 - L + i) ) > SLL)
                    goto NEXT;
            std::cout << s.to_string ('-', '+') << std::endl;
            NEXT:
                i = -1;
                if (l > TL) {
                    l = (l - SLL - 1) / 2;
                    s = (s >> l) << l;
                    i += l;
                }
        }

    return EXIT_SUCCESS;
}
