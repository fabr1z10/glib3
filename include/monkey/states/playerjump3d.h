#pragma once

#include <monkey/states/base3d.h>
#include <monkey/components/ianimator.h>
#include <monkey/components/animrenderer.h>

class InputMethod;

class PlayerJump3D : public Base3D {
public:
    //PlayerJump3D(float accelerationTimeAirborne, float speed, bool fliph, const std::string& animUp, const std::string& animDown);
    explicit PlayerJump3D(const ITab&);
	void Run (double) override;
	void Init (const ITab&) override {}
	void End () override {}
	void AttachStateMachine(StateMachine*) override;
private:
	InputMethod * m_input;
	std::string m_walkState;
};
