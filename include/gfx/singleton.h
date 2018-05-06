//
//  singleton.h
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#ifndef singleton_h
#define singleton_h

template<class T>
class Singleton
{
public:
    static T & get()
    {
        static T instance;
        return instance;
    }
    Singleton(Singleton const &) = delete;
    Singleton & operator=(Singleton const &) = delete;
protected:
    Singleton() { }
};

#endif /* singleton_h */
