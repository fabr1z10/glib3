#pragma once

#include <gfx/activity.h>
#include <string>


class ChangeRoom : public Activity {
public:
    ChangeRoom(const std::string& roomId) : Activity(), m_roomId{roomId}{}
    void Start() override;
    void Run (float dt) override {}
private:
    std::string m_roomId;
};
