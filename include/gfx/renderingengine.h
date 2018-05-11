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
    virtual ~RenderingEngine();
    void Start() override;
    void Update(double) override;
    void AddShader (ShaderType id);
    void AddCamera (std::unique_ptr<Camera>);
    void Notify(float, float) override;
    using ParentClass = RenderingEngine;
private:
    std::vector<Shader*> m_shaders;
    std::vector<std::unique_ptr<Camera>> m_cameras;
};

inline void RenderingEngine::AddCamera(std::unique_ptr<Camera> cam) {
    m_cameras.push_back(std::move(cam));
}


#endif /* renderingengine_h */
