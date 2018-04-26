#ifndef __GRAPH_H
#define __GRAPH_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <limits>

template<typename Key, typename Value>
class Node {
public:
    Node(Value value);
    void AddEdge(Key otherNode, double weight);
    double GetWeightTo (Key otherNode) const;
private:
    std::unordered_map<Key, double> m_connections;
    Value m_value;
};

template<typename Key, typename Value>
void Node::AddEdge(Key otherNode, double weight) {
    m_connections[otherNode] = weight;
}

template<typename Key, typename Value>
double Node::GetWeightTo(Key otherNode) const {
    auto iter = m_connections.find(otherNode);
    if (iter == m_connections.end())
        return std::numeric_limits<double>::infinity();
    return iter->second;
}

template<class Key, class Value>
class Graph {
public:
    Graph();
    void AddNode (Key value, std::shared_ptr<Node<Key, Value>> node);
    void AddEdge (Key first, Key second, double weight);
    Node<Key, Value>* Get(Key key) const;
    std::unordered_set<Key> GetKeys() const;
private:
    std::unordered_map<Key, std::shared_ptr<Node<Key, Value>>> m_nodes;

};

template<typename Key, typename Value>
void Graph::AddNode(Key key, std::shared_ptr<Node<Key, Value>> node) {
    m_nodes[key] = node;
}

template<typename Key, typename Value>
void Graph::AddEdge(Key first, Key second, double weight) {
    auto n1 = Get(first);
    if (n1 == nullptr)
        throw std::runtime_error("Cannot find node");
    auto n2 = Get(second);
    if (n2 == nullptr)
        throw std::runtime_error("Cannot find node");
    n1->AddEdge(second, weight));
    n2->AddEdge(first, weight));
}



#endif
