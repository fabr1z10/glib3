//#pragma once
//
//#include "monkey/component.h"
//#include "monkey/skeletal/skcoll.h"
//
//// TODO why does it have to be skeletal collider manager? Can it be just a generic coll manager?
//class SkeletalColliderManager : public Component {
//public:
//	SkeletalColliderManager (const ITable&);
//	void Start() override;
//	void Update(double) override;
//private:
//	std::vector<std::shared_ptr<SkColl> > m_colliders;
//};