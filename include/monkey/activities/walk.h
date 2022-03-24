#pragma once

#include <monkey/activities/sequence.h>
#include <glm/glm.hpp>
#include <monkey/math/shape.h>
#include <string>
#include <unordered_map>
#include <monkey/math/geom.h>
#include <iostream>
#include <monkey/components/animrenderer.h>


class Walk : public Sequence {
public:
    Walk (const ITab&);
    Walk (int actor, glm::vec2 p) : Sequence(), m_actorId{actor}, m_p{p} {}
    ~Walk() override { }
    Walk (const std::string& tag, glm::vec2 p) : Sequence(), m_tag{tag}, m_actorId(-1), m_p{p} {}
    void Start() override;
    void SetComplete() override;
    void NotifySuspend() override;
    void onResume() override;
private:
    char m_lastDirection;
    IShape* m_shape;
    int m_actorId;
    std::string m_tag;
    glm::vec2 m_p;
    int m_pathFound;
    AnimationRenderer* m_animator;
    Entity* m_entity;
    std::string m_currentAnim;
    bool m_flip;
};
