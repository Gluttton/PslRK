#include <bitset>
#include <iostream>

int main ()
{
    static constexpr int L   {28}; // Length.
    static constexpr int SLL {2};  // Sidelobe limit.

    std::bitset <L> s {};
    for (int i = 0; i < L - 1; ++i)
        if (s.flip (i).test (i) ) {
            for (i = 1; i < L - SLL; ++i)
                if (abs ( ( (s >> i ^ s) << i).count () * 2 - L + i) > SLL)
                    goto NEXT;
            std::cout << s.to_string ('-', '+') << std::endl;
            NEXT:
                i = -1;
        }

    return EXIT_SUCCESS;
}
