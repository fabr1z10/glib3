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
#include <vector>

// class responsible for rendering the entire scene.
// handles camera and loops through all rendering components
class RenderingEngine : public Component {
public:
    
    void Update(double) override;
    
private:
    std::vector<Shader*> m_shaders;
    std::vector<std::unique_ptr<Camera>> m_cameras;
};

#endif /* renderingengine_h */
