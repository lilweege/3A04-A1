#include <cstdint>
#include <iostream>
#include <cassert>
#include "Subject.hpp"
#include "Observer.hpp"

// class ClockTimer : public Subject
// {
//     int x;
// public:
//     ClockTimer();
//     int GetState() const;
//     void Tick();
// };
//
// ClockTimer::ClockTimer()
// {
//     x = 0;
// }
//
// void ClockTimer::Tick()
// {
//     ++x;
//     Notify();
// }
//
// int ClockTimer::GetState() const
// {
//     return x;
// }
//
// class DigitalClock : public Observer
// {
//     ClockTimer* mSubject;
//     int mId;
// public:
//     DigitalClock(ClockTimer*, int);
//     virtual ~DigitalClock() override;
//     virtual void Update(Subject*) override;
//     void Display();
// };
//
// DigitalClock::DigitalClock(ClockTimer* subject, int id)
//     : mSubject(subject), mId(id)
// {
//     mSubject->Attach(this);
// }
//
// DigitalClock::~DigitalClock()
// {
//     mSubject->Detach(this);
// }
//
// void DigitalClock::Update(Subject* subject)
// {
//     if (subject == mSubject)
//         Display();
// }
//
// void DigitalClock::Display()
// {
//     int x = mSubject->GetState();
//     std::cout << mId << " got " << x << '\n';
// }
//
// int main()
// {
//     ClockTimer ct{};
//     DigitalClock dc1{&ct, 1};
//     ct.Tick();
//     DigitalClock dc2{&ct, 2};
//     ct.Tick();
//
//     std::cout << "hello\n";
// }

template<std::integral InputType>
class NumberPublisher : public Subject
{
    InputType mNumber = 0;
public:
    [[nodiscard]] InputType GetNumber() const;
    void SetNumber(InputType);
};

template<typename InputType>
InputType NumberPublisher<InputType>::GetNumber() const
{
    return mNumber;
}


template<typename InputType>
void NumberPublisher<InputType>::SetNumber(InputType number)
{
    // NOTE: Do NOT call this function from an observer.
    // Doing so would result in infinite mutual recursion (this is bad).
    mNumber = number;
    Notify();
}


// template <typename InputType>
// concept PubSubCompatible = requires(InputType x)
// {
//     NumberPublisher<InputType>{}.GetNumber();
// };

template <typename InputType, typename OutputType>
class NumberSubscriber : public Observer
{
    NumberPublisher<InputType>* mSubject;
protected:
    OutputType mResult;
public:
    NumberSubscriber(NumberPublisher<InputType>*);
    virtual ~NumberSubscriber() override;
    virtual void Update(Subject*) override;
private:
    virtual void RecomputeResult(InputType) = 0;

public:
    [[nodiscard]] OutputType GetResult() const;
};

template <typename InputType, typename OutputType>
NumberSubscriber<InputType, OutputType>::NumberSubscriber(NumberPublisher<InputType>* subject)
    : mSubject(subject)
{
    mSubject->Attach(this);
}

template <typename InputType, typename OutputType>
NumberSubscriber<InputType, OutputType>::~NumberSubscriber()
{
    mSubject->Detach(this);
}

template <typename InputType, typename OutputType>
void NumberSubscriber<InputType, OutputType>::Update(Subject* subject)
{
    if (subject == mSubject)
        RecomputeResult(mSubject->GetNumber());
}

template <typename InputType, typename OutputType>
OutputType NumberSubscriber<InputType, OutputType>::GetResult() const
{
    return mResult;
}


template <typename InputType>
class EvenNumberSubscriber : public NumberSubscriber<InputType, bool>
{
    using NumberSubscriber<InputType, bool>::NumberSubscriber;
    virtual void RecomputeResult(InputType) override;
};

template <typename InputType>
void EvenNumberSubscriber<InputType>::RecomputeResult(InputType number)
{
    this->mResult = !(number & 1);
}

template <typename InputType>
class PrimeNumberSubscriber : public NumberSubscriber<InputType, bool>
{
    using NumberSubscriber<InputType, bool>::NumberSubscriber;
    virtual void RecomputeResult(InputType) override;
};


template <typename InputType>
void PrimeNumberSubscriber<InputType>::RecomputeResult(InputType number)
{
    auto binpow = [](__uint128_t base, __uint128_t e, __uint128_t mod) {
        __uint128_t result = 1;
        base %= mod;
        while (e) {
            if (e & 1)
                result = result * base % mod;
            base = base * base % mod;
            e >>= 1;
        }
        return result;
    };

    auto composite = [binpow](uint64_t n, uint64_t a, uint64_t d, int s) {
        __uint128_t x = binpow(a, d, n);
        if (x == 1 || x == n - 1)
            return false;
        for (int r = 1; r < s; r++) {
            x = (__uint128_t) x * x % n;
            if (x == n - 1)
                return false;
        }
        return true;
    };

    auto MillerRabin = [composite](InputType _n) {
        if (_n < 2)
            return false;

        uint64_t n = _n;
        int r = 0;
        uint64_t d = n - 1;
        while ((d & 1) == 0) {
            d >>= 1;
            r++;
        }

        for (uint32_t a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
            if (n == a)
                return true;
            if (composite(n, a, d, r))
                return false;
        }
        return true;
    };


    this->mResult = MillerRabin(number);
}



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

    for (int64_t x = (1L<<62)-10000L; x < (1L<<62)+99L; ++x) {
        CheckNumber(x);
    }
}
