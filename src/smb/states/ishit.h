#pragma once

#include <monkey/states/platformerstate.h>

class Controller2D;
class Dynamics2D;
class InputMethod;

// this is the walk state used in platformers like SuperMario
class IsHit : public PlatformerState {
public:
	/**
	 *
	 * @param speed The maximum speed
	 * @param acceleration The acceleration
	 * @param fliph Flip entity horizontally when going left
	 */
	IsHit (const ITable&);
	IsHit (const IsHit &);
	std::shared_ptr<State> clone() const override;

	void Run(double) override;
	void Init (pybind11::dict&) override;
	void End () override;
	void ResetAnimation() override {}
	void ModifyAnimation() override {}
private:
	float m_distanceTravelled;
	float m_dist;
	std::string m_anim;
	float m_sgn;
	float m_acceleration;
	float m_velocitySmoothing;
	float m_jumpSpeed;
	std::string m_walkAnim;
	std::string m_jumpState;
	std::string m_idleAnim;
};

