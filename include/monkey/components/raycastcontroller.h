//#pragma once
//
//#include <monkey/component.h>
//#include <monkey/keyboard.h>
//#include <monkey/engine.h>
//#include <monkey/collisionengine.h>
//
//class HeightMap;
//
//class RaycastController : public Component {
//public:
//    RaycastController (const std::string& hm) : Component(), m_keyboard(Engine::get().GetKeyboard()), m_heightmap(hm) {}
//    void Start() override;
//    void Update(double) override;
//private:
//    std::string m_heightmap;
//    Keyboard& m_keyboard;
//    CollisionEngine * m_collision;
//    HeightMap* m_heightMap;
//};