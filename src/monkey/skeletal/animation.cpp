#include <monkey/skeletal/animation.hpp>

SkAnimation::SkAnimation(const ITable & t) {
    m_loop = t.get<bool>("loop", true);
    m_length = t.get<float>("length");
    t.foreach<PyDict>("keyframes", [&] (const PyDict& dict) {
        // get the timestamp
        auto t = dict.get<float>("t");
        std::unordered_map<std::string, JointTransform> pose;
        dict.foreach<pybind11::tuple>("pose", [&] (const pybind11::tuple& tup) {
            std::string jointName = tup[0].cast<std::string>();
            float x = tup[1].cast<float>();
            float y = tup[2].cast<float>();
            float alpha = tup[3].cast<float>();
            pose[jointName] = JointTransform {x, y, alpha};
        });
        m_keyFrames.push_back(std::make_shared<SKeyFrame>(t, pose));
    });

}

float SkAnimation::getLength() {
    return m_length;

}

