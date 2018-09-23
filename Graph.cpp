#include "Graph.h"

Graph::Graph () {

}

Graph::Graph (int n, int m) {
	numNodes = n;
	numEdges = m;

	initGraph(numNodes);
}

void Graph::initGraph (int n) {

	int ** tempEdgeMatrix = new int*[n];

	
	for (int i = 0; i < n; i++) {
		tempEdgeMatrix[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tempEdgeMatrix[i][j] = -1;
		}
	}

	edgeMatrix = tempEdgeMatrix;

}

bool checkEdge (int n1, int n2) {

	if(edgeMatrix[n1-1][n2-1] == 1)
		return true;
	return false;
}

void addEdge (int n1, int n2) {

	if(edgeMatrix[n1-1][n2-1] == -1)
		edgeMatrix[n1-1][n2-1] = 1;
	else
		cout << "Edge probably already exists from: " << n1 << " to " << n2;

	if(n1 != n2) {
		if(edgeMatrix[n2-1][n1-1] == -1)
			edgeMatrix[n2-1][n1-1] = 1;
		else
			cout << "Edge probably already exists from: " << n2 << " to " << n1;
	}
	
}