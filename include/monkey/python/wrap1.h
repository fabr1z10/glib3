#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class Entity;

class PYBIND11_EXPORT Wrap1 {
public:
    Wrap1();
    float x() const ;
    float y() const ;
    float getVy() const;
    void setVy(float);
    float getVx() const;
    void setVx(float);
    void move(float dx, float dy, float dz);
    int id() const;
    void setEntity(Entity* e);
    void setColor (std::vector<float>& l);
    void setText (const std::string&);
    void setModel (const std::string&, const std::string& animId);
    void appendText (pybind11::object);
    int add(pybind11::object);
    std::string getState();

    void clearText ();
    void setActive (bool);
    void enableControls(bool);
    pybind11::object getParent();
    pybind11::object getInfo ();
    static pybind11::object create(Entity*);
private:
    int g;
    Entity* m_entity;
};

inline void Wrap1::setEntity(Entity *e) {
    m_entity = e;
}

