#pragma once

#include <monkey/component.h>
#include <glm/glm.hpp>
#include <vector>

class Mover : public Component {

public:
    Mover();
    void setPause(bool);

protected:
    bool m_pause;
    bool m_hold;
    float m_holdTime;
    float m_holdTimer;
};

class PolygonalMover : public Mover {
public:
    PolygonalMover(const ITab&);
    void Start() override;
    void Update(double) override ;
private:
    float m_speed;
    std::vector<glm::vec2> m_points;
    std::vector<glm::vec2> m_uvec;
    std::vector<float> m_distances;
    int m_currentEdge;
    int m_next;
    float m_distance;
    int m_direction;
    int m_mode;
    bool m_done;
};

//
//class AcceleratedMover : public Mover {
//public:
//	AcceleratedMover(const ITab&);
//	void Start() override  {}
//	void Update(double) override ;
//private:
//	glm::vec2 m_acceleration;
//	glm::vec2 m_initialVelocity;
//	glm::vec2 m_velocity;
//	float m_angularSpeed;
//	float m_angle;
//};
//
//class PolygonalMover : public Mover {
//public:
//    PolygonalMover (int loopType, glm::vec2 origin = glm::vec2(0.0f));
//    PolygonalMover (const ITab&);
//    std::type_index GetType() override;
//    void addMovement(glm::vec2 delta, float speed, float hold);
//    void Start() override ;
//    void Update(double) override ;
//    void setStartPosition(int, float);
//    void setCompleteCallback(pybind11::function f);
//private:
//    struct Movement {
//        Movement(glm::vec2 delta, float speed, float hold);
//        glm::vec2 dir;
//        glm::vec2 endPosition;
//        float speed;
//        float hold;
//        float length;
//        float time;
//        glm::vec2 startPosition;
//    };
//    glm::vec2 m_O;          // origin
//    // set starting point
//    int m_startIndex;
//    float m_pctComplete;
//
//    //int m_loopType;         // 0 = bidirectional, 1 = unidirectional (discontinuity at end)
//    std::vector<Movement> m_movements;
//    int m_currentMovement;
//    float m_cumulatedLength;
//    bool m_fwd;
//    std::shared_ptr<pybind11::function> m_hook;
//    bool m_hasSinX;
//    bool m_hasSinY;
//    glm::vec3 m_sinx;
//    glm::vec3 m_siny;
//    float m_t;
//
//};
//
//inline std::type_index PolygonalMover::GetType() {
//    return std::type_index(typeid(Mover));
//}
