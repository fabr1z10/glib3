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
#include <vector>

// class responsible for rendering the entire scene.
// handles camera and loops through all rendering components
class RenderingEngine : public Component, public WindowResizeListener {
public:
    //virtual ~RenderingEngine();
    void Start() override;
    void Update(double) override;
    void AddShader (ShaderType id);
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
