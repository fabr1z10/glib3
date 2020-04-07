#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class Entity;

class Wrap1 {
public:
    Wrap1();
    float x() const ;
    void setEntity(Entity* e);
    void setColor (std::vector<float>& l);
    void setText (const std::string&);
    void appendText (const std::string&);
private:
    int g;
    Entity* m_entity;
};

inline void Wrap1::setEntity(Entity *e) {
    m_entity = e;
}

