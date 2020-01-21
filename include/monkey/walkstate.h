//#pragma once
//
//#include <monkey/state.h>
//#include <glm/glm.hpp>
//#include <unordered_map>
//
//class CollisionEngine;
//class Renderer;
//
//class WalkState : public StateBehaviour {
//public:
//    WalkState(float speed) : StateBehaviour(), m_speed(speed) {}
//    void Init(Entity*) override;
//    bool Run(double) override;
//private:
//    Entity* m_entity;
//    float m_speed;
//};
//
//class WalkStateCollision : public StateBehaviour {
//public:
//    WalkStateCollision (float width, float height, float speed, int horizontalRays, int verticalRays);
//    void Init(Entity*) override;
//    bool Run(double) override;
//    void AddAnimation(const std::string& id, const std::string& name);
//private:
//    Entity* m_entity;
//
//    CollisionEngine* m_engine;
//    Renderer* m_renderer;
//    float m_width;
//    float m_height;
//    float m_speed;
//    int m_horizontalRays;
//    int m_verticalRays;
//    float m_horizontalRaySpace;
//    float m_verticalRaySpace;
//    bool m_handleAnimations;
//    //glm::vec2 m_prevMove;
//    std::unordered_map<std::string, std::string> m_animations;
//};
