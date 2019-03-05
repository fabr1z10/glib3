#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gfx/singleton.h>
#include <gfx/shader.h>
#include <gfx/scenefactory.h>
#include <gfx/listener.h>
#include <unordered_set>
#include <gfx/assetman.h>
#include <gfx/error.h>
#include <gfx/renderingengine.h>
#include <gfx/scheduler.h>
#include <gfx/collisionengine.h>
#include <gfx/runner.h>
#include <gfx/keyboard.h>

class Engine : public Singleton<Engine> {
public:
    ~Engine();
    void Init(const std::string& home);
    void MainLoop();
    bool isRunning() const;
    Entity* GetScene() const;
    SceneFactory* GetSceneFactory();
    void SetSceneFactory (std::unique_ptr<SceneFactory> factory);
    glm::vec2 GetDeviceSize() const;
    void SetDeviceSize(glm::vec2);
    void RegisterToWindowResizeEvent(WindowResizeListener*);
    void UnregisterToWindowResizeEvent(WindowResizeListener*);
    void RegisterToMouseEvent(MouseListener*);
    void UnregisterToMouseEvent(MouseListener*);
    void RegisterToKeyboardEvent(KeyboardListener*);
    void UnregisterToKeyboardEvent(KeyboardListener*);
    glm::vec4 GetViewport(float x, float y, float width, float height);
    void SetViewport(float x, float y, float width, float height);
    void Remove(Entity*);

    template <typename T>
    T* GetRef(const std::string& id) {
        auto it = m_taggedReferences.find(id);
        if (it == m_taggedReferences.end())
            GLIB_FAIL("Unknown reference " << id);
        T* cref = dynamic_cast<T*>(it->second);
        if (cref == nullptr)
            GLIB_FAIL("Reference " << id << " has incorrect type.");
        return cref;
    }
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

    void AddTaggedRef (const std::string&, Ref*);
    void RemoveTaggedRef (const std::string&);
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
    int getIdFromTag(const std::string& tag);
private:
    friend class Singleton<Engine>;
    Engine() : m_mouseEnabled{true}, m_sceneFactory{nullptr} {}
    std::unordered_map<std::string, Ref*> m_taggedReferences;
    void InitGL();
    std::unordered_set<Entity*> m_garbage;
    std::unique_ptr<SceneFactory> m_sceneFactory;
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
    std::string m_title;
};

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

inline void Engine::SetSceneFactory (std::unique_ptr<SceneFactory> factory) {
    m_sceneFactory = std::move(factory);
}

inline void Engine::Remove(Entity * entity) {
    m_garbage.insert(entity);
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

