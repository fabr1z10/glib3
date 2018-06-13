//
//  event.h
//  glib
//
//  Created by Fabrizio Venturini on 13/06/2018.
//
//

#ifndef event_h
#define event_h

#include <gfx/ref.h>
#include <functional>
#include <list>

// generic class that enables to register interest
// objects can expose different events other objects can register to
// an event require a function (callback) to call when something happens
// this func can be a global function or a member function
// in this case every object registering must be a ref, in order that we
// can detect when it goes out of scope

template<typename Args>
class Event {
private:
    struct Callback {
        int id;
        std::function<void(Args)> callback;
    };
    
    
    // register interest in this event with context
    void Register(Ref* object, std::function<void(Args)> f) {
        m_callbacks[object->GetId()] = Callback{ object, f };
    }
    
    void Unregister(Object* obj) {
        m_callbacks.erase(obj->GetHandle());
    }

    
private:
    std::list<Callback> m_callbacks;
};

#endif /* event_h */
