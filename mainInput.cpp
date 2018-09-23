#include <bits/stdc++.h>

#include "Wrapper.h"

using namespace std;

int main (int argc, char** argv) {

    string inFile = "";
    string outFile = "";
    if(argc == 3) {
    	inFile = argv[1];
    	outFile = argv[2];
    }
    else {
		cout << "Usage: ./cppfile InputFile\n";
		return 1;
	}

	ifstream inStream;
	inStream.open(inFile);

	Wrapper wrapInput = new Wrapper();
	wrapInput.readInput(inStream);

	inStream.close();

	ofstream outStream;
	outStream.open(outFile);

	wrapInput.makeClauses();
	wrapInput.generateInputSAT(outStream);

	outStream.close();
}