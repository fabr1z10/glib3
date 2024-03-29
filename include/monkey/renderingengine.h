//
//  renderingengine.h
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#ifndef renderingengine_h
#define renderingengine_h

#include <monkey/component.h>
#include <monkey/camera.h>
#include <monkey/listener.h>
#include <monkey/iterator.h>
#include <vector>
#include <stack>
#include <unordered_set>
#include <monkey/components/light.h>

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
    RenderingEngine();
    //virtual ~RenderingEngine();
    void Start() override;
    void Update(double) override;
    void AddShader (std::unique_ptr<Shader> shader);
//    void AddCamera (std::unique_ptr<Camera>);
//    void RemoveCamera(int);
//    Camera* GetCamera (int);
    Camera* getCurrentCamera();
    void Notify(float, float) override;
    using ParentClass = RenderingEngine;
    void AddLight (Light*);
    void RemoveLight(Light*);
    std::unordered_set<Light*>& GetLights();
    //glm::mat4& getModelViewMatrix();
    void setupCamera(Camera*);

private:
    int m_i;
    std::vector<std::unique_ptr<Shader>> m_shaders;
    std::unordered_map<int, std::unique_ptr<Camera>> m_cameras;
    std::unordered_set<Light*> m_lights;
    std::unordered_map<Camera*, Entity*> m_roots;
    //glm::mat4 m_mvm;
    Camera* m_currentCamera;
};

//inline Camera* RenderingEngine::GetCamera(int id) {
//    return m_cameras[id].get();
//}

inline std::unordered_set<Light*>& RenderingEngine::GetLights() {
    return m_lights;
}



#endif /* renderingengine_h */
