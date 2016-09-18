#include "Subject.hpp"

void Subject::subscribe( Observer * ob ) {

    observers.insert( ob );

}

void Subject::unsubscribe( Observer * ob ) {

    observers.erase( ob );

}

void Subject::notify() {

    std::set<Observer *>::iterator it;

    for( it = observers.begin(); it != observers.end(); it++ ) {
        ( *it )->update();
    }

}