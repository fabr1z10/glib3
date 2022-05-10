#pragma once

#include <monkey/activity.h>
#include <string>


class ChangeRoom : public Activity {
public:
    ChangeRoom(const std::string& roomId) : Activity(), m_roomId{roomId}{}
    ChangeRoom(const ITab&);
    void Start() override;
    void Run (float dt) override {}
private:
    std::string m_roomId;
    pybind11::object m_args;
};
