#pragma once

#include <monkey/skeletalanimation.h>
#include <alglib/interpolation.h>
#include <memory>
#include <unordered_map>

class SplineAnimation : public SkeletalAnimation {
public:
    SplineAnimation(bool loop, int boundltype, double boundl, int boundrtype, double boundr);
    void init() override;
    SkeletalAnimationState getTransformation (float t) override;

private:
    int m_boundltype;
    int m_boundrtype;
    double m_boundl;
    double m_boundr;
    std::vector<std::unique_ptr<alglib::spline1dinterpolant>> m_interpolants;

};