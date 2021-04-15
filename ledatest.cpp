#include "LEDA/graph/graph.h"
#include <iostream>
#include "LEDA/core/queue.h"
using namespace leda;

list<node> my_BFS(const graph &G, node s, node_array<int> &dist, node_array<edge> &pred)
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
            std::cout << "different level \n";
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
                    G.print_edge(e);
                    std::cout << "\n";
                }
            }
        }
    }
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
    }
    return visitedList;
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
    //node five = G.new_node();
    G.new_edge(one, four);
    G.new_edge(one, three);
    G.new_edge(two, four);
    //G.new_edge(three, five);
    G.new_edge(center, one);
    G.new_edge(center, two);
    edge e;
    //node_array<int> Colors(G, 0);
    //node_array<bool> visited(G, false);
    node_array<edge> pred(G, NULL);
    //int levelCounter = 0;
    node_array<int> dist(G, 0);
    list<node> ex = my_BFS(G,center,dist,pred);
    std::cout << ex;
    return 0;
}