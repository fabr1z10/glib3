#pragma once

#include <monkey/component.h>
#include <monkey/components/inputmethod.h>
#include "rigidbody.h"

class Controller3Db : public Component {
public:
    Controller3Db(const Controller3Db&);
    Controller3Db(const LuaTable& t);
    void Start() override;
    void Update(double) override;
    std::shared_ptr<Component> clone() const override;

private:
    RigidBody* m_rigidBody;
    InputMethod * m_input;

};