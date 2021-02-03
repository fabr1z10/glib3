/*
#pragma once

#include <monkey/asset.h>
#include <monkey/py.h>
#include <monkey/skeletal/animation/frame.hpp>

class SkeletalAnimation3D : public Object {
public:
	SkeletalAnimation3D(const ITable&);
	float getLength() const;
	std::tuple<KeyFrameSkeletal*, KeyFrameSkeletal*, float> getPreviousAndNextKeyFrames (float t);
private:
	bool m_loop;
	float m_duration;
	std::vector<std::shared_ptr<KeyFrameSkeletal>> m_frames;
};*/
