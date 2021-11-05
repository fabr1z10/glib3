#include <monkey/components/box2dbody.h>
#include <monkey/box2dworld.h>
#include <monkey/entity.h>
#include <monkey/engine.h>
#include <glm/gtx/transform.hpp>

std::unordered_map<std::string, b2BodyType> Box2DBody::g_strToBodyType = {
        {"static", b2BodyType::b2_staticBody},
        {"dynamic", b2BodyType::b2_dynamicBody},
        {"kinematic", b2BodyType::b2_kinematicBody}};

Box2DBody::Box2DBody(const ITab& t) : m_body(nullptr) {
    b2FixtureDef def;
    auto shapeDef = t["shape"];
    m_density = t.get<float>("density");
    m_friction = t.get<float>("friction", def.friction);
    m_bodyType = g_strToBodyType[t.get<std::string>("body_type", "static")];
    auto shapeType = shapeDef->get<std::string>("type");
    std::cerr << "shapetype = " << shapeType;
    if (shapeType == "box2d_rect") {
        auto shape = std::make_unique<b2PolygonShape>();
        auto size = shapeDef->get<glm::vec2>("half_size");
        shape->SetAsBox(size.x, size.y);
        m_shape = std::move(shape);
    }
}

void Box2DBody::Start() {
    auto world = Engine::get().GetRunner<Box2DWorld>();
    float scale = world->getScalingFactor();
    m_scaleBoxToGL = 1.0f / scale;
    auto worldPos = m_entity->GetPosition();
    float x = worldPos.x * scale;
    float y = worldPos.y * scale;
    b2BodyDef bodyDef;
    bodyDef.position.Set(x, y);
    bodyDef.type = m_bodyType;
    m_body = world->createBody(&bodyDef);




    // create shape

    b2FixtureDef fixtureDef;
    fixtureDef.shape = m_shape.get();
    fixtureDef.density = m_density;
    fixtureDef.friction = m_friction;
    m_body->CreateFixture(&fixtureDef);
    //body->CreateFixture()
}

void Box2DBody::Update(double dt) {

    auto pos = m_body->GetPosition();
    auto angle = m_body->GetAngle();
    std::cerr << pos.x << ", " << pos.y << "\n";
    auto mat = glm::rotate(angle, glm::vec3(0, 0, 1));
    mat[3][0] = pos.x * m_scaleBoxToGL;
    mat[3][1] = pos.y * m_scaleBoxToGL;
    m_entity->SetLocalTransform(mat);
}