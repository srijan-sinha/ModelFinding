#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

class Graph {
	
	private:
		
		int ** nodeMatrix;
		int numNodes;
		int numEdges;

	public:

		/**
		 * An empty constructor.
		 */
		Graph();

		/**
		 * Generates an empty graph with given number of nodes.
		 * @param n is the number of nodes in the graph.
		 * @param m is the number of edges in the graph.
		 */
		Graph(int n, int m);


		/**
		 * Initializes an empty graph with no edges.
		 * @param n is the number of nodes in the graph.
		 */
		void initGraph(int n);


		/**
		 * Checks if an edge exists between two nodes.
		 * @param n1 is the first node.
		 * @param n2 is the second node.
		 * @return true if edge exists between the two nodes.
		 */
		bool checkEdge(int n1, int n2);


		/**
		 * Adds an edge between the two nodes.
		 * @param n1 is the first node.
		 * @param n2 is the second node.
		 */
		void addEdge(int n1, int n2);

}