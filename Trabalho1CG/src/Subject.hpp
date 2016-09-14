#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include "Observer.hpp"

class Subject {

    std::set<Observer *> observers;

public:
    void subscribe(Observer *ob);
    void unsubscribe(Observer *ob);
protected:
    void notify();
};

#endif