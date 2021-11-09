#include <monkey/components/box2dbody.h>
#include <monkey/box2dworld.h>
#include <monkey/entity.h>
#include <monkey/engine.h>
#include <glm/gtx/transform.hpp>
#include <monkey/model/factory.h>
#include <monkey/components/renderer.h>

std::unordered_map<std::string, b2BodyType> Box2DBody::g_strToBodyType = {
        {"static", b2BodyType::b2_staticBody},
        {"dynamic", b2BodyType::b2_dynamicBody},
        {"kinematic", b2BodyType::b2_kinematicBody}};

Box2DBody::Box2DBody(const ITab& t) : m_body(nullptr) {
    b2FixtureDef def;
    m_shapeDef = t["shapes"];

    m_bodyType = g_strToBodyType[t.get<std::string>("body_type", "static")];
    m_angle = t.get<float>("angle", 0.0f);
    m_fixedRotation = t.get<bool>("fixed_rot", false);
    m_drawShape = t.get<bool>("draw_shape", false);

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
    bodyDef.angle = m_angle;
    bodyDef.fixedRotation = m_fixedRotation;
    bodyDef.type = m_bodyType;
    m_body = world->createBody(&bodyDef);
    m_body->SetLinearDamping(1.5);


    // create shape & fixtures
    std::shared_ptr<Model> model;
    if (m_drawShape) {
        model = std::make_shared<Model>();
    }
    m_shapeDef->foreach([&] (const ITab& shape) {
        b2FixtureDef fixtureDef;
        auto density = shape.get<float>("density");
        auto friction = shape.get<float>("friction", fixtureDef.friction);
        auto shapeType = shape.get<std::string>("type");
        auto offset = shape.get<glm::vec2>("offset", glm::vec2(0.0f));
        std::unique_ptr<b2Shape> sha;
        if (shapeType == "box2d_rect") {
            auto sh = std::make_unique<b2PolygonShape>();
            auto size = shape.get<glm::vec2>("half_size");
            sh->SetAsBox(size.x, size.y);
            sh->m_centroid = b2Vec2(offset.x, offset.y);

            if (m_drawShape) {
                auto mesh = ModelFactory::b2Poly(*sh.get(), glm::vec4(1.0f));
                model->addMesh(mesh);
            }
            sha = std::move(sh);
        } else if (shapeType == "box2d_poly") {
            auto sh = std::make_unique<b2PolygonShape>();
            auto pts = shape.get<std::vector<float>>("points");
            b2Vec2 points[8];
            size_t j = 0;
            for (size_t i = 0; i < pts.size(); i+=2) {
                b2Vec2 p(pts[i], pts[i+1]);
                points[j++] = p;
            }
            sh->Set(points, j);
            sh->m_centroid = b2Vec2(offset.x, offset.y);
            if (m_drawShape) {
                auto mesh = ModelFactory::b2Poly(*sh.get(), glm::vec4(1.0f));
                model->addMesh(mesh);
            }
            sha = std::move(sh);

        }
        fixtureDef.shape = sha.get();
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        m_body->CreateFixture(&fixtureDef);

    });

    if (m_drawShape) {
        auto entity = std::make_shared<Entity>();
        auto renderer = model->makeRenderer(model);
        entity->AddComponent(renderer);
        m_entity->AddChild(entity);
    }

    // create shape

    //body->CreateFixture()
}

void Box2DBody::Update(double dt) {


    auto pos = m_body->GetPosition();
    auto angle = m_body->GetAngle();
    //std::cerr << pos.x << ", " << pos.y << "\n";
    auto mat = glm::rotate(angle, glm::vec3(0, 0, 1));
    mat[3][0] = pos.x * m_scaleBoxToGL;
    mat[3][1] = pos.y * m_scaleBoxToGL;
    m_entity->SetLocalTransform(mat);
}