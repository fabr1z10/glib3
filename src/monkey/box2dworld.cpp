#include <monkey/box2dworld.h>



Box2DWorld::Box2DWorld(const ITab& t) {
    m_velocityIterations = 6;
    m_positionIterations = 2;
    auto g = t.get<glm::vec2>("gravity");
    b2Vec2 gravity(g.x, g.y);
    m_scalingFactor = t.get<float>("scale");
    // Construct a world object, which will hold and simulate the rigid bodies.
    m_world = std::make_unique<b2World>(gravity);
}

void Box2DWorld::Update(double dt) {
    m_world->Step(dt, m_velocityIterations, m_positionIterations);
}

b2Body * Box2DWorld::createBody(b2BodyDef * def) {
    return m_world->CreateBody(def);
}