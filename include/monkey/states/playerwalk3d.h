#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/animrenderer.h>

class Controller3D;
class Dynamics3D;
class InputMethod;

// this is the walk state for moving in 3d world (x, z horizontal)
class PlayerWalk3D : public State {
public:
	/**
	 *
	 * @param speed The maximum speed
	 * @param acceleration The acceleration
	 * @param fliph Flip entity horizontally when going left
	 */
	//PlayerWalk3D(float speed, float acceleration, bool fliph, float jumpSpeed);
	explicit PlayerWalk3D(const ITab&);
	void AttachStateMachine(StateMachine*) override;

	void Run(double) override;
	void Init (const ITab&) override;
	void End () override;


private:
	Controller3D* m_controller;
    Dynamics3D * m_dynamics;
	InputMethod * m_input;
    AnimationRenderer* m_renderer;
	Entity * m_entity;

	//bool m_flipHorizontally;
	float m_speed;
	float m_acceleration;
	float m_velocitySmoothing;
	float m_jumpSpeed;
	std::string m_walkAnim;
	std::string m_jumpState;
	std::string m_idleAnim;
	//std::shared_ptr<WalkAnim> m_walkAnimator;
	int m_jumpKey;
    float m_maxSpeed;
    float m_gravity;

};

