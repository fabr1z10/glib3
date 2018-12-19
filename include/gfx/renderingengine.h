//
//  renderingengine.h
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#ifndef renderingengine_h
#define renderingengine_h

#include <gfx/component.h>
#include <gfx/camera.h>
#include <gfx/listener.h>
#include <gfx/iterator.h>
#include <vector>
#include <stack>

// stack with extended push/pop functionalities
//class RenderingStack {
//public:
//    void push(Entity*);
//    void pop();
//    bool empty() const;
//    bool operator== (const RenderingStack& r) const {
//        return m_stack == r.m_stack;
//    }
//    Entity* top();
//    Camera* GetCamera() {
//        return (m_cameras.empty() ? nullptr : m_cameras.top());
//    }
//private:
//    std::stack<Camera*> m_cameras;
//    std::stack<Entity*> m_stack;
//    std::stack<glm::vec4> m_viewportStack;
//};

// class responsible for rendering the entire scene.
// handles camera and loops through all rendering components
class RenderingEngine : public Component, public WindowResizeListener {
public:
    //virtual ~RenderingEngine();
    void Start() override;
    void Update(double) override;
    void AddShader (Shader* id);
    void AddCamera (std::unique_ptr<Camera>);
    void RemoveCamera(int);
    Camera* GetCamera (int);
    void Notify(float, float) override;
    using ParentClass = RenderingEngine;
private:
    std::vector<Shader*> m_shaders;
    std::unordered_map<int, std::unique_ptr<Camera>> m_cameras;

    std::unordered_map<Camera*, Entity*> m_roots;
};




inline Camera* RenderingEngine::GetCamera(int id) {
    return m_cameras[id].get();
}

#endif /* renderingengine_h */
