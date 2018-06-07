#pragma once

#include <gfx/activity.h>
#include <string>


class ChangeRoom : public Activity {
public:
    ChangeRoom(int id, const std::string& roomId) : Activity(id), m_roomId{roomId}{}
    void Start() override;
    void Run (float dt) override {}
private:
    std::string m_roomId;
};
