#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gfx/singleton.h>
#include <gfx/shader.h>
#include <gfx/entity.h>
#include <gfx/listener.h>
#include <unordered_set>

struct EngineConfig {
    EngineConfig (float devWidth, float devHeight) :
        window{nullptr}, frameRate (60.0), deviceWidth{devWidth}, deviceHeight{devHeight} {}
    
    GLFWwindow* window;
    double frameRate;
    float deviceWidth;
    float deviceHeight;
};

class SceneFactory {
public:
    virtual std::shared_ptr<Entity> Create() = 0;
};



class Engine : public Singleton<Engine> {
public:
    ~Engine();
    void Init(const EngineConfig& config);
    void MainLoop();
    void Draw();
    bool isRunning() const;
    Shader* GetShader (ShaderType id);
    void AddShader (std::unique_ptr<Shader>);
    Entity* GetScene() const;
    void SetSceneFactory (std::unique_ptr<SceneFactory> factory);
    glm::vec2 GetDeviceSize() const;
    void RegisterToWindowResizeEvent(WindowResizeListener*);
    void UnregisterToWindowResizeEvent(WindowResizeListener*);
    static void WindowResizeCallback(GLFWwindow* win, int width, int height);
private:
    std::unique_ptr<SceneFactory> m_sceneFactory;
    std::unordered_map<ShaderType, std::unique_ptr<Shader>> m_shaders;
    std::shared_ptr<Entity> m_scene;
    bool m_running;
    double m_frameTime;
    double m_timeLastUpdate;
    GLFWwindow* m_window;
    glm::vec2 m_deviceSize;
    std::unordered_set<WindowResizeListener*> m_resizeListeners;

};

inline glm::vec2 Engine::GetDeviceSize() const {
    return m_deviceSize;
}

inline Entity* Engine::GetScene() const {
    return m_scene.get();
}


inline void Engine::AddShader (std::unique_ptr<Shader> shader) {
    m_shaders[shader->GetShaderId()] = std::move(shader);
}

inline bool Engine::isRunning() const {
    return m_running;
}

inline void Engine::SetSceneFactory (std::unique_ptr<SceneFactory> factory) {
    m_sceneFactory = std::move(factory);
}

inline Shader* Engine::GetShader(ShaderType id) {
    auto it = m_shaders.find(id);
    if (it == m_shaders.end())
        return nullptr;
    return it->second.get();
}