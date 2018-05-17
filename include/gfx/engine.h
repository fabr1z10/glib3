#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gfx/singleton.h>
#include <gfx/shader.h>
#include <gfx/entity.h>
#include <gfx/listener.h>
#include <unordered_set>
#include <gfx/assetman.h>

struct EngineConfig {
    EngineConfig (float devWidth, float devHeight) : frameRate (60.0), deviceWidth{devWidth}, deviceHeight{devHeight}, enableMouse{false}, enableKeyboard{false},
    windowWidth{800}, windowHeight{600} {}
    double frameRate;
    float deviceWidth;
    float deviceHeight;
    bool enableMouse;
    bool enableKeyboard;
    int windowWidth;
    int windowHeight;
    std::string name;
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
    void RegisterToMouseEvent(MouseListener*);
    void UnregisterToMouseEvent(MouseListener*);
    void RegisterToKeyboardEvent(KeyboardListener*);
    void UnregisterToKeyboardEvent(KeyboardListener*);
    void Remove(Entity*);
    AssetManager& GetAssetManager();
    const AssetManager& GetAssetManager() const;
    static void WindowResizeCallback(GLFWwindow* win, int width, int height);
    static void mouse_button_callback(GLFWwindow*, int, int, int);
    static void cursor_pos_callback(GLFWwindow*, double xpos, double ypos);
    static void scroll_callback(GLFWwindow*, double xoffset, double yoffset);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
    void InitGL(const EngineConfig& config);
    std::unordered_set<Entity*> m_garbage;
    std::unique_ptr<SceneFactory> m_sceneFactory;
    std::unordered_map<ShaderType, std::unique_ptr<Shader>, EnumClassHash> m_shaders;
    std::shared_ptr<Entity> m_scene;
    bool m_running;
    double m_frameTime;
    double m_timeLastUpdate;
    //GLFWwindow* m_window;
    glm::vec2 m_deviceSize;
    std::unordered_set<WindowResizeListener*> m_resizeListeners;
    std::unordered_set<MouseListener*> m_mouseListeners;
    std::unordered_set<KeyboardListener*> m_keyboardListeners;
    AssetManager m_assetManager;
    GLuint m_vao;
};

inline AssetManager& Engine::GetAssetManager() {
    return m_assetManager;
}
inline const AssetManager& Engine::GetAssetManager() const {
    return m_assetManager;
}


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

inline void Engine::Remove(Entity * entity) {
    m_garbage.insert(entity);
}
inline Shader* Engine::GetShader(ShaderType id) {
    auto it = m_shaders.find(id);
    if (it == m_shaders.end())
        return nullptr;
    return it->second.get();
}
