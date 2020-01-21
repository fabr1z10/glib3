#include <monkey/activity.h>

Activity::~Activity() {
    //std::cerr << "clering activity...\n" << &typeid(*this);
    // if (!m_complete)
    //    SetComplete();
}


void Activity::Reset() {
    m_complete = false;
//    for (auto& a : m_following) {
//        a->Reset();
//    }
}


void Activity::SetComplete() {
    m_complete = true;

}