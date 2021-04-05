#pragma once

#include <monkey/states/platformerstate.h>

class Controller3D;
class Dynamics2D;
class InputMethod;

// this is the walk state for moving in 3d world (x, z horizontal)
class WalkSide3D : public State {
public:
	/**
	 *
	 * @param speed The maximum speed
	 * @param acceleration The acceleration
	 * @param fliph Flip entity horizontally when going left
	 */
	WalkSide3D(float speed, float acceleration, bool fliph, float jumpSpeed);
	WalkSide3D(const ITab&);
	void AttachStateMachine(StateMachine*) override;

	void Run(double) override;
	void Init (pybind11::dict&) override;
	void End () override;


private:
	Controller3D* m_controller;
	Dynamics2D * m_dynamics;
	InputMethod * m_input;
	Entity * m_entity;

	bool m_flipHorizontally;
	float m_speed;
	float m_acceleration;
	float m_velocitySmoothing;
	float m_jumpSpeed;
	std::string m_walkAnim;
	std::string m_jumpState;
	std::string m_idleAnim;
};

