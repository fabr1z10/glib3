#pragma once

#include <monkey/activities/targetactivity.h>
#include <alglib/interpolation.h>
#include <monkey/icollisionengine.h>

// generic animation. You can add keyframes with:
// x, y, angle, scalex, scaley
// you can choose interpolation (monotonic spline, spline)
class FreeMove : public TargetActivity {
public:
    struct KeyFrame {
        float t;
        float x;
        float y;
        float z;
        float angle;
        float scalex;
        float scaley;
    };

    FreeMove(const ITable&);
    void Start() override;
    void Run (float dt) override;
    void Reset() override;
private:
    void updateTransform();
    bool m_loop;
    float m_duration;
    float m_time;
    float m_c1;
    float m_c2;
    int m_castMask;
    int m_castTag;
    std::shared_ptr<Shape> m_shape;
    ICollisionEngine* m_engine;

    std::vector<KeyFrame> m_keyFrames;
    // need 5 interpolants, one for each variable (x, y, angle, sx, sy)
    std::array<alglib::spline1dinterpolant, 6> m_interpolants;

};
