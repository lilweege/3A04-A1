#pragma once

#include "Subject.hpp"

template<std::integral InputType>
class NumberPublisher : public Subject
{
    InputType mNumber = 0;
public:
    [[nodiscard]] InputType GetNumber() const;
    void SetNumber(InputType);
};

template<std::integral InputType>
InputType NumberPublisher<InputType>::GetNumber() const
{
    return mNumber;
}

template<std::integral InputType>
void NumberPublisher<InputType>::SetNumber(InputType number)
{
    // NOTE: Do NOT call this function from an observer.
    // Doing so would result in infinite mutual recursion (this is bad).
    mNumber = number;
    Notify();
}

