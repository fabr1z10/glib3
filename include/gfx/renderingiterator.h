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
    RenderingIterator(bool setCameras = true) : m_setCameras{setCameras}, m_changeCamera{false} {}
    RenderingIterator(Entity* root, bool setCameras = true) : m_setCameras{setCameras}, m_changeCamera{false} {
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

    RenderingIterator& advanceSkippingChildren() {
        m_iter.advanceSkippingChildren();
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
    glm::vec4 GetCurrentViewport() const;
    void HandleCamera();
    bool changedCamera() const;
    bool hasActiveViewport () const;
private:
    bool m_setCameras;
    bool m_changeCamera;
    DepthFirstIterator<Entity> m_iter;
    std::stack<CameraInfo> m_viewportStack;
};

inline bool RenderingIterator::changedCamera() const {
    return m_changeCamera;
}

inline glm::vec4 RenderingIterator::GetCurrentViewport() const {
    return m_viewportStack.top().viewport;
}

inline bool RenderingIterator::hasActiveViewport () const {
    return !m_viewportStack.empty();
}