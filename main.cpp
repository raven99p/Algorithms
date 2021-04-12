#include "LEDA/graph/graph.h"
#include "LEDA/core/random_source.h"
#include <iostream>

using namespace leda;

int main(){
	graph G;
	
	node center= G.new_node();
	edge e;
	for (int i=0;i<20;i++){
		node v = G.new_node();
		G.new_edge(center,v);
	}
	edge_array<int> cost(G);
	
	random_source S;
	
	forall_edges(e,G){
		cost[e]=(S(10,200));
	}
	
	forall_edges(e,G){
		node source=G.source(e);
		node target=G.target(e);
		
		G.print_edge(e);
		std::cout<<"with cost "<<cost[e]<<"\n";
		
		//std::cout<<"\"";
		//G.print_node(source);		webgraphviz output
		//std::cout<<"\"->\"";
		//G.print_node(target);
		//std::cout<<"\"\n";
	}
	
	return 0;
}