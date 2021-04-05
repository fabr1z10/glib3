#pragma once

#include <pybind11/embed.h>
//#include <monkey/py.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <monkey/monkey.h>
#include <monkey/singleton.h>
#include <monkey/shader.h>
#include <monkey/scenefactory.h>
#include <monkey/listener.h>
#include <unordered_set>
#include <monkey/assetman.h>
#include <monkey/error.h>
#include <monkey/renderingengine.h>
#include <monkey/scheduler.h>
#include <monkey/collisionengine.h>
#include <monkey/runner.h>
#include <monkey/keyboard.h>

class SceneFactory;
class PyTable;

class Engine : public Singleton<Engine> {
public:
    ~Engine();
    void init(const std::string&);
    void Init(const std::string& home, const std::string& game);
    void MainLoop();
    bool isRunning() const;
    Entity* GetScene() const;
    SceneFactory* GetSceneFactory();
    void SetSceneFactory (std::shared_ptr<SceneFactory> factory);
    glm::vec2 GetDeviceSize() const;
    void SetDeviceSize(glm::vec2);
    void SetTitle(const std::string&);
    void RegisterToWindowResizeEvent(WindowResizeListener*);
    void UnregisterToWindowResizeEvent(WindowResizeListener*);
    void RegisterToMouseEvent(MouseListener*);
    void UnregisterToMouseEvent(MouseListener*);
    void RegisterToKeyboardEvent(KeyboardListener*);
    void UnregisterToKeyboardEvent(KeyboardListener*);
    glm::vec4 GetViewport(float x, float y, float width, float height);
    void SetViewport(float x, float y, float width, float height);
    void Remove(Entity*);
    void Remove(int);
    void RemoveUnsafe(int);
    void Move (Entity*, Entity*);
    void restart();
    template <class T>
    T* GetRunner() {
        auto it = m_runners.find(std::type_index(typeid(T)));
        if (it != m_runners.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    template <typename T>
    void AddRunner(std::shared_ptr<T> c) {
        m_runners[c->GetType()] = c;
    }

    void EndScene();
    glm::vec2 GetWindowSize() const;
    void SetWindowSize(glm::ivec2);
    void SetFPS(int);
    float GetPixelRatio() const;
    AssetManager& GetAssetManager();
    const AssetManager& GetAssetManager() const;
    static void WindowResizeCallback(GLFWwindow* win, int width, int height);
    static void mouse_button_callback(GLFWwindow*, int, int, int);
    static void cursor_pos_callback(GLFWwindow*, double xpos, double ypos);
    static void scroll_callback(GLFWwindow*, double xoffset, double yoffset);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void SetRenderingEngine(std::unique_ptr<RenderingEngine>);
    void EnableMouse();
    void EnableKeyboard();
    RenderingEngine* GetRenderingEngine();
    Keyboard& GetKeyboard();
    double GetFrameTime() const;
    void SetDirectory(const std::string&);
    std::string GetDirectory() const;
    std::string GetGame() const;
    std::string GetGameDirectory() const;
    PyTable& getMainTable() const;
    float getTickMultiplier() const;
private:
    pybind11::scoped_interpreter m_guard;
    std::unique_ptr<PyTable> m_mainTable;
    friend class Singleton<Engine>;
    Engine();
    void InitGL();
    std::unordered_map<Entity*, Entity*> m_garbage;
    std::shared_ptr<SceneFactory> m_sceneFactory;
    std::unordered_map<ShaderType, std::unique_ptr<Shader>, EnumClassHash> m_shaders;
    std::shared_ptr<Entity> m_scene;
    bool m_running;
    double m_frameTime;
    double m_timeLastUpdate;
    glm::vec2 m_deviceSize;
    float m_aspectRatio;
    float m_winAspectRatio;
    glm::vec2 m_actualSize;
    glm::ivec2 m_winSize;
    std::unordered_set<WindowResizeListener*> m_resizeListeners;
    std::unordered_set<MouseListener*> m_mouseListeners;
    AssetManager m_assetManager;
    GLuint m_vao;
    bool m_endScene;
    bool m_mouseEnabled;
    float m_pixelRatio;
    std::unique_ptr<RenderingEngine> m_renderingEngine;
    // the runners (i.e. script engine, collision engine, hostpot manager etc)
    std::unordered_map<std::type_index, std::shared_ptr<Runner> > m_runners;
    Keyboard m_keyboard;
    std::string m_directory;
    std::string m_game;
    std::string m_gameDirectory;
    std::string m_title;
    float m_tickMultiplier;
};

inline PyTable& Engine::getMainTable() const {
    return *(m_mainTable.get());
}

inline double Engine::GetFrameTime() const {
    return m_frameTime;
}
inline SceneFactory* Engine::GetSceneFactory() {
    return m_sceneFactory.get();
}

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


//inline void Engine::AddShader (std::unique_ptr<Shader> shader) {
//    m_shaders[shader->GetShaderId()] = std::move(shader);
//}

inline bool Engine::isRunning() const {
    return m_running;
}

inline void Engine::SetSceneFactory (std::shared_ptr<SceneFactory> factory) {
    m_sceneFactory = factory;
}

inline void Engine::Remove(Entity* entity) {
    m_garbage.insert(std::make_pair(entity, nullptr));
}

inline void Engine::Move(Entity* entity, Entity* parent) {
    m_garbage.insert(std::make_pair(entity, parent));
}


inline void Engine::Remove(int id) {
    if (Monkey::get().isAlive(id)) {
        m_garbage.insert(std::make_pair(Monkey::get().Get<Entity>(id), nullptr));
    }
}

inline void Engine::RemoveUnsafe(int id) {
    m_garbage.insert(std::make_pair(Monkey::get().Get<Entity>(id), nullptr));
}
/*
inline Shader* Engine::GetShader(ShaderType id) {
    auto it = m_shaders.find(id);
    if (it == m_shaders.end())
        return nullptr;
    return it->second.get();
}
*/

inline void Engine::EndScene() {
    m_endScene = true;
}

inline float Engine::GetPixelRatio() const {
    return m_pixelRatio;
}

inline glm::vec2 Engine::GetWindowSize() const {
    return m_winSize;
}

inline RenderingEngine* Engine::GetRenderingEngine() {
    return m_renderingEngine.get();
}

inline Keyboard& Engine::GetKeyboard() {
    return m_keyboard;
}

inline std::string Engine::GetDirectory() const {
    return m_directory;
}

inline std::string Engine::GetGame() const {
    return m_game;
}
inline std::string Engine::GetGameDirectory() const {
    return m_gameDirectory;
}


inline float Engine::getTickMultiplier() const {
    return m_tickMultiplier;
}