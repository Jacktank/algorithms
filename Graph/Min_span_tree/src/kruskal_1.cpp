#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

#define MAX_VERTEX 100

//define a parent vector for vertex
int head[MAX_VERTEX];

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

//the sort function
template<class T>
bool cmp(edge<T> a, edge<T> b) {
    return a.cost < b.cost;
}

//merge two different tree in a graph
void merge_tree(int head[], int u, int v) {
    int temp = head[v];
    int target_head = head[u];
    for (size_t i = 0; i < MAX_VERTEX; i++)
    {
       if (head[i] == temp) {
           head[i] = target_head;
       }
    }    
}

int main(int argc, char* argv[]) {
    //create undirected graph
    std::vector<edge<float>> edge_vec;
    edge_vec.push_back(edge<float>(0, 1, 6));
    edge_vec.push_back(edge<float>(0, 2, 1));
    edge_vec.push_back(edge<float>(0, 3, 5));

    edge_vec.push_back(edge<float>(1, 2, 5));
    edge_vec.push_back(edge<float>(1, 4, 3));

    edge_vec.push_back(edge<float>(2, 3, 5));
    edge_vec.push_back(edge<float>(2, 4, 6));
    edge_vec.push_back(edge<float>(2, 5, 4));

    edge_vec.push_back(edge<float>(3, 5, 2));

    edge_vec.push_back(edge<float>(4, 5, 6));

    //init head vector
    for (size_t i = 0; i < MAX_VERTEX; i++)
    {
        head[i] = i; //differeny from kruskal_2.cpp
    }

    //sort edges by cost
    std::sort(std::begin(edge_vec), std::end(edge_vec), cmp<float>);
    std::cout << "show all edge in graph in order of cost" << std::endl;
    for (size_t i = 0; i < edge_vec.size(); i++)
    {
       std::cout << "from: " << id_to_string_map[edge_vec[i].from] 
                << " to: " << id_to_string_map[edge_vec[i].to] 
                << " cost: " << edge_vec[i].cost << std::endl;
    }
    
    std::vector<edge<float>> min_span_tree_edge;
    for (size_t i = 0; i < edge_vec.size(); i++)
    {
        int u = edge_vec[i].from;
        int v = edge_vec[i].to;
        if (min_span_tree_edge.size() == edge_vec.size() - 1) {
            //we have made a min_span_tree successfully;
            break;
        }
        if (head[u] != head[v]) {
            //merge two different tree by modify parent vector flag
            merge_tree(head, u, v);
            min_span_tree_edge.emplace_back(edge_vec[i]);
        }
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


