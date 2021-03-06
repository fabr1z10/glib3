#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/ianimator.h>

class Controller3D;
class Dynamics2D;
class InputMethod;

class Jump3D : public State {
public:
	Jump3D(float accelerationTimeAirborne, float speed, bool fliph, const std::string& animUp, const std::string& animDown);
	Jump3D(const ITab&);
	void Run (double) override;
	void Init (const ITab&) override {}
	void End () override {}
	void AttachStateMachine(StateMachine*) override;

private:
	Controller3D* m_controller;
	Dynamics2D * m_dynamics;
	InputMethod * m_input;
	IAnimator* m_animator;

	Entity * m_entity;
	float m_speed;
	float m_accTimeAir;
	//float m_velocitySmoothing;
	bool m_flipHorizontally;
	//bool m_setJumpDownAnim;
	//bool m_goingUp;
	bool m_bounce;
	float m_bounceFactor;
	std::string m_jumpAnimUp;
	std::string m_jumpAnimDown;
	float m_vy0;
	std::string m_walkState;
	//std::string m_jumpDownAnim;
};
