#include "Graph.h"

Graph::Graph () {

}

Graph::Graph (int n, int m) {
	numNodes = n;
	numEdges = m;

	initGraph(numNodes);
}

void Graph::initGraph (int n) {

	int ** tempNodeMatrix = new int*[n];

	
	for (int i = 0; i < n; i++) {
		tempNodeMatrix[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tempNodeMatrix[i][j] = -1;
		}
	}

	nodeMatrix = tempNodeMatrix;

}

bool Graph::checkEdge (int n1, int n2) {

	if(nodeMatrix[n1-1][n2-1] == 1)
		return true;
	return false;
}

void Graph::addEdge (int n1, int n2) {

	if(nodeMatrix[n1-1][n2-1] == -1)
		nodeMatrix[n1-1][n2-1] = 1;
	else
		cout << "Edge probably already exists from: " << n1 << " to " << n2;

	if(n1 != n2) {
		if(nodeMatrix[n2-1][n1-1] == -1)
			nodeMatrix[n2-1][n1-1] = 1;
		else
			cout << "Edge probably already exists from: " << n2 << " to " << n1;
	}
	
}