#pragma once

#include <monkey/component.h>
#include <box2d/box2d.h>
#include "inputmethod.h"


class Box2DCharacterControllerBase : public Component {
public:
    Box2DCharacterControllerBase(const ITab&);
    void Start() override;
    //void Update(double) override;
protected:
    float m_halfWidth;
    float m_halfHeight;
    InputMethod * m_input;
    b2Body* m_body;
};