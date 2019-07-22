#pragma once

#include <unordered_map>
#include <unordered_set>
#include "gfx/components/collider.h"
#include "gfx/hashpair.h"
#include <gfx/collisionresponse.h>
#include "gfx/math/intersect.h"
#include "gfx/runner.h"

class ICollisionEngine : public Runner {
public:
    ICollisionEngine();
    virtual void Add (ICollider*) = 0;
    virtual void Remove(ICollider*) = 0;
    virtual void Move(ICollider*) = 0;
    virtual void Clear() = 0;
    virtual RayCastHit Raycast (glm::vec3 rayOrigin, glm::vec3 rayDir, float length, int mask) = 0;
    virtual ICollider* ShapeCast (std::shared_ptr<Shape>, const glm::mat4& transform, int mask) = 0;
    void SetResponseManager(std::unique_ptr<CollisionResponseManager>);
    CollisionResponseManager* GetResponseManager();
protected:
    std::unique_ptr<CollisionResponseManager> m_responseManager;
};

