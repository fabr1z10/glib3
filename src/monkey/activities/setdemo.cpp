#include <monkey/activities/setdemo.h>

SetDemo::SetDemo(bool value, bool sync, double length) : TargetActivity(), m_value(value),
    m_sync(sync), m_length(length) {
}

void SetDemo::Start() {
    TargetActivity::Start();

    m_im = dynamic_cast<KeyboardInputMethod*>(m_entity->GetComponent<InputMethod>());
    m_im->setDemoMode(m_value);
    if (m_value) {
        m_im->setDemoSequence(m_events, m_length);
    }
    if (!m_sync) {
        SetComplete();
    }\
}

void SetDemo::addEvent(float t, int key, int type) {
    m_events.insert(std::make_pair(t, DemoKeyEvent{key, type}));
}

void SetDemo::Run(float dt) {
    // runs only if loop is set

    if (!m_im->getDemoMode()) {
        SetComplete();
    }

}
