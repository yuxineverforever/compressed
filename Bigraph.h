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

uint64_t fasthash(uint64_t a, uint64_t b){
    return (a > b) ? ((a << 32) | b) : ((b << 32) | a);
}

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

    std::unordered_map<uint64_t, std::vector<uint64_t>> rightEdgeAdjLists;

    BiGraph() = default;

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
            ostream << e.first << " " << e.second << std::endl;
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
        processIntoAdjList();
    }

    void processIntoAdjList(){
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
    }



    uint64_t monarch(){
        uint64_t butterflyCount = 0;
        uint64_t leftDegreeSquare = 0;
        uint64_t rightDegreeSquare = 0;
        std::unordered_map<uint64_t, uint64_t> hashMap;
        for (auto& v:leftEdgeAdjLists){
            auto degree = v.second.size();
            leftDegreeSquare += (degree*degree);
        }
        for (auto& v: rightEdgeAdjLists){
            auto degree = v.second.size();
            rightDegreeSquare += (degree*degree);
        }

        if (leftDegreeSquare < rightDegreeSquare) {
            size_t loopCount = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto& e:leftEdgeAdjLists){
                size_t neighbor_size = e.second.size();
                auto& adjList = e.second;
                for (size_t i = 0; i<neighbor_size; i++){
                    for (size_t j = i+1; j<neighbor_size; j++){
                        loopCount++;
                        uint64_t hash_code = fasthash(adjList[i], adjList[j]);
                        if (hashMap.find(hash_code)!=hashMap.end())
                            hashMap[hash_code]++;
                        else
                            hashMap.insert({hash_code,1});
                    }
                }
            }
            auto mid = std::chrono::high_resolution_clock::now();
            for (auto& p:hashMap){
                butterflyCount += ((p.second -1) * p.second / 2);
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Time of neighbor searching: " << std::chrono::duration_cast<std::chrono::duration<float>>(mid - begin).count() << " secs." << std::endl;
            std::cout << "Time of aggregation: " << std::chrono::duration_cast<std::chrono::duration<float>>(end - mid).count() << " secs." << std::endl;
            std::cout << "Loop Count : " << loopCount << std::endl;
        }
        else {
            size_t loopCount = 0;
            auto begin = std::chrono::high_resolution_clock::now();
            for (auto& e:rightEdgeAdjLists){
                size_t neighbor_size = e.second.size();
                auto& adjList = e.second;
                for (size_t i = 0; i<neighbor_size; i++){
                    for (size_t j = i+1; j<neighbor_size; j++){
                        loopCount++;
                        uint64_t hash_code = fasthash(adjList[i], adjList[j]);
                        if (hashMap.find(hash_code)!=hashMap.end())
                            hashMap[hash_code]++;
                        else
                            hashMap.insert({hash_code,1});
                    }
                }
            }
            auto mid = std::chrono::high_resolution_clock::now();
            for (auto& p:hashMap){
                butterflyCount += ((p.second -1) * p.second / 2);
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Time of neighbor searching: " << std::chrono::duration_cast<std::chrono::duration<float>>(mid - begin).count() << " secs." << std::endl;
            std::cout << "Time of aggregation: " << std::chrono::duration_cast<std::chrono::duration<float>>(end - mid).count() << " secs." << std::endl;
            std::cout << "Loop Count : " << loopCount << std::endl;
        }
        return butterflyCount;
    }

    uint64_t BFC_IBS() {
        uint64_t butterflyCount = 0;
        uint64_t leftDegreeSquare = 0;
        uint64_t rightDegreeSquare = 0;
        for (auto& v:leftEdgeAdjLists){
            auto degree = v.second.size();
            leftDegreeSquare += (degree*degree);
        }
        for (auto& v: rightEdgeAdjLists){
            auto degree = v.second.size();
            rightDegreeSquare += (degree*degree);
        }


        float neighbor_search_time = 0.0;
        float aggregation_time = 0.0;

        if (leftDegreeSquare < rightDegreeSquare){
            size_t loopCount = 0;
            for (auto& start:rightEdgeAdjLists){
                std::unordered_map<uint64_t, uint64_t> wedge_count;
                auto b1 = std::chrono::high_resolution_clock::now();

                for (auto& middle : start.second) {
                    for (auto& end : leftEdgeAdjLists[middle]){
                        loopCount++;
                        if (end > start.first){
                            if (wedge_count.find(end)==wedge_count.end()){
                                wedge_count.insert({end,1});
                            } else {
                                wedge_count[end]++;
                            }
                        }
                    }
                }

                auto b2 = std::chrono::high_resolution_clock::now();

                for (auto& w:wedge_count){
                    if (w.second>1){
                        butterflyCount += ((w.second -1) * w.second / 2);
                    }
                }

                auto b3 = std::chrono::high_resolution_clock::now();
                neighbor_search_time += std::chrono::duration_cast<std::chrono::duration<float>>(b2 - b1).count();
                aggregation_time += std::chrono::duration_cast<std::chrono::duration<float>>(b3 - b2).count();
            }

            std::cout << "Time of neighbor searching: " << neighbor_search_time << " secs." << std::endl;
            std::cout << "Time of aggregation: " << aggregation_time << " secs." << std::endl;
            std::cout << "Loop Count : " << loopCount << std::endl;
        }
        else {

            size_t loopCount = 0;
            for (auto& start:leftEdgeAdjLists){
                std::unordered_map<uint64_t, uint64_t> wedge_count;
                auto b1 = std::chrono::high_resolution_clock::now();
                for (auto& middle : start.second) {
                    for (auto& end : rightEdgeAdjLists[middle]){
                        loopCount++;
                        if (end > start.first){
                            if (wedge_count.find(end)==wedge_count.end()){
                                wedge_count.insert({end,1});
                            } else {
                                wedge_count[end]++;
                            }
                        }
                    }
                }

                auto b2 = std::chrono::high_resolution_clock::now();
                for (auto& w:wedge_count){
                    if (w.second>1){
                        butterflyCount += ((w.second -1) * w.second / 2);
                    }
                }

                auto b3 = std::chrono::high_resolution_clock::now();
                neighbor_search_time += std::chrono::duration_cast<std::chrono::duration<float>>(b2 - b1).count();
                aggregation_time += std::chrono::duration_cast<std::chrono::duration<float>>(b3 - b2).count();
            }
            std::cout << "Time of neighbor searching: " << neighbor_search_time << " secs." << std::endl;
            std::cout << "Time of aggregation: " << aggregation_time << " secs." << std::endl;
            std::cout << "Loop Count : " << loopCount << std::endl;
        }
        return butterflyCount;
    }
};

#endif //BUTTERFLY_COUNTING_BIGRAPH_H
