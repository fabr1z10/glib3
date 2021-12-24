#pragma once

#include <monkey/states/base3d.h>
#include <monkey/components/animrenderer.h>

class InputMethod;

// this is the walk state for moving in 3d world (x, z horizontal)
class PlayerWalk3D : public Base3D {
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
	InputMethod * m_input;

	float m_speed;
	float m_jumpSpeed;
	std::string m_walkAnim;
	std::string m_jumpState;
	std::string m_idleAnim;
	//std::shared_ptr<WalkAnim> m_walkAnimator;
	int m_jumpKey;

};

