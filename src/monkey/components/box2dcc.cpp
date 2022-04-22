//#include <monkey/components/box2dcc.h>
//#include <monkey/entity.h>
//#include <monkey/engine.h>
//#include <monkey/components/box2dbody.h>
//#include <glm/gtx/vector_angle.hpp>
//
//Box2DCharacterController::Box2DCharacterController(const ITab & t) : Box2DCharacterControllerBase(t) {
//}
//
//
//void Box2DCharacterController::Start() {
//    Box2DCharacterControllerBase::Start();
//}
//
//float Pippo::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) {
//    n++;
//    if (fraction < m_fraction) {
//        collide = true;
//        m_fraction = fraction;
//        closestNormal= normal;
//    }
//    return 1;
//}
//
//CRep Box2DCharacterController::raycastDown(b2Vec2 P) {
//    auto detail = std::make_unique<Pippo>();
//    auto Q = P + b2Vec2(0, -100);
//    m_body->GetWorld()->RayCast(detail.get(), P, Q);
//    float angle = glm::angle(glm::vec2(0,1), glm::vec2(detail->closestNormal.x, detail->closestNormal.y));
//    return CRep{detail->collide, detail->m_fraction * 100, detail->closestNormal, angle};
//}
//
//void Box2DCharacterController::checkGrounded() {
//    auto pos = m_body->GetPosition();
//    auto left = b2Vec2(pos.x - m_halfWidth, pos.y - m_halfHeight);//aabb.lowerBound;//+ b2Vec2(0.1,0.1);
//    auto right = b2Vec2(pos.x + m_halfWidth, pos.y - m_halfHeight);//aabb.lowerBound;//+ b2Vec2(0.1,0.1);
//    m_left = raycastDown(left);
//    m_right = raycastDown(right);
//}
//
//bool Box2DCharacterController::grounded() const {
//    // std::cerr << m_right.collide << ", " << m_right.distance <<std::endl;
//    return ((m_left.collide && m_left.distance < 0.1f) || (m_right.collide && m_right.distance < 0.1f));
//}
//bool Box2DCharacterController::lgrounded() const {
//    // std::cerr << m_right.collide << ", " << m_right.distance <<std::endl;
//    return (m_left.collide && m_left.distance < 0.1f);
//}
//bool Box2DCharacterController::rgrounded() const {
//    // std::cerr << m_right.collide << ", " << m_right.distance <<std::endl;
//    return (m_right.collide && m_right.distance < 0.1f);
//}
//void Box2DCharacterController::Update(double) {
//    // ray cast from
//    checkGrounded();
//    auto pk = b2Dot(m_body->GetLinearVelocity(), m_right.normal);
//
//    if (grounded()) {
//        if (m_right.angle < m_previousAngle) {
//            std::cerr << "grounded = " << grounded() << ", angle =  " << glm::degrees(m_right.angle) << " " << pk << std::endl;
//
//        }
//    }
//    if (m_input != nullptr) {
//        bool up = m_input->isKeyDown(GLFW_KEY_UP);
//        if (up && grounded()) {
//
//            m_body->ApplyLinearImpulseToCenter(b2Vec2(0,30), true);
//        }
//        bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
//        bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
//        if (right) {
//            b2Vec2 u(1, 0);
//            if (!rgrounded() && lgrounded()) {
//                u = b2Vec2(m_right.normal.y, -m_right.normal.x);
//            }
//            m_body->ApplyForceToCenter(50.0f * u, true);
//        } else if (left) {
//            b2Vec2 u(-1, 0);
//            std::cerr << m_left.collide << " " << m_right.collide << std::endl;
//            if (!lgrounded() && rgrounded()) {
//                u = b2Vec2(-m_right.normal.y, m_right.normal.x);
//            }
//            m_body->ApplyForceToCenter(50.0f * u, true);
//        }
//        //m_body->ApplyForceToCenter(b2Vec2(-2.0f*m_body->GetLinearVelocity().x, 0), true);
//    }
//    m_previousAngle = m_right.angle;
//    std::cerr << "vel x = " << m_body->GetLinearVelocity().x << std::endl;
//}