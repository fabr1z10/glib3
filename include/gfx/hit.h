//#pragma once
//
//#include <gfx/state.h>
//#include <gfx/math/shape.h>
//#include <gfx/lua/luawrapper.h>
//
//
//class CollisionEngine;
//class Renderer;
//
//class Hit : public StateBehaviour {
//public:
//    Hit ();
//    void Init(Entity*) override;
//    bool Run(double) override;
//protected:
//    Renderer* m_renderer;
//};
//
//class HitCollision : public Hit {
//public:
//    HitCollision (int frame, std::shared_ptr<Shape> collisionShape, glm::vec2 offset, int mask, luabridge::LuaRef callback);
//    void Init(Entity*) override;
//    bool Run(double) override;
//    void ResetState() override;
//private:
//    Entity* m_entity;
//    luabridge::LuaRef m_callback;
//    //t m_frame;
//    //int m_mask;
//    //glm::vec2 m_offset;
//    std::shared_ptr<Shape> m_shape;
//    CollisionEngine* m_engine;
//    bool m_hitDone;
//};
