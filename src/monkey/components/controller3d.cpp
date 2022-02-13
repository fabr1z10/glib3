//##define GLM_ENABLE_EXPERIMENTAL

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
#include <monkey/math/shapes3d/aabb.h>
#include <monkey/meshfactory.h>
#include <monkey/components/renderer.h>

using namespace glm;

Controller3D::Controller3D(glm::vec3 size, glm::vec3 shift, int maskUp, int maskDown, float skinWidth, float maxClimbAngle, float maxDescendAngle,
    bool debugShape) : IController(size, shift, debugShape), m_maxClimbAngle{maxClimbAngle}, m_maxDescendAngle{maxDescendAngle},
    m_skinWidth{skinWidth}, m_maskUp{maskUp}, m_maskDown{maskDown} {
}

Controller3D::Controller3D(const ITab & t) : IController(t) {

	m_maxClimbAngle = t.get<float>("maxClimbAngle");
	m_maxDescendAngle = t.get<float>("maxDescendAngle");
	m_skinWidth = t.get<float>("skinWidth", .015f);
	m_maskUp = t.get<int>("mask_up");
	m_maskDown = t.get<int>("mask_down");
	m_platform = nullptr;



}

void Controller3D::drawShape() {
    auto debugEntity = std::make_shared<Entity>();
    auto shape = std::make_shared<AABB>(2.0f * m_halfSize, glm::vec3(-m_halfSize.x, 0.0f, -m_halfSize.z));
    MeshFactory m;
    auto model = m.createWireframe(shape.get(), glm::vec4(1.0f));
    auto renderer = std::make_shared<Renderer>(model);
//        glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
//        renderer->setMultColor(color);
    debugEntity->AddComponent(renderer);
    m_entity->AddChild(debugEntity);
    m_debugShape = debugEntity.get();
}

void Controller3D::Start() {
	m_details.Reset();
    m_engine = Engine::get().GetRunner<ICollisionEngine>();
	m_collision = Engine::get().GetRunner<ICollisionEngine>();

	if (m_engine == nullptr)
        GLIB_FAIL("Controller3D requires a collision engine running!");
	if (m_debug) {
        drawShape();
	}

}

void Controller3D::Begin() {

}

void Controller3D::CalculateRaySpacing() {
}

void Controller3D::UpdateRaycastOrigins() {
	auto scale = m_entity->GetScale();
	glm::vec3 pos = m_entity->GetPosition();

	pos += scale * m_shift;
	auto scaledHalfSize = scale * m_halfSize;

	m_raycastOrigins.left = pos.x - scaledHalfSize.x;
	m_raycastOrigins.right = pos.x + scaledHalfSize.x;

	m_raycastOrigins.bottom = pos.y - scaledHalfSize.y;
	m_raycastOrigins.top = pos.y + scaledHalfSize.y;

	m_raycastOrigins.back = pos.z - scaledHalfSize.z;
	m_raycastOrigins.front = pos.z + scaledHalfSize.z;
}

bool Controller3D::IsFalling(int x, int z) {
//    //glm::vec3 rayOrigin = m_entity->GetPosition();
//    glm::vec3 rayOrigin;
//    rayOrigin.x = (x == 0 ? m_raycastOrigins.xMid() : (x > 0 ? m_raycastOrigins.xRight() : m_raycastOrigins.xLeft()));
//    rayOrigin.z = (z == 0 ? m_raycastOrigins.zMid() : (z > 0 ? m_raycastOrigins.zFront() : m_raycastOrigins.zBack()));
//    rayOrigin.y = m_raycastOrigins.yBottom();
//
//    RayCastHit hit = m_engine->Raycast(rayOrigin, monkey::down, 5.0, 2);
//    if (!hit.collide)
//        return true;
//    return false;
}
//bool Controller2D::IsFalling(int dir) {
//    glm::vec2 rayOrigin = (dir == -1) ? m_raycastOrigins.bottomLeft : m_raycastOrigins.bottomRight;
//    RayCastHit2D hit = m_collision->Raycast(glm::vec3(rayOrigin, 0.0f), glm::vec2(0.0f, -1.0f), 5.0, 2);
//    if (!hit.collide)
//        return true;
//    return false;
//}


void Controller3D::Move(glm::vec3& dx) {
    auto scale = m_entity->getScaleVec();
    if (dx != vec3(0.0f)) {
        UpdateRaycastOrigins();
		m_details.Reset();
        //m_ppp.clear();
        bool movingHorizontally = !isEqual(dx.x, 0.0f) || !isEqual(dx.z, 0.0f);
        if (movingHorizontally)
            HorizontalCollisions(dx);
        if (!isEqual(dx.y, 0.0f))
            VerticalCollisions(dx);
        glm::vec3 actualMove(dx.x / scale.x, dx.y/scale.y, dx.z/scale.z);
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
	if (fabs(vel.x) > 0.0f) {

		bool facingLeft = (flipx && vel.x > 0) || (!flipx && vel.x < 0);
		float directionX = facingLeft ? -1.0 : 1.0;
		float rayLength = fabs(vel.x) + m_skinWidth;
		auto pos = m_entity->GetPosition();
		float dx = facingLeft ? -m_halfSize[0] : m_halfSize[0];

		int i = 0;
		// try first moving along X direction
		float x = facingLeft ? m_raycastOrigins.left : m_raycastOrigins.right;
		std::array<glm::vec3, 2> raycastOrigins = {
				glm::vec3(x, m_raycastOrigins.bottom, m_raycastOrigins.front),
				glm::vec3(x, m_raycastOrigins.bottom, m_raycastOrigins.back)};

		for (const auto &r0 : raycastOrigins) {
			RayCastHit hit = m_collision->Raycast(r0, monkey::right * directionX, rayLength, 2 | 32);
			if (hit.collide) {
				float slopeAngle = glm::angle(hit.normal, glm::vec3(0.0f, 1.0f, 0.0f));
				//std::cout << "SLOPE ANGLE = " << rad2deg*slopeAngle << std::endl;
				if (slopeAngle * rad2deg <= m_maxClimbAngle) {
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

				if (!m_details.climbingSlope || (slopeAngle * rad2deg) > m_maxClimbAngle) {
					//float newVelX = std::max(hit.length - m_skinWidth, 0.0f) * sign(vel.x);
					//if (r0.x + newVelX > 8.0f) {
				//		std::cerr << "AH!\n";
				//	}
					vel.x = std::max(hit.length - m_skinWidth, 0.0f) * sign(vel.x);
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

	if (fabs(vel.z) > 0.0f) {
		float z = vel.z > 0 ? m_raycastOrigins.front : m_raycastOrigins.back;
		float directionZ = vel.z < 0 ? -1.0 : 1.0;
		glm::vec3 dirZ (0.0f, 0.0f, vel.z > 0 ? 1.0f : -1.0f);
		float dx = vel.x * (flipx ? -1.0f : 1.0f);
		std::array<glm::vec3, 2> raycastOrigins = {
				glm::vec3(m_raycastOrigins.left + dx, m_raycastOrigins.bottom, z),
				glm::vec3(m_raycastOrigins.right + dx, m_raycastOrigins.bottom, z)};
		float rayLength = fabs(vel.z) + m_skinWidth;
		for (const auto &r0 : raycastOrigins) {
			RayCastHit hit = m_collision->Raycast(r0, glm::vec3(0.0f, 0.0f, 1.0f) * directionZ, rayLength, 2 | 32);
			if (hit.collide) {
				float slopeAngle = glm::angle(hit.normal, glm::vec3(0.0f, 1.0f, 0.0f));
				//std::cout << "SLOPE ANGLE = " << rad2deg*slopeAngle << std::endl;
				if (slopeAngle * rad2deg <= m_maxClimbAngle) {
					if (m_details.descendingSlope) {
						m_details.descendingSlope = false;
						// TODO vel = m_details.velocityOld;
					}
					float distanceToSlopeStart = 0;
					if (slopeAngle != m_details.slopeAngleOld) {
						distanceToSlopeStart = hit.length - m_skinWidth;
						vel.z -= distanceToSlopeStart * directionZ;
					}
					ClimbSlopeZ(vel, slopeAngle);
					vel.z += distanceToSlopeStart * directionZ;
				}

				if (!m_details.climbingSlope || (slopeAngle * rad2deg) > m_maxClimbAngle) {
					vel.z = std::max(hit.length - m_skinWidth, 0.0f) * sign(vel.z);
					rayLength = hit.length;
					if (m_details.climbingSlope) {
						vel.y = tan(m_details.slopeAngle) * fabs(vel.z);
					}
					m_details.back = directionZ == -1;
					m_details.front = directionZ == 1;
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
void Controller3D::ClimbSlopeZ(glm::vec3& velocity, float slopeAngle) {
	float moveDistance = fabs(velocity.z);
	float climbVelocityY = sin(slopeAngle) * moveDistance;
	if (velocity.y <= climbVelocityY) {
		velocity.y = climbVelocityY;
		velocity.z = cos(slopeAngle) * moveDistance * sign(velocity.z);
		m_details.below = true;
		m_details.climbingSlope = true;
		m_details.slopeAngle = slopeAngle;
	}
}
void Controller3D::VerticalCollisions(glm::vec3& velocity) {

	float directionY = sign(velocity.y);
	float rayLength = std::abs(velocity.y) + m_skinWidth;
	Entity* m_obstacle = nullptr;

	float velx = velocity.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);
	float velz = velocity.z;
	glm::vec3 pos = m_entity->GetPosition();
	//vec2 r0 = pos + vec2(-m_halfSize[0], directionY > 0 ? m_halfSize[1] : -m_halfSize[1]);
	//auto pos = m_entity->GetPosition();
	//auto scale = m_entity->GetScale();
	//float dy = scale * (m_shift.y + (directionY > 0 ? m_halfSize[1] : -m_halfSize[1]));
	std::array<glm::vec3, 4> raycastOrigins = {
			glm::vec3(m_raycastOrigins.left + velx, m_raycastOrigins.bottom, m_raycastOrigins.front + velz),
			glm::vec3(m_raycastOrigins.right + velx, m_raycastOrigins.bottom,m_raycastOrigins.front + velz),
			glm::vec3(m_raycastOrigins.left + velx, m_raycastOrigins.bottom, m_raycastOrigins.back + velz),
			glm::vec3(m_raycastOrigins.right + velx, m_raycastOrigins.bottom,m_raycastOrigins.back + velz)};

	for (const auto& r0 : raycastOrigins) {
		int collMask = (directionY == -1 ? (m_maskDown) : m_maskUp);
		RayCastHit hit = m_collision->Raycast(r0, monkey::up * directionY, rayLength, collMask);
		if (hit.collide) {
			velocity.y = (hit.length - m_skinWidth) * directionY;
			rayLength = hit.length;
			rayLength = hit.length;
			if (m_details.climbingSlope) {
				velocity.x = (velocity.y / tan(m_details.slopeAngle)) * sign(velocity.x);
			}
			m_details.below = directionY == -1;
			m_details.above = directionY == 1;
			m_obstacle = hit.entity->GetObject();
		}
	}

	if (m_details.below == 0) {
		// leaving
		std::cout << "leaving platform\n";
	}


//	if (m_details.climbingSlope) {
//		float directionX = sign(velocity.x);
//		rayLength = fabs(velocity.x) + m_skinWidth;
//		vec2 pos = m_entity->GetPosition();
//		vec2 rayOrigin = pos + vec2( (directionX == -1) ? -m_halfSize[0] : m_halfSize[0], -m_halfSize[1]);
//		rayOrigin += vec2(0, 1) * velocity.y;
//		//RayCastHit2D hit = m_collision->Raycast(rayOrigin, vec2(1, 0) * directionX, rayLength, 2);
//		RayCastHit hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), monkey::right * directionX, rayLength, 2);
//		if (hit.collide) {
//			float slopeAngle = angle(hit.normal, vec2(0, 1));
//			if (slopeAngle != m_details.slopeAngle) {
//				velocity.x = (hit.length - m_skinWidth) * directionX;
//				m_details.slopeAngle = slopeAngle;
//			}
//		}
//	}
//
//	// for tomorrow
//
//	// if I land on a platform, need to register if it's a moving platform
//	if (m_details.below && m_platform != m_obstacle && m_obstacle != nullptr) {
//		// notify platform that I'm on top of it
//		if (m_platform != nullptr) {
//			auto platformController = m_platform->GetComponent<PlatformComponent>();
//			if (platformController != nullptr)
//				platformController->Unregister(this);
//		}
//
//		auto platformController = m_obstacle->GetComponent<PlatformComponent>();
//		if (platformController != nullptr) {
//			m_platform = m_obstacle;
//			platformController->Register(this);
//		}
//	}
//	// leave a platform
//	if (!m_details.below && m_platform != nullptr) {
//		//auto platformController = m_platform->GetComponent<PlatformComponent>();
//		//if (platformController != nullptr)
//		//	platformController->Unregister(this);
//		//m_platform = nullptr;
//		DetachFromPlatform();
//	}

}

