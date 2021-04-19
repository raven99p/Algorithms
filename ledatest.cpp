#include "LEDA/graph/graph.h"
#include <iostream>
#include "LEDA/core/queue.h"
#include "LEDA/graph/basic_graph_alg.h"
#include "LEDA/system/timer.h"
#include "LEDA/graph/graph_gen.h"
#include "rep/Algorithms/header/circle_graph.h"
using namespace leda;

node_array<int> my_BFS(const graph &G, node s, node_array<int> &dist, node_array<edge> &pred)
{
    queue<node> Q;
    node_array<int> Colors(G, 0);
    node_array<bool> visited(G, false);

    int levelCounter = 0;

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

            dist[current_node] = levelCounter;
            forall_out_edges(e, current_node)
            {
                if (visited[G.target(e)] == false)
                {
                    Q.append(G.target(e));
                    visited[G.target(e)] = true;
                    pred[G.target(e)] = e;
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

    node_array<edge> pred(G, NULL);

    node_array<int> dist(G, 0);
    node_array<int> ex = my_BFS(G, s, dist, pred);
    node_array<bool> visited_ancestor(G, false);

    bool is_bipartite = true;
    forall_edges(e, G)
    {

        if ((ex[G.target(e)] && ex[G.source(e)]) && (ex[G.target(e)] == ex[G.source(e)]))
        {
            node temp = G.source(e);
            while(temp!=s)
            {
                if(pred[temp] && G.source(pred[temp])!=s)
                {
                    V1.append(temp);
                    temp = G.source(pred[temp]);
                }
                else
                {
                    break;
                }
            }
            temp = G.target(e);
            is_bipartite = false;
            while(temp != s)
            { 
                if(pred[temp])
                {
                    V1.append(temp);
                    temp = G.source(pred[temp]);
                    
                }
                else
                {
                    break;
                }
            }
            
            /*
            while ((temp != s))
            {

                visited_ancestor[temp] = true;
                if (pred[temp])
                {
                    temp = G.source(pred[temp]);
                }
                else
                {
                    std::cout << "pred[temp] does not exist";
                }
            }
            node source = G.source(e);
            node lca = s;
            temp = source;
            while ((temp != s))
            {
                if ((visited_ancestor[temp] = false) && pred[temp])
                {
                    temp = G.source(pred[temp]);
                }
                else
                {
                    lca = G.source(pred[temp]);
                    break;
                }
            }
            temp = G.target(e);
            //V1.append(G.target(e));
            V1.append(lca);

            while ((temp != lca))
            {

                if (pred[temp])
                {
                    V1.append(temp);
                    temp = G.source(pred[temp]);
                }
                else
                {
                    std::cout << "pred[temp] does not exist";
                    break;
                }
            }

            temp = source;
            while ((temp != lca))
            {
                if (pred[temp])
                {
                    V1.append(temp);
                    temp = G.source(pred[temp]);
                    
                }
                else
                {
                    std::cout << "pred[temp] does not exist";
                    break;
                }
            }*/
            break;
        }
    }
    if (is_bipartite)
    {
        node temp;
        forall_nodes(temp, G)
        {
            if (ex[temp] == 2)
            {
                V1.push(temp);
            }
            else
            {
                V2.push(temp);
            }
        }
    }

    return is_bipartite;
}
int main()
{
    graph G;
    edge e;
    circle_graph(51,G);
    forall_edges(e,G)
    {
        G.print_edge(e);
        std::cout << "\n";
    }
    /*
    graph G;
    node center = G.new_node();
    node one = G.new_node();
    node two = G.new_node();
    node three = G.new_node();
    G.new_edge(center, one);
    G.new_edge(one, center);
    G.new_edge(center, two);
    G.new_edge(two, center);
    G.new_edge(one, three);  
    G.new_edge(three, one); 
    G.new_edge(three,two);
    G.new_edge(two,three);

*/
    leda::list<node> A;
    leda::list<node> B;
    leda::list<node> V1;
    leda::list<node> V2;
    timer a;
    timer b;
    a.start();
    bool isBipartite = Is_Bipartite(G, A, B);
    a.stop();
    //std::cout << isBipartite << "\n";

    std::cout << "Time a:" << a.elapsed_time() << "\n";
    std::cout << "\nLEDA A\n";
    node iter;
    forall(iter, A)
    {
        G.print_node(iter);
    }
    std::cout << "\nLEDA B\n";
    forall(iter, B)
    {
        G.print_node(iter);
    }
    //std::cout << "created graph";
    b.start();
    isBipartite = my_bipartite_checker(G, V1, V2);
    b.stop();
    std::cout << "Time b:" << b.elapsed_time() << "\n";
    std::cout << isBipartite << "\n";
    std::cout << "\nMY A\n";
    forall(iter, V1)
    {
        G.print_node(iter);
    }
    std::cout << "\nMY B\n";
    forall(iter, V2)
    {
        G.print_node(iter);
    }
    std::cout << "\n";
    return 0;
}