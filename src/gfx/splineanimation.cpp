#include <gfx/splineanim.h>


SplineAnimation::SplineAnimation(bool loop, int boundltype, double boundl, int boundrtype, double boundr) : SkeletalAnimation(loop),
        m_boundltype(boundltype), m_boundl(boundl), m_boundrtype(boundrtype), m_boundr(boundr) {}

void SplineAnimation::init() {
    if (m_keyFrames.size() >= 2) {
        int n = m_keyFrames[0].getAngleCount();
        for (size_t i = 0; i < n; ++i) {
            std::vector<double> times;
            std::vector<double> angles;

            for (const auto &frame : m_keyFrames) {
                times.push_back(frame.getTime());
                angles.push_back(frame.getAngle(i));
            }
            alglib::real_1d_array x;
            alglib::real_1d_array y;
            x.setcontent(times.size(), &(times[0]));
            y.setcontent(angles.size(), &(angles[0]));
            auto interp = std::make_unique<alglib::spline1dinterpolant>();
            alglib::spline1dbuildcubic(x, y, x.length(), m_boundltype, m_boundl, m_boundrtype, m_boundr,
                                       *(interp.get()));
            m_interpolants.push_back(std::move(interp));
        }
    }
}


SkeletalAnimationState SplineAnimation::getTransformation(float t) {
    SkeletalAnimationState state;
    if (m_keyFrames.size() == 1) {
        state.boneAngles = m_keyFrames.front().getAngles();
    } else {
        for (const auto& i : m_interpolants) {
            double value = alglib::spline1dcalc(*(i.get()), t);
            state.boneAngles.push_back(value);
        }


    }

    return state;
}
