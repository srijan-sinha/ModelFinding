#include "InWrapper.h"

InWrapper::InWrapper () {

}

void InWrapper::readInputGraph (istream& file) {
	
	file >> numPeople >> numCalls >> numMafiaGroups;
	file.ignore();

	dummyLiteralNum = (numPeople * numMafiaGroups) + 1;

	int person1 = 0;
	int person2 = 0;

	callLogs = new Graph(numPeople, numCalls);

	for(int i = 0; i < numCalls; i++) {
		file >> person1 >> person2;
		callLogs->addEdge(person1, person2);
	}

}

void InWrapper::generateInputSAT (ostream& file) {
	
	file << "p cnf " << dummyLiteralNum - 1 << " " << clauses.size() << endl;
	for(int i = 0; i < clauses.size(); i++) {
		for(int j = 0; j < clauses.at(i).size(); j++) {
			file << clauses.at(i).at(j) << " ";
		}
		file << "0" << endl;
	}
	cout << "Output created!" << endl;
}

void InWrapper::makeClauses () {

	nonEmptyMafiaGroups();
		cout << "EmptyMafiaGroups done." << endl;
	allPersonAssigned();
		cout << "allPersonsAssigned done." << endl;
	allPairCreate();
		cout << "allPairCreate done." << endl;
	subGroupCheck();
		cout<< "subGroupCheck done." << endl;

}

void InWrapper::nonEmptyMafiaGroups () {

	for(int i = 1; i <= numMafiaGroups; i++) {
		vector<int> clause;
		int varNum = 0;

		for(int j = 1; j <= numPeople; j++) {
			varNum = literalNumGenerator(j, i);
			clause.push_back(varNum);
		}

		for(int i = 0; i < clause.size(); i++) {
			cout << clause.at(i) << " ";
		}
		cout << endl;

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

void InWrapper::subGroupCheck () {

	int varNum = 0;

	for(int i = 1; i <= numMafiaGroups; i++) {
		for(int j = i+1; j <= numMafiaGroups; j++) {

			vector< vector<int> > clausesDNF;

			for(int k = 1; k <= numPeople; k++) {

				vector<int> clause;
				varNum = literalNumGenerator(k, i);
					clause.push_back(varNum);
				varNum = literalNumGenerator(k, j);
					clause.push_back(-1 * varNum);
				clausesDNF.push_back(clause);

			}

			changeToCNF(clausesDNF);
			clausesDNF.clear();

			for(int k = 1; k <= numPeople; k++) {

				vector<int> clause;

				varNum = literalNumGenerator(k, j);
					clause.push_back(varNum);
				varNum = literalNumGenerator(k, i);
					clause.push_back(-1 * varNum);
				
				clausesDNF.push_back(clause);

			}

			changeToCNF(clausesDNF);

		}
	}

}

void InWrapper::callMade (int p1, int p2) {
	
	vector< vector<int> > clausesDNF;
	int varNum = 0;

	for(int i = 1; i <= numMafiaGroups; i++) {

		vector<int> clause;

		varNum = literalNumGenerator(p1, i);
			clause.push_back(varNum);
		varNum = literalNumGenerator(p2, i);
			clause.push_back(varNum);
		
		clausesDNF.push_back(clause);
	}

	changeToCNF(clausesDNF);

}

void InWrapper::changeToCNF (vector< vector<int> > clausesDNF) {

	int size = clausesDNF.size();
	int tempDummyLiteral = dummyLiteralNum;

	vector<int> clause;
	for(int i = 0; i < size; i++) {
		clause.push_back(tempDummyLiteral);
		tempDummyLiteral++;
	}
	clauses.push_back(clause);

	vector<int> clauseDNF;
	for(int i = 0; i < clausesDNF.size(); i++) {

		clauseDNF = clausesDNF.at(i);
		vector<int> subClause1, subClause2, subClause3;

		subClause1.push_back(clauseDNF.at(0)); subClause1.push_back(-1 * dummyLiteralNum);
		subClause2.push_back(-1 * clauseDNF.at(0)); subClause2.push_back(-1 * clauseDNF.at(1)); subClause2.push_back(dummyLiteralNum);
		subClause3.push_back(-1 * clauseDNF.at(0)); subClause3.push_back(clauseDNF.at(1)); subClause3.push_back(-1 * dummyLiteralNum);
	
		clauses.push_back(subClause1); clauses.push_back(subClause2); clauses.push_back(subClause3);
		dummyLiteralNum++;

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
