//
//  iterator.h
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#ifndef iterator_h
#define iterator_h

#include <stack>
#include <queue>

// need to do something after each atomic operation on the stack.
// it will check the top element and do some custom operation

// generic iterator for Depth-first search in tree structures (for instance game objects and scheduler)
template <class T>
class DepthFirstIterator {
public:
    DepthFirstIterator() {}
    DepthFirstIterator(T* root) {
        m_stack.push(root);
        // custom operation here
    }
    
    
    DepthFirstIterator& operator++() {
        // pop
        T* top = m_stack.top();
        m_stack.pop();
        auto children = top->GetChildren();
        for (auto r = children.rbegin(); r != children.rend(); ++r) {
            m_stack.push(r->get());
        }
        // custom operation here
        return *this;
    }


    DepthFirstIterator& advanceSkippingChildren() {
        T* top = m_stack.top();
        m_stack.pop();
        return *this;
    }

    
    T& operator*() {
        return *(m_stack.top());
    }
    
    T* operator->()
    { return (m_stack.top()); }
    
    
    std::stack<T*> m_stack;


    bool operator== (const DepthFirstIterator& rhs) {
        return (m_stack.empty() ? rhs.m_stack.empty() : (m_stack == rhs.m_stack));
    }
    
    bool operator!= (const DepthFirstIterator& rhs) {
        return !(operator==(rhs));
    }
};

template <class T>
inline DepthFirstIterator<T> begin(T* root) {
    return DepthFirstIterator<T>(root);
}

template <class T>
inline DepthFirstIterator<T> end(T* root) {
    return DepthFirstIterator<T>();
}

#endif /* iterator_h */
