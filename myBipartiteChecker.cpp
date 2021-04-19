#include "LEDA/graph/graph.h"
#include <iostream>
#include "LEDA/core/queue.h"
#include "LEDA/graph/basic_graph_alg.h"
#include "LEDA/system/timer.h"
#include "LEDA/graph/graph_gen.h"
#include "complex_graph.h"
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
    pred[s] = nil;
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
    std::cout<<"This is inside of BFS\n";
    node iter;
    forall_nodes(iter,G) {
        if(pred[iter]){
            G.print_node(G.source(pred[iter]));
            std::cout<<"\n";
        }
    }
    return Colors;
}

bool my_bipartite_checker(const graph &G, list<node> &V1, list<node> &V2)
{
    node s = G.first_node();
    edge e;

    node_array<edge> pred(G, NULL);
    node alpha;
    node_array<int> dist(G, 0);
    node_array<int> ex = my_BFS(G, s, dist, pred);
    node_array<bool> visited_ancestor(G, false);
    node_array<bool> visited(G, false);
    
    bool is_bipartite = true;
    forall_edges(e, G)
    {

        if ((ex[G.target(e)] && ex[G.source(e)]) && (ex[G.target(e)] == ex[G.source(e)]))
        {
            std::cout << "This is the root:";
            G.print_node(s);
            std::cout << "\n";

            node temp = G.source(e);
            std::cout << "source and target:";
            G.print_node(G.source(e));
            G.print_node(G.target(e));
            std::cout << "\n";                 

            while (pred[temp] != nil) // Επειδη δεν μπορει να φτασει το Root του αν ειναι root το κανω visited true
            {
                if (pred[temp]) {

                    visited[temp] = true;
                    V1.append(temp);
                    temp = G.source(pred[temp]); 
                    if(temp==s){
                        visited[s]= true;
                    }
                }
                else {
                    break;
                }
            }   
            temp = G.target(e);

            is_bipartite = false;
            node lca;

            while (temp != s)
            {
                if (pred[temp])
                {
                    if (visited[temp] == false)
                    {
                        V2.append(temp);
                        temp = G.source(pred[temp]);
                    }
                    else if ( ( (dist[G.target(e)] - dist[temp]) + (dist[G.source(e)] - dist[temp]) + 1) % 2 != 0 )
                    {
                        lca = temp;
                        break;
                    }
                    else
                    {
                        //V2.append(temp);
                        //temp = G.source(pred[temp]);
                        continue;
                    }
                }
                if (temp==s){ // If i become root then lca = root.
                    lca = s;
                }
            }

            V1.append(lca);

            std::cout<<"Lca is"; G.print_node(lca); std::cout<<"\n";    

            for (int i = 0; i < V1.size(); i++)
            {
                if ((node)V1.last() != lca)
                {
                    G.print_node((node)V1.pop_back());
                }
            }
            /*
            if(V1.last()==V2.last())
            {
                std::cout << "did";
                V2.pop_back();
            }*/
            V2.reverse_items();
            V2.conc(V1);
            V1 = V2;
            V2.clear();
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
    edge e;
    graph G;

    node center = G.new_node();
    node one = G.new_node();
    node two = G.new_node();

    G.new_edge(center, one);
    G.new_edge(one, center);
    G.new_edge(center, two);
    G.new_edge(two, center);
    // G.new_edge(one, two);  
    // G.new_edge(two, one); 



    leda::list<node> A;
    leda::list<node> B;
    leda::list<node> V1;
    leda::list<node> V2;


    // timer a;
    // timer b;
    // a.start();
    //bool isBipartite = Is_Bipartite(G, A, B);
    // a.stop();
    // //std::cout << isBipartite << "\n";

    // std::cout << "Time a:" << a.elapsed_time() << "\n";
    // std::cout << "\nLEDA A\n";
    // node iter;
    // forall(iter, A)
    // {
    //     G.print_node(iter);
    // }
    // std::cout << "\n"
    //           << A.size() << "\nLEDA B\n";
    // forall(iter, B)
    // {
    //     G.print_node(iter);
    // }
    // //std::cout << "created graph";
    // b.start();
    bool isBipartite = my_bipartite_checker(G, V1, V2);
    std::cout<<"The graph is: "<<isBipartite<<"\n";
    // b.stop();
    // std::cout << "Time b:" << b.elapsed_time() << "\n";
    // std::cout << isBipartite << "\n";
    // std::cout << "\nMY A\n";
    // forall(iter, V1)
    // {
    //     G.print_node(iter);
    // }
    // std::cout << "\n"
    //           << V1.size() << "\nMY B\n";
    // forall(iter, V2)
    // {
    //     G.print_node(iter);
    // }
    // std::cout << "\n";



    return 0;



}