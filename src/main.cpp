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
    if (number < 2) {
        this->mResult = false;
        return;
    }

    uint64_t x = number;
    for (uint64_t d = 2; d * d <= x; d++) {
        if (x % d == 0) {
            this->mResult = false;
            return;
        }
    }
    this->mResult = true;
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

    for (int64_t x = 0; x <= 100; ++x) {
        CheckNumber(x);
    }
}
