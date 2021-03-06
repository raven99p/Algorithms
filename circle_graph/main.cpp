#include "LEDA/graph/graph.h"
#include "LEDA/core/random_source.h"
#include <iostream>

using namespace leda;

void create_circle_graph(int test_N, graph& G) {

	node v[test_N];
	node temp_node;

	// Creating first node
	v[0] = G.new_node();
	temp_node = v[0];
	int i=0;
	for(i=1; i<test_N; i++) {

		v[i]= G.new_node();
		// Connecting the current note with the previous one.
		G.new_edge(v[i],temp_node); G.new_edge(temp_node, v[i]);

		//Making current node the old node.
		temp_node=v[i];
	}

	// Connecting last note with first node
	G.new_edge(v[i-1],v[0]); G.new_edge(v[0], v[i-1]);



	// edge e;
	// forall_edges(e,G) {
	// 	G.print_edge(e);
	// 	std::cout<<"\n";

	// }
}



int main(){
	graph G;
	
	list<node> A;
	list<node> B;

	create_circle_graph(10001, G);
	bool flag = Is_Bipartite(G, A, B);
	std::cout<<flag;
	


	return 0;
}
