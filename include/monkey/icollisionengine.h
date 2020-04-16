#pragma once

#include <unordered_map>
#include <unordered_set>
#include <monkey/components/collider.h>
#include <monkey/hashpair.h>
#include <monkey/collisionresponse.h>
#include <monkey/math/intersect.h>
#include <monkey/runner.h>

class ICollisionEngine : public Runner {
public:
    ICollisionEngine();
    ICollisionEngine(const LuaTable& t) : Runner(t) {}
    ICollisionEngine(const ITable& t) : Runner(t) {}
    virtual void Add (ICollider*) = 0;
    virtual void Remove(ICollider*) = 0;
    virtual void Move(ICollider*) = 0;
    virtual void Clear() = 0;
    virtual RayCastHit Raycast (glm::vec3 rayOrigin, glm::vec3 rayDir, float length, int mask, bool use_z = false) = 0;
    virtual ShapeCastHit ShapeCast (std::shared_ptr<Shape>, const glm::mat4& transform, int mask) = 0;
    void SetResponseManager(std::unique_ptr<CollisionResponseManager>);
    CollisionResponseManager* GetResponseManager();
protected:
    std::unique_ptr<CollisionResponseManager> m_responseManager;
};

