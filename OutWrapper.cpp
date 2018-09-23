#include "OutWrapper.h"

OutWrapper::OutWrapper () {

}

void OutWrapper::initVariableMatrix() {

	int ** tempVariableMatrix = new int*[numPeople];

	
	for (int i = 0; i < numPeople; i++) {
		tempVariableMatrix[i] = new int[numMafiaGroups];
	}

	for (int i = 0; i < numPeople; i++) {
		for (int j = 0; j < numMafiaGroups; j++) {
			tempVariableMatrix[i][j] = -1;
		}
	}

	variableMatrix = tempVariableMatrix;

}

void OutWrapper::readInputGraph (ifstream file) {

	file >> numPeople >> numCalls >> numMafiaGroups;
	
}

void OutWrapper::readOutputSAT (ifstream file) {

	string SAT;
	getline(file, SAT);

	if(SAT == "SAT")
		satisfiability = true;
	else
		satisfiability = false;

	if(satisfiability) {

		initVariableMatrix();
		int literalNum = 0;
		for(int i = 1; i <= numPeople * numMafiaGroups; i++) {
			
			file >> literalNum;

			if(literalNum < 0) 
				variableMatrix[personNum(-1 * literalNum)][mafiaNum(-1 * literalNum)] = 0;
			else
				variableMatrix[personNum(literalNum)][mafiaNum(literalNum)] = 1;

		}

	}

}

void OutWrapper::generateOutput (ofstream file) {

	if(satisfiability) {

		for(int i = 0; i < numMafiaGroups; i++) {

			int graphSize = 0;
			
			for(int j = 0; j < numPeople; j++) {
				if(variableMatrix[j][i] == 1)
					graphSize++;
			}

			file << "#" << i << " " << graphSize << endl;

			for(int j = 0; j < numPeople; j++) {
				if(variableMatrix[j][i] == 1)
					file << j+1 << " ";
			}

			file << endl;

		}

	}
	else {
		
		file << 0 << endl;
	
	}

}

int OutWrapper::personNum (int literal) {

	if(literal % numPeople != 0)
		return (literal % numPeople) - 1;
	else
		return numPeople - 1;

}

int OutWrapper::mafiaNum (int literal) {

	if(literal % numPeople != 0)
		return literal / numPeople;
	else {
		return (literal / numPeople) - 1;
	}

}