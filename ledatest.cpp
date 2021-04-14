#include "LEDA/graph/graph.h"
#include <iostream>
#include "LEDA/core/queue.h"
using namespace leda;

int main()
{

    graph G;
    node center = G.new_node();
    queue<node> Q;
    int x;
    /*
    for (int i = 0; i < 10; i++)
    {
        node v = G.new_node();
        G.new_edge(center, v);
    }*/
    node one = G.new_node();
    node two = G.new_node();
    node three = G.new_node();
    node four = G.new_node();
    node five = G.new_node();
    G.new_edge(one, two);
    G.new_edge(one, three);
    G.new_edge(two, four);
    G.new_edge(three, five);
    G.new_edge(center, one);
    edge e;
    /*
    bool visited = new bool[10];
    for (int i = 0; i < 10; i++)
    {
        visited[i] = false;
    }*/
    list<int> Colors;

    std::cout << Colors;

    Q.append(center);
    Q.append(NULL);

    //Colors[0] = 1;
    int color = 2;
    int counter = 1;
    while (!Q.empty())
    {

        node current_node = Q.pop();

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
            Colors.push_back(color);
            list<edge> outgoing_edges = G.out_edges(current_node);
            forall_out_edges(e, current_node)
            {
                Q.append(G.target(e));
                G.print_edge(e);
                std::cout << "\n";
            }
        }

        std::cout << "Passed the for loop \n";
        counter++;
    }
    std::cout << Colors;
    std::cout << "This is your conciousness \nYou fucked up\n";
    return 0;
}