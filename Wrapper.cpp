#include "Wrapper.h"

Wrapper::Wrapper () {

}

void Wrapper::initVariableMatrix() {

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

void Wrapper::readInput (ifstream file) {
	
	file >> numPeople >> numCalls >> numMafiaGroups;
	file.ignore();

	int person1 = 0;
	int person2 = 0;

	callLogs = new Graph(numPeople, numCalls)

	for(int i = 0; i < numCalls i++) {
		file >> person1 >> person2;
		callLogs->addEdge(person1, person2);
	}

}

void Wrapper::generateInputSAT (ofstream file) {
	
	file << "p cnf " << numPeople * numMafiaGroups << " " << clauses.size() << endl;
	for(int i = 0; i < clause.size(); i++) {
		for(int j = 0; j < clause.at(i).size(); i++) {
			file << clause.at(i).at(j) << " ";
		}
		file << "0" << endl;
	}

}

void Wrapper::readOutputSAT (ifstream file) {

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

void Wrapper::generateOutput (ofstream file) {

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

void Wrapper::makeClauses () {

	nonEmptyMafiaGroups();
	allPersonAssigned();
	allPairCreate();

}

void Wrapper::nonEmptyMafiaGroups () {

	for(int i = 1; i <= numMafiaGroups; i++) {
		vector<int> clause;
		int varNum = 0;

		for(int j = 1; j <= numPeople; j++) {
			varNum = varNumGenerator(j, i);
			clause.push_back(varNum);
		}

		clauses.push_back(clause);
	}

}

void Wrapper::allPersonAssigned () {

	for(int i = 1; i <= numPeople; i++) {
		vector<int> clause;
		int varNum = 0;

		for(int j = 1; j <= numMafiaGroups; j++) {
			varNum = varNumGenerator(i, j);
			clause.push_back(varNum);
		}

		clauses.push_back(clause);
	}

}

void Wrapper::allPairCreate () {

	for(int i = 1; i <= numPeople; i++) {
		for(int j = i+1; j <= numPeople; j++) {

			if(callLogs->checkEdge(i, j))
				callMade(i, j);
			else
				callNotMade(i, j);

		}
	}

}

void Wrapper::callMade (int p1, int p2) {
	
	vector<int> clause;
	recursiveClause(p1, p2, 1, clause);

}

void Wrapper::recursiveClause (int p1, int p2, int mafiaGroupNum, vector<int> &clause) {
	
	int varNum1 = varNumGenerator(p1, mafiaGroupNum);
	int varNum2 = varNumGenerator(p2, mafiaGroupNum);

	if(mafiaGroupNum == numMafiaGroups) {
		clause.push_back(varNum1);
		clauses.push_back(clause);
		clause.pop_back();
		clause.push_back(varNum2);
		clauses.push_back(clause);
		clause.pop_back();
	}
	else {
		clause.push_back(varNum1);
		recursiveClause(p1, p2, mafiaGroupNum + 1, clause);
		clause.pop_back();
		clause.push_back(varNum2);
		recursiveClause(p1, p2, mafiaGroupNum + 1, clause);
		clause.pop_back();
	}

}

void Wrapper::callNotMade (int p1, int p2) {

	int varNum1 = 0;
	int varNum2 = 0;
	for(int i = 1; i <= numMafiaGroups; i++) {
		vector<int> clause;
		varNum1 = -1 * varNumGenerator(p1, i);
		varNum2 = -1 * varNumGenerator(p2, i);
		clause.push_back(varNum1);
		clause.push_back(varNum2);
		clause.push_back(clause);
	}

}

int Wrapper::literalNumGenerator (int person, int mafiaGroupNum) {
	
	int literalNum = 0;
	literalNum += (mafiaGroupNum - 1) * numPeople;
	literalNum += person;
	return literalNum;

}

int Wrapper::personNum (int literal) {

	if(literal % numPeople != 0)
		return (literal % numPeople) - 1;
	else
		return numPeople - 1;

}

int Wrapper::mafiaNum (int literal) {

	if(literal % numPeople != 0)
		return literal / numPeople;
	else {
		return (literal / numPeople) - 1;
	}

}