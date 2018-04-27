//
// Created by fabrizio on 25/04/18.
//

#ifndef GLIB_ALGO_H
#define GLIB_ALGO_H

#include "graph.h"
#include <unordered_set>
#include <deque>

// Find the shortest path between start and end returning a sequence of keys
// using Dijkstra algorithm
template<typename Key, typename Value>
std::deque<Key> FindShortestPath (const Graph<Key, Value>& graph, Key start, Key end) {
    std::deque<Key> out;
    out.push_back(end);
    if (start == end) {
        return out;
    }
    std::unordered_set<Key> keys = graph.GetKeys();
    auto startNode = graph.Get(start);

    std::unordered_map<Key, double> l;
    std::unordered_map<Key, Key> p;
    // initialize the maps
    for (auto& k : keys) {
        l[k] = startNode->GetWeightTo(k);
        p[k] = start;
    }

    // set of explored nodes
    std::unordered_set<Key> S {start};
    // set of unexplored nodes
    keys.erase(start);
    while (true) {
        // find node with min distance
        Key u;
        double currMin = std::numeric_limits<double>::infinity();
        for (auto& n : keys) {
            if (l[n] < currMin)
            {
                currMin = l[n];
                u = n;
            }
        }

        S.insert(u);
        keys.erase(u);
        if (u == end) {
            // we can exit
            break;
        }
        // now update distances of neighbors of u
        auto neighbors = graph.Get(u)->GetNeighbors();
        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            double alt = currMin + it->second;
            if (alt < l[it->first]) {
                l[it->first] = alt;
                p[it->first] = u;
            }
        }
    }

    // build the path from the end
    Key u = end;
    while (p[u] != start) {
        out.push_front(p[u]);
        u = p[u];
    }
    out.push_front(start);
    return out;


};

#endif //GLIB_ALGO_H
