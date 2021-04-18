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
    node s = G.first_node();
    edge e;
    //node_array<int> Colors(G, 0);
    //node_array<bool> visited(G, false);
    node_array<edge> pred(G, NULL);
    //int levelCounter = 0;
    node_array<int> dist(G, 0);
    node_array<int> ex = my_BFS(G, s, dist, pred);
    node_array<edge> pred_from_s_to_u = pred;
    node_array<int> dist_from_s_to_u = dist;
    node_array<bool> visited_ancestor(G, false);
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
            std::cout << "Starting\n";
            node temp = G.target(e);//target;
            while (temp != s)
            {
                visited_ancestor[temp] = true;
                temp = G.source(pred[temp]);
            }
            std::cout << "Done";
            std::cout << "Marked preds for u";
            node source = G.source(e);
            node lca;
            temp = source;
            while (temp != s)
            {
                if (visited_ancestor[temp] = false)
                {
                    temp = G.source(pred[temp]);
                }
                else
                {
                    lca = G.source(pred[temp]);
                    break;
                }
            }
            std::cout << "Marked for v";
            temp = G.target(e);
            G.print_node(G.target(e));
            std::cout << "------>";
            G.print_node(G.source(e));
            while (temp != lca)
            {
                G.print_node(G.target(pred[temp]));
                std::cout << "------>";
                G.print_node(G.source(pred[temp]));
                temp = G.source(pred[temp]);
            }
            temp = source;
            while (temp != lca)
            {
                G.print_node(G.target(pred[temp]));
                std::cout << "------>";
                G.print_node(G.source(pred[temp]));
                temp = G.source(pred[temp]);
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
    node four = G.new_node();
    node five = G.new_node();

    //node four = G.new_node();
    //node five = G.new_node();
    G.new_edge(center, one);
    G.new_edge(one, two);
    G.new_edge(one, three);
    //G.new_edge(two, three);
    G.new_edge(one, center);
    G.new_edge(two, one);
    G.new_edge(three, one);
    //G.new_edge(three, two);
    G.new_edge(two,four);
    G.new_edge(four,two);
    G.new_edge(three,five);
    G.new_edge(five,three);
    G.new_edge(four,five);
    G.new_edge(five,four);
    list<node> A;
    list<node> B;
    bool a = Is_Bipartite(G, A, B);
    std::cout << a << "\n";
    
    // for (int i = 0; i < A.size(); i++)
    // {
    //     node a = A[i];
    //     std::cout << G.print_node(a);
    // }

    // //std::cout << B << "\n";
    // forall_nodes(one, G)
    // {
    //     std::cout << one << "\n";
    // }
    bool isBipartite = my_bipartite_checker(G, A, B);
    std::cout << isBipartite;
    // G.new_edge(center, one);
    // G.new_edge(center, two);

    return 0;
}