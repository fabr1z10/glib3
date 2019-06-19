#pragma once

#include "entity.h"
#include <gfx/math/collisionreport.h>
#include <gfx/components/icollider.h>
#include <unordered_map>
#include <memory>
#include <gfx/hashpair.h>

class Entity;



class CollisionResponse {
public:
    virtual ~CollisionResponse() {}
    virtual void onStart (Entity*, Entity*, const CollisionReport& report) = 0;
    virtual void onEnd (Entity*, Entity*, const CollisionReport& report) = 0;
    virtual void onStay (Entity*, Entity*, const CollisionReport& report) = 0;
};

struct CollisionHandler {
    CollisionHandler() : response{nullptr}, flip{false} {}
    CollisionHandler(CollisionResponse* resp, bool f) : response(resp), flip(f) {}
    CollisionResponse* response;
    bool flip;
};

class CollisionResponseManager {
public:
    void AddCollisionResponse(int tag1, int tag2, std::unique_ptr<CollisionResponse>);
    bool HasCollision(ICollider*, ICollider*) const;
    void onStart (ICollider*, ICollider*, CollisionReport&);
    void onStay (ICollider*, ICollider*, CollisionReport&);
    void onEnd (ICollider*, ICollider*, CollisionReport&);
    CollisionHandler GetHandler (int tag1, int tag2);
private:
    CollisionHandler GetCollisionResponse(ICollider*, ICollider*) const;
    std::unordered_map<std::pair<int, int>, std::unique_ptr<CollisionResponse> > m_response;
};
