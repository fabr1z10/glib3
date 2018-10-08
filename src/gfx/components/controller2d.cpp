#define GLM_ENABLE_EXPERIMENTAL

#include <gfx/components/controller2d.h>
#include <glm/gtx/vector_angle.hpp>
#include <gfx/error.h>
#include <gfx/engine.h>
#include <gfx/collisionengine.h>
#include <gfx/entity.h>
#include <gfx/math/geom.h>
#include <gfx/components/platform.h>
#include <iostream>

using namespace glm;

void Controller2D::Start() {
    CalculateRaySpacing();
    m_details.Reset();
    m_collision = Engine::get().GetRunner<CollisionEngine>();
    if (m_collision == nullptr)
        GLIB_FAIL("Controller2D requires a collision engine running!");
}

void Controller2D::CalculateRaySpacing() {
    m_cc =  m_entity->GetComponent<Collider>();
    Bounds bounds = m_cc->GetShape()->getBounds();
    bounds.Expand(m_skinWidth * -2);
    m_horizontalRaySpacing = bounds.GetSize().y / (m_horizontalRayCount - 1);
    m_verticalRaySpacing = bounds.GetSize().x / (m_verticalRayCount - 1);
    std::cout <<"ray spacing = "<< m_horizontalRaySpacing << ","<<m_verticalRaySpacing<<"\n";
}

void Controller2D::UpdateRaycastOrigins() {
    Bounds bounds = m_cc->GetBounds();
    bounds.Expand(m_skinWidth * -2);
    m_raycastOrigins.bottomLeft = vec2(bounds.min.x, bounds.min.y);
    m_raycastOrigins.bottomRight = vec2(bounds.max.x, bounds.min.y);
    m_raycastOrigins.topLeft = vec2(bounds.min.x, bounds.max.y);
    m_raycastOrigins.topRight = vec2(bounds.max.x, bounds.max.y);

}

void Controller2D::Move(glm::vec2& dx) {
    if (dx != vec2(0.0f)) {
        UpdateRaycastOrigins();
        //m_ppp.clear();
        // get all the stuff that might be on the way
        Bounds b;
        b.min = m_raycastOrigins.bottomLeft + glm::vec2((dx.x < 0.0f) ? dx.x : 0.0f, (dx.y < 0.0f)? dx.y : 0.0f);
        b.max = m_raycastOrigins.topRight + glm::vec2((dx.x > 0.0f) ? dx.x : 0.0f, (dx.y > 0.0f)? dx.y : 0.0f);
        //m_ppp = m_collision->GetNodes(b, 2 | 32);


        m_details.Reset();
        m_details.velocityOld = dx;

        // before we do that... we have code handling collisions
        if (dx.y < 0 && m_details.below) {
            DescendSlope(dx);
        }
        if (!isEqual(dx.x, 0.0f))
            HorizontalCollisions(dx);
        if (!isEqual(dx.y, 0.0f))
            VerticalCollisions(dx);
        m_entity->Move(glm::vec3(dx.x, dx.y, 0));
    }
}

void Controller2D::HorizontalCollisions(glm::vec2& velocity) {

    float directionX = sign(velocity.x);// *m_gameObject->GetFlipX());
    float rayLength = fabs(velocity.x) + m_skinWidth;

    for (int i = 0; i < m_horizontalRayCount; i++) {
        vec2 rayOrigin = (directionX == -1) ? m_raycastOrigins.bottomLeft : m_raycastOrigins.bottomRight;
        rayOrigin += vec2(0.0f, 1.0f) * (i *m_horizontalRaySpacing);
        //RayCastHit2D hit = m_collision->Raycast(rayOrigin, glm::vec2(1, 0) * directionX, rayLength, 2);
        RayCastHit2D hit = m_collision->Raycast(glm::vec3(rayOrigin, 0.0f), glm::vec2(1.0f, 0.0f) * directionX, rayLength, 2);
        if (hit.collide) {

            float slopeAngle = angle(hit.normal, vec2(0, 1));
            if (i == 0 && (slopeAngle*rad2deg) <= m_maxClimbAngle) {
                if (m_details.descendingSlope) {
                    m_details.descendingSlope = false;
                    velocity = m_details.velocityOld;
                }
                //std::cout << "angle = " << slopeAngle * Rad2Deg << "\n";
                float distanceToSlopeStart = 0;
                if (slopeAngle != m_details.slopeAngleOld) {
                    distanceToSlopeStart = hit.length - m_skinWidth;
                    velocity.x -= distanceToSlopeStart * directionX;
                }
                ClimbSlope(velocity, slopeAngle);
                velocity.x += distanceToSlopeStart * directionX;

            }

            if (!m_details.climbingSlope || (slopeAngle*rad2deg) > m_maxClimbAngle) {
                velocity.x = (hit.length - m_skinWidth) *directionX;

                rayLength = hit.length;
                if (m_details.climbingSlope) {
                    velocity.y = tan(m_details.slopeAngle)* fabs(velocity.x);
                }
                m_details.left = directionX == -1;
                m_details.right = directionX == 1;
            }
            // this condition should go
            //if (hit.object != nullptr) {
            //	auto callback = m_wallCallback.find (hit.object->getCollisionResponseId());
            //	if (callback != m_wallCallback.end())
            //		callback->second->Run (m_target, hit.object, hit);
            //}
        }
    }

}

void Controller2D::ClimbSlope(glm::vec2& velocity, float slopeAngle) {
    float moveDistance = fabs(velocity.x);
    float climbVelocityY = sin(slopeAngle) * moveDistance;
    if (velocity.y <= climbVelocityY) {
        velocity.y = climbVelocityY;
        velocity.x = cos(slopeAngle) * moveDistance * sign(velocity.x);
        m_details.below = true;
        m_details.climbingSlope = true;
        m_details.slopeAngle = slopeAngle;
    }
}


void Controller2D::DescendSlope(glm::vec2& velocity) {
    //if (velocity.x == 0.0f)
     //   return;
    float directionX = sign(velocity.x);
    vec2 rayOrigin = ((directionX == -1) ? m_raycastOrigins.bottomRight : m_raycastOrigins.bottomLeft);
    //RayCastHit2D hit = m_collision->Raycast(rayOrigin, vec2(0, -1), 100.0f, m_platform != nullptr ? 2 | 32 : 2);
    RayCastHit2D hit = m_collision->Raycast(vec3(rayOrigin,0.0f), vec2(0, -1), 100.0f, m_platform != nullptr ? 2 | 32 : 2);
    if (hit.collide) {
        float slopeAngle = angle(hit.normal, vec2(0, 1));
        if (slopeAngle != 0 && slopeAngle <= m_maxDescendAngle) {
            if (sign(hit.normal.x) == directionX) {
                if (hit.length - m_skinWidth <= tan(slopeAngle) * fabs(velocity.x)) {
                    float moveDistance = fabs(velocity.x);
                    float descendVelocityY = sin(slopeAngle) * moveDistance;
                    velocity.x = cos(slopeAngle) * moveDistance * sign(velocity.x);
                    velocity.y -= descendVelocityY;
                    m_details.slopeAngle = slopeAngle;
                    m_details.descendingSlope = true;
                    m_details.below = true;
                }
            }
        }
    }
}

void Controller2D::VerticalCollisions(glm::vec2& velocity) {
    glm::vec2 originalVelocity = velocity;
    float directionY = sign(velocity.y);
    float rayLength = std::abs(velocity.y) + m_skinWidth;
    Entity* m_obstacle = nullptr;

    for (int i = 0; i < m_verticalRayCount; i++) {
        vec2 rayOrigin = (directionY == -1) ? m_raycastOrigins.bottomLeft : m_raycastOrigins.topLeft;
        rayOrigin += vec2(1, 0) * (i *m_verticalRaySpacing + velocity.x);
        int collMask = (directionY == -1 ? (2 | 32) : 2);
        RayCastHit2D hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), glm::vec2(0, 1) * directionY, rayLength, collMask);// (directionY == -1 ? m_collisionMaskDown : m_collisionMaskAny));
        //RayCastHit2D hit = Raycast(rayOrigin, glm::vec2(0, 1) * directionY, rayLength, collMask);// (directionY == -1 ? m_collisionMaskDown : m_collisionMaskAny));
        //RayCastHit2D hit;
        //hit.collide = true;
        //hit.length = 0;
        //hit.other = nullptr;
        if (hit.collide) {
            velocity.y = (hit.length - m_skinWidth) * directionY;
            rayLength = hit.length;

            if (m_details.climbingSlope) {
                velocity.x = (velocity.y / tan(m_details.slopeAngle)) * sign(velocity.x);
            }
            m_details.below = directionY == -1;
            m_details.above = directionY == 1;
            m_obstacle = hit.entity;
        }
    }
//    if (m_obstacle == nullptr) {
//        // no coll
//        for (int i = 0; i < m_verticalRayCount; i++) {
//            vec2 rayOrigin = (directionY == -1) ? m_raycastOrigins.bottomLeft : m_raycastOrigins.topLeft;
//            rayOrigin += vec2(1, 0) * (i *m_verticalRaySpacing + velocity.x);
//            int collMask = (directionY == -1 ? (2 | 32) : 2);
//            RayCastHit2D hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), glm::vec2(0, 1) * directionY, rayLength, collMask);// (directionY == -1 ? m_collisionMaskDown : m_collisionMaskAny));
//
//        }
//    }


    if (m_details.climbingSlope) {
        float directionX = sign(velocity.x);
        rayLength = fabs(velocity.x) + m_skinWidth;
        vec2 rayOrigin = ((directionX == -1) ? m_raycastOrigins.bottomLeft : m_raycastOrigins.bottomRight) + vec2(0, 1) * velocity.y;
        //RayCastHit2D hit = m_collision->Raycast(rayOrigin, vec2(1, 0) * directionX, rayLength, 2);
        RayCastHit2D hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), vec2(1, 0) * directionX, rayLength, 2);
        if (hit.collide) {
            float slopeAngle = angle(hit.normal, vec2(0, 1));
            if (slopeAngle != m_details.slopeAngle) {
                velocity.x = (hit.length - m_skinWidth) * directionX;
                m_details.slopeAngle = slopeAngle;
            }
        }
    }

    // for tomorrow

    // if I land on a platform, need to register if it's a moving platform
    if (m_details.below && m_platform != m_obstacle && m_obstacle != nullptr) {
        // notify platform that I'm on top of it
        if (m_platform != nullptr) {
            auto platformController = m_platform->GetComponent<PlatformComponent>();
            if (platformController != nullptr)
                platformController->Unregister(this);
        }

        auto platformController = m_obstacle->GetComponent<PlatformComponent>();
        if (platformController != nullptr) {
            m_platform = m_obstacle;
            platformController->Register(this);
        }
    }
    // leave a platform
    if (!m_details.below && m_platform != nullptr) {
        //auto platformController = m_platform->GetComponent<PlatformComponent>();
        //if (platformController != nullptr)
        //	platformController->Unregister(this);
        //m_platform = nullptr;
        DetachFromPlatform();
    }
    ////// hit a platform from below... platform decides what to do
    //if (m_details.above) {
    //	auto platformController = m_obstacle->GetComponent<PlatformComponent>();
    //	platformController->Collide(this, originalVelocity);
    //	//	auto platformController = m_obstacle->GetChildByTag<PlatformController>(PlatformController::Tag);
    //	//	//auto platformController = Store::GetFromTag<PlatformController>(1234);
    //	//	if (platformController != nullptr)
    //	//		platformController->HitFromBelow(this, m_target);
    //	//	m_platform = nullptr;
    //}

}

void Controller2D::DetachFromPlatform() {
    if (m_platform != nullptr) {
        auto platformController = m_platform->GetComponent<PlatformComponent>();
        if (platformController != nullptr)
            platformController->Unregister(this);
        m_platform = nullptr;
    }
}
Controller2D::~Controller2D() {
    DetachFromPlatform();
}