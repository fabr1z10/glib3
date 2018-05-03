#ifndef __GRAPH_H
#define __GRAPH_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <limits>

template<typename Key, typename Value = Key>
class Graph;


template<typename Key, typename Value = Key>
class Node {
public:
    Node(Key key) : m_key(key), m_value(key) {}
    Node(Key key, Value value) : m_key(key), m_value(value) {}
    double GetWeightTo (Key otherNode) const;
    Key GetKey() const {
        return m_key;
    }
    Value& GetValue() {
        return m_value;
    }
    friend class Graph<Key, Value>;
    const std::unordered_map<Key, double>& GetNeighbors() const {
        return m_connections;
    };
private:
    void AddEdge(Key otherNode, double weight);
    std::unordered_map<Key, double> m_connections;
    Key m_key;
    Value m_value;
};

template<typename Key, typename Value>
void Node<Key, Value>::AddEdge(Key otherNode, double weight) {
    m_connections[otherNode] = weight;
}

template<typename Key, typename Value>
double Node<Key, Value>::GetWeightTo(Key otherNode) const {
    if (otherNode == m_key)
        return 0.0;
    auto iter = m_connections.find(otherNode);
    if (iter == m_connections.end())
        return std::numeric_limits<double>::infinity();
    return iter->second;
}

template<class Key, class Value>
class Graph {
public:
    Graph() {}
    void AddNode (Key key) {
        AddNode(key, key);
    }
    void AddNode (Key key, Value value) {
        AddNode(std::make_shared<Node<Key, Value>>(key, value));
    }
    void AddNode (std::shared_ptr<Node<Key, Value>> node);
    void AddEdge (Key first, Key second, double weight);
    Node<Key, Value>* Get(Key key) const;
    Value& GetValue(Key key) const;
    std::unordered_set<Key> GetKeys() const;
    int GetNodeCount() {
        return m_nodes.size();
    }
private:
    std::unordered_map<Key, std::shared_ptr<Node<Key, Value>>> m_nodes;

};

template<typename Key, typename Value>
std::unordered_set<Key> Graph<Key, Value>::GetKeys() const {
    std::unordered_set<Key> keys;
    for (auto& node : m_nodes)
        keys.insert(node.first);
    return keys;
};

template<typename Key, typename Value>
Node<Key, Value>* Graph<Key, Value>::Get(Key key) const {
    auto it = m_nodes.find(key);
    if (it == m_nodes.end())
        return nullptr;
    return it->second.get();

};

template <typename Key, typename Value>
Value& Graph<Key, Value>::GetValue(Key key) const {
    auto node = Get(key);
    return node->GetValue();
}

template<typename Key, typename Value>
void Graph<Key, Value>::AddNode(std::shared_ptr<Node<Key, Value>> node) {
    m_nodes[node->GetKey()] = node;
}

template<typename Key, typename Value>
void Graph<Key, Value>::AddEdge(Key first, Key second, double weight) {
    auto n1 = Get(first);
    if (n1 == nullptr)
        throw std::runtime_error("Cannot find node");
    auto n2 = Get(second);
    if (n2 == nullptr)
        throw std::runtime_error("Cannot find node");
    n1->AddEdge(second, weight);
    n2->AddEdge(first, weight);
}



#endif
