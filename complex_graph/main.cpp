#include "LEDA/graph/graph.h"
#include "LEDA/core/random_source.h"
#include <iostream>
#include <time.h>

using namespace leda;
using namespace std;
int main(){
	graph G;
	srand (time(NULL));
	int k = 5;

	node L1[k];
	node L2[k];
	node L3[k];
	node L4[k];
    
    // Creating the nodes of each level.
	for(int i=0; i<k; i++) {
		L1[i] = G.new_node();
		L2[i] = G.new_node();
		L3[i] = G.new_node();
		L4[i] = G.new_node();
	}

	// Connecting each level
	for(int i=0; i<k; i++) {
		G.new_edge(L1[i],L2[i]); G.new_edge(L2[i],L1[i]); 
        G.new_edge(L2[i],L3[i]); G.new_edge(L3[i],L2[i]);
 		G.new_edge(L3[i],L4[i]); G.new_edge(L4[i],L3[i]); 
	}
	
	
	// Picking a random node to connect with the next level nodes.
	int random_node = rand() % k;
	
	for(int i=0; i<k; i++) {
		G.new_edge(L1[random_node],L2[i]); G.new_edge(L2[i],L1[random_node]); 
	}
	random_node = rand() % k;
	for(int i=0; i<k; i++) {
		G.new_edge(L2[random_node],L3[i]); G.new_edge(L3[i],L2[random_node]); 
	}
	random_node = rand() % k;
	for(int i=0; i<k; i++) {
		G.new_edge(L3[random_node],L4[i]); G.new_edge(L4[i],L3[random_node]); 
	}
		

	// Connecting L1-L3 and L2-L4 with one edge.
	G.new_edge(L1[rand() % k],L3[rand() % k]); G.new_edge(L2[rand() % k],L4[rand() % k]); 

	
	










	
	/*forall_edges(e,G) {
		G.print_edge(e);
		std::cout<<"\n";



	}*/


	return 0;
}