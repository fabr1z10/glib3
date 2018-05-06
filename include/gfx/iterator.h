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

// generic iterator for Depth-first search in tree structures (for instance game objects and scheduler)
template <class T>
class DepthFirstIterator {
public:
    DepthFirstIterator() {}
    DepthFirstIterator(T* root) {
        m_stack.push(root);
    }
    
    
    DepthFirstIterator& operator++() {
        T* top = m_stack.top();
        m_stack.pop();
        if (!top->m_children.empty()) {
            for (auto& c : top->m_children)
                m_stack.push(c.get());
        }
        return *this;
        
    }
    
    T& operator*() const {
        return *(m_stack.top());
    }
    
    T* operator->() const
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
