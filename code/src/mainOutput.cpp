#include <bits/stdc++.h>

#include "OutWrapper.h"

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
	inStreamGraph.open(inFileGraph, ios_base::in);

	ifstream inStreamSAT;
	inStreamSAT.open(inFileSAT, ios_base::in);
	
	OutWrapper* wrapOutput = new OutWrapper();
	wrapOutput->readInputGraph(inStreamGraph);
	wrapOutput->readOutputSAT(inStreamSAT);

	inStreamGraph.close();
	inStreamSAT.close();

	ofstream outStream;
	outStream.open(outFile, ios_base::out);

	wrapOutput->generateOutput(outStream);

	outStream.close();
	
}