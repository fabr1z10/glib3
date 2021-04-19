#pragma once

#include <monkey/collisionresponse.h>

class LuaCollisionResponse : public CollisionResponse {
public:
    LuaCollisionResponse () : CollisionResponse() {}
    void onStart (Entity*, Entity*, const CollisionReport& report) override;
    void onEnd (Entity*, Entity*, const CollisionReport& report) override;
    void onStay (Entity*, Entity*, const CollisionReport& report) override;

    void setOnEnter(pybind11::function& ref);
    void setOnLeave(pybind11::function& ref);
    void setOnStay(pybind11::function& ref);
private:
    pybind11::function m_onEnter;
    pybind11::function m_onLeave;
    pybind11::function m_onStay;
};
