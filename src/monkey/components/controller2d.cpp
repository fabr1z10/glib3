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
//#include <monkey/meshfactory.h>
#include <monkey/components/renderer.h>
#include <monkey/model/factory.h>

using namespace glm;

Controller2D::Controller2D(const ITab& t) : IController(t) {
    m_maxClimbAngle = t.get<float>("maxClimbAngle", 80);
    m_maxDescendAngle = t.get<float>("maxDescendAngle", 80);
    m_horizontalRayCount = t.get<int>("horRays", 4);
    m_verticalRayCount = t.get<int>("vertRays", 4);
    m_skinWidth = t.get<float>("skinWidth", .015f);
    m_maskUp = t.get<int>("mask_up");
    m_maskDown = t.get<int>("mask_down");
    //m_platform = nullptr;
    //mint maskUp = table.Get<int>("maskup", 2);
    //int maskDown = table.Get<int>("maskdown", 2|32);
    //return std::make_shared<Controller2D>(maxClimbAngle, maxDescendAngle, maskUp, maskDown, skinWidth, horCount, vertCount);
	m_horizontalRaySpacing = (2.0f * m_halfSize[1]) / (m_horizontalRayCount - 1);
	m_verticalRaySpacing = (2.0f * m_halfSize[0]) / (m_verticalRayCount - 1);
}


void Controller2D::drawShape() {
    auto debugEntity = std::make_shared<Entity>();
    auto model = ModelFactory::rect(
            m_halfSize[0] * 2.0f,
            m_halfSize[1] * 2.0f,
            glm::vec2(-m_halfSize[0] + m_shift[0], -m_halfSize[1] + m_shift[1]),
            RenderType::WIREFRAME,
            glm::vec4(1.0f));
    auto renderer = model->makeRenderer(model);
    debugEntity->AddComponent(renderer);
    m_entity->AddChild(debugEntity);
    m_debugShape = debugEntity.get();
}

void Controller2D::Start() {
    m_details.Reset();
    m_collision = Engine::get().GetRunner<ICollisionEngine>();
    if (m_collision == nullptr)
        GLIB_FAIL("Controller2D requires a collision engine running!");
    if (m_debug) {
        drawShape();


    }
    //m_entity->onMove.Register(this, [&] (Entity*) { this->updateRaycastOrigins(); });

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
void Controller2D::Update(double dt) {
    m_forcedMove = glm::vec2(0.0f);
}

void Controller2D::updateRaycastOrigins() {
	auto scale = m_entity->GetScale();
	glm::vec3 pos = m_entity->GetPosition();
	pos += scale * m_shift;
	auto scaledHalfsize = scale * m_halfSize;
	m_horizontalRaySpacing = (2.0f * scaledHalfsize[1]) / (m_horizontalRayCount - 1);
	m_verticalRaySpacing = (2.0f * scaledHalfsize[0]) / (m_verticalRayCount - 1);

	m_raycastOrigins.bottomLeft = pos - scaledHalfsize;
	m_raycastOrigins.bottomRight = pos + glm::vec3(scaledHalfsize[0], -scaledHalfsize[1], 0.0f);
	m_raycastOrigins.topLeft = pos + vec3(-scaledHalfsize[0], scaledHalfsize[1], 0.0f);
	m_raycastOrigins.topRight = pos + scaledHalfsize;
}

bool Controller2D::IsFalling(int dir) {
	//glm::vec2 pos = m_entity->GetPosition();
	//glm::vec2 rayOrigin = pos + glm::vec2(dir==-1 ? -m_halfSize[0] : -m_halfSize[0], -m_halfSize[1]);
    updateRaycastOrigins();
	auto rayOrigin = (dir == -1 ? m_raycastOrigins.bottomLeft : m_raycastOrigins.bottomRight);

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
		updateRaycastOrigins();
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
        //std::cout << "moving by " << actualMove.x << ", " << actualMove.y << "\n";
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
	float sgnx = sign(velocity.x);
	//glm::vec2 pos = m_entity->GetPositfion();
	//vec2 r0 = pos + glm::vec2(facingLeft ? - m_halfSize[0] : m_halfSize[0], -m_halfSize[1]);

	vec2 r0 = facingLeft ? m_raycastOrigins.bottomLeft : m_raycastOrigins.bottomRight;
	//std::cout << "r0 = " << r0.x << ", " << r0.y << "\n";
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
                velocity.x = std::max(hit.length - m_skinWidth, 0.0f) * sgnx;
                //std::cerr << "ray " << i << " " << hit.length  << ", velx = " << velocity.x << "\n";
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

	//glm::vec2 pos = m_entity->GetPosition();
	//vec2 r0 = pos + glm::vec2(facingLeft ? m_halfSize[0] : -m_halfSize[0], -m_halfSize[1]);
	vec2 r0 = facingLeft ? m_raycastOrigins.bottomRight : m_raycastOrigins.bottomLeft;

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

    float obstacleDistance = std::numeric_limits<float>::max();
    std::unordered_set<Entity*> obstacles;

    float velx = velocity.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);
    //glm::vec2 pos = m_entity->GetPosition();
    //vec2 r0 = pos + vec2(-m_halfSize[0], directionY > 0 ? m_halfSize[1] : -m_halfSize[1]);

    vec2 r0 = directionY > 0 ? m_raycastOrigins.topLeft : m_raycastOrigins.bottomLeft;
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
            // only do this if going DOWN!!!!
            if (directionY < 0.0f) {
                if (hit.length < obstacleDistance) {
                    obstacles.clear();
                    obstacleDistance = hit.length;
                }
                //std::cout << "hitting " << hit.entity->GetObject() << " with dist " << hit.length << " \n";
                obstacles.insert(hit.entity->GetObject());
            }

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

    // TODO do we need this???
//    if (m_details.climbingSlope) {
//        float directionX = sign(velocity.x);
//        rayLength = fabs(velocity.x) + m_skinWidth;
//        vec2 pos = m_entity->GetPosition();
//        vec2 rayOrigin = pos + vec2( (directionX == -1) ? -m_halfSize[0] : m_halfSize[0], -m_halfSize[1]);
//        rayOrigin += vec2(0, 1) * velocity.y;
//        //RayCastHit2D hit = m_collision->Raycast(rayOrigin, vec2(1, 0) * directionX, rayLength, 2);
//        RayCastHit hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), monkey::right * directionX, rayLength, 2);
//        if (hit.collide) {
//            float slopeAngle = angle(hit.normal, vec2(0, 1));
//            if (slopeAngle != m_details.slopeAngle) {
//                velocity.x = (hit.length - m_skinWidth) * directionX;
//                m_details.slopeAngle = slopeAngle;
//            }
//        }
//    }

    // for tomorrow
    //std::cout << "cane: " << obstacles.size() <<  " " << m_platforms.size() << "\n";
    // unregister to ALL platforms I am not on top anymore
    if (!m_platforms.empty()) {
        auto j = m_platforms.begin();
        while (j != m_platforms.end()) {
            auto i = obstacles.begin();
            bool found = false;
            while (i != obstacles.end())
            {
                if ((*j)->GetId() == (*i)->GetId()) {
                    // ok, this means o is already registered
                    obstacles.erase(i++);
                    found = true;
                    break;
                } else {
                    i++;
                }
            }
            if (!found) {
                // unregister
                auto platformController = (*j)->GetComponent<PlatformComponent>();
                platformController->Unregister(this);
                m_platforms.erase(j++);
            } else {
                j++;
            }
        }
    }

    // register to new platforms
    for (const auto& o : obstacles) {
        auto platformController = o->GetComponent<PlatformComponent>();
        if (platformController != nullptr) {
            platformController->Register(this);
            m_platforms.push_back(o);
        }

    }


    for (const auto& p : m_platforms) {
        std::cout << m_entity->GetId() << " on top of " << p->GetId() << "\n";
    }

}

void Controller2D::ForceDetach(Entity * e) {
    m_platforms.remove(e);
}

//void Controller2D::DetachFromPlatform() {
//    if (m_platform != nullptr) {
//        auto platformController = m_platform->GetComponent<PlatformComponent>();
//        if (platformController != nullptr)
//            platformController->Unregister(this);
//        m_platform = nullptr;
//    }
//}
Controller2D::~Controller2D() {
    for (const auto& p : m_platforms) {
        p->GetComponent<PlatformComponent>()->Unregister(this);
    }
}

void Controller2D::setMask(int maskUp, int maskDown) {
    m_maskDown = maskDown;
    m_maskUp = maskUp;
}

void Controller2D::forceMove(glm::vec2 delta) {
    // move the entity by some amount
    glm::vec2 incrementalMove = delta - m_forcedMove;
    m_forcedMove += incrementalMove;
    m_entity->MoveOrigin(incrementalMove);

}