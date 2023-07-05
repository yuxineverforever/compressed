//
// Created by Yuxin Tang on 7/3/23.
//
#include "countingAlgorithm.h"

uint64_t ButterflyCounting::monarch(const BiGraph &b) {
    assert(b.isProcessIntoAdjList==true);
    uint64_t butterflyCount = 0;
    uint64_t leftDegreeSquare = 0;
    uint64_t rightDegreeSquare = 0;
    std::unordered_map<uint64_t, uint64_t> hashMap;
    for (auto& v:b.leftEdgeAdjLists){
        auto degree = v.second.size();
        leftDegreeSquare += (degree*degree);
    }
    for (auto& v: b.rightEdgeAdjLists){
        auto degree = v.second.size();
        rightDegreeSquare += (degree*degree);
    }

    if (leftDegreeSquare < rightDegreeSquare) {
        size_t loopCount = 0;
        auto begin = std::chrono::high_resolution_clock::now();
        for (auto& e:b.leftEdgeAdjLists){
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
        std::cout << "size of the hash map: " << hashMap.size() << std::endl;
        std::cout << "Time of neighbor searching: " << std::chrono::duration_cast<std::chrono::duration<float>>(mid - begin).count() << " secs." << std::endl;
        std::cout << "Time of aggregation: " << std::chrono::duration_cast<std::chrono::duration<float>>(end - mid).count() << " secs." << std::endl;
        std::cout << "Loop Count : " << loopCount << std::endl;
    }
    else {
        size_t loopCount = 0;
        auto begin = std::chrono::high_resolution_clock::now();
        for (auto& e:b.rightEdgeAdjLists){
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
        std::cout << "size of the hash map: " << hashMap.size() << std::endl;
        std::cout << "Time of neighbor searching: " << std::chrono::duration_cast<std::chrono::duration<float>>(mid - begin).count() << " secs." << std::endl;
        std::cout << "Time of aggregation: " << std::chrono::duration_cast<std::chrono::duration<float>>(end - mid).count() << " secs." << std::endl;
        std::cout << "Loop Count : " << loopCount << std::endl;
    }
    return butterflyCount;
}

uint64_t ButterflyCounting::BFC_IBS(BiGraph &b) {
    assert(b.isProcessIntoAdjList==true);
    uint64_t butterflyCount = 0;
    uint64_t leftDegreeSquare = 0;
    uint64_t rightDegreeSquare = 0;
    for (auto& v:b.leftEdgeAdjLists){
        auto degree = v.second.size();
        leftDegreeSquare += (degree*degree);
    }
    for (auto& v: b.rightEdgeAdjLists){
        auto degree = v.second.size();
        rightDegreeSquare += (degree*degree);
    }
    float neighbor_search_time = 0.0;
    float aggregation_time = 0.0;
    if (leftDegreeSquare < rightDegreeSquare){
        size_t loopCount = 0;
        size_t accumulatedHashMapSize = 0;
        for (auto& start:b.rightEdgeAdjLists){
            std::unordered_map<uint64_t, uint64_t> wedge_count;
            auto b1 = std::chrono::high_resolution_clock::now();
            for (auto& middle : start.second) {
                for (auto& end : b.leftEdgeAdjLists[middle]){
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
            accumulatedHashMapSize += wedge_count.size();
            for (auto& w:wedge_count){
                if (w.second>1){
                    butterflyCount += ((w.second -1) * w.second / 2);
                }
            }

            auto b3 = std::chrono::high_resolution_clock::now();
            neighbor_search_time += std::chrono::duration_cast<std::chrono::duration<float>>(b2 - b1).count();
            aggregation_time += std::chrono::duration_cast<std::chrono::duration<float>>(b3 - b2).count();
        }
        std::cout << "size of the hash map: " << accumulatedHashMapSize << std::endl;
        std::cout << "Time of neighbor searching: " << neighbor_search_time << " secs." << std::endl;
        std::cout << "Time of aggregation: " << aggregation_time << " secs." << std::endl;
        std::cout << "Loop Count : " << loopCount << std::endl;
    }
    else {

        size_t loopCount = 0;
        size_t accumulatedHashMapSize = 0;
        for (auto& start:b.leftEdgeAdjLists){
            std::unordered_map<uint64_t, uint64_t> wedge_count;
            auto b1 = std::chrono::high_resolution_clock::now();
            for (auto& middle : start.second) {
                for (auto& end : b.rightEdgeAdjLists[middle]){
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
            accumulatedHashMapSize += wedge_count.size();
            for (auto& w:wedge_count){
                if (w.second>1){
                    butterflyCount += ((w.second -1) * w.second / 2);
                }
            }

            auto b3 = std::chrono::high_resolution_clock::now();
            neighbor_search_time += std::chrono::duration_cast<std::chrono::duration<float>>(b2 - b1).count();
            aggregation_time += std::chrono::duration_cast<std::chrono::duration<float>>(b3 - b2).count();
        }
        std::cout << "size of the hash map: " << accumulatedHashMapSize << std::endl;
        std::cout << "Time of neighbor searching: " << neighbor_search_time << " secs." << std::endl;
        std::cout << "Time of aggregation: " << aggregation_time << " secs." << std::endl;
        std::cout << "Loop Count : " << loopCount << std::endl;
    }
    return butterflyCount;
}

uint16_t ButterflyCounting::BFC_VPS(BiGraph &b) {
    assert(b.isProcessIntoAdjList==true);
    uint64_t butterflyCount = 0;
    float neighbor_search_time = 0.0;
    float aggregation_time = 0.0;
    size_t loopCount = 0;
    size_t accumulatedHashMapSize = 0;
    for (auto& start:b.rightEdgeAdjLists){
        std::unordered_map<uint64_t, uint64_t> wedge_count;
        auto b1 = std::chrono::high_resolution_clock::now();
        auto start_priority = start.second.size();
        for (auto& middle : start.second) {
            auto middle_priority = b.leftEdgeAdjLists[middle].size();
            // if p(middle) is larger than p(start), then contine;
            // else go to next step
            if (middle_priority > start_priority){
                continue;
            } else if (middle_priority == start_priority){
                if (middle>start.first){
                    continue;
                }
            }
            for (auto& end : b.leftEdgeAdjLists[middle]){
                auto end_priority = b.rightEdgeAdjLists[end].size();
                // if p(end) is larger than p(start), then contine;
                // else go to next step
                if (end_priority > start_priority){
                    continue;
                } else if (end_priority == start_priority){
                    if (end>=start.first){
                        continue;
                    }
                }
                loopCount++;
                if (wedge_count.find(end)==wedge_count.end()){
                    wedge_count.insert({end,1});
                } else {
                    wedge_count[end]++;
                }
            }
        }
        auto b2 = std::chrono::high_resolution_clock::now();
        accumulatedHashMapSize += wedge_count.size();
        for (auto& w:wedge_count){
            if (w.second>1){
                butterflyCount += ((w.second -1) * w.second / 2);
            }
        }
        auto b3 = std::chrono::high_resolution_clock::now();
        neighbor_search_time += std::chrono::duration_cast<std::chrono::duration<float>>(b2 - b1).count();
        aggregation_time += std::chrono::duration_cast<std::chrono::duration<float>>(b3 - b2).count();
    }

    for (auto& start:b.leftEdgeAdjLists){
        std::unordered_map<uint64_t, uint64_t> wedge_count;
        auto b1 = std::chrono::high_resolution_clock::now();
        auto start_priority = start.second.size();
        for (auto& middle : start.second) {
            auto middle_priority = b.rightEdgeAdjLists[middle].size();
            // if p(middle) is larger than p(start), then contine;
            // else go to next step
            if (middle_priority > start_priority){
                continue;
            } else if (middle_priority == start_priority){
                if (middle>start.first){
                    continue;
                }
            }
            for (auto& end : b.rightEdgeAdjLists[middle]){
                auto end_priority = b.leftEdgeAdjLists[end].size();
                // if p(end) is larger than p(start), then contine;
                // else go to next step
                if (end_priority > start_priority){
                    continue;
                } else if (end_priority == start_priority){
                    if (end>=start.first){
                        continue;
                    }
                }
                loopCount++;
                if (wedge_count.find(end)==wedge_count.end()){
                    wedge_count.insert({end,1});
                } else {
                    wedge_count[end]++;
                }
            }
        }
        auto b2 = std::chrono::high_resolution_clock::now();
        accumulatedHashMapSize += wedge_count.size();
        for (auto& w:wedge_count){
            if (w.second>1){
                butterflyCount += ((w.second -1) * w.second / 2);
            }
        }
        auto b3 = std::chrono::high_resolution_clock::now();
        neighbor_search_time += std::chrono::duration_cast<std::chrono::duration<float>>(b2 - b1).count();
        aggregation_time += std::chrono::duration_cast<std::chrono::duration<float>>(b3 - b2).count();
    }
    std::cout << "size of the hash map: " << accumulatedHashMapSize << std::endl;
    std::cout << "Time of neighbor searching: " << neighbor_search_time << " secs." << std::endl;
    std::cout << "Time of aggregation: " << aggregation_time << " secs." << std::endl;
    std::cout << "Loop Count : " << loopCount << std::endl;
    return butterflyCount;
}

uint16_t ButterflyCounting::ParButterfly(const BiGraph &b) {
    return 0;
}
