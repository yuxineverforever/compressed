//
// Created by nodeu on 6/28/23.
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

class BiGraph {
public:
    // Number of Nodes on the left side of the bipartite graph.
    uint64_t leftNodesNum;

    // Number of Nodes on the right side of the bipartite graph.
    uint64_t rightNodesNum;

    // a set of all the edges
    std::set<std::pair<uint64_t, uint64_t>> edges;

    BiGraph(const uint64_t& leftSetSize,
            const uint64_t& rightSetSize,
            const std::set<std::pair<uint64_t, uint64_t>>& edgeSet) {
        leftNodesNum = leftSetSize;
        rightNodesNum = rightSetSize;
        edges = edgeSet;
    }

    BiGraph(const uint64_t& leftSetSize,
            const uint64_t& rightSetSize){
        leftNodesNum = leftSetSize;
        rightNodesNum = rightSetSize;
    }

    void addEdge(const uint64_t& s, const uint64_t& d){
        edges.insert(std::make_pair(s,d));
    }

    void printEdgesToFile(const std::string& edgeFile){
        std::ofstream ostream(edgeFile);

        ostream << leftNodesNum << std::endl;

        ostream << rightNodesNum << std::endl;

        for (auto& e: edges){
            ostream << e.first << ", " << e.second << std::endl;
        }
        ostream.close();
    }

    void loadFromFile(const std::string& filename){
        std::ifstream istream(filename);
        istream >> leftNodesNum >> rightNodesNum;
        uint64_t source;
        uint64_t dest;
        while (istream >> source >> dest){
            addEdge(source,dest);
        }
    }

    uint64_t monarch(){
        uint64_t butterflyCount = 0;
        return butterflyCount;
    }



};

#endif //BUTTERFLY_COUNTING_BIGRAPH_H
