#pragma once

#include <gfx/component.h>
#include <glm/glm.hpp>
#include <vector>

class Mover : public Component {

public:
    Mover();
    void setPause(bool);

private:
    bool m_pause;
};

class PolygonalMover : public Mover {
public:
    PolygonalMover (int loopType, glm::vec2 origin = glm::vec2(0.0f));
    PolygonalMover (const PolygonalMover&);
    std::shared_ptr<Component> clone() const override;
    std::type_index GetType() override;
    void addMovement(glm::vec2 delta, float speed);
    void Start() override ;
    void Update(double) override ;
private:
    struct Movement {
        glm::vec2 delta;
        glm::vec2 finalPosition;
        float speed;
        float length;
    };
    glm::vec2 m_O;          // origin
    int m_loopType;         // 0 = bidirectional, 1 = unidirectional (discontinuity at end)
    std::vector<Movement> m_movements;
    int m_currentMovement;
    float m_cumulatedLength;
    bool m_fwd;
};

inline std::type_index PolygonalMover::GetType() {
    return std::type_index(typeid(Mover));
}
