# ModelFinding

C++ project which formulates the following problem as a SAT problem and solves it using miniSAT.

## Problem Statement
You are an investigative agency working on uncovering the hidden connections between the various drug agencies. You have got telephone records of various telephone numbers which are believed to be associated with the mafia. Some external source has suggested that there are K different drug agencies with several people part of multiple agencies. Your goal is to automatically uncover the various drug agencies from the telephone records. To solve this problem, you make a few assumptions:
* Each person has exactly one phone.
* All drug agencies are very close-knit: if two people are in the same agency they must have called each other.
* People don't directly call anyone outside their agency.
* No agency is a strict subsidiary of another agency.

##Input Format
The first line has three numbers: number of vertices in G, number of edges in G and K. Nodes are represented by positive integers starting from 1. Each subsequent line represents an edge between two nodes.

##Output Format
Each subgraph will be prefaced with a #i |G<sub>i</sub>| indicating that it is the i<sup>th</sup> subgraph of number of vertices |G<sub>i</sub>|. Post that, mention the vertices in one line.

## Installation

### Requirements
* Linux
* miniSAT
* Sublime-text

`$ sudo apt-get install minisat`

## Usage

```
./clean.sh testfile
./compile.sh
./run.sh testfile
./output.sh testfile

```
The above commands do the following actions:
* Delete any output files previously created by `testfile.graph` as input.
* Create fresh executables.
* Read input graph from `testfile.graph` placed in `code/tests/` folder and create output files `testfile.minisatinput` `testfile.minisatoutput` `testfile.subgraphs`.
* Open all the files related to `testfile.graph` in sublime-text. 

## License
[MIT](https://choosealicense.com/licenses/mit/)
