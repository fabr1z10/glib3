#pragma once

#include <monkey/states/base3d.h>
#include <monkey/components/icollider.h>

struct AttackDetails {
    int attackId;
    glm::vec2 range;
    bool inRange;               // attacks only if within range
};

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
    bool randomAttack(float distance, float scale);
    Entity* m_target;
    glm::vec2 m_attackRange;
    float m_attackDistance;
    glm::vec2 m_unscaledAttackRange;
    float m_unscaledAttackDistance;
    float m_unscaledThickness;
    bool m_inRange;
	std::string m_walkAnim;
	std::string m_idleAnim;
	std::map<float, AttackDetails> m_attackMap;
	float m_thickness;
	float m_halfThickness;
	ICollider* m_collider;
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