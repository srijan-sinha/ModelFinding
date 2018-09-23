#ifndef WRAPPER_H
#define WRAPPER_H

#include <bits/stdc++.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Graph.h"

class Wrapper {
	
	private:

		Graph * callLogs;
		int numPeople;
		int numCalls;
		int numMafiaGroups;
		vector < vector<int> > clauses;
		bool satisfiability;
		int ** variableMatrix;

	public:

		/**
		 * An empty constructor.
		 */
		Wrapper();


		/**
		 * Initializes an empty variable matrix with no edges.
		 */
		void initVariableMatrix();


		/**
		 * Read input from file and create the graph.
		 * @param file is the file from which the graph input is to be read.
		 */
		void readInput(ifstream file);


		/**
		 * Output the CNF formula for the input to miniSAT.
		 * @param file is the file in which the CNF formula is to be written.
		 */
		void generateInputSAT(ofstream file);


		/**
		 * Read the output file of miniSAT and translate back to the original problem.
		 * @param file is the file from which the miniSAT solution is to be read.
		 */
		void readOutputSAT(ifstream file);


		/**
		 * Generate the final output for the input problem
		 * @param file is the file in which the final subgraphs are to be written.
		 */
		void generateOutput(ofstream file);
		

		/**
		 * Makes all the required clauses.
		 */
		void makeClauses();

		/**
		 * Adds clauses to check if every Mafia group has atleast one person.
		 */
		void nonEmptyMafiaGroups();

		
		/**
		 * Adds clauses to check that every person is assigned atleast one Mafia group.
		 */
		void allPersonAssigned();


		/**
		 * Checks all pairs of person and creates clauses for them.
		 */
		void allPairCreate();


		/**
		 * Adds the clause when two people have called each other.
		 * @param p1 is the first person.
		 * @param p2 is the second person.
		 */
		void callMade(int p1, int p2);


		/**
		 * Recursively adds all variations of a clause to clause list.
		 * @param p1 is the first person.
		 * @param p2 is the second person.
		 * @param mafiaGroupNum is the depth of recursion.
		 * @param clause is the clause which is modified multiple times.
		 */
		void recursiveClause (int p1, int p2, int mafiaGroupNum, vector<int> &clause);


		/**
		 * Adds the clause when two people haven't called each other.
		 * @param p1 is the first person.
		 * @param p2 is the second person.
		 */
		void callNotMade(int p1, int p2);


		/**
		 * Generates a literal number for a variable assigned to a pair of person and mafia group.
		 * @param person is the person number.
		 * @param mafiaGroupNum is the mafia group number.
		 * @return literal number for the pair.
		 */
		int literalNumGenerator(int person, int mafiaGroupNum);


		/**
		 * Converts a literal number to the corresponding person number.
		 * @param literal is the literal number.
		 * @return the person number for the literal.
		 */
		int personNum (int literal);


		/**
		 * Converts a literal number to the corresponding mafia number.
		 * @param literal is the literal number.
		 * @return the mafia number for the literal.
		 */
		int mafiaNum (int literal);

}