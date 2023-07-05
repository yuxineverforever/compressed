//
// Created by Yuxin Tang on 6/30/23.
//
#ifndef BUTTERFLY_COUNTING_BIGRAPH_H
#define BUTTERFLY_COUNTING_BIGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <random>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <chrono>
#include "hash.h"
class BiGraph {
public:
    // Number of Nodes on the left side of the bipartite graph.
    uint64_t leftNodesNum{};

    // Number of Nodes on the right side of the bipartite graph.
    uint64_t rightNodesNum{};

    // a set of all the edges.
    std::set<std::pair<uint64_t, uint64_t>> edges;

    // a map to store edges and put neighbors into adjacency lists.
    std::unordered_map<uint64_t, std::vector<uint64_t>> leftEdgeAdjLists;

    // a map to store edges and put neighbors into adjacency lists.
    std::unordered_map<uint64_t, std::vector<uint64_t>> rightEdgeAdjLists;

    // mark if bipartite graph has been processed into adjaency list
    bool isProcessIntoAdjList = false;

    BiGraph() = default;

    BiGraph(const uint64_t& leftSetSize,
            const uint64_t& rightSetSize,
            const std::set<std::pair<uint64_t, uint64_t>>& edgeSet);

    [[maybe_unused]] BiGraph(const uint64_t& leftSetSize,
            const uint64_t& rightSetSize);

    void addEdge(const uint64_t& s, const uint64_t& d);

    void printEdgesToFile(const std::string& edgeFile);

    void loadFromFile(const std::string& filename);

    void processIntoAdjList();
};

#endif //BUTTERFLY_COUNTING_BIGRAPH_H
