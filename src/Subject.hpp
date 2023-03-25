#pragma once

#include <list>

class Subject;
#include "Observer.hpp"

class Subject
{
public:
    virtual ~Subject() = default;
    void Attach(Observer*);
    void Detach(Observer*);
    void Notify();
protected:
    Subject() = default;
private:
    std::list<Observer*> mObservers;
};
