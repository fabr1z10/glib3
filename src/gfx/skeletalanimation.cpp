#include <gfx/skeletalanimation.h>


KeyFrame::KeyFrame() {}
void KeyFrame::AddAngle(const std::string & boneId, float angle) {
    m_angles.insert(std::make_pair(boneId, angle));

}

void SkeletalAnimation::checkAttack(float t0, float t1) {
    if (!m_hasAttack) {
        return;
    }

    if (t0 <=m_attackTime && t1 >= m_attackTime) {

        // do a shapecast!
        std::cout <<" **** hit ****\n";
//        std::cout << "character at position = " << t[3][0] << ", " << t[3][1] << " scale " << t[0][0] << "\n";
//        auto e = m_engine->ShapeCast(bi.m_attackShape, t, attackInfo.second);
//
//        if (e != nullptr) {
//            std::cerr << "HIT!\n";
//            auto rm = m_engine->GetResponseManager();
//            if (rm == nullptr) {
//                std::cerr << "no handler!\n";
//            }
//            auto handler = rm->GetHandler(attackInfo.first, e->GetCollisionTag());
//            if (handler.response != nullptr) {
//                std::cerr << "FOUND RESPONSE\n";
//                if (handler.flip) {
//                    handler.response->onStart(e->GetObject(), m_entity, CollisionReport());
//                } else {
//                    handler.response->onStart(m_entity, e->GetObject(), CollisionReport());
//                }
//            }
//        }
    }
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