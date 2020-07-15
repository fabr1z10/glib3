#include <monkey/activities/freemove.h>
#include <glm/gtx/transform.hpp>
#include <monkey/math/geom.h>
#include <monkey/engine.h>

FreeMove::FreeMove(const ITable & t) : TargetActivity(t), m_shape(nullptr) {

    float x_default = 0.0f;
    float y_default = 0.0f;
    float z_default = 0.0f;
    float angle_default = 0.0f;
    float scalex_default = 1.0f;
    float scaley_default = 1.0f;

    m_loop = t.get<bool>("loop");
    int interpolationType = t.get<int>("itype");
    //alglib::spline1dbuildcubic(x, y, x.length(),- m_boundltype, m_boundl, m_boundrtype, m_boundr,
    //                           *(interp.get()));
    //m_interpolants.push_back(std::move(interp));
    // at least one keyframe should be provided
    t.foreach<PyTable>("keyframes", [&] (const PyTable& t) {
        float time = t.get<float>("t");
        // for keyframe whatever item you don't specify takes the last value
        float x = t.get<float>("x", x_default);
        float y = t.get<float>("y", y_default);
        float z = t.get<float>("z", y_default);
        float angle = deg2rad * (t.get<float>("angle", angle_default));
        float sx = t.get<float>("scalex", scalex_default);
        float sy = t.get<float>("scaley", scaley_default);
        m_keyFrames.push_back(KeyFrame{time, x, y, z, angle, sx, sy});
        x_default = x;
        y_default = y;
        z_default = z;
        angle_default = angle;
        scalex_default = sx;
        scaley_default = sy;

    });
    auto n = m_keyFrames.size();
    alglib::real_1d_array vecs[7];
    for (auto& a : vecs) {
        a.setlength(n);
    }
    int frameId = 0;
    // now loop through value and keyframe
    for (const auto& keyFrame : m_keyFrames) {
        vecs[0][frameId] = keyFrame.t;
        vecs[1][frameId] = keyFrame.x;
        vecs[2][frameId] = keyFrame.y;
        vecs[3][frameId] = keyFrame.z;
        vecs[4][frameId] = keyFrame.angle;
        vecs[5][frameId] = keyFrame.scalex;
        vecs[6][frameId] = keyFrame.scaley;

        frameId++;
    }
    m_duration = m_keyFrames.back().t;
    int j= 1;
    for (auto& i : m_interpolants) {
        switch (interpolationType) {
            case 0:
                alglib::spline1dbuildlinear(vecs[0], vecs[j++], i);
                break;
            case 1:
                alglib::spline1dbuildcubic(vecs[0], vecs[j++], i);
                break;
            case 2:
                alglib::spline1dbuildmonotone(vecs[0], vecs[j++], i);
                break;
        }
    }

    // cast shape ?
    if (t.hasKey("cast")) {
        auto factory = Engine::get().GetSceneFactory();
        auto shapeR = t.get<PyTable>("cast");
        m_shape = factory->make2<Shape>(shapeR);
        m_c1 = t.get<float>("c1");
        m_c2 = t.get<float>("c2");
        m_castTag = t.get<int>("cast_tag");
        m_castMask = t.get<int>("cast_mask");

    }

}

void FreeMove::Start() {
    TargetActivity::Start();
    m_time = 0.0f;
    updateTransform();
    if (m_shape != nullptr) {
        m_engine = Engine::get().GetRunner<ICollisionEngine>();
    }
}

void FreeMove::updateTransform() {
    // the transformation will be
    std::array<double, 5> values;
    unsigned int j = 0;
    for (const auto& interp : m_interpolants) {
        values[j++] = alglib::spline1dcalc(interp, m_time);
    }
    float angle = static_cast<float>(values[3]);
    glm::mat4 transform = glm::rotate(angle, glm::vec3(0, 0, 1));
    // apply translation
    transform[3][0] = values[0];
    transform[3][1] = values[1];
    transform[3][2] = values[2];
    // apply scale
    transform[0][0] *= values[4];
    transform[1][1] *= values[5];
    m_entity->SetLocalTransform(transform);
    if (m_shape != nullptr && m_time >= m_c1 && m_time < m_c2) {
        // cast shape
        auto e = m_engine->ShapeCast(m_shape.get(), transform, m_castMask);
        if (e.report.collide) {
            std::cerr << "HIT!\n";
            auto rm = m_engine->GetResponseManager();
            if (rm == nullptr) {
                std::cerr << "no handler!\n";
            }
            auto handler = rm->GetHandler(m_castTag, e.entity->GetCollisionTag());
            if (handler.response != nullptr) {
                auto object = e.entity->GetObject();
                std::cerr << "FOUND RESPONSE\n";
                if (handler.flip) {
                    handler.response->onStart(object, m_entity.get(), e.report);
                } else {
                    handler.response->onStart(m_entity.get(), object, e.report);
                }
            }
        }
    }
}

void FreeMove::Run(float dt) {
    m_time += dt;
    // update timer
    if (m_time > m_duration) {
        if (m_loop) {
            m_time = m_duration - m_time;
        } else {
            m_time = m_duration;
            SetComplete();
        }
    }

    updateTransform();



}

void FreeMove::Reset() {
}