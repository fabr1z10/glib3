#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/ianimator.h>
#include <monkey/components/animrenderer.h>

class Controller3D;
class Dynamics3D;
class InputMethod;

class PlayerJump3D : public State {
public:
    //PlayerJump3D(float accelerationTimeAirborne, float speed, bool fliph, const std::string& animUp, const std::string& animDown);
    PlayerJump3D(const ITab&);
	void Run (double) override;
	void Init (const ITab&) override {}
	void End () override {}
	void AttachStateMachine(StateMachine*) override;

private:
	Controller3D* m_controller;
	Dynamics3D * m_dynamics;
	InputMethod * m_input;
    AnimationRenderer* m_renderer;

	Entity * m_entity;
    float m_maxSpeed;
    float m_accTimeAir;
    float m_acceleration;

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
    float m_gravity;

};
