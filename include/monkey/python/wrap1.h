#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class Entity;

class PYBIND11_EXPORT Wrap1 {
public:
    Wrap1();
    bool valid() const;
    float x() const ;
    float y() const ;
    float getVy() const;
    bool getFlipx() const;
    void setVy(float);
    float getVx() const;
    void setVx(float);
    float getScale() const;
    void setScale(float);
    void follow(bool);
    void move(float dx, float dy, float dz);
    int id() const;
    void setEntity(Entity* e);
    void setColor (std::vector<float>& mult, std::vector<float>& add);
    void setText (const std::string&);
    void setModel (const std::string&, const std::string& animId);
    void appendText (pybind11::object);
    int add(pybind11::object);
    std::string getState();
    void setState(const std::string&, pybind11::dict d = pybind11::dict());
    void clearText ();
    void setActive (bool);
    void enableControls(bool);
    pybind11::object getParent();
    pybind11::object getInfo ();
    pybind11::list getAttackPos();
    static pybind11::object create(Entity*);
private:
    int g;
    Entity* m_entity;
};

inline void Wrap1::setEntity(Entity *e) {
    m_entity = e;
}

