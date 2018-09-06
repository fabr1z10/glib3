#pragma once

#include "entity.h"
#include <graph/collisionreport.h>
#include <gfx/collider.h>
#include <unordered_map>
#include <memory>
#include <gfx/hashpair.h>

class Entity;



class CollisionResponse {
public:
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
    bool HasCollision(Collider*, Collider*) const;
    void onStart (Collider*, Collider*, CollisionReport&);
    void onStay (Collider*, Collider*, CollisionReport&);
    void onEnd (Collider*, Collider*, CollisionReport&);
private:
    CollisionHandler GetCollisionResponse(Collider*, Collider*) const;
    std::unordered_map<std::pair<int, int>, std::unique_ptr<CollisionResponse> > m_response;
};