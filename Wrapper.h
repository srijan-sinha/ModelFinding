#ifndef WRAPPER_H
#define WRAPPER_H

#include <bits/stdc++.h>
#include <string.h>
#include <iostream>
#include <fstream>
// #include <vector>

using namespace std;

#include "Graph.h"

class Wrapper {
	
	private:

		Graph * callLogs;
		int numPeople;
		int numEdges;
		int numSubgraphs;

	public:

		/**
		 * An empty constructor.
		 */
		Wrapper();


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
		
}