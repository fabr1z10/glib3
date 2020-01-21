#pragma once

#include <unordered_map>
#include <unordered_set>
#include <monkey/components/collider.h>
#include <monkey/hashpair.h>
#include <monkey/collisionresponse.h>
#include <monkey/math/intersect.h>
#include <monkey/icollisionengine.h>
#include <monkey/math/shape3d.h>

struct CollisionEngine3DCell {
    bool dirty;
    std::unordered_set<ICollider*> colliders;
};

struct Location3D {
    int x0, x1, y0, y1, z0, z1;
    bool operator == (const Location3D& l) const {
        return (x0 == l.x0 && x1 == l.x1 && y0 == l.y0 && y1 == l.y1 && z0 == l.z0 && z1 == l.z1);
    }
    bool operator!= (const Location3D& l) const {
        return !(this->operator==(l));
    }
};

struct CollisionInfo3D {
    CollisionReport report;
    int i, j;
};

class CollisionEngine3D : public ICollisionEngine {
public:
    CollisionEngine3D (float dx, float dy, float dz);
    ~CollisionEngine3D() override {}
    void Add (ICollider*) override;
    void Remove(ICollider*) override;
    void Move(ICollider*) override;
    void Clear() override;
    Location3D GetLocation(const Bounds& b);
    void PopCollider(ICollider*);
    void PushCollider(ICollider*, Location3D);
    // runner implementation
    void Update(double) override;
    using ParentClass = CollisionEngine3D;
    // Casts a ray against colliders in the scene.
    // A raycast is conceptually like a laser beam that is fired from a point in space along a particular direction.
    // Any object making contact with the beam can be detected and reported.
    // This function returns a RaycastHit object with a reference to the collider that is hit by the ray
    // (the collider property of the result will be NULL if nothing was hit). The layerMask can be used to detect objects selectively only on certain layers (this allows you to apply the detection only to enemy characters, for example).
    RayCastHit Raycast (glm::vec3 rayOrigin, glm::vec3 rayDir, float length, int mask, bool use_z = false) override ;
    ShapeCastHit ShapeCast (std::shared_ptr<Shape>, const glm::mat4& transform, int mask) override;

    std::string toString() override ;
    std::type_index GetType() override;
    glm::ivec3 getCell(glm::vec3);
private:
    void helperLoc(float x0, float x1, int& a, int& b, float size);
    std::unordered_map<glm::ivec3, CollisionEngine3DCell> m_cells;
    std::unordered_map<ICollider*, Location3D> m_colliderLocations;
    float m_width;
    float m_height;
    float m_depth;
    std::unique_ptr<Intersector> m_intersector;
    std::unordered_map<std::pair<ICollider*, ICollider*>, CollisionInfo3D> m_previouslyCollidingPairs;
    float m_eps;
};

