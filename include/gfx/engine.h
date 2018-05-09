#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gfx/singleton.h>
#include <gfx/shader.h>
#include <gfx/entity.h>


struct EngineConfig {
    EngineConfig () : window{nullptr}, frameRate (60.0) {}
    
    GLFWwindow* window;
    double frameRate;
};

class SceneFactory {
public:
    virtual std::shared_ptr<Entity> Create() = 0;
};



class Engine : public Singleton<Engine> {
public:
    void Init(const EngineConfig& config);
    void MainLoop();
    void Draw();
    bool isRunning() const;
    void AddShader (std::unique_ptr<Shader>);
    Entity* GetScene() const;
    void SetSceneFactory (std::unique_ptr<SceneFactory> factory);
    glm::vec2 GetDeviceSize() const;
private:
    std::unique_ptr<SceneFactory> m_sceneFactory;
    std::vector<std::unique_ptr<Shader> > m_shaders;
    std::shared_ptr<Entity> m_scene;
    bool m_running;
    double m_frameTime;
    double m_timeLastUpdate;
    GLFWwindow* m_window;
    glm::vec2 m_deviceSize;

};

inline glm::vec2 Engine::GetDeviceSize() const {
    return m_deviceSize;
}

inline Entity* Engine::GetScene() const {
    return m_scene.get();
}


inline void Engine::AddShader (std::unique_ptr<Shader> shader) {
    m_shaders.push_back(std::move(shader));
}

inline bool Engine::isRunning() const {
    return m_running;
}

inline void Engine::SetSceneFactory (std::unique_ptr<SceneFactory> factory) {
    m_sceneFactory = std::move(factory);
}