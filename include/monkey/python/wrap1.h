#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class Entity;

class PYBIND11_EXPORT Wrap1 {
public:
    Wrap1();
    float x() const ;
    void setEntity(Entity* e);
    void setColor (std::vector<float>& l);
    void setText (const std::string&);
    void appendText (pybind11::object);
    void clearText ();
    void setActive (bool);
    void enableControls(bool);

    static pybind11::object create(Entity*);
private:
    int g;
    Entity* m_entity;
};

inline void Wrap1::setEntity(Entity *e) {
    m_entity = e;
}

