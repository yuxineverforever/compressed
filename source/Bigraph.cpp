//
// Created by Yuxin Tang on 6/30/23.
//
#include "Bigraph.h"


BiGraph::BiGraph(const uint64_t& leftSetSize,
        const uint64_t& rightSetSize,
        const std::set<std::pair<uint64_t, uint64_t>>& edgeSet) {
    leftNodesNum = leftSetSize;
    rightNodesNum = rightSetSize;
    edges = edgeSet;
}

[[maybe_unused]] BiGraph::BiGraph(const uint64_t& leftSetSize,
        const uint64_t& rightSetSize){
    leftNodesNum = leftSetSize;
    rightNodesNum = rightSetSize;
}

void BiGraph::addEdge(const uint64_t& s, const uint64_t& d){
    edges.insert(std::make_pair(s,d));
}

void BiGraph::printEdgesToFile(const std::string& edgeFile){
    std::ofstream ostream(edgeFile);
    ostream << leftNodesNum << std::endl;
    ostream << rightNodesNum << std::endl;
    for (auto& e: edges){
        ostream << e.first << " " << e.second << std::endl;
    }
    ostream.close();
}

void BiGraph::loadFromFile(const std::string& filename){
    std::ifstream istream(filename);
    istream >> leftNodesNum >> rightNodesNum;
    uint64_t source;
    uint64_t dest;
    while (istream >> source >> dest){
        addEdge(source,dest);
    }
    processIntoAdjList();
}

void BiGraph::processIntoAdjList(){
    // process the edge into adjacency list format
    for (auto& e: edges){
        if (leftEdgeAdjLists.find(e.first) == leftEdgeAdjLists.end()){
            std::vector<uint64_t> neighbors;
            neighbors.push_back(e.second);
            leftEdgeAdjLists[e.first] = neighbors;
        } else {
            leftEdgeAdjLists[e.first].push_back(e.second);
        }

        if (rightEdgeAdjLists.find(e.second) == rightEdgeAdjLists.end()){
            std::vector<uint64_t> neighbors;
            neighbors.push_back(e.first);
            rightEdgeAdjLists[e.second] = neighbors;
        } else {
            rightEdgeAdjLists[e.second].push_back(e.first);
        }
    }
    isProcessIntoAdjList = true;
}