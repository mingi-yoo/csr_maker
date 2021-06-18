#include <iostream>
#include <fstream>
#include <string>

#include "command_line.h"
#include "builder.h"
#include "graph.h"

using namespace std;

typedef int32_t NodeID;
typedef CSRGraph<NodeID> Graph;
typedef BuilderBase<NodeID, NodeID> Builder;

int main(int argc, char* argv[]) {
	CLIterApp cli(argc, argv, ".", 1);
	if (!cli.ParseArgs())
		return -1;
	Builder b(cli);
	Graph g = b.MakeGraph();

	ofstream out(cli.o_file_name());

	for (int i = 0; i < g.num_edges(); i++) {
		out<<"1";
		if (i != g.num_edges() - 1)
			out<<" ";
		else
			out<<endl;
	}

	for (int i = 0; i < g.num_nodes() + 1; i++) {
		out<<g.in_vertex_table_[i];
		if (i != g.num_nodes())
			out<<" ";
		else
			out<<endl;
	}

	for (int i = 0; i < g.num_edges(); i++) {
		out<<g.in_edge_table_[i];
		if (i != g.num_edges() - 1)
			out<<" ";
		else
			out<<endl;
	}

	return 0;
}