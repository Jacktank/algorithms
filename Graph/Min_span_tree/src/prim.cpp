#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>

#define INF_VAL 0x8888888
#define MAX_VERTEX 100
    
//define a vector for closed set;
int closed_node[MAX_VERTEX];

//define a dict for vertex to print node info
std::unordered_map<int, std::string> id_to_string_map = {
    {0, "A"}, {1, "B"}, {2, "C"}, 
    {3, "D"}, {4, "E"}, {5, "F"}
    };

//define edge
template<class T>
struct edge
{
    int from, to;
    T cost;
    edge(int u, int v, T dist): from(u), to(v), cost(dist) {}
};

template<class T>
struct Graph {
    T cost[MAX_VERTEX][MAX_VERTEX];
    int vertex_num = MAX_VERTEX;
    int edge_num = MAX_VERTEX - 1;
    int ids[MAX_VERTEX];
};

//the sort function
template<class T>
bool cmp(edge<T> a, edge<T> b) {
    return a.cost < b.cost;
}

int main(int argc, char* argv[]) {
    //create undirected graph
    Graph<float> graph;
    for(size_t i = 0; i < MAX_VERTEX; i++) {
        graph.ids[i] = i;
        for(size_t j = 0; j < MAX_VERTEX; j++) {
            graph.cost[i][j] = INF_VAL;
        }
    }

    std::vector<edge<float>> edge_vec;
    graph.edge_num = 0;

    edge_vec.push_back(edge<float>(0, 1, 6));
    graph.cost[0][1] = 6;
    graph.cost[1][0] = 6;
    graph.edge_num += 1;
    
    edge_vec.push_back(edge<float>(0, 2, 1));
    graph.cost[0][2] = 1;
    graph.cost[2][0] = 1;
    graph.edge_num += 1;
    
    edge_vec.push_back(edge<float>(0, 3, 5));
    graph.cost[0][3] = 5;
    graph.cost[3][0] = 5;
    graph.edge_num += 1;

    edge_vec.push_back(edge<float>(1, 2, 5));
    graph.cost[1][2] = 5;
    graph.cost[2][1] = 5;
    graph.edge_num += 1;

    edge_vec.push_back(edge<float>(1, 4, 3));
    graph.cost[1][4] = 3;
    graph.cost[4][1] = 3;
    graph.edge_num += 1;

    edge_vec.push_back(edge<float>(2, 3, 5));
    graph.cost[2][3] = 5;
    graph.cost[3][2] = 5;
    graph.edge_num += 1;
    
    edge_vec.push_back(edge<float>(2, 4, 6));
    graph.cost[2][4] = 6;
    graph.cost[4][2] = 6;
    graph.edge_num += 1;
    
    edge_vec.push_back(edge<float>(2, 5, 4));
    graph.cost[2][5] = 4;
    graph.cost[5][2] = 4;
    graph.edge_num += 1;

    edge_vec.push_back(edge<float>(3, 5, 2));
    graph.cost[3][5] = 2;
    graph.cost[5][3] = 2;
    graph.edge_num += 1;

    edge_vec.push_back(edge<float>(4, 5, 6));
    graph.cost[4][5] = 6;
    graph.cost[5][4] = 6;
    graph.edge_num += 1;
    
    graph.vertex_num = 6;

    //init closed vector
    for (size_t i = 0; i < MAX_VERTEX; i++)
    {
        closed_node[i] = -1;
    }
    closed_node[0] = 1;
    
    float max_cost = 0.0;
    //sort edges by cost
    std::sort(std::begin(edge_vec), std::end(edge_vec), cmp<float>);
    max_cost = edge_vec.back().cost;
    std::cout << "show all edge in graph in order of cost" << std::endl;
    for (size_t i = 0; i < edge_vec.size(); i++)
    {
       std::cout << "from: " << id_to_string_map[edge_vec[i].from] 
                << " to: " << id_to_string_map[edge_vec[i].to] 
                << " cost: " << edge_vec[i].cost << std::endl;
    }

    std::vector<edge<float>> min_span_tree_edge;
    while (true) {
        if (min_span_tree_edge.size() == graph.vertex_num - 1) {
            break;
        }
        float min_cost = max_cost; 
        int u, v;
        for(size_t i = 0; i < graph.vertex_num; i++) {
            if (closed_node[i] != -1) {
                for(size_t j = 0; j < graph.vertex_num; j++) {
                    if (i == j) {
                        continue;
                    }

                    if (closed_node[j] == -1) {
                        if (graph.cost[i][j] < min_cost) {
                            u = i;
                            v = j;
                            min_cost = graph.cost[i][j];
                        }
                    }
                }
            }
        }
        
        closed_node[v] = 1; 
        min_span_tree_edge.emplace_back(edge<float>(u, v, min_cost));
    }

    //show every edge of min_span_tree
    std::cout << "process..." << std::endl;
    for (size_t i = 0; i < min_span_tree_edge.size(); i++)
    {
        std::cout << "from: " << id_to_string_map[min_span_tree_edge[i].from] 
                << " to: " << id_to_string_map[min_span_tree_edge[i].to] 
                << " cost: " << min_span_tree_edge[i].cost << std::endl;
    }

    return 0;
}

