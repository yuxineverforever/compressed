//
// Created by Yuxin Tang on 6/30/23.
//
#include <vector>
#include <cassert>
#include <set>
#include <random>
#include "Bigraph.h"

// Function to generate a random bipartite graph.
BiGraph generateBipartiteGraph(uint64_t num_left_vertices, uint64_t num_right_vertices, uint64_t num_edges) {
    assert (num_left_vertices * num_right_vertices >= num_edges);
    std::set<std::pair<uint64_t, uint64_t> > edgeSet;

    std::random_device rd_left;
    std::mt19937 gen_left(rd_left());
    std::uniform_int_distribution<uint64_t> distr_left(1, num_left_vertices);

    std::random_device rd_right;
    std::mt19937 gen_right(rd_right());
    std::uniform_int_distribution<uint64_t> distr_right(num_left_vertices+1, num_right_vertices+num_left_vertices);

    uint64_t edge_count = 0;
    while (edge_count < num_edges){
        uint64_t source = distr_left(gen_left);
        uint64_t destination = distr_right(gen_right);
        if (edgeSet.find(std::make_pair(source,destination))==edgeSet.end()){
            edgeSet.insert(std::make_pair(source, destination));
            edge_count++;
        }
    }
    std::cout << edge_count << std::endl;
    return BiGraph{num_left_vertices, num_right_vertices, edgeSet};
}

int main(){
    uint64_t left_graph_nodes_num = 60000;
    uint64_t right_graph_nodes_num = 60000;
    uint64_t edge_num = 69999;
    auto g= generateBipartiteGraph(left_graph_nodes_num, right_graph_nodes_num, edge_num);
    g.printEdgesToFile("in.in");
    return 0;
}
