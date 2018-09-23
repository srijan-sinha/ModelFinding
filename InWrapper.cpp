#include "InWrapper.h"

InWrapper::InWrapper () {

}

void InWrapper::readInputGraph (ifstream file) {
	
	file >> numPeople >> numCalls >> numMafiaGroups;
	file.ignore();

	int person1 = 0;
	int person2 = 0;

	callLogs = new Graph(numPeople, numCalls);

	for(int i = 0; i < numCalls; i++) {
		file >> person1 >> person2;
		callLogs->addEdge(person1, person2);
	}

}

void InWrapper::generateInputSAT (ofstream file) {
	
	file << "p cnf " << numPeople * numMafiaGroups << " " << clauses.size() << endl;
	for(int i = 0; i < clauses.size(); i++) {
		for(int j = 0; j < clauses.at(i).size(); i++) {
			file << clauses.at(i).at(j) << " ";
		}
		file << "0" << endl;
	}

}

void InWrapper::makeClauses () {

	nonEmptyMafiaGroups();
	allPersonAssigned();
	allPairCreate();

}

void InWrapper::nonEmptyMafiaGroups () {

	for(int i = 1; i <= numMafiaGroups; i++) {
		vector<int> clause;
		int varNum = 0;

		for(int j = 1; j <= numPeople; j++) {
			varNum = literalNumGenerator(j, i);
			clause.push_back(varNum);
		}

		clauses.push_back(clause);
	}

}

void InWrapper::allPersonAssigned () {

	for(int i = 1; i <= numPeople; i++) {
		vector<int> clause;
		int varNum = 0;

		for(int j = 1; j <= numMafiaGroups; j++) {
			varNum = literalNumGenerator(i, j);
			clause.push_back(varNum);
		}

		clauses.push_back(clause);
	}

}

void InWrapper::allPairCreate () {

	for(int i = 1; i <= numPeople; i++) {
		for(int j = i+1; j <= numPeople; j++) {

			if(callLogs->checkEdge(i, j))
				callMade(i, j);
			else
				callNotMade(i, j);

		}
	}

}

void InWrapper::callMade (int p1, int p2) {
	
	vector<int> clause;
	recursiveClause(p1, p2, 1, clause);

}

void InWrapper::recursiveClause (int p1, int p2, int mafiaGroupNum, vector<int> &clause) {
	
	int varNum1 = literalNumGenerator(p1, mafiaGroupNum);
	int varNum2 = literalNumGenerator(p2, mafiaGroupNum);

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

void InWrapper::callNotMade (int p1, int p2) {

	int varNum1 = 0;
	int varNum2 = 0;
	for(int i = 1; i <= numMafiaGroups; i++) {
		vector<int> clause;
		varNum1 = -1 * literalNumGenerator(p1, i);
		varNum2 = -1 * literalNumGenerator(p2, i);
		clause.push_back(varNum1);
		clause.push_back(varNum2);
		clauses.push_back(clause);
	}

}

int InWrapper::literalNumGenerator (int person, int mafiaGroupNum) {
	
	int literalNum = 0;
	literalNum += (mafiaGroupNum - 1) * numPeople;
	literalNum += person;
	return literalNum;

}
