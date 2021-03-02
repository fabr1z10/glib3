#define GLM_ENABLE_EXPERIMENTAL

#include <monkey/components/controller3d.h>
#include <glm/gtx/vector_angle.hpp>
#include <monkey/error.h>
#include <monkey/engine.h>
#include <monkey/geom3d/collisionengine3d.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>
#include <monkey/components/platform.h>
#include <iostream>
#include <monkey/math/geomalgo.h>
#include <glm/gtx/vector_angle.hpp>

using namespace glm;


Controller3D::Controller3D(const ITable & t) {

    m_horizontalRayCount = t.get<int>("hor_raycount");
    auto size = t.get<glm::vec2>("size");
    // half sizes
    m_widthX = 0.5f * size.x;
    m_widthZ = 0.5f * size.y;
    m_horXSpacing = size.y / (m_horizontalRayCount - 1);
    m_horZSpacing = size.x / (m_horizontalRayCount - 1);


}

void Controller3D::Start() {
    m_engine = Engine::get().GetRunner<ICollisionEngine>();
    if (m_engine == nullptr)
        GLIB_FAIL("Controller3D requires a collision engine running!");
}

void Controller3D::Begin() {

}

void Controller3D::CalculateRaySpacing() {
}

void Controller3D::UpdateRaycastOrigins() {
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
        //UpdateRaycastOrigins();
        //m_ppp.clear();
        bool movingHorizontally = !isEqual(dx.x, 0.0f) || !isEqual(dx.z, 0.0f);
        if (movingHorizontally)
            HorizontalCollisions(dx);
        if (!isEqual(dx.y, 0.0f))
            VerticalCollisions(dx);
        glm::vec3 actualMove = dx / scale;
        m_entity->MoveLocal(actualMove);
//        if (m_details.climbingSlope) {
//            UpdateRaycastOrigins();
//            std::cerr << m_raycastOrigins.topRight.x << ", " << m_raycastOrigins.bottomLeft.y << ", " << m_raycastOrigins.topRight.x*tan() << "\n";
//
//        }
        if (!m_wasGnd && m_details.below) {
            glm::vec3 p=m_entity->GetPosition();
            // std::cout << "AFTER+++ " << p.x << "," << p.y << std::endl;
        }

    }
}

//void Controller3D::DescendSlope(glm::vec3& vel) {
//    float dxw = vel.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);
//    glm::vec3 horizontalShift(dxw, 0.0f, vel.z);
//    //glm::vec3 horizontalDir = glm::normalize(horizontalShift);
//    glm::vec3 horizontalDir = glm::normalize(glm::vec3(vel.x, 0, vel.z));
//
//    float hLength = glm::length(horizontalShift);
//
//    glm::vec3 rayOrigin;
//    rayOrigin.x = isZero(dxw) ? m_raycastOrigins.xMid() : ( (dxw < 0) ? m_raycastOrigins.xRight() : m_raycastOrigins.xLeft());
//    rayOrigin.y = m_raycastOrigins.yBottom();
//    rayOrigin.z = isZero(vel.z) ? m_raycastOrigins.zMid() : ( (vel.z < 0) ? m_raycastOrigins.zFront() : m_raycastOrigins.zBack());
//
//    RayCastHit hit = m_engine->Raycast(rayOrigin, monkey::down, 1000.0f, 2 | 32);
//    if (hit.collide) {
//        float slopeAngle = glm::angle(hit.normal, monkey::up);
//
//        if (!isZero(slopeAngle) && slopeAngle*rad2deg <= m_maxDescendAngle) {
//            // check if this is a slope, this replaces
//            // isDescending = (Mathf.sign(hit.normal.x) == directionX)
//            bool isDescending = (glm::dot (horizontalShift, hit.normal) > 0);
//            if (isDescending) {
////                if (isZero(dxw)) {
////                int kkfkf=20;
////                }
////                if (isZero(vel.z)) {
////                    int ikk = 10;
////                }
//                if (hit.length - m_skinWidth <= tan(slopeAngle) * hLength) {
//                    // it's close enough
//                    float descendVelocityY = sin(slopeAngle) * hLength;
//                    vel.x = horizontalDir.x * cos(slopeAngle) * hLength;
//                    vel.z = horizontalDir.z * cos(slopeAngle) * hLength;
//                    vel.y -= descendVelocityY;
//                    m_details.below = true;
//                }
//            }
//        }
//
//    }
//}

// this will have x and z components
void Controller3D::HorizontalCollisions(glm::vec3& vel) {
	bool flipx = m_entity->GetFlipX();
	bool facingLeft = (flipx && vel.x > 0) || (!flipx && vel.x < 0);
	float directionX = facingLeft ? -1.0 : 1.0;
	float rayLength = fabs(vel.x) + m_skinWidth;
	auto pos = m_entity->GetPosition();
	float dx = facingLeft ? -m_halfSize[0] : m_halfSize[0];
	std::array<glm::vec3, 4> raycastOrigins = {
			pos + glm::vec3(dx, -m_halfSize[1], -m_halfSize[2]),
			pos + glm::vec3(dx, -m_halfSize[1], m_halfSize[2]),
			pos + glm::vec3(dx, m_halfSize[1], -m_halfSize[2]),
			pos + glm::vec3(dx, m_halfSize[1], m_halfSize[2])};

	int i = 0;
	// try first moving along X direction
	for (const auto& r0 : raycastOrigins) {

		RayCastHit hit = m_collision->Raycast(r0, monkey::right * directionX, rayLength, 2 | 32);
		if (hit.collide) {
			float slopeAngle = angle(hit.normal, vec2(0, 1));
			//std::cout << "SLOPE ANGLE = " << rad2deg*slopeAngle << std::endl;
			if (i < 2 && (slopeAngle*rad2deg) <= m_maxClimbAngle) {
				if (m_details.descendingSlope) {
					m_details.descendingSlope = false;
					// TODO vel = m_details.velocityOld;
				}
				float distanceToSlopeStart = 0;
				if (slopeAngle != m_details.slopeAngleOld) {
					distanceToSlopeStart = hit.length - m_skinWidth;
					vel.x -= distanceToSlopeStart * directionX;
				}
				ClimbSlope(vel, slopeAngle);
				vel.x += distanceToSlopeStart * directionX;

			}

			if (!m_details.climbingSlope || (slopeAngle*rad2deg) > m_maxClimbAngle) {
				vel.x = (hit.length - m_skinWidth) * sign(vel.x);
				rayLength = hit.length;
				if (m_details.climbingSlope) {
					vel.y = tan(m_details.slopeAngle) * fabs(vel.x);
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

void Controller3D::ClimbSlope(glm::vec3& velocity, float slopeAngle) {
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

void Controller3D::VerticalCollisions(glm::vec3& velocity) {


}

