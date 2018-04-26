//
// Created by fabrizio on 25/04/18.
//

#ifndef GLIB_ALGO_H
#define GLIB_ALGO_H

#include "graph.h"
#include <unordered_set>

template<typename Key, typename Value>
std::vector<Key> FindShortestPath (const Graph<Key, Value>& graph, Key start, Key end) {
    std::vector<Key> out;
    out.push_back(start);
    if (start == end)
        return out;
    std::unordered_set<Key> keys = graph.GetKeys();
    auto startNode = graph.Get(start);

    std::unordered_map<Key, double> l;
    std::unordered_map<Key, Node<Key, Value>*> p;
    // initialize the maps
    for (auto& k : keys) {
        l[k] = startNode->GetWeightTo(k);
        p[k] = startNode;
    }


};

#endif //GLIB_ALGO_H
