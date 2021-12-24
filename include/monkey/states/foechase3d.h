#pragma once

#include <monkey/states/base3d.h>


/**
 * This enemy follows the player and places himself at a distance where he's able to attack him
 * If player is at range, the enemy will attack with some probability
 * Also, you can provide several attack states
 */
class FoeChase3D : public Base3D {
public:
    explicit FoeChase3D(const ITab &);

	void AttachStateMachine(StateMachine*) override;
    void Run(double) override;

    void Init(const ITab &) override;

    void End() override;
private:
    Entity* m_target;
    float m_attackDistance;
    bool m_inRange;
	std::string m_walkAnim;
	std::string m_idleAnim;

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
//	std::map<float, int> m_attackMap;
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