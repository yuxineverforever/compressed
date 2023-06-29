
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <set>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

#define SZ(x) ((int)x.size())
#define ll long long
#define ull unsigned long long
#define ld long double
#define eps 1e-11
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

const int ITER_VER = 2200;
const ll shift = 1000 * 1000 * 1000LL;
const double TIME_LIMIT = 20;
const int N_WEDGE_ITERATIONS = 2 * 1000 * 1000 * 10;
const int ITERATIONS_SAMPLING = 5;
const int N_SPARSIFICATION_ITERATIONS = 5;
const int TIME_LIMIT_SPARSIFICATION = 10000; // !half an hour
const int N_FAST_EDGE_BFC_ITERATIONS = 2100; // used for fast edge sampling
const int N_FAST_WEDGE_ITERATIONS = 50; // used for fast wedge sampling

set < pair <int, int> > edges;
vector < pair <int, int> > list_of_edges;
map < int, int > vertices [2];
vector <int> index_map;
vector <int> vertices_in_left;
vector <int> vertices_in_right;
vector < vector <int> > adj;
vector < vector < int > > sampled_adj_list;
vector <bool> visited;
vector <int> list_of_vertices;
vector <int> vertex_counter;

ll n_vertices;
ll n_edges;
ld exact_n_bf;
ll n_wedge_in_partition[2];
ll largest_index_in_partition[2];

vector <int> clr;
vector <int> hashmap_C;
vector <ll> sum_wedges;
vector <ll> sum_deg_neighbors;
vector <int> aux_array_two_neighboorhood;

void clear_everything() {
	largest_index_in_partition[0] = largest_index_in_partition[1] = 0;
	n_vertices = 0;
	n_edges = 0;
	edges.clear();
	vertices[0].clear(); vertices[1].clear();
	index_map.clear();
	vertices_in_left.clear();
	vertices_in_right.clear();
	adj.clear();
	sampled_adj_list.clear();
	visited.clear();
	list_of_edges.clear();
	vertex_counter.clear();
	clr.clear();
	hashmap_C.clear();
	sum_wedges.clear();
	sum_deg_neighbors.clear();
	aux_array_two_neighboorhood.clear();
}
void resize_all() {
	clr.resize(n_vertices);
	hashmap_C.resize(n_vertices);
	aux_array_two_neighboorhood.resize(n_vertices);
	sum_wedges.resize(n_vertices);
	visited.resize(n_vertices);
	index_map.resize(n_vertices);
	sum_deg_neighbors.resize(n_vertices);
}

// ------------- Read the graph ---------------------
void add_vertex(int A, int side) {
	if (vertices[side].find(A) == vertices[side].end()) {
		if (side == 0) vertices_in_left.push_back(A);
		else vertices_in_right.push_back(A);
		vertices[side][A] = 1;
	}
}

void get_index(int &A, int side) {
	if (vertices[side].find(A) == vertices[side].end()) {
		vertices[side][A] = largest_index_in_partition[side] ++ ;
	}
	A = vertices[side][A];
}

void add_edge(int &A, int &B) {
	add_vertex(A, 0);
	add_vertex(B, 1);
	if (edges.find(make_pair(A, B)) == edges.end()) {
		edges.insert(make_pair(A, B));
		n_edges++;
	}
}

bool all_num(string &s) {
	for (int i = 0; i < SZ(s); i++) if ((s[i] >= '0' && s [i] <= '9') == false) return false;
	return true;
}

void get_graph() {
	string s;
	cin.clear();
	while (getline(cin, s)) {
 		stringstream ss;
         ss << s;
		vector <string> vec_str; 
		for (string z; ss >> z; vec_str.push_back(z));
		if (SZ(vec_str) >= 2) {
			bool is_all_num = true;
			for (int i = 0; i < min (2, SZ(vec_str)) ; i++) is_all_num &= all_num(vec_str[i]);
			if (is_all_num) {
				int A, B;
				ss.clear();
                ss << vec_str[0];
                ss >> A;
				ss.clear();
                ss << vec_str[1];
                ss >> B;
				add_edge(A, B);
			}
		}
	}
	vertices[0].clear();
	vertices[1].clear();
	largest_index_in_partition[0] = 0;
	largest_index_in_partition[1] = SZ(vertices_in_left);
	n_vertices = SZ(vertices_in_left) + SZ(vertices_in_right);
	adj.resize(n_vertices, vector <int> ());
	for (auto edge : edges) {
		int A = edge.first;
		int B = edge.second;
		get_index(A, 0);
		get_index(B, 1);
		adj[A].push_back(B);
		adj[B].push_back(A);
		list_of_edges.emplace_back(A, B);
	}
	resize_all();

	n_wedge_in_partition[0] = 0;
	for (int i = 0; i < largest_index_in_partition[0]; i++) {
		n_wedge_in_partition[0] += (((ll)SZ(adj[i])) * (SZ(adj[i]) - 1)) >> 1;
	}
	n_wedge_in_partition[1] = 0;
	for (int i = largest_index_in_partition[0]; i < largest_index_in_partition[1]; i++) {
		n_wedge_in_partition[1] += ((ll)SZ(adj[i]) * (SZ(adj[i]) - 1)) >> 1;
	}
	for (int i = 0; i < n_vertices; i++) {
		sort(adj[i].begin(), adj[i].end());
		sum_deg_neighbors[i] = 0;
		for (auto neighbor : adj[i]) {
			sum_deg_neighbors[i] += SZ(adj[neighbor]);
		}
	}
	cerr << " for test # edges :: " << SZ(list_of_edges) << " left :: " << SZ(vertices_in_left) << " right :: "  << SZ(vertices_in_right) << endl;
	sort(list_of_edges.begin(), list_of_edges.end());
	fclose(stdin);
}
// ------------- Read the graph ---------------------

ll exact_butterfly_counting(vector < vector <int> > &graph) {
	int side = n_wedge_in_partition[0] < n_wedge_in_partition[1];
	ld res = 0;
	for (int vertex = side == 0 ? 0 : SZ(vertices_in_left) ; vertex < largest_index_in_partition[side]; vertex++) {
		int idx = 0;
		for (int j = 0; j < SZ(graph[vertex]); j++) {
			int neighbor = graph[vertex][j];
			for (int k = 0; k < SZ(graph[neighbor]); k++) {
				int two_hop_neighborhood = graph[neighbor][k];
				if (vertex > two_hop_neighborhood) {
					res += hashmap_C[two_hop_neighborhood];
					hashmap_C[two_hop_neighborhood] ++;
					if (hashmap_C[two_hop_neighborhood] == 1)
						aux_array_two_neighboorhood[idx++] = two_hop_neighborhood;
				}
				else break;
			}
		}
		for (int j = 0; j < idx; j++) {
			hashmap_C[aux_array_two_neighboorhood[j]] = 0;
		}
	}
	return res;
}


void exact_algorithm_time_tracker() {
	double beg_clock = clock();
	exact_n_bf = exact_butterfly_counting(adj);
	double end_clock = clock();
	double elapsed_time = (end_clock - beg_clock) / CLOCKS_PER_SEC;
	cout << " Exact algorithm is done in " << elapsed_time << " secs. There are " << exact_n_bf << " butterflies." << endl;
}

void read_the_graph() {
	clear_everything();
	get_graph();
}

int main() {
    read_the_graph();
    exact_algorithm_time_tracker();
	cerr << " Take a look at the output file ..." << endl;
	return 0;
}