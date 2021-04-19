#include "LEDA/graph/graph.h"
#include "LEDA/core/random_source.h"
#include <iostream>

using namespace leda;
using namespace std;

void create_square_graph(int test_N, graph& G) {

	node v[test_N];
	node inner_square_node[4];
    
	// Creating inner most square nodes
	for(int i=0; i<4; i++) {
		v[i]=G.new_node();
		inner_square_node[i] = v[i];		// connected to the inner one.
	}

	// Connect inner most square nodes to form a square.
	G.new_edge(v[0],v[1]); G.new_edge(v[1],v[0]); // upper edge
	G.new_edge(v[1],v[2]); G.new_edge(v[2],v[1]); // right edge
 	G.new_edge(v[2],v[3]); G.new_edge(v[3],v[2]); // lower edge
	G.new_edge(v[3],v[0]); G.new_edge(v[0],v[3]); // left  edge

	for( int i=4; i<test_N; i+=4) { // This is the creation of the second square.
		// Creating square nodes for every outer square
		v[i]=G.new_node();
		v[i+1]=G.new_node();
		v[i+2]=G.new_node();
		v[i+3]=G.new_node();

		//Connecting square nodes to form a square.
		G.new_edge(v[i],v[i+1]);   G.new_edge(v[i+1],v[i]);   // upper edge 
        G.new_edge(v[i+1],v[i+2]); G.new_edge(v[i+2],v[i+1]); // right edge
 		G.new_edge(v[i+2],v[i+3]); G.new_edge(v[i+3],v[i+2]); // lower edge
		G.new_edge(v[i+3],v[i]);   G.new_edge(v[i],v[i+3]);   // left  edge
        
		// Connect current square with the inner one
		for( int y=0; y<4; y++) {
			G.new_edge(v[i+y],inner_square_node[y]); 
            G.new_edge(inner_square_node[y],v[i+y]);
		}

		// Update the inner_square_node , so the current square becomes the 
		// inner square of the next square.
		for( int y=0; y<4; y++) {
			inner_square_node[y] = v[i+y];
		}	
	}
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

	create_square_graph(90000, G);
	bool flag = Is_Bipartite(G, A, B);
	cout<<flag;
	
	return 0;
}