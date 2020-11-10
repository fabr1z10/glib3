#include <monkey/components/controller25.h>
#include <monkey/engine.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>

using namespace glm;


std::type_index Controller25::GetType() {
    return std::type_index(typeid(IController));
}

Controller25::~Controller25() {
}


Controller25::Controller25(const ITable &t) : IController() {
    m_horizontalRayCount = t.get<int>("horRays", 4);
    m_verticalRayCount = t.get<int>("vertRays", 4);
    m_maskWall = t.get<int>("mask");
    m_skinWidth = t.get<float>("skinWidth", .015f);
    m_elevation = t.get<float>("elevation", 0.0f);
    m_depth = t.get<float>("depth", 0.0f);
}


void Controller25::Start() {
    m_collision = Engine::get().GetRunner<ICollisionEngine>();
    auto pos = m_entity->GetPosition();
    //m_depth = pos.y;
    //m_elevation = 0.0f;
    //pos.x += velocity.x * (flipx? -1.0f : 1.0f);
    pos.y = m_elevation + m_depth;
    pos.z = -0.01f * m_depth;
    m_entity->SetPosition(pos);

    //m_entity->SetZ(-0.01f * m_depth);

}

void Controller25::Begin() {
    m_collider =  m_entity->GetComponent<ICollider>();
    if (m_collider == nullptr) {
        GLIB_FAIL("The controller2D requires a collider!");
    }
    //m_cc->onShapeChanged.Register(this, [&] (Collider* c) { this->ResetShape(c); });
    CalculateRaySpacing();

}



void Controller25::ResetShape(ICollider*) {
    CalculateRaySpacing();
}


void Controller25::CalculateRaySpacing() {

    Bounds bounds = m_collider->GetDynamicBounds();
    bounds.Expand(m_skinWidth * -2);
    m_verticalRaySpacing = bounds.GetSize().x / (m_verticalRayCount - 1);
    //std::cout <<"ray spacing = "<< m_horizontalRaySpacing << ","<<m_verticalRaySpacing<<"\n";
}

void Controller25::UpdateRaycastOrigins() {
    Bounds bounds = m_collider->GetDynamicBounds();
    //bounds.Expand(m_skinWidth * -2);
    m_raycastOrigins.bottomLeft = vec2(bounds.min.x, bounds.min.y);
    m_raycastOrigins.bottomRight = vec2(bounds.max.x, bounds.min.y);
    m_raycastOrigins.topLeft = vec2(bounds.min.x, bounds.max.y);
    m_raycastOrigins.topRight = vec2(bounds.max.x, bounds.max.y);
}

// (dx, d(elevation), d(depth))
void Controller25::Move(glm::vec3 & velocity) {
    //std::cerr << velocity.y << "\n";
    if (glm::length(velocity) < 0.01f)
        return;
    UpdateRaycastOrigins();

    bool flipx = m_entity->GetFlipX();

    bool goingLeft = (flipx && velocity.x > 0) || (!flipx && velocity.x < 0);

    float sgn_vx = (velocity.x > 0) ? 1.0f: -1.0f;
    float directionX = goingLeft ? -1.0f : 1.0f;
    float rayLength = fabs(velocity.x) + m_skinWidth;

    //for (int i = 0; i < m_horizontalRayCount; i++) {
    vec2 rayOrigin = goingLeft ? m_raycastOrigins.bottomLeft : m_raycastOrigins.bottomRight;
    rayOrigin.y = m_depth;
    //rayOrigin += vec2(0.0f, 1.0f) * (i *m_horizontalRaySpacing);
        //RayCastHit2D hit = m_collision->Raycast(rayOrigin, glm::vec2(1, 0) * directionX, rayLength, 2);
    RayCastHit hit = m_collision->Raycast(
        glm::vec3(rayOrigin, 0.0f),
        monkey::right * directionX,
        rayLength,
        m_maskWall);

    if (hit.collide) {

        velocity.x = (hit.length - m_skinWidth) * sgn_vx;
    }

    // y displacemente
    float directionY = (velocity.z > 0) ? 1.0f: -1.0f;
    rayLength = fabs(velocity.z) + m_skinWidth;

    for (int i = 0; i < m_verticalRayCount; i++) {
        vec2 rayOrigin = m_raycastOrigins.bottomLeft;
        rayOrigin.y = m_depth;
        rayOrigin += vec2(1, 0) * (i * m_verticalRaySpacing + velocity.x);
        RayCastHit hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), monkey::up * directionY, rayLength, m_maskWall);
        if (hit.collide) {
            velocity.z = (hit.length - m_skinWidth) * directionY;
            rayLength = hit.length;
        }
    }
    float dDepth = velocity.z;
    float dx = velocity.x;
    float dElevation = velocity.y;
    //std::cerr << "ddeèth="<< dDepth;
    glm::vec3 pos = m_entity->GetPosition();
    m_elevation += dElevation;
    m_elevation = std::max(0.0f, m_elevation);
    m_depth += dDepth;
   // std::cout << " depth = " << m_depth << ", elev " << m_elevation << "\n";
    pos.x += velocity.x * (flipx? -1.0f : 1.0f);
    pos.y = m_elevation + m_depth;
    pos.z = -0.01f * m_depth;
    m_entity->SetPosition(pos);
    //m_entity->MoveLocal(glm::vec3(velocity.x, velocity.y, 0));
    //m_entity->SetZ()
}


bool Controller25::grounded() const {
    return m_elevation == 0.0f;
}
