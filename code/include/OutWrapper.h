#ifndef OUTWRAPPER_H
#define OUTWRAPPER_H

#include <bits/stdc++.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Graph.h"

class OutWrapper {
	
	private:

		int numPeople;
		int numCalls;
		int numMafiaGroups;
		bool satisfiability;
		int ** variableMatrix;

	public:

		/**
		 * An empty constructor.
		 */
		OutWrapper();


		/**
		 * Initializes an empty variable matrix with no edges.
		 */
		void initVariableMatrix();


		/**
		 * Read input from file and sets the variables.
		 * @param file is the file from which the graph input is to be read.
		 */
		void readInputGraph(istream& file);


		/**
		 * Read the output file of miniSAT and translate back to the original problem.
		 * @param file is the file from which the miniSAT solution is to be read.
		 */
		void readOutputSAT(istream& file);


		/**
		 * Generate the final output for the input problem
		 * @param file is the file in which the final subgraphs are to be written.
		 */
		void generateOutput(ostream& file);


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

};

#endif