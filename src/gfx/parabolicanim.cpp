#include <gfx/parabolicanim.h>
#include <alglib/solvers.h>

ParabolicAnimation::ParabolicAnimation(bool loop) : SkeletalAnimation(loop) {}

void ParabolicAnimation::init() {
    if (m_keyFrames.size() >= 2) {
        int n = getBonesCount();
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
            alglib::spline1dbuildmonotone(x, y, *(interp.get()));
            m_interpolants.push_back(std::move(interp));
        }
    }

//    // for every (frame, bone) I need to store (a, b, c)
//    // the coefficients of the equation
//    // _alpha = at^2 + bt + c
//    int n = getBonesCount();
//    int frameId = 0;
//
//    for (size_t i = 0; i < m_keyFrames.size()-1; ++i) {
//
//        const auto& keyFrame = m_keyFrames[i];
//        const auto& nextKeyFrame = m_keyFrames[i+1];
//        m_map[keyFrame.getTime()] = i;
//        double t0 = keyFrame.getTime();
//        double t1 = nextKeyFrame.getTime();
//        std::vector<std::array<double, 3>> coeff;
//        for (size_t j= 0; j < n; ++j) {
//            float speed = m_speeds[i][j];
//            double a0 = keyFrame.getAngle(j);
//            double a1 = nextKeyFrame.getAngle(j);
//            alglib::real_2d_array a;
//            alglib::real_1d_array b;
//            double da[] = {t1*t1, t1, 1, t0*t0, t0, 1, 2*t0, 1, 0};
//            double db[] = {a1, a0, speed};
//            a.setcontent(3, 3, da);
//            b.setcontent(3, db);
//            alglib::ae_int_t info;
//            alglib::rmatrixsolvefast(a, 3, b, info);
//            coeff.push_back({b[0], b[1], b[2]});
//        }
//        m_coefficients.push_back(coeff);
//    }
//    //alglib::rmatrixsolve()
}

//void ParabolicAnimation::addSpeed(const std::vector<float> &speeds) {
//m_speeds.push_back(speeds);
//}


SkeletalAnimationState ParabolicAnimation::getTransformation(float t) {
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