#include <monkey/components/statemachine.h>

// do-nothing state
class NullState : public State {
public:
    NullState(const ITab& t);
    void Init(const ITab& d) override;
    void Run(double) override;
    void End() override;
};