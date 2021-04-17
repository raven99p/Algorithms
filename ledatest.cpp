#include "LEDA/graph/graph.h"
#include <iostream>
#include "LEDA/core/queue.h"
#include "LEDA/graph/basic_graph_alg.h"
using namespace leda;

node_array<int> my_BFS(const graph &G, node s, node_array<int> &dist, node_array<edge> &pred)
{
    queue<node> Q;
    node_array<int> Colors(G, 0);
    node_array<bool> visited(G, false);
    //node_array<edge> pred(G, NULL);
    int levelCounter = 0;
    //node_array<int> dist(G, 0);
    Q.append(s);
    Q.append(NULL);

    int color = 2;
    edge e;
    visited[s] = true;
    pred[s] = NULL;
    node current_node;
    while (!Q.empty())
    {

        current_node = Q.pop();

        if (current_node == NULL)
        {
            if (color == 2)
            {
                color = 1;
            }
            else
            {
                color = 2;
            }
           // std::cout << "different level \n";
            levelCounter++;
            Q.append(NULL);
            if (Q.top() == NULL)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            Colors[current_node] = color;
            //visited[current_node] = true;
            dist[current_node] = levelCounter;
            forall_out_edges(e, current_node)
            {
                if (visited[G.target(e)] == false)
                {
                    Q.append(G.target(e));
                    visited[G.target(e)] = true;
                    pred[G.target(e)] = e;
                    //G.print_edge(e);
                   // std::cout << "\n";
                }
            }
        }
    }
    /*
    node v;
    forall_nodes(v, G)
    {
        std::cout << Colors[v];
    }
    std::cout << "\n";
    forall_nodes(v, G)
    {
        std::cout << visited[v];
    }
    std::cout << "\n";
    forall_nodes(v, G)
    {
        std::cout << dist[v];
    }
    std::cout << "\n";
    list<node> visitedList;
    forall_nodes(v, G)
    {
        if (visited[v] == true)
        {
            visitedList.append(v);
        }
    }*/
    return Colors;
}

bool my_bipartite_checker(const graph &G, list<node> &V1, list<node> &V2)
{
    edge e;
    //node_array<int> Colors(G, 0);
    //node_array<bool> visited(G, false);
    node_array<edge> pred(G, NULL);
    //int levelCounter = 0;
    node_array<int> dist(G, 0);
    node_array<int> ex = my_BFS(G, 	G.first_node(), dist, pred);
    //node_array<bool> reached(G, false);
    bool is_bipartite = true;
    forall_edges(e, G)
    {
        //std::cout << "new node \n";
       // std::cout << ex[G.source(e)] << "\n";
       // std::cout << ex[G.target(e)] << "\n";
       // std::cout << "--------\n";
        if (ex[G.target(e)] == ex[G.source(e)])
        {
            is_bipartite = false;
            std::cout << "found an edge with same color on its ends\n";
            //list<node> sth = DFS(G, center, reached);
            //std::cout << sth << "\n";
            node a = G.target(e);
            while (a!= G.first_node()){
                G.print_node(G.target(pred[a]));
                std::cout << "------>";
                G.print_node(G.source(pred[a]));
                //G.print_edge(pred[a]);
                a = G.source(pred[a]);
            }
            
        }
    }
    return is_bipartite;
}
int main()
{

    graph G;
    node center = G.new_node();
    queue<node> Q;
    int x;
    node one = G.new_node();
    node two = G.new_node();
    node three = G.new_node();
    //node four = G.new_node();
    //node five = G.new_node();
    G.new_edge(center, three);
    G.new_edge(center, two);
    G.new_edge(two, one);
    G.new_edge(center, one);
    G.new_edge(three, center);
    G.new_edge(two, center);
    G.new_edge(one, two);
    G.new_edge(one, center);
    list<node> A;
    list<node> B;
    bool a = Is_Bipartite(G, A, B);
    std::cout << a << "\n";
    for (int i = 0; i < A.size(); i++)
    {
        node a = A[i];
       std::cout << G.print_node(a);
    }
    
    // //std::cout << B << "\n";
    // forall_nodes(one, G)
    // {
    //     std::cout << one << "\n";
    // }
    bool isBipartite = my_bipartite_checker(G,A,B);
    std::cout << isBipartite;
    // G.new_edge(center, one);
    // G.new_edge(center, two);


    return 0;
}