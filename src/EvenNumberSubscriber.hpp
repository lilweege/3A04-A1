#pragma once

#include "NumberSubscriber.hpp"

template <typename InputType>
class EvenNumberSubscriber : public NumberSubscriber<InputType, bool>
{
public:
    using NumberSubscriber<InputType, bool>::NumberSubscriber;
private:
    virtual void RecomputeResult(InputType);
};

template <typename InputType>
void EvenNumberSubscriber<InputType>::RecomputeResult(InputType number)
{
    this->mResult = !(number & 1);
}

