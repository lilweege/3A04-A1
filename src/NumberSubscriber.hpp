#pragma once

#include "Observer.hpp"
#include "NumberPublisher.hpp"

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
    virtual void ComputeResult(InputType) = 0;

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
        ComputeResult(mSubject->GetNumber());
}

template <typename InputType, typename OutputType>
OutputType NumberSubscriber<InputType, OutputType>::GetResult() const
{
    return mResult;
}
