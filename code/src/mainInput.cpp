#include <bits/stdc++.h>

#include "InWrapper.h"

using namespace std;

int main (int argc, char** argv) {

	string inFileGraph = "";
	string outFileSAT = "";
	string test = "";

	if(argc == 2) {
		test = argv[1];
	}
	else {
		cout << "Usage: ./cppfile InputFile\n";
		return 1;
	}

	inFileGraph = test + ".graph";
	outFileSAT = test + ".satinput";

	ifstream inStream;
	inStream.open(inFileGraph, ios_base::in);

	InWrapper* wrapInput = new InWrapper();
	wrapInput->readInputGraph(inStream);

	inStream.close();

	ofstream outStream;
	outStream.open(outFileSAT, ios_base::out);

	wrapInput->makeClauses();
	wrapInput->generateInputSAT(outStream);

	outStream.close();
	
}