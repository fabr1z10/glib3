#pragma once

#include <monkey/activity.h>
#include <queue>

class __attribute__ ((visibility ("default"))) Sequence : public Activity {
public:
    Sequence();
    Sequence (const ITab& t);

    void Start() override {}
    void Run (float dt) override;
    void Push (std::shared_ptr<Activity> activity);
    void NotifySuspend() override;
private:
    std::shared_ptr<Activity> m_current;
    std::queue<std::shared_ptr<Activity>> m_innerActivities;
};