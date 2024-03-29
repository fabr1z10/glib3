#include <monkey/activities/setstate.h>
#include <monkey/components/statemachine.h>
#include <monkey/engine.h>
#include <monkey/input/pytab.h>

namespace py = pybind11;



SetState::SetState(const ITab& t) : TargetActivity(t) {
        m_state = t.get<std::string>("state");
    m_args = std::make_unique<PyTab>(t.get<py::object>("args", py::dict()));
}

void SetState::Start() {
    TargetActivity::Start();
    if (m_entity.isValid()) {

        auto sm = m_entity->GetComponent<StateMachine>();
        if (sm == nullptr) {
            GLIB_FAIL("Setting the state requires a state machine component attached.");
        }
        sm->SetState(m_state, *m_args.get());
    }
    SetComplete();
}

