#define GLM_ENABLE_EXPERIMENTAL

#include <monkey/components/controller2d.h>
#include <glm/gtx/vector_angle.hpp>
#include <monkey/error.h>
#include <monkey/engine.h>
#include <monkey/collisionengine.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>
#include <monkey/components/platform.h>
#include <iostream>
#include <monkey/math/geomalgo.h>

using namespace glm;

Controller2D::Controller2D(const ITable &t) {
    m_maxClimbAngle = t.get<float>("maxClimbAngle");
    m_maxDescendAngle = t.get<float>("maxDescendAngle");
    m_horizontalRayCount = t.get<int>("horRays", 4);
    m_verticalRayCount = t.get<int>("vertRays", 4);
    m_skinWidth = t.get<float>("skinWidth", .015f);
    m_maskUp = t.get<int>("maskUp");
    m_maskDown = t.get<int>("maskDown");
    m_platform = nullptr;
    //mint maskUp = table.Get<int>("maskup", 2);
    //int maskDown = table.Get<int>("maskdown", 2|32);
    //return std::make_shared<Controller2D>(maxClimbAngle, maxDescendAngle, maskUp, maskDown, skinWidth, horCount, vertCount);
	m_halfSize = t.get<glm::vec2>("size");
	m_horizontalRaySpacing = (2.0f * m_halfSize[1]) / (m_horizontalRayCount - 1);
	m_verticalRaySpacing = (2.0f * m_halfSize[0]) / (m_verticalRayCount - 1);
}



void Controller2D::Start() {
    m_details.Reset();
    m_collision = Engine::get().GetRunner<ICollisionEngine>();
    if (m_collision == nullptr)
        GLIB_FAIL("Controller2D requires a collision engine running!");
}

void Controller2D::Begin() {
//    m_cc =  m_entity->GetComponent<ICollider>();
//    if (m_cc == nullptr) {
//        GLIB_FAIL("The controller2D requires a collider!");
//    }
//    // recalc ray spacing when shape changes
//    m_cc->onShapeChange.Register(this, [&] (ICollider* c) {
//        CalculateRaySpacing();
//    });
    //m_cc->onShapeChanged.Register(this, [&] (Collider* c) { this->ResetShape(c); });
    //CalculateRaySpacing();
	//UpdateRaycastOrigins();
}




//void Controller2D::CalculateRaySpacing() {
//
//    // Bounds bounds = m_cc->GetDynamicBounds();
//    Bounds bounds = m_cc->getControllerBounds();
//    bounds.Expand(m_skinWidth * -2);
//    m_horizontalRaySpacing = bounds.GetSize().y / (m_horizontalRayCount - 1);
//    m_verticalRaySpacing = bounds.GetSize().x / (m_verticalRayCount - 1);
//    //std::cout <<"ray spacing = "<< m_horizontalRaySpacing << ","<<m_verticalRaySpacing<<"\n";
//}

//void Controller2D::UpdateRaycastOrigins() {
//	if (m_cc != nullptr) {
//		//Bounds bounds = m_cc->GetDynamicBounds();
//		Bounds bounds = m_cc->getControllerBounds();
//		bounds.Expand(m_skinWidth * -2);
//		m_raycastOrigins.bottomLeft = vec2(bounds.min.x, bounds.min.y);
//		m_raycastOrigins.bottomRight = vec2(bounds.max.x, bounds.min.y);
//		m_raycastOrigins.topLeft = vec2(bounds.min.x, bounds.max.y);
//		m_raycastOrigins.topRight = vec2(bounds.max.x, bounds.max.y);
//	}
//}

bool Controller2D::IsFalling(int dir) {
	glm::vec2 pos = m_entity->GetPosition();
	glm::vec2 rayOrigin = pos + glm::vec2(dir==-1 ? -m_halfSize[0] : -m_halfSize[0], -m_halfSize[1]);
    //glm::vec2 rayOrigin = (dir == -1) ? m_raycastOrigins.bottomLeft : m_raycastOrigins.bottomRight;
    RayCastHit hit = m_collision->Raycast(glm::vec3(rayOrigin, 0.0f), monkey::down, 5.0, 2|32);
    if (!hit.collide)
        return true;
    return false;
}


void Controller2D::Move(glm::vec3& delta) {
glm::vec2 dx(delta);
    float scale = m_entity->GetScale();
    if (dx != vec2(0.0f)) {

        m_wasGnd = m_details.below;
        m_details.Reset();
        m_details.velocityOld = dx;

        // before we do that... we have code handling collisions
        if (dx.y < 0 && m_wasGnd) {
            DescendSlope(dx);
        }
        //std::cout << m_raycastOrigins.bottomLeft.y << "\n";
        if (!isEqual(dx.x, 0.0f))
            HorizontalCollisions(dx);
        if (!isEqual(dx.y, 0.0f))
            VerticalCollisions(dx);
        glm::vec2 actualMove = dx / scale;
        m_entity->MoveLocal(glm::vec3(actualMove.x, actualMove.y, 0));
        if (!m_wasGnd && m_details.below) {
            glm::vec3 p=m_entity->GetPosition();
            //std::cout << "AFTER+++ " << p.x << "," << p.y << std::endl;
        }
    }
}

void Controller2D::HorizontalCollisions(glm::vec2& velocity) {

    bool flipx = m_entity->GetFlipX();
    bool facingLeft = (flipx && velocity.x > 0) || (!flipx && velocity.x < 0);
    float directionX = facingLeft ? -1.0 : 1.0;
    float rayLength = fabs(velocity.x) + m_skinWidth;

	glm::vec2 pos = m_entity->GetPosition();
	vec2 r0 = pos + glm::vec2(facingLeft ? - m_halfSize[0] : m_halfSize[0], -m_halfSize[1]);

    for (int i = 0; i < m_horizontalRayCount; i++) {
        vec2 rayOrigin = r0 + vec2(0.0f, i * m_horizontalRaySpacing);

		//RayCastHit2D hit = m_collision->Raycast(rayOrigin, glm::vec2(1, 0) * directionX, rayLength, 2);
        RayCastHit hit = m_collision->Raycast(glm::vec3(rayOrigin, 0.0f), monkey::right * directionX, rayLength, 2 | 32);
        if (hit.collide) {

            float slopeAngle = angle(hit.normal, vec2(0, 1));
            //std::cout << "SLOPE ANGLE = " << rad2deg*slopeAngle << std::endl;
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
                velocity.x = (hit.length - m_skinWidth) * sign(velocity.x);

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
    //float directionX = sign(velocity.x);
    bool flipx = m_entity->GetFlipX();
    bool facingLeft = (flipx && velocity.x > 0) || (!flipx && velocity.x < 0);
    float directionX = facingLeft ? -1.0 : 1.0;

	glm::vec2 pos = m_entity->GetPosition();
	vec2 r0 = pos + glm::vec2(facingLeft ? m_halfSize[0] : -m_halfSize[0], -m_halfSize[1]);
    RayCastHit hit = m_collision->Raycast(vec3(r0, 0.0f), monkey::down, 100.0f, 2 | 32);
    if (hit.collide) {
        float slopeAngle = angle(hit.normal, vec2(0, 1));
        //std::cout << "DESCEND SLOPE, angle = " << rad2deg * slopeAngle << "\n";
        if (slopeAngle != 0 && slopeAngle <= m_maxDescendAngle) {
            if (sign(hit.normal.x) == directionX) {
                if (hit.length - m_skinWidth <= tan(slopeAngle) * fabs(velocity.x)) {
                    float moveDistance = fabs(velocity.x);
                    float descendVelocityY = sin(slopeAngle) * moveDistance;
                    velocity.x = cos(slopeAngle) * moveDistance;// * sign(velocity.x);
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
    float directionY = sign(velocity.y);
    float rayLength = std::abs(velocity.y) + m_skinWidth;
    Entity* m_obstacle = nullptr;
    float velx = velocity.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);
	glm::vec2 pos = m_entity->GetPosition();
	vec2 r0 = pos + vec2(-m_halfSize[0], directionY > 0 ? m_halfSize[1] : -m_halfSize[1]);

    for (int i = 0; i < m_verticalRayCount; i++) {
		vec2 rayOrigin = r0 + vec2(1,0) * (velx + i * m_verticalRaySpacing);

        int collMask = (directionY == -1 ? (m_maskDown) : m_maskUp);
        RayCastHit hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), monkey::up * directionY, rayLength, collMask);
        if (hit.collide) {
            velocity.y = (hit.length - m_skinWidth) * directionY;
            rayLength = hit.length;


            if (m_details.climbingSlope) {
                velocity.x = (velocity.y / tan(m_details.slopeAngle)) * sign(velocity.x);
            }
            m_details.below = directionY == -1;
            m_details.above = directionY == 1;
            m_obstacle = hit.entity->GetObject();
        }
    }

    // cast an extra ray at the bottom
//    if (velocity.y < 0 && !m_details.descendingSlope) {
//        vec2 rayOrigin = m_raycastOrigins.bottomLeft + vec2(0.0f, velocity.y);
//        float length = m_raycastOrigins.bottomRight.x - m_raycastOrigins.bottomLeft.x;
//        RayCastHit2D hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), vec2(1.0f, 0.0f), length, 2 | 32);
//        if (hit.collide) {
//            auto m = hit.entity->GetObject()->GetWorldTransform();
//            Shape * s = hit.entity->GetShape();
//            glm::vec2 platformProjection = s->project(glm::vec2(0, 1), m);
//            glm::vec2 charProjection (rayOrigin.y, m_raycastOrigins.topLeft.y + velocity.y);
//            float overlap = ComputeOverlap(charProjection, platformProjection);
//            std::cout << "vy = " << velocity.y << ", Overlap is = " << overlap << "\n";
//            velocity.y += overlap;
//            m_details.below = true;
//            m_obstacle = hit.entity->GetObject();
//        }
//
//    }



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
        vec2 pos = m_entity->GetPosition();
        vec2 rayOrigin = pos + vec2( (directionX == -1) ? -m_halfSize[0] : m_halfSize[0], -m_halfSize[1]);
        rayOrigin += vec2(0, 1) * velocity.y;
        //RayCastHit2D hit = m_collision->Raycast(rayOrigin, vec2(1, 0) * directionX, rayLength, 2);
        RayCastHit hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), monkey::right * directionX, rayLength, 2);
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

void Controller2D::setMask(int maskUp, int maskDown) {
    m_maskDown = maskDown;
    m_maskUp = maskUp;
}