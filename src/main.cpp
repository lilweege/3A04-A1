#include <cstdint>
#include <iostream>

#include "NumberPublisher.hpp"
#include "EvenNumberSubscriber.hpp"
#include "PrimeNumberSubscriber.hpp"

int main()
{
    // The templated type specified the kind of integer (signed 64 bit).
    using T = int64_t;

    // A publisher that is interested in some qualities of numbers.
    // The qualities that this publisher cares about are defined below.
    NumberPublisher<T> pub;

    {
        // Create an even number subscriber that attaches (subscribes) to the
        // publisher. The constructor of even calls `pub->Attach(this)`, then
        // stores a pointer to pub.
        std::cout << "Attaching EvenNumberSubscriber...\n";
        EvenNumberSubscriber<T> even{&pub};
        // Similarly, create a prime number subscriber that attaches (subscribes)
        // to the publisher.
        std::cout << "Attaching PrimeNumberSubscriber...\n";
        PrimeNumberSubscriber<T> prime{&pub};

        // Pulish numbers to both subscribers, and get the results.
        pub.SetNumber(1);
        std::cout << pub.GetNumber()
            << ": " << (even.GetResult() ? "Even" : "Odd")
            << ", " << (prime.GetResult() ? "Prime" : "Composite") << '\n';
        pub.SetNumber(2);
        std::cout << pub.GetNumber()
            << ": " << (even.GetResult() ? "Even" : "Odd")
            << ", " << (prime.GetResult() ? "Prime" : "Composite") << '\n';

        // Unsubscribe *only* the EvenNumberSubscriber. After this point, the
        // subscriber won't receive notifications, and won't update the result.
        std::cout << "Detaching EvenNumberSubscriber...\n";
        pub.Detach(dynamic_cast<Observer*>(&even));

        // Publish some more numbers and get the result(s). If there were more
        // subscribers then the results would be computed in a similar way.
        for (int x = 2; x <= 10; ++x) {
            pub.SetNumber(x);
            std::cout << x << ": " << (prime.GetResult() ? "Prime\n" : "Composite\n");
        }

        // When the subscribers go out of scope, their destructors are called and
        // they are automatically unsubscribed.
    }

    // You can continue to use the same publisher after adding new subscribers.
}
