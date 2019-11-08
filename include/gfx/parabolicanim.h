#pragma once

#include <gfx/skeletalanimation.h>
#include <map>
#include <alglib/interpolation.h>



class ParabolicAnimation : public SkeletalAnimation {
public:
    ParabolicAnimation(bool loop);
    void init() override;
    SkeletalAnimationState getTransformation (float t) override;

    //void addSpeed(const std::vector<float>& speeds);
private:
    std::vector<std::unique_ptr<alglib::spline1dinterpolant>> m_interpolants;

    //std::map<float, int> m_map;
    //std::vector<std::vector<float>> m_speeds;
    //std::vector<std::vector<std::array<double, 3> > > m_coefficients;
};