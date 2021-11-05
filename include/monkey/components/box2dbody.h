#pragma once

#include <monkey/component.h>
#include <box2d/box2d.h>

class Box2DBody : public Component {
public:
    Box2DBody(const ITab&);
    void Start() override;
    void Update(double) override;
private:
    std::unique_ptr<b2Shape> m_shape;
    float m_density;
    float m_friction;
    b2BodyType m_bodyType;
    b2Body* m_body;
    float m_scaleBoxToGL;
    static std::unordered_map<std::string, b2BodyType> g_strToBodyType;
};