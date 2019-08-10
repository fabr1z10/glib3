#include <gfx/skeletalanimation.h>


KeyFrame::KeyFrame() {}
void KeyFrame::AddAngle(const std::string & boneId, float angle) {
    m_angles.insert(std::make_pair(boneId, angle));

}


void SkeletalAnimation::addKeyFrame(float t, KeyFrame keyframe) {

    m_keyFrames.insert(std::make_pair(t, keyframe));
}
void SkeletalAnimation::init() {

    // find the splines for all the bones involved


    std::unordered_map<std::string, std::vector<double>> times;
    std::unordered_map<std::string, std::vector<double>> funcValues;


    for (const auto& frame : m_keyFrames) {
        const auto& angles = frame.second.getAngles();
        for (const auto& b : angles) {
            times[b.first].push_back(frame.first);
            funcValues[b.first].push_back(b.second);
        }
    }

    for (const auto& b : times) {
        // for every bone involved in the animation, create a spline
        alglib::real_1d_array x;
        alglib::real_1d_array y;
        x.setcontent(b.second.size(), &(b.second[0]));
        const auto& values = funcValues.at(b.first);
        y.setcontent(values.size(), &(values[0]));
        auto interp = std::make_unique<alglib::spline1dinterpolant>();
        alglib::spline1dbuildcubic(x, y, b.second.size(), -1, 0.0, -1, 0.0, *(interp.get()));
        m_interpolants.insert(std::make_pair(b.first, std::move(interp)));
    }






}

SkeletalAnimationState SkeletalAnimation::getTransformation(float t) {
    SkeletalAnimationState state;
    for (const auto& i : m_interpolants) {
        double value = alglib::spline1dcalc(*(i.second.get()), t);
        state.bones.push_back(BoneInfo {i.first, value});
    }
    return state;
}