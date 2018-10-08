#ifndef __DIRECTED_GRAPH_H
#define __DIRECTED_GRAPH_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <limits>

template<typename Key, typename Value = Key>
class DirectedGraph;


template<typename Key, typename Value = Key>
class DNode {
public:
    DNode(Key key) : m_key(key), m_value(key) {}
    DNode(Key key, Value value) : m_key(key), m_value(value) {}
    Key GetKey() const {
        return m_key;
    }
    Value& GetValue() {
        return m_value;
    }
    friend class DirectedGraph<Key, Value>;
    const std::unordered_map<Key, double>& GetNext() const {
        return m_next;
    };
    const std::unordered_map<Key, double>& GetPrevious() const {
        return m_prev;
    };
    int GetInDegree();
    int GetOutDegree();
private:
    void AddEdgeTo(Key otherNode, double weight);
    void AddEdgeFrom(Key otherNode, double weight);
    std::unordered_map<Key, double> m_next;
    std::unordered_map<Key, double> m_prev;
    Key m_key;
    Value m_value;
};

template<typename Key, typename Value>
void DNode<Key, Value>::AddEdgeTo(Key otherNode, double weight) {
    m_next[otherNode] = weight;
}

template<typename Key, typename Value>
void DNode<Key, Value>::AddEdgeFrom(Key otherNode, double weight) {
    m_prev[otherNode] = weight;
}


template<class Key, class Value>
class DirectedGraph {
public:
    DirectedGraph() {}
    void AddNode (Key key) {
        AddNode(key, key);
    }
    void AddNode (Key key, Value value) {
        AddNode(std::make_shared<DNode<Key, Value>>(key, value));
    }
    void AddNode (std::shared_ptr<DNode<Key, Value>> node);
    void AddEdge (Key source, Key dest, double weight);
    DNode<Key, Value>* Get(Key key) const;
    Value& GetValue(Key key) const;
    std::unordered_set<Key> GetKeys() const;
    int GetNodeCount() {
        return m_nodes.size();
    }
private:
    std::unordered_map<Key, std::shared_ptr<DNode<Key, Value>>> m_nodes;

};

template<typename Key, typename Value>
std::unordered_set<Key> DirectedGraph<Key, Value>::GetKeys() const {
    std::unordered_set<Key> keys;
    for (auto& node : m_nodes)
        keys.insert(node.first);
    return keys;
};

template<typename Key, typename Value>
DNode<Key, Value>* DirectedGraph<Key, Value>::Get(Key key) const {
    auto it = m_nodes.find(key);
    if (it == m_nodes.end())
        return nullptr;
    return it->second.get();

};

template <typename Key, typename Value>
Value& DirectedGraph<Key, Value>::GetValue(Key key) const {
    auto node = Get(key);
    return node->GetValue();
}

template<typename Key, typename Value>
void DirectedGraph<Key, Value>::AddNode(std::shared_ptr<DNode<Key, Value>> node) {
    m_nodes[node->GetKey()] = node;
}

template<typename Key, typename Value>
void DirectedGraph<Key, Value>::AddEdge(Key first, Key second, double weight) {
    auto n1 = Get(first);
    if (n1 == nullptr)
        throw std::runtime_error("Cannot find node");
    auto n2 = Get(second);
    if (n2 == nullptr)
        throw std::runtime_error("Cannot find node");
    n1->AddEdgeTo(second, weight);
    n2->AddEdgeFrom(first, weight);
}



#endif
