#include <bits/stdc++.h>

#include "Wrapper.h"

using namespace std;

int main (int argc, char** argv) {

	string inFileGraph = "";
	string inFileSAT = "";
	string outFile = "";
	string test = "";

	if(argc == 2) {
		test = argv[1];
	}
	else {
		cout << "Usage: ./cppfile InputFile\n";
		return 1;
	}

	inFileGraph = test + ".graph";
	inFileSAT = test + ".satoutput";
	outFile = test + ".subgraphs";

	ifstream inStreamGraph;
	inStreamGraph.open(inFileGraph);

	ifstream inStreamSAT;
	inStreamSAT.open(inFileSAT);
	
	OutWrapper wrapOutput = new OutWrapper();
	wrapOutput.readInputGraph(inStreamGraph);
	wrapOutput.readOutputSAT(inStreamSAT);

	inStreamGraph.close();
	inStreamSAT.close();

	ofstream outStream;
	outStream.open(outFile);

	wrapOutput.generateOutput(outStream);

	outStream.close();
	
}