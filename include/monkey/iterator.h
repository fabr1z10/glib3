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
#include <functional>

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
    bool end() {
        return m_stack.empty();
    }
    // this function is called when a node is being popped (when the func is called the node passed has just been popped)
    virtual void onPop(T*) {}
    // this function is called everytime a new node is ready to be accessed with the deref operator
    virtual void onNext() {}

    DepthFirstIterator& operator++() {
        auto top = m_stack.top();
        m_stack.pop();
        // Do something here
        onPop(top);

        auto& children = top->GetChildren();
        for (auto it = children.rbegin(); it != children.rend(); it++) {
        //for (const auto& layer : children) {
            for (auto& child : it->second) {
                m_stack.push(child.second.get());
            }
        }
        if (!m_stack.empty()) {
            onNext();
        }
        return *this;
    }


    DepthFirstIterator& advanceSkippingChildren() {
        T* top = m_stack.top();
        m_stack.pop();
        onPop(top);
        if (!m_stack.empty()) {
            onNext();
        }
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
