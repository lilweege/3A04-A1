#include <cstdint>
#include <iostream>
#include <cassert>

#include "NumberPublisher.hpp"
#include "EvenNumberSubscriber.hpp"
#include "PrimeNumberSubscriber.hpp"

int main()
{
    NumberPublisher<int64_t> pub;
    EvenNumberSubscriber<int64_t> even{&pub};
    PrimeNumberSubscriber<int64_t> prime{&pub};

    auto CheckNumber = [&](auto x) {
        pub.SetNumber(x);
        std::cout << pub.GetNumber()
            << ": " << (even.GetResult() ? "Even" : "Odd")
            << ", " << (prime.GetResult() ? "Prime" : "Composite")
            << '\n';
    };

    for (int64_t x = 0; x <= 100; ++x) {
        CheckNumber(x);
    }
}

