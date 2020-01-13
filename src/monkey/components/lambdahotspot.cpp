
#include <monkey/components/lambdahotspot.h>

LambdaHotSpot::LambdaHotSpot(const LambdaHotSpot& orig) : HotSpot(orig),
m_onEnter(orig.m_onEnter), m_onLeave(orig.m_onLeave), m_onClick(orig.m_onClick) {
}

std::shared_ptr<Component> LambdaHotSpot::clone() const {
    return std::make_shared<LambdaHotSpot>(LambdaHotSpot(*this));
}
