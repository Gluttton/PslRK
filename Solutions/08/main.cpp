#include <bitset>
#include <random>
#include <thread>
#include <iostream>

int main ()
{
    static constexpr int        L    {52}; // Length.
    static constexpr int        SLL  {4};  // Sidelobe limit.
    static constexpr int        N    {8};  // Number of threads.
    static constexpr long int   from {1};
    static constexpr long int   to   {static_cast <long int> (1) << (L - 2)};

    bool stop {false};
    const auto task = [& stop](){
        std::random_device device;
        std::mt19937 generator (device () );
        std::uniform_int_distribution <long int> distribution (from, to);

        std::bitset <L> s {};
        while (!stop) {
            s ^= distribution (generator);
            for (int i = 1; i < L - SLL; ++i)
                if (abs (static_cast <int> ( ( (s >> i ^ s) << i).count () ) * 2 - L + i) > SLL)
                    goto NEXT;
            std::cout << s.to_string ('-', '+') << std::endl;
            stop = true;
            NEXT:;
        }
    };

    std::vector <std::thread> pull;
    for (int i = 0; i < N; ++i) {
        pull.push_back (std::thread (task) );
    }
    for (int i = 0; i < N; ++i) {
        pull [i].join ();
    }

    return EXIT_SUCCESS;
}
