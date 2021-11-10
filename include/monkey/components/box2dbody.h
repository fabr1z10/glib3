#pragma once

#include <monkey/component.h>
#include <box2d/box2d.h>
#include <monkey/components/box2dlistener.h>
#include "inputmethod.h"

class Box2DBody : public Component {
public:
    Box2DBody(const ITab&);
    void Start() override;
    void Update(double) override;
    b2Body* getBody();
    using ParentClass = Box2DBody;
    void startContact(Box2DBody* other, b2Contact*, bool youAreA);
    void endContact(Box2DBody* other, b2Contact*, bool youAreA);

    void registerCallback(IBox2DBodyListener*);
private:

    std::unique_ptr<b2Shape> m_shape;
    float m_density;
    float m_friction;
    b2BodyType m_bodyType;
    b2Body* m_body;
    float m_scaleBoxToGL;
    static std::unordered_map<std::string, b2BodyType> g_strToBodyType;
    //InputMethod * m_input;
    float m_angle;
    bool m_fixedRotation;
    std::unique_ptr<ITab> m_shapeDef;
    bool m_drawShape;

    std::vector<IBox2DBodyListener*> m_contactListeners;

};

inline b2Body * Box2DBody::getBody() {
    return m_body;
}