#pragma once

#include <cstdint>

#include "NumberSubscriber.hpp"

template <typename InputType>
class PrimeNumberSubscriber : public NumberSubscriber<InputType, bool>
{
public:
    using NumberSubscriber<InputType, bool>::NumberSubscriber;
private:
    virtual void ComputeResult(InputType);
};

template <typename InputType>
void PrimeNumberSubscriber<InputType>::ComputeResult(InputType number)
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
