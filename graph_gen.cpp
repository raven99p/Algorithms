#include "LEDA/graph/graph.h"
#include "LEDA/core/random_source.h"
#include "LEDA/core/list.h"
#include "LEDA/graph/graph_gen.h"
#include <iostream>
using namespace leda;

int main(){
	graph G; 
	list<node> A;
	list<node> B;


	//complete_ugraph(G,5); // Complete undirected graph
	complete_bigraph(G, 3, 3,  A,  B);  // complete bipartile graph

	edge e;
	forall_edges(e, G) {
		//node source = G.source(e);
		//node target = G.target(e);

		G.print_edge(e);
		std::cout<<"\n";
	}

	

	return 0;
	
}