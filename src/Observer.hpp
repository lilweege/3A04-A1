#pragma once

class Observer;
#include "Subject.hpp"

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void Update(Subject*) = 0;
protected:
    Observer() = default;
};

