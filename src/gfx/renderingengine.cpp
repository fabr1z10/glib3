//
//  renderingengine.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include <gfx/renderingengine.h>
#include <gfx/engine.h>

void RenderingEngine::Update(double)
{
    auto root = Engine::get().GetScene();
    for (auto& shader : m_shaders) {
        shader->Start();
        for (auto& cam : m_cameras) {
            cam->SetCurrentCamera(shader);
            int camLayer = cam->GetLayer();
            // loop through all nodes
            for (auto iter = root->begin(); iter != root->end(); ++iter) {
                if ( (camLayer & iter->GetLayer()) > 0) {
                    // get the renderer component
                    
                    
                }
            }
        }
    }
}
