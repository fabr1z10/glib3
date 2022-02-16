#pragma once

#include <monkey/states/base3d.h>
#include <monkey/components/icollider.h>

class FoePath : public Base3D {
public:
    explicit FoePath(const ITab &);

    void AttachStateMachine(StateMachine*) override;
    void Run(double) override;

    void Init(const ITab &) override;

    void End() override;
private:
    struct PathSeg {
        glm::vec3 direction;
        float time;
    };
    std::vector<PathSeg> m_segments;
    bool m_loop;
    bool m_disappearOnEnd;
    float m_time;
    unsigned m_currentIndex;
};
//private:
//    bool randomAttack(glm::vec3);
//	float computeDirection();
//	void setDirection(int);
//	Controller3D* m_controller;
//	Dynamics2D * m_dynamics;
//	IAnimator* m_animator;
//	Entity * m_entity;
//
//	//std::vector<std::string> m_attacks;
//	std::vector<AttackInfo> m_attacks;

//	float m_speed;
//	float m_acceleration;
//	//float m_probAttack;
//	// flip gfx horizontally when going left
//	// bool m_fliph;
//	//bool m_flipIfPlatformEnds;
//	int m_left;
//	float m_attackPos;
//	float m_targetVelocityX;
//	float m_targetVelocityZ;
//	bool m_jumpAttack;
//	bool m_jumping;
//};