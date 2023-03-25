#include "Subject.hpp"

void Subject::Attach(Observer* observer)
{
    mObservers.push_back(observer);
}

void Subject::Detach(Observer* observer)
{
    mObservers.remove(observer);
}

void Subject::Notify()
{
    for (Observer* observer : mObservers)
        observer->Update(this);
}

