#define GLM_ENABLE_EXPERIMENTAL

#include <gfx/components/controller3d.h>
#include <glm/gtx/vector_angle.hpp>
#include <gfx/error.h>
#include <gfx/engine.h>
#include <gfx/collisionengine3d.h>
#include <gfx/entity.h>
#include <gfx/math/geom.h>
#include <gfx/components/platform.h>
#include <iostream>
#include <gfx/math/geomalgo.h>
#include <glm/gtx/vector_angle.hpp>

using namespace glm;

Controller3D::Controller3D(const Controller3D& orig) : IController(orig),
    m_horizontalRayCount(orig.m_horizontalRayCount),
    m_verticalRayCount(orig.m_verticalRayCount),
    m_skinWidth(orig.m_skinWidth), m_maxClimbAngle(orig.m_maxClimbAngle),
    m_maxDescendAngle(orig.m_maxDescendAngle)
{

}

std::shared_ptr<Component> Controller3D::clone() const {
    return std::make_shared<Controller3D>(Controller3D(*this));
}

void Controller3D::Start() {
    m_details.Reset();
    m_engine = Engine::get().GetRunner<ICollisionEngine>();
    if (m_engine == nullptr)
        GLIB_FAIL("Controller3D requires a collision engine running!");
}

void Controller3D::Begin() {
    m_cc =  m_entity->GetComponent<ICollider>();
    if (m_cc == nullptr) {
        GLIB_FAIL("Controller3D requires a collider!")
    }
    //m_c->onShapeChanged.Register(this, [&] (Collider* c) { this->ResetShape(c); });
    CalculateRaySpacing();

}

//void CollisionEngine::Add(ICollider* c) {
//    // this is called when a new collider starts. It registers with the engine
//    // get the shape bounding box, transform it, map it
//    auto aabb = c->GetBounds();
//    if (!aabb.isVoid()) {
//        Location loc = GetLocation(aabb);
//        PushCollider(c, loc);
//    }
//
//
//}


//void Controller2D::ResetShape(ICollider*) {
//    CalculateRaySpacing();
//}

void Controller3D::CalculateRaySpacing() {

    Bounds bounds = m_cc->GetDynamicBounds();
    bounds.Expand(m_skinWidth * -2);
    m_horizontalRaySpacing = bounds.GetSize().y / (m_horizontalRayCount - 1);
    m_verticalRaySpacing = bounds.GetSize().x / (m_verticalRayCount - 1);
    //std::cout <<"ray spacing = "<< m_horizontalRaySpacing << ","<<m_verticalRaySpacing<<"\n";
}

void Controller3D::UpdateRaycastOrigins() {
    Bounds bounds = m_cc->GetDynamicBounds();
    bounds.Expand(m_skinWidth * -2);
    m_raycastOrigins.bottomLeft = bounds.min;
    m_raycastOrigins.topRight = bounds.max;
    //m_raycastOrigins.bottomLeft = vec2(bounds.min.x, bounds.min.y);
//    m_raycastOrigins.bottomRight = vec2(bounds.max.x, bounds.min.y);
//    m_raycastOrigins.topLeft = vec2(bounds.min.x, bounds.max.y);
//    m_raycastOrigins.topRight = vec2(bounds.max.x, bounds.max.y);
}

bool Controller3D::IsFalling(int x, int z) {
    //glm::vec3 rayOrigin = m_entity->GetPosition();
    glm::vec3 rayOrigin;
    rayOrigin.x = (x == 0 ? m_raycastOrigins.xMid() : (x > 0 ? m_raycastOrigins.xRight() : m_raycastOrigins.xLeft()));
    rayOrigin.z = (z == 0 ? m_raycastOrigins.zMid() : (z > 0 ? m_raycastOrigins.zFront() : m_raycastOrigins.zBack()));
    rayOrigin.y = m_raycastOrigins.yBottom();

    RayCastHit hit = m_engine->Raycast(rayOrigin, monkey::down, 5.0, 2);
    if (!hit.collide)
        return true;
    return false;
}
//bool Controller2D::IsFalling(int dir) {
//    glm::vec2 rayOrigin = (dir == -1) ? m_raycastOrigins.bottomLeft : m_raycastOrigins.bottomRight;
//    RayCastHit2D hit = m_collision->Raycast(glm::vec3(rayOrigin, 0.0f), glm::vec2(0.0f, -1.0f), 5.0, 2);
//    if (!hit.collide)
//        return true;
//    return false;
//}


void Controller3D::Move(glm::vec3& dx) {
    float scale = m_entity->GetScale();
    if (dx != vec3(0.0f)) {
        UpdateRaycastOrigins();
        //m_ppp.clear();
        bool movingHorizontally = !isEqual(dx.x, 0.0f) || !isEqual(dx.z, 0.0f);
        if (dx.y < 0) {
            DescendSlope(dx);
        }
//        if (m_details.onSlope && movingHorizontally) {
//            float k = glm::dot(glm::vec3(dx.x * (m_entity->GetFlipX() ? -1 : 1), 0.0f, dx.z), m_details.normal);
//            if (k >= 0) {
//                DescendSlope();
//            } else {
//                //std::cerr << "asc\n";
//            }
//        }
//        m_wasGnd = m_details.below;
//        m_detailsOld = m_details;
        m_details.Reset();
//        m_details.velocityOld = dx;
//
//
//        // before we do that... we have code handling collisions
////        if (dx.y < 0 && m_wasGnd) {
////            DescendSlope(dx);
////        }
        if (movingHorizontally)
            HorizontalCollisions(dx);
        if (!isEqual(dx.y, 0.0f))
            VerticalCollisions(dx);
        glm::vec3 actualMove = dx / scale;
        m_entity->MoveLocal(actualMove);
        if (!m_wasGnd && m_details.below) {
            glm::vec3 p=m_entity->GetPosition();
            // std::cout << "AFTER+++ " << p.x << "," << p.y << std::endl;
        }

    }
}

void Controller3D::DescendSlope(glm::vec3& vel) {
    float dxw = vel.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);
    glm::vec3 horizontalShift(dxw, 0.0f, vel.z);
    //glm::vec3 horizontalDir = glm::normalize(horizontalShift);
    glm::vec3 horizontalDir = glm::normalize(glm::vec3(vel.x, 0, vel.z));

    float hLength = glm::length(horizontalShift);

    glm::vec3 rayOrigin;
    rayOrigin.x = isZero(dxw) ? m_raycastOrigins.xMid() : ( (dxw < 0) ? m_raycastOrigins.xRight() : m_raycastOrigins.xLeft());
    rayOrigin.y = m_raycastOrigins.yBottom();
    rayOrigin.z = isZero(vel.z) ? m_raycastOrigins.zMid() : ( (vel.z < 0) ? m_raycastOrigins.zFront() : m_raycastOrigins.zBack());

    RayCastHit hit = m_engine->Raycast(rayOrigin, monkey::down, 1000.0f, 2 | 32);
    if (hit.collide) {
        float slopeAngle = glm::angle(hit.normal, monkey::up);

        if (!isZero(slopeAngle) && slopeAngle*rad2deg <= m_maxDescendAngle) {
            // check if this is a slope, this replaces
            // isDescending = (Mathf.sign(hit.normal.x) == directionX)
            bool isDescending = (glm::dot (horizontalShift, hit.normal) > 0);
            if (isDescending) {
                if (isZero(dxw)) {
                int kkfkf=20;
                }
                if (isZero(vel.z)) {
                    int ikk = 10;
                }
                if (hit.length - m_skinWidth <= tan(slopeAngle) * hLength) {
                    // it's close enough
                    float descendVelocityY = sin(slopeAngle) * hLength;
                    vel.x = horizontalDir.x * cos(slopeAngle) * hLength;
                    vel.z = horizontalDir.z * cos(slopeAngle) * hLength;
                    vel.y -= descendVelocityY;
                    m_details.below = true;
                }
            }
        }

    }
}

// this will have x and z components
void Controller3D::HorizontalCollisions(glm::vec3& vel) {

    float dxw = vel.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);
    glm::vec3 horizontalShift(dxw, 0.0f, vel.z);
    glm::vec3 horizontalDir = glm::normalize(glm::vec3(vel.x, 0.0f, vel.z));
    glm::vec3 rayDir = glm::normalize(horizontalShift);
    float hLength = glm::length(horizontalShift);
    float rayLength = hLength + m_skinWidth;

    glm::vec3 rayOrigin;
    rayOrigin.x = isZero(dxw) ? m_raycastOrigins.xMid() : ( (dxw < 0) ? m_raycastOrigins.xLeft() : m_raycastOrigins.xRight());
    rayOrigin.y = m_raycastOrigins.yBottom();
    rayOrigin.z = isZero(vel.z) ? m_raycastOrigins.zMid() : ( (vel.z < 0) ? m_raycastOrigins.zBack() : m_raycastOrigins.zFront());

    for (int i = 0; i < m_horizontalRayCount; i++) {
        //vec2 rayOrigin = facingLeft ? m_raycastOrigins.bottomLeft : m_raycastOrigins.bottomRight;
        rayOrigin += monkey::up * (i *m_horizontalRaySpacing);
        RayCastHit hit = m_engine->Raycast(rayOrigin, rayDir, rayLength, 2 | 32);
        if (hit.collide) {
            float slopeAngle = glm::angle(hit.normal, monkey::up);

            float sadeg = slopeAngle * rad2deg;
            if (i == 0 && sadeg <= m_maxClimbAngle) {
                float distanceToSlopeStart = 0.0f;
                if (slopeAngle != m_details.slopeAngleOld) {
                    distanceToSlopeStart = hit.length - m_skinWidth;
                    vel.x -= horizontalDir.x*distanceToSlopeStart;
                    vel.z -= horizontalDir.z*distanceToSlopeStart;
                }
                ClimbSlope(vel, slopeAngle);
                vel.x += horizontalDir.x * distanceToSlopeStart;
                vel.z += horizontalDir.z * distanceToSlopeStart;
            }

            if (!m_details.climbingSlope || sadeg > m_maxClimbAngle) {
                float dist = (hit.length - m_skinWidth) ;//*directionX;

                vel.x = horizontalDir.x * dist;
                vel.z = horizontalDir.z * dist;
                rayLength = dist;
                m_details.left = dxw < 0;
                m_details.right = dxw > 0;

            }

        }
    }



}

void Controller3D::ClimbSlope(glm::vec3& vel, float slopeAngle) {
    float dxw = vel.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);
    glm::vec3 horizontalShift(dxw, 0.0f, vel.z);
    glm::vec3 horizontalDir = glm::normalize(glm::vec3(vel.x,0,vel.z));
    float moveDistance = glm::length(horizontalShift);
    float climbVelocityY = sin(slopeAngle) * moveDistance;
    if (vel.y > climbVelocityY) {
        // here we are jumping
    } else {
        vel.y = climbVelocityY;
        vel.x = cos(slopeAngle) * moveDistance * horizontalDir.x;
        vel.z = cos(slopeAngle) * moveDistance * horizontalDir.z;
        m_details.below = true;
        m_details.climbingSlope = true;
        m_details.slopeAngle = slopeAngle;
    }
}


//void Controller2D::DescendSlope(glm::vec2& velocity) {
//    //if (velocity.x == 0.0f)
//    //   return;
//    //float directionX = sign(velocity.x);
//    bool facingLeft = m_entity->GetFlipX();
//    float directionX = facingLeft ? -1.0 : 1.0;
//    vec2 rayOrigin = ((directionX == -1) ? m_raycastOrigins.bottomRight : m_raycastOrigins.bottomLeft);
//    //RayCastHit2D hit = m_collision->Raycast(rayOrigin, vec2(0, -1), 100.0f, m_platform != nullptr ? 2 | 32 : 2);
//    RayCastHit2D hit = m_collision->Raycast(vec3(rayOrigin,0.0f), vec2(0, -1), 100.0f, 2 | 32);
//    if (hit.collide) {
//        float slopeAngle = angle(hit.normal, vec2(0, 1));
//        //std::cout << "DESCEND SLOPE, angle = " << rad2deg * slopeAngle << "\n";
//        if (slopeAngle != 0 && slopeAngle <= m_maxDescendAngle) {
//            if (sign(hit.normal.x) == directionX) {
//                if (hit.length - m_skinWidth <= tan(slopeAngle) * fabs(velocity.x)) {
//                    float moveDistance = fabs(velocity.x);
//                    float descendVelocityY = sin(slopeAngle) * moveDistance;
//                    velocity.x = cos(slopeAngle) * moveDistance;// * sign(velocity.x);
//                    velocity.y -= descendVelocityY;
//                    m_details.slopeAngle = slopeAngle;
//                    m_details.descendingSlope = true;
//                    m_details.below = true;
//                }
//            }
//        }
//    }
//}

void Controller3D::VerticalCollisions(glm::vec3& velocity) {
    float directionY = sign(velocity.y);
    float rayLength = std::abs(velocity.y) + m_skinWidth;
    Entity* m_obstacle = nullptr;
    float velx = velocity.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);

    glm::vec3 rayOrigin;
    rayOrigin.x = m_raycastOrigins.xLeft() + velx;
    rayOrigin.y = (directionY == -1 ? m_raycastOrigins.bottomLeft.y : m_raycastOrigins.topRight.y);
    rayOrigin.z = m_raycastOrigins.zBack() + velocity.z; //(velocity.z >= 0 ? m_raycastOrigins.zFront() : m_raycastOrigins.zBack()) + velocity.z;
    //glm::vec3 horizontalDir = glm::normalize(glm::vec3(abs(velocity.x), 0.0f, abs(velocity.z)));

    // check x axis

    for (int i = 0; i < m_verticalRayCount; i++) {
        //vec2 rayOrigin = (directionY == -1) ? m_raycastOrigins.bottomLeft : m_raycastOrigins.topLeft;
        rayOrigin += monkey::right * (i *m_verticalRaySpacing );
        int collMask = (directionY == -1 ? (2 | 32) : 2);
        RayCastHit hit = m_engine->Raycast(rayOrigin, glm::vec3(0, directionY, 0), rayLength, collMask);
        if (hit.collide) {
            velocity.y = (hit.length - m_skinWidth) * directionY;
            rayLength = hit.length;

            m_details.below = directionY == -1;
            m_details.above = directionY == 1;
        }
    }
    for (int i = 0; i < m_verticalRayCount; i++) {
        //vec2 rayOrigin = (directionY == -1) ? m_raycastOrigins.bottomLeft : m_raycastOrigins.topLeft;
        rayOrigin += monkey::front * (i *m_verticalRaySpacing );
        int collMask = (directionY == -1 ? (2 | 32) : 2);
        RayCastHit hit = m_engine->Raycast(rayOrigin, glm::vec3(0, directionY, 0), rayLength, collMask);
        if (hit.collide) {
            velocity.y = (hit.length - m_skinWidth) * directionY;
            rayLength = hit.length;

            m_details.below = directionY == -1;
            m_details.above = directionY == 1;
        }
    }

}

//void Controller2D::DetachFromPlatform() {
//    if (m_platform != nullptr) {
//        auto platformController = m_platform->GetComponent<PlatformComponent>();
//        if (platformController != nullptr)
//            platformController->Unregister(this);
//        m_platform = nullptr;
//    }
//}
//Controller2D::~Controller2D() {
//    DetachFromPlatform();
//}
