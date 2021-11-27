#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class Entity;
class Engine;

class PYBIND11_EXPORT Wrap1 {
public:
    Wrap1();
    bool valid() const;
    std::string tag() const;
    float x() const ;
    float y() const ;
    float z() const;
    void rotx(float) ;
    float getVy() const;
    float getElevation() const;
    void setElevation(float);
    bool getFlipx() const;
    std::string getAnim() const;
    int getKeyFrame() const;
    void setVy(float);
    float getVx() const;
    void setVx(float);
    void clear();
    float getScale() const;
    void setScale(float);
    void follow(bool);
    void setPosition(float x, float y, float z);
    void setTransform(std::vector<float>& f);
    void move(float dx, float dy, float dz);
    int id() const;
    void setEntity(Entity* e);
    void setColor (std::vector<float>& mult, std::vector<float>& add);
    void setText (const std::string&);
    void setModel (pybind11::object obj);
    void setMesh (const std::string&, const std::string&, float scale, float ox, float oy);
    void setAnim (const std::string&);
    void appendText (pybind11::object);
    void setEnableUpdate (bool);
    int add(pybind11::object);
    std::string getState();
    void setState(const std::string&, pybind11::dict d = pybind11::dict());
    void clearText ();
    void setActive (bool);
    void setVisible(bool);
    void enableControls(bool);
    pybind11::object getParent();
    pybind11::object getInfo ();
    pybind11::list getAttackPos();
	pybind11::list getTextSize();
	pybind11::list getCollisionBounds();
	pybind11::list getAttackCollisionBounds();
	pybind11::list getChildren(bool recursive);
	pybind11::object getKeyPoint(const std::string& joint, const std::string& point);
	pybind11::list getBoxSize(const std::string& animId="");
    static pybind11::object create(Entity*);
    static void runScript(Engine& engine, pybind11::object);
    void play (pybind11::object o);
    void killScripts ();
    void setControllerBounds(float width, float height, float depth, float x, float y, float z);
    int getCollisionFlag() const;
    void setCollisionFlag(int);
private:
    int g;
    Entity* m_entity;
};

inline void Wrap1::setEntity(Entity *e) {
    m_entity = e;
}

