#pragma once


#pragma once

#include <monkey/states/platformerstate.h>

class Controller2D;
class Dynamics2D;
class InputMethod;
class ICollisionEngine;

// this is the walk state used in platformers like SuperMario
class JAttack : public PlatformerState {
public:
	/**
	 *
	 * @param speed The maximum speed
	 * @param acceleration The acceleration
	 * @param fliph Flip entity horizontally when going left
	 */
	JAttack (const ITable&);
	void AttachStateMachine(StateMachine * sm) override;

	void Run(double) override;
	void Init (pybind11::dict&) override;
	void End () override;
	void ResetAnimation() override {}
	void ModifyAnimation() override {}
private:
	float m_colliderWidth;
	std::string m_animUp;
	std::string m_animDown;
	std::string m_animLand;
	std::string m_stateNext;
	// this is the height w.r.t. target
	float m_jumpHeight;
	float m_timeToJumpApex;
	Entity* m_target;
	StateMachine* m_targetStateMachine;
	pybind11::function m_callback;
	ICollisionEngine* m_collision;
	float m_jumpSpeed;
	float m_targetVelocityX;
	float m_timeDown;
	float m_speedDown;
	int m_hitMask;
};

