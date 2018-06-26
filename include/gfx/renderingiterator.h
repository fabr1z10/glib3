#pragma once

#include <gfx/iterator.h>
#include <gfx/entity.h>

struct CameraInfo {
    Entity* entity;
    Camera* camera;
    glm::vec4 viewport;
};

class RenderingIterator {
public:
    RenderingIterator() {}
    RenderingIterator(Entity* root) {
        m_iter.m_stack.push(root);
        HandleCamera();
        // custom operation here
    }


    RenderingIterator& operator++() {
        // just fwd this call to the inner iterator
        ++m_iter;
        // do check
        HandleCamera();
        return *this;
    }

    Entity& operator*() {
        return *m_iter;
    }

    Entity* operator->()
    { return m_iter.operator->(); }


    bool operator== (const RenderingIterator& rhs) {
        return (m_iter == rhs.m_iter);
    }

    bool operator!= (const RenderingIterator& rhs) {
        return !(operator==(rhs));
    }

    Camera* GetCamera();
    void HandleCamera();
private:
    DepthFirstIterator<Entity> m_iter;
    std::stack<CameraInfo> m_viewportStack;
};


