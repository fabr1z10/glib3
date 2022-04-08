#pragma once

#include <monkey/runner.h>
#include "btBulletDynamicsCommon.h"

class BulletWorld : public Runner {
public:
	BulletWorld(const ITab& t);
	void Update(double) override;
private:

};


