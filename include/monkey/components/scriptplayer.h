#pragma once

#include <monkey/component.h>
#include <monkey/script.h>

class ScriptPlayer : public Component {
public:
    ScriptPlayer(const ITab&);

    virtual ~ScriptPlayer();

    void Start() override {}
    void Update(double) override {}
    void play (std::shared_ptr<Script>);
    using ParentClass = ScriptPlayer;
    void killScripts ();
private:
    std::vector<std::shared_ptr<Script>> m_scripts;
};