//
//  renderingengine.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include <gfx/renderingengine.h>
#include <gfx/renderer.h>
#include <gfx/engine.h>
#include <gfx/shader.h>

void RenderingEngine::Update(double)
{
    int drawCount {0};
    auto root = Engine::get().GetScene();
    for (auto& shader : m_shaders) {
        ShaderType stype = shader->GetShaderId();
        shader->Start();
        for (auto& cam : m_cameras) {
            cam->SetCurrentCamera(shader);
            int camLayer = cam->GetLayer();
            // loop through all nodes
            for (auto iter = root->begin(); iter != root->end(); ++iter) {
                if ( (camLayer & iter->GetLayer()) > 0) {
                    // get the renderer component
                    Renderer* renderer = iter->GetComponent<Renderer>();
                    
                    if (renderer != nullptr && renderer->GetShaderType() == stype) {
                        glm::mat4 wt = iter->GetWorldTransform() * renderer->GetTransform();
                        // check for frustrum culling ...
                        drawCount++;
                        
                        // compute model view matrix
                        glm::mat4 mvm = cam->m_viewMatrix * wt;
                        GLuint mvLoc = shader->GetUniformLocation(MODELVIEW);
                        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);
                        renderer->Draw(shader);
                    }
                    
                }
            }
        }
        shader->Stop();
    }
}
