#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

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

	string csr_file = cli.o_file_name();
	string x_file = "x_" + cli.o_file_name();

	int zero_row = 0;
	int previous = -1;
	int feature = cli.num_trials();
	bool sort_ = true;

	// make csr file
	ofstream out(csr_file);

	//VAL
	for (int i = 0; i < g.num_edges(); i++) {
		out<<"1";
		if (i != g.num_edges() - 1)
			out<<" ";
		else
			out<<endl;
	}

	//ROW_PTR
	for (int i = 0; i < g.num_nodes() + 1; i++) {
		out<<g.in_vertex_table_[i];
		if (i != g.num_nodes())
			out<<" ";
		else
			out<<endl;
		
		if (previous == g.in_vertex_table_[i])
			zero_row++;
		
		previous = g.in_vertex_table_[i];
	}

	//COL_IDX	
	if (sort_){
		int counter = 0;
		for (int i = 0; i < g.num_nodes(); i++){
			 vector<int> temp;
			 int beg = g.in_vertex_table_[i];
			 int end = g.in_vertex_table_[i+1];
			 for (int j = beg; j < end; j++)
				temp.push_back(g.in_edge_table_[j]);

			 sort(temp.begin(), temp.end());
			 //cout<<i<<": ";
			 for (int j = 0; j < temp.size(); j++){
				//cout<<temp[j]<<" ";
				out<<temp[j]; counter++;
				if (counter != g.num_edges() - 1)
					out<<" ";
				else
					out<<endl;
			 }//cout<<endl;
		}

	}
	else {
		for (int i = 0; i < g.num_edges(); i++) {
			out<<g.in_edge_table_[i];
			if (i != g.num_edges() - 1)
				out<<" ";
			else
				out<<endl;
		}
	}

	// make x file
	ofstream x_out(x_file);

	x_out<<feature<<endl<<feature<<endl;
	x_out<<g.num_nodes()<<endl;
	x_out<<zero_row<<endl;


	return 0;
}
